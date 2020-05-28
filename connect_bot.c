
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define BOTtoken "8326846:AAHejGz3y494y8Fhs324kjhd-niapEMmLizU5g"	//Token de "su" bot
#define LED_BUILTIN 2								//Led en la placa - pin2

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
 
String id, text;		//Variables para almacenar el ID y TEXTO generado por el Usuario
unsigned long tiempo;
 
void setup()
{
   pinMode(LED_BUILTIN, OUTPUT);			//pin2 salida
   WiFi.mode(WIFI_STA);					//WiFi como Estación de trabajo
   connect();						//Función para Conectar al WiFi
}
 
void loop()
{
   if (millis() - tiempo > 2000) 			//verifica las funciones cada 2 segundos
   {
      connect();  					//Función para verificar si hay conexión
      readTel();  					//Función para leer Telegram
      tiempo = millis(); 				//Reset al tiempo
   }
}
 
void connect()  //Función para Conectar al wifi y verificar la conexión
{
   if (WiFi.status() != WL_CONNECTED) 		//si no está conectado al WiFi, se conecta
   {
      WiFi.begin("Wifi", "contraseña"); //datos de la red
      delay(2000);
   }
}
 
void readTel()						//Función que hace la lectura de Telegram
{
   int newmsg = bot.getUpdates(bot.last_message_received + 1);
 
   for (int i = 0; i < newmsg; i++)			//para X mensajes nuevos, loop X veces
   {
      id = bot.messages[i].chat_id;			//almacena ID del Usuario en variable
      text = bot.messages[i].text;			//almacena texto del usuario en variable
      text.toUpperCase();				//STRING_TEXT a mayúscula
 
      if (text.indexOf("ON") > -1)			//si el texto recibido contiene "ON"
      {
         digitalWrite(LED_BUILTIN, 0);		//enciende LED
         bot.sendMessage(id, "LED ON", "");	//envia mensaje
      }

      else if (text.indexOf("OFF") > -1)		// si el texto recibido contiene "OFF"
      {
         digitalWrite(LED_BUILTIN, 1);		//apaga LED
         bot.sendMessage(id, "LED OFF", "");	//envia mensaje
}
 
      else if (text.indexOf("START") > -1)	//si el texto recibido contiene "START"
      {
         bot.sendSimpleMessage(id, id, "");	//envia mensaje con su ID
      }
 
      Else 				//si texto no es ninguno de los anteriores, mensaje de error
      {
         bot.sendSimpleMessage(id, "Comando Invalido", "");
      }
   }
}
