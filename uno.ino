#define PHOTO A0 
#define RELAY 8
#define LED 13

// calibration
int calMin;
int calMax;

int lightCurrent;
int lightLevel;

// threshold for relay
int thrOn = 50;
int thrOff = 40;

void setup() {
  Serial.begin(9600);
  pinMode(PHOTO, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(RELAY, LOW);
  
  lightCurrent = analogRead(PHOTO);
  calMin = lightLevel - 25;
  calMax = lightLevel;
}

void loop() {

  // calibrate
  lightCurrent = analogRead(PHOTO);
  if (calMin > lightCurrent) {
    calMin = lightCurrent;
  }
  if (calMax < lightCurrent) {
    calMax = lightCurrent;
  }
 
  lightLevel = map(lightCurrent, calMin, calMax, 0, 100);
  Serial.println(lightLevel);

  if (lightLevel > thrOn) {
    digitalWrite(LED, HIGH);
    digitalWrite(RELAY, HIGH);
  } else if (lightLevel < thrOff) {
    digitalWrite(LED, LOW);
    digitalWrite(RELAY, LOW);
  }
  
  delay(500);
}
