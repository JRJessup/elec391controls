// variable declaration
long count = 0;
long angle = 0;
long lastAngle = 0;
float speed = 0;
float angleMoved = 0;

unsigned long programTime, loopTime, refreshTime;
volatile int A,B;

byte state, prevState;




void setup()
{
  Serial.begin(115200); //faster bit rate for debugging

  pinMode(2, INPUT);
  pinMode(3, INPUT);
//  attachInterrupt(digitalPinToInterrupt(2), Achange, CHANGE); //alternative method of defining interrupts
//  attachInterrupt(digitalPinToInterrupt(3), Bchange, CHANGE);
  attachInterrupt(0, aTrigger, CHANGE); //interrupt pins declared here
  attachInterrupt(1, bTrigger, CHANGE);
  programTime = millis();
}

void loop()
{
  loopTime = millis();// this timer is used for the angle to be refreshed every'n' seconds (dictated by refreshTime)
  angle = count * 0.9;//. count to angle conversion
  refreshTime = loopTime - programTime;
  if (refreshTime > 1000)
  {
    angle = angle%360;
    count = count%400;

    angleMoved = (angle - lastAngle)*(3.14159/180); //calc magnitude of angular rotation in radians
    speed = angleMoved; //Dependent on Serial Refresh Time

    Serial.print("Count: ");
    Serial.print(count);
    Serial.print("  Angle: ");
    Serial.print(angle);
    Serial.print("  Speed: ");
    Serial.print(speed);
    Serial.print("\n");

    lastAngle = angle; //update lastAngle for accurate movement calculations
    programTime = loopTime; //Equalizes program and loopTime, in order to restart Refresh Timer
  }

}

void aTrigger()
{
  A = digitalRead(2);
  B = digitalRead(3);

  if ((A==HIGH) && (B==HIGH)) state = 1;
  if ((A==HIGH) && (B==LOW))  state = 2;
  if ((A==LOW)  && (B==LOW))  state = 3;
  if ((A==LOW)  && (B==HIGH)) state = 4;

  switch (state)
  {
    case 1:
    {
      if (prevState == 2) count++;
      if (prevState == 4) count--;
      break;
    }
    case 2:
    {
      if (prevState == 1) count--;
      if (prevState == 3) count++;
      break;
    }
    case 3:
    {
      if (prevState == 2) count --;
      if (prevState == 4) count ++;
      break;
    }
    default:
    {
      if (prevState == 1) count++;
      if (prevState == 3) count--;
    }
  }
  prevState = state;
}

void bTrigger()
{
  A = digitalRead(2);
  B = digitalRead(3);

  if ((A==HIGH) && (B==HIGH)) state = 1;
  if ((A==HIGH) && (B==LOW))  state = 2;
  if ((A==LOW)  && (B==LOW))  state = 3;
  if ((A==LOW)  && (B==HIGH)) state = 4;

  switch (state)
  {
    case 1:
    {
      if (prevState == 2) count++;
      if (prevState == 4) count--;
      break;
    }
    case 2:
    {
      if (prevState == 1) count--;
      if (prevState == 3) count++;
      break;
    }
    case 3:
    {
      if (prevState == 2) count --;
      if (prevState == 4) count ++;
      break;
    }
    default:
    {
      if (prevState == 1) count++;
      if (prevState == 3) count--;
    }
  }
  prevState = state;
}
