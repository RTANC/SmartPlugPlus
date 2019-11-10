#include <ESP8266WiFi.h>
#include <MicroGear.h>
#define APPID "SmartPlugPlus"
#define KEY "QsOd4qJNBW9HgUw"
#define SECRET "W6QXVUoCDhtDq8EYS4BslVr0i"
#define ALIAS "plug01"

const char *ssid = "Unknow";
const char *password = "qwertyuiop"; 
WiFiClient client;
MicroGear microgear(client);

void onConnected(char *attribute,uint8_t *msg, unsigned int msglen){
  Serial.println("Connected to NETPIE...");
  microgear.setAlias(ALIAS);
}

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen){
  Serial.print("Incomming msg : ");
  msg[msglen] = '\0';
  String sMsg = (char *)msg;
  Serial.println(sMsg);
  
}

void setup() {
  // put your setup code here, to run once:
  microgear.on(MESSAGE,onMsghandler);
  microgear.on(CONNECTED,onConnected);
  WiFi.begin(ssid,password);
  Serial.begin(9600);
  Serial.println("Starting...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("\nWiFi is Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  microgear.init(KEY,SECRET,ALIAS);
  microgear.connect(APPID);
}

void loop() {
  microgear.loop();
  if(microgear.connected()){
    
  }else {
    microgear.connect(APPID);
  }
}
