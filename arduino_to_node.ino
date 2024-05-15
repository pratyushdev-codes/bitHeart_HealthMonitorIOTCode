#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define STEP_THRESHOLD 1.0
#define STEP_TIME_THRESHOLD 300

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

float prevAccelY = 0;
unsigned long prevStepTime = 0;
int stepCount = 0;

void setup(void) {
  Serial.begin(9600);
  
  if (!accel.begin()) {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1);
  }

  accel.setRange(ADXL345_RANGE_16_G);
}

void loop(void) {
  sensors_event_t event; 
  accel.getEvent(&event);

  float accelY = event.acceleration.y;
  
  unsigned long currentTime = millis();
  unsigned long timeDiff = currentTime - prevStepTime;

  if (timeDiff > STEP_TIME_THRESHOLD) {
    if (accelY > STEP_THRESHOLD && prevAccelY < STEP_THRESHOLD) {
      stepCount++;
      Serial.print("Step count: ");
      Serial.println(stepCount);
      prevStepTime = currentTime;
    }
  }

  prevAccelY = accelY;
}
