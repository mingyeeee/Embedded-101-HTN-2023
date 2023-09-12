#define SENSOR1_TRIG_PIN 8
#define SENSOR1_ECHO_PIN 9
#define SENSOR2_TRIG_PIN 10
#define SENSOR2_ECHO_PIN 11

#define DISTANCE_THRESHOLD 30

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(SENSOR1_TRIG_PIN, OUTPUT); // trig pin sensor 1
  pinMode(SENSOR1_ECHO_PIN, INPUT); // echo pin sensor 1

  pinMode(SENSOR2_TRIG_PIN, OUTPUT); // trig pin sensor 2
  pinMode(SENSOR2_ECHO_PIN, INPUT); // echo pin sensor 2

}

int GetDistanceFromSensor1()
{
  digitalWrite(SENSOR1_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SENSOR1_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENSOR1_TRIG_PIN, LOW);

  long duration = pulseIn(SENSOR1_ECHO_PIN, HIGH);

  int distanceCM1 = duration * 0.034/2;

  return distanceCM1;
}

int GetDistanceFromSensor2()
{
  digitalWrite(SENSOR2_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SENSOR2_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENSOR2_TRIG_PIN, LOW);

  long duration = pulseIn(SENSOR2_ECHO_PIN, HIGH);

  int distanceCM2 = duration * 0.034/2;

  return distanceCM2;
}

void loop() {
  // put your main code here, to run repeatedly:

  int sensor1Distance = GetDistanceFromSensor1();
  int sensor2Distance = GetDistanceFromSensor2();
  /*Serial.print("sensor 1 data: ");
  Serial.println(sensor1Distance);

  Serial.print("sensor 2 data: ");
  Serial.println(sensor2Distance);
*/

  if(sensor1Distance < DISTANCE_THRESHOLD) // check if the left sensor has detect a hand
  {
    delay(1000);

    while(!(sensor2Distance < DISTANCE_THRESHOLD))
    {
      sensor2Distance = GetDistanceFromSensor2();
      delay(20);
    }

    Serial.println("GESTURE DETECTED!!!!!!!");
    delay(2000);
  }

}
