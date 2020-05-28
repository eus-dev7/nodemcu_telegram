#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define BOTtoken "4937477401:AAHejGzJ293y83hsJUu98-niapEMmLizU5g"
#define LED_BUILTIN 2

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
 
String id, text;
unsigned long tiempo;
 
void setup(){
   pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, 1);
   WiFi.mode(WIFI_STA);
   connect();
}
 
void loop(){
   if (millis() - tiempo > 1000){
      connect();
      readTel();
      tiempo = millis();
   }
}
 
void connect(){
   if (WiFi.status() != WL_CONNECTED){
      WiFi.begin("Wifi", "Contraseña");
      delay(2000);
   }
}
 
void readTel(){
   int newmsg = bot.getUpdates(bot.last_message_received + 1);
   for (int i = 0; i < newmsg; i++){
      id = bot.messages[i].chat_id;
      text = bot.messages[i].text;
      text.toUpperCase();
      if (text.indexOf("ON") > -1){
         digitalWrite(LED_BUILTIN, 0);
         bot.sendMessage(id, "LED ON", "");
      }
      else if (text.indexOf("OFF") > -1){
         digitalWrite(LED_BUILTIN, 1);
         bot.sendMessage(id, "LED OFF", "");
      }
      else if (text.indexOf("START") > -1){
         bot.sendSimpleMessage(id, id, "");
      }
      else      {
         bot.sendSimpleMessage(id, "Comando Invalido", "");
      }
   }
}
