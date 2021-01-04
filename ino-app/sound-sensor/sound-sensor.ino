#include <Time.h>
#include <TimeLib.h>

// Board setup
int led=13;
int sensorPin=7;
int sensorAnalog=A0;

float environmentAvg= 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(sensorPin, INPUT);
}

int lastStat = 0;
void stats(int t) {
  Serial.println("environment avg");
  Serial.print(environmentAvg);
  Serial.println();
  lastStat = t;
}

const int SENSOR_THRESHOLD=1;
boolean isBarking(int sensorValue) {
  if (sensorValue >= (environmentAvg+SENSOR_THRESHOLD)){
    return true;
  }
  return false;
}

const int STATS_SEC = 10;
boolean shouldShowStats(int t) {
  if (t >= (lastStat + STATS_SEC)) {
    return true;
  }
  return false;
}

int getSensorValue(int sensor) {
  return analogRead(sensorAnalog);
}

void updateAverage(int sensorValue) {
  if (environmentAvg == 0) {
    environmentAvg = sensorValue;
    return;
  }
  environmentAvg = (environmentAvg + sensorValue)/2;
}

void nap(int n) {
  delay(n);
}

int lastBark;
void triggerBark(int t, int s) {
  Serial.println("guau guau");
  Serial.println(s);
  digitalWrite(led, HIGH);
  lastBark = t;
}

const int BARK_THRESHOLD = 5;
void clearBark(int t) {
  if (t >= (lastBark + BARK_THRESHOLD)) {
    digitalWrite(led, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue=getSensorValue(sensorAnalog);
  updateAverage(sensorValue);
  nap(500);  
  int tt = now();
  if (isBarking(sensorValue)) {
      triggerBark(tt, sensorValue);
  }
  if (shouldShowStats(tt)) {
    stats(tt);
  }
  clearBark(tt);
}
