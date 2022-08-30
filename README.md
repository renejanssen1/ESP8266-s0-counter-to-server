# ESP8266-s0-counter-to-server
Aansluiting van je ESP.
![fig_02_arduino_pv_sd_logger_96dpi_01](https://user-images.githubusercontent.com/94928681/187402873-13d0c8a3-68b8-413d-b25e-5fcf21039dcb.png)

### Installatie van de ESP
- script werkt met de laatste versie van boardmanager ESP8266.
- voeg de bibliotheek Cronalarms van Martin Laclaustra toe.
- Het Cron alarm staat in het script op 5 minuten. Dit wil zeggen dat exact elke 5 minuten de data wordt verzonden naar de server. Tevens wordt dan de counter weer gereset. Cronalarm werkt hetzelfde als de Crontab in linux met als uitzondering dat het eerste * je zelfs seconden kunt invoeren.

### Pulsjes en Pulstime
Stel je hebt een kWh meter van 1000pulsjes/Kwh dat betekend dat elke puls 1 Watt is.<br>
Per 5 minuten krijg je een x aantal pulsjes door b.v.<br>
pulsetime = 1.96905	Aantal pulsjes= 146	Actuele Wattage = 1883<br>
Deze 146 pulsen zijn per uur * 12 = 1752 Watt (actueel)<br>
De pulsetijd (tijd tussen 2 pulsjes) is hier wat nauwkeurige in. nl 3600 / 1.96905 = 1828 Watt

### Als je server is beveiligd met een .htacces en .htpasswd bestand.
Ga naar de volgende website https://www.base64encode.org/
vul hier je naam en password in "username:password" let op de dubbele punt :
klik op encode en je krijgt een code die dus bestaat uit je naam en paswoord.
![image](https://user-images.githubusercontent.com/94928681/187403982-59c8a2d3-2855-401a-9871-f20d5e2c809f.png)

Scrol in je ino bestand naar de volgende regel
```
		clientGet.println("Authorization: Basic code=");
```
en wijzig dit naar het volgende
```
		clientGet.println("Authorization: Basic dXNlcm5hbWU6cGFzc3dvcmQ=");
```
