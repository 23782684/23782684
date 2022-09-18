//RIGHT WHEEL
const int ledPin = 23;
const int freq = 16;
const int ledChannel = 0;
const int resolution = 16;

//LEFT WHEEL
const int freqLeftWheel = 1000;
const int echoPin = 18;
const int motorPin = 25;
const int motorChannel = 1;

//Difference between ultrasonic sensor.
float diff = 0;
float dac3=0;
float dac2=0;
float dac1=0;
float dac0=0;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define LED 2  // pin 2 will flash for debug only

#define bit3 34
#define bit2 35 
#define bit1 32
#define bit0 33

long duration=0;
float distanceCM=0;
float dutyCycle=0;
float voltage=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // uart setup
  pinMode(LED,OUTPUT); //set up pin 2 as output
  
  pinMode(echoPin, INPUT);
  pinMode(bit3, INPUT);
  pinMode(bit2, INPUT);
  pinMode(bit1, INPUT);
  pinMode(bit0, INPUT);

  ledcSetup(ledChannel, freq, resolution); //set pwn freq and resulution
  ledcAttachPin(ledPin, ledChannel); //select pwm outpit pin and channel
  ledcWrite(ledChannel, 11); // set dutycycle to 11/65536 (10u out of 62.5ms)

  ledcSetup(motorChannel,freqLeftWheel, resolution);
  ledcAttachPin(motorPin,motorChannel);

}

void loop() {
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  dac3 = digitalRead(bit3) *3.3;
  dac2 = digitalRead(bit2) *3.3;
  dac1 = digitalRead(bit1) *3.3;
  dac0 = digitalRead(bit0) *3.3;
  dutyCycle= duration * 0.000001*100/0.06;
  voltage = dutyCycle*3.3*9.5/100;
  // Calculate the distance
  distanceCM = duration * SOUND_SPEED/2;
  diff = voltage - ((3.3- ((dac3*8 + dac2*4 + dac1*2 + dac0*1)/15)));
  if (diff <= 0){
    diff =0.0;
  }
  if (diff>=3.3){
    diff=3.3;
  }
  ledcWrite(motorChannel, (diff/3.3) * 65536);
//    Serial.print("Distance (cm): ");
//  Serial.println(distanceCM);
//    Serial.println(dac3);
//      Serial.println(dac2);
//        Serial.println(dac1);
//          Serial.println(dac0);
//  Serial.println(voltage);
//   Serial.print("Diff = ");
//   Serial.println(diff);
}
