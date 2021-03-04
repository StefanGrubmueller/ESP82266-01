//#include <PubSubClient.h>
//#include <ESP8266WiFi.h>
//
//const char* SSID = "iphonevonstefan";  //Wlan SSID
//const char* PSK = "12345678";   //Wlan Password
//const char* broker = "172.20.10.10"; //IP Address des MQTT Brokers
//const char* topic = "battery/data"; //MQTT topic auf dem gepublisht werden soll 
////static char msg[1024];
//
//
//WiFiClient espClient;
//PubSubClient mqttClient(espClient);
//
//void setup_wifi(){  //Mit Wlan verbinden
//  delay(10);
//  Serial.println();
//  Serial.print("Configuration WIFI ...");
//  Serial.println(SSID);
//  Serial.println(": ");
//  Serial.println(PSK);
// 
//  WiFi.begin(SSID, PSK); //Wlan verbindung einrichten
//  while(WiFi.status()!=WL_CONNECTED) { //warten bis Wlanverbing eingerichtet ist
//    delay(500);
//    Serial.println(".");
//  }
//
//  Serial.println("");   //Mit Wlan verbunden
//  Serial.println("WiFi configured");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
//}
//
//void setup_mqtt(){  //Mit MQTT broker verbinden
//  mqttClient.setServer(broker,1883);
//  mqttClient.connect("mqttClient");
//  Serial.println("mqtt successful");
//}
//
//void reconnect() {
//  // Loop until we're reconnected
//  while (!mqttClient.connected()) {
//    // Attempt to connect
//    if (mqttClient.connect("mqttClient")) {
//    } else {
//      //delay(5000);
//    }
//  }
//}
//
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(115200);   //Serielle Verbindung einrichten (Baudrate=9600)
//  //msg[0]='\0';
//  while(!Serial) {}
//  delay(5000);
//  Serial.println("Setup Module");
//  setup_wifi();   //WLan einrichten
//  setup_mqtt();   //MQTT einrichten
//  Serial.println("warte auf daten");
//}
//
//void loop() {
//  String z;
//  // put your main code here, to run repeatedly:
//  char msg[1024];
//  msg[0]='\0';
//  int i = 0;
//  int x = Serial.available();
//  if(x!=0)
//  {     
//    Serial.println(x);
//  }
//  while(Serial.available()>0) //wenn Serielle Daten kommen
//  {
//    char newByte = Serial.read();  //ein Bit lesen
//    //Serial.println(msg);
//    if(newByte != '\n')
//    {
//      msg[i] = newByte;
//      i++;
//      delay(20);
//    }
//    else  //wenn letztes Bit gesendet worden ist
//    {
//      //Serial.println(msg[i]);
//      //msg[i] = '\0';
//      //reconnect();
//      //mqttClient.publish("battery/data", msg);
//      Serial.println(msg);
//      memset(msg, 0, sizeof(msg));
//      i = 0;
//      
//    }
//  }
//}
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char* SSID = "iphonevonstefan";  //Wlan SSID
const char* PSK = "12345678";   //Wlan Password
const char* broker = "172.20.10.10"; //IP Address des MQTT Brokers
const char* topic = "battery/data"; //MQTT topic auf dem gepublisht werden soll 
//static char msg[1024];


WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup_wifi(){  //Mit Wlan verbinden
  delay(10);
  Serial.println();
  Serial.print("Configuration WIFI ...");
  Serial.println(SSID);
  Serial.println(": ");
  Serial.println(PSK);
 
  WiFi.begin(SSID, PSK); //Wlan verbindung einrichten
  while(WiFi.status()!=WL_CONNECTED) { //warten bis Wlanverbing eingerichtet ist
    delay(500);
    Serial.println(".");
  }

  Serial.println("");   //Mit Wlan verbunden
  Serial.println("WiFi configured");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup_mqtt(){  //Mit MQTT broker verbinden
  mqttClient.setServer(broker,1883);
  mqttClient.connect("mqttClient");
  Serial.println("mqtt successful");
}

void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    // Attempt to connect
    if (mqttClient.connect("mqttClient")) {
    } else {
      delay(5000);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);   //Serielle Verbindung einrichten (Baudrate=9600)
  //msg[0]='\0';
  while(!Serial) {}
  delay(5000);
  Serial.println("Setup Module");
  setup_wifi();   //WLan einrichten
  setup_mqtt();   //MQTT einrichten
  Serial.println("warte auf daten");
}

void loop() {
  String z;
  while(Serial.available()>0) //wenn Serielle Daten kommen
  {
      z.concat(Serial.readString());  //ein Bit lesen
  }
  if(z.length()>0)
  {
    Serial.println(z);
    char msg[1024];
    z.toCharArray(msg,z.length());
    reconnect();
    mqttClient.publish("battery/data", msg);
  }
}
