/* Original script from Pawel Dulak https://handyman.dulare.com/iot-impulse-counter-esp8266/
 * Add a ntp server and a CronAlarms libary.
 * */
#include <ESP8266WiFi.h>
#include <time.h>
#include "CronAlarms.h"
const char* ssid = "ssid"; 
const char* password = "password"; 
const char* getHost = "ip adres"; 
const int httpGetPort = 80;
long pulsetime = 0;
String getReceiverURL = "/received.php";
#define interruptPin 5 // GPIO 5 = D1 on a Wemos D1 mini v.3.0
int interruptCounter = 0;
//unsigned long last_sent_time = millis();


void ICACHE_RAM_ATTR handleInterrupt() {
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	if (interrupt_time - last_interrupt_time > 100){
		interruptCounter++;
		pulsetime = interrupt_time - last_interrupt_time;
		Serial.print("<<< Interrupt counter value:");
		Serial.print(interruptCounter);
		Serial.print("   Pulstijd:");
		Serial.println(pulsetime);
	}
	last_interrupt_time = interrupt_time;
}

void setup() {
	Serial.begin(115200);
	while (!Serial) ; // wait for Arduino Serial Monitor and set up the Cron
		Serial.println("Starting setup...");
		Cron.create("0 */5 * * * *", Repeats, false); // repeat every 5 minutes
		Serial.println("Ending setup...");
	Serial.println('\n');
	WiFi.hostname("ESPboard-counter");
	WiFi.begin(ssid, password);
	Serial.print("Connecting to ");
	Serial.print(ssid); Serial.println(" ...");
	int i = 0;
	while (WiFi.status() != WL_CONNECTED) {
		Cron.delay(1000);
		Serial.print(++i); Serial.print(' ');
	}
	Serial.println('\n');
	Serial.println("Connection established!");
	Serial.print("IP address:\t");
	Serial.println(WiFi.localIP());
	
	// Get time from a server
	configTime(2 * 3600, 0, "pool.ntp.org", "time.nist.gov"); // 2 = timezone
	Serial.println("\nWaiting for time");
	while (!time(nullptr)) {
		Serial.print(".");
		Cron.delay(1000);
	}
	Serial.println("");

	attachInterrupt(interruptPin, handleInterrupt, FALLING);
}

void postData() {
	WiFiClient clientGet;
	// We now create and add parameters:
	int vint = interruptCounter;
	String getReceiverURLtemp = getReceiverURL + "?int=" + vint + "&puls=" + pulsetime;
	Serial.println("-------------------------------");
	Serial.print(">>> Connecting to host: ");
	Serial.println(getHost);
	if (!clientGet.connect(getHost, httpGetPort)) {
		Serial.print("Connection failed: ");
		Serial.print(getHost);
	} else {
		clientGet.println("GET " + getReceiverURLtemp + " HTTP/1.1");
		clientGet.print("Host: ");
		clientGet.println(getHost);
		clientGet.println("User-Agent: ESP8266/1.0");
		// uncommend the next line if your server has een .htaccess with .htpasswd see readme file
//		clientGet.println("Authorization: Basic code=");
		clientGet.println("Connection: close\r\n\r\n");
		unsigned long timeoutP = millis();
		while (clientGet.available() == 0) {
			if (millis() - timeoutP > 10000) {
				Serial.print(">>> Client Timeout: ");
				Serial.println(getHost);
				clientGet.stop();
				return;
			}
		}
		while(clientGet.available()){
			String retLine = clientGet.readStringUntil('\r');
			Serial.print(">>> Host returned: ");
			Serial.println(retLine);
			// reset counter if successully connected
			if (retLine == "HTTP/1.1 200 OK") {
				Serial.println(">>> Communication successful");
				interruptCounter -= vint;
				Serial.print(">>> Changed interrupt counter to: ");
				Serial.println(interruptCounter);
			} else {
				Serial.println(">>> Communication failed!!!");
			}
			break;
		}
	} //end client connection if else
	Serial.print(">>> Closing host: ");
	Serial.println(getHost);
	Serial.println("-------------------------------");
	clientGet.stop();
}

void loop() {
	time_t now = time(nullptr);
//  Serial.println(ctime(&now));
	Cron.delay(1000);
}

void Repeats() {
	postData();
}
