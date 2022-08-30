# ESP8266-s0-counter-to-server
Aansluiting van je ESP.
![fig_02_arduino_pv_sd_logger_96dpi_01](https://user-images.githubusercontent.com/94928681/187402873-13d0c8a3-68b8-413d-b25e-5fcf21039dcb.png)

## Als je server is beveiligd met een .htacces en .htpasswd bestand.
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
