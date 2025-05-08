#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include <Servo.h>

const char* ssid = "iSpan-R201";
const char* password = "66316588";
const char server[] = "192.168.51.145";
// const char* ssid = "Chang";
// const char* password = "27830709";
// const char server[] = "192.168.0.23";
const int port = 5090;

WiFiClient wifi;//<-----

// 定義 LED 與伺服馬達腳位
#define GREEN_LED 15  // 綠燈
#define RED_LED 14    // 紅燈

Servo myservo; // 伺服馬達（SG90）

void setup() {
  Serial.begin(115200);
  delay(1000);

  // 初始化伺服馬達
  myservo.attach(2); // SG90 接 GP2
  myservo.write(0);  // 初始位置

  // 設定 LED 為輸出
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  // 連線WiFi
  Serial.println("正在連線Wi-Fi...");
  WiFi.begin(ssid, password);
  delay(1000);

  while(WiFi.status() != WL_CONNECTED){
    delay(200);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi連線成功!");
  Serial.print("IP 位置: ");
  Serial.println(WiFi.localIP()); 

  while(!(wifi.connect(server, port))){
    Serial.println("Try reconnect to server!");
    delay(500);
  }
  if (wifi.connect(server, port)) {//<-----
     Serial.println("Server connected successful");
      // Make a HTTP request:
  }
}

void accessGranted() {
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  myservo.write(150);  // 轉到 150 度
  delay(3000);         // 保持 3 秒
  myservo.write(0);    // 關門
  digitalWrite(GREEN_LED, LOW);
}

void accessDenied() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  delay(2000);         // 紅燈亮 2 秒
  digitalWrite(RED_LED, LOW);
}

void openDoor() {
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  myservo.write(150);
}

void closeDoor() {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  myservo.write(0);    // 旋轉回 0 度關門
  // delay(1000);         // 讓紅燈顯示 1 秒
  digitalWrite(RED_LED, LOW);
}

void loop() {
  // 檢查來自伺服器的數據
  while(wifi.available()) {
    String msg = wifi.readStringUntil('\n');
    int value = msg.toInt();
    Serial.print("接收到值: ");
    Serial.println(value);

    // char buffer[10] = {0};
    // int bytesRead = wifi.readBytes(buffer, 10); // 這會盡量把 10 個 byte 都讀滿才停，或等超時，所以會把多筆資料黏在一起
    // buffer[bytesRead] = '\0';
    
    // int value = atoi(buffer); // convert string into int 
    // Serial.print("接收到值: ");
    // Serial.println(value);
    
    // 處理接收到的值
    if (value == 44) { // 網頁開門指令
      Serial.println("門已保持開啟");
      openDoor();
    } else if (value == 33) { // 網頁關門指令
      Serial.println("門已關閉");
      closeDoor();
    } else if (value == 22) {
      Serial.println("授權通過!");
      accessGranted();
    } else if (value == 11) {
      Serial.println("授權拒絕!");
      accessDenied();
    }
  }
  
  // 檢查連接狀態
  if (!wifi.connected()) {
    Serial.println("與伺服器連接斷開。重新連接...");
    wifi.stop();
    
    // 嘗試重新連接
    while(!(wifi.connect(server, port))){
      Serial.println("嘗試重新連接至伺服器!");
      delay(500);
    }
    
    if (wifi.connect(server, port)) {
      Serial.println("伺服器連接成功");
    }
  }
  
  delay(100);  // 短暫延遲以保持穩定
}
