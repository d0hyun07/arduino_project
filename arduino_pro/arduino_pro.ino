
#include <WiFi.h>

#include <WebSocketServer.h>

WiFiServer server(80);

WebSocketServer webSocketServer;

const char* ssid = "bssm_free";

const char* password = "bssm_free";

void setup()

{

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);

    Serial.println("Connecting to WiFi...");

  }
  pinMode(2, OUTPUT);

  Serial.println("Connected to the WiFi network");

  Serial.println(WiFi.localIP());

  server.begin();

  delay(1000);

}

void loop()

{

  WiFiClient client = server.available();

  if (client.connected() && webSocketServer.handshake(client)) {

    String data;
    int dt;
    while (client.connected()) {
      data = webSocketServer.getData();
      Serial.println(data);
      webSocketServer.sendData(data);
      dt=data.toInt();
      if (dt==1) {
        digitalWrite(2, HIGH);
        delay(3000);
      }
      else if(dt==0){
        digitalWrite(2, LOW);
        delay(3000);
      }
      delay(10);   // Delay needed for receiving data correctly
    }
  }
}
