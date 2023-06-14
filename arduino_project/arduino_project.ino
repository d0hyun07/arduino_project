#include <WiFi.h>

#include <WebSocketServer.h>

WiFiServer server(80);

WebSocketServer webSocketServer;

const char* ssid = "bssm_free";
const char* password = "bssm_free";  //와이파이에 연결하기 위해 와이파이명과 비밀번호 저장

void setup()

{

  Serial.begin(115200); //esp32는 상위 모듈이라 9600이 아닌 115200으로 통신

  WiFi.begin(ssid, password); //와이파이에 연결

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);

    Serial.println("Connecting to WiFi...");

  }
  pinMode(2, OUTPUT);

  Serial.println("Connected to the WiFi network");

  Serial.println(WiFi.localIP()); //통신에 쓰일 IP출력

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
      data = webSocketServer.getData(); //서버에서 소켓으로 보낸 데이터를 변수에 저장
      Serial.println(data);
      webSocketServer.sendData(data);
      dt=data.toInt(); //문자로 받아온 데이터를 정수로 변환
      if (dt==1) {
        digitalWrite(2, HIGH); //릴레이 모듈 ON
        delay(3000);
      }
      else if(dt==0){
        digitalWrite(2, LOW); //릴레이 모듈 OFF
        delay(3000);
      }
      delay(10); 
    }
  }
}
