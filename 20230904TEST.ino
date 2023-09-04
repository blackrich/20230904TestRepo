// TMP 센서 핀 설정
const int tempPin = A0;
// 조도센서 핀 설정
const int lightSensorPin = A1;
// 초음파센서 핀 설정
const int potPin = A2;

// LED 핀 설정
const int ledPin = 13;
// 초음파센서 핀 설정
const int echoPin = 10;  
const int trigPin = 9; 
// 초음파 거리
const int maxDistance = 100; 
void setup() {
  // 시리얼 통신을 초기화 (필요한 경우)
  Serial.begin(9600);
  
  // LED 핀을 출력으로 설정
  pinMode(ledPin, OUTPUT);

  pinMode(potPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600); // 시리얼 통신 속도 설정
}

void loop() {

  if (Serial.available()) {
    char command = Serial.read(); // 시리얼로부터 명령을 읽음
    switch(command){
      case '1': 
        digitalWrite(ledPin, HIGH); // LED 1 켜기
        Serial.println("LED1 ON");
        break;
      case '0': 
        digitalWrite(ledPin, LOW); // LED 1 끄기
        Serial.println("LED1 OFF");
        break;
        
    }
  }


  usound();
  temp();
  light();

  // 잠시 대기
  delay(500); // 적절한 간격으로 조도값을 읽음
}



void usound(){

  int potValue = analogRead(potPin);
  long duration, distance;
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;
  Serial.println("Distance: ");
  if (distance > maxDistance) {
    Serial.println("Error: Out of range");
    distance = maxDistance;
  }
}

void temp(){
  // TMP 센서로부터 온도 값을 읽음
  int rawValue = analogRead(tempPin);

  // TMP 센서의 출력을 온도로 변환
  float temperatureCelsius = (rawValue / 1023.0) * 500.0;

  // 온도 값을 시리얼 모니터에 출력
  Serial.print("Celsius: ");
  Serial.println(temperatureCelsius);
}

void light(){
  // 조도센서로부터 값을 읽음 (0 ~ 1023 범위의 값)
  int lightValue = analogRead(lightSensorPin);
  
  // 조도값을 0~1 범위로 정규화
  float normalizedValue = float(lightValue) / 1023.0;

  // 조도 값을 시리얼 모니터에 출력 (디버깅용, 필요한 경우 활성화)
   Serial.print("Illuminance: ");
   Serial.println(normalizedValue);
}
