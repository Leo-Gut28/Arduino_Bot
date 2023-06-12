//Pins for QTI connections on board
#define lineSensor1 47 
#define lineSensor2 51
#define lineSensor3 52
#include <Servo.h>                           // Include servo library
#define Rx 17                                //XBee setup
#define Tx 16
Servo servoLeft;                             // Declare left servo signal
Servo servoRight;                            // Declare right servo signal
#include <Wire.h>                            //enables reading of sda, scl, etc.
#include "Adafruit_TCS34725.h"               //For RBG
#include <LiquidCrystal_I2C.h>               //For LCD
#define commonAnode true
byte gammatable[256];
LiquidCrystal_I2C lcd(0x27, 16, 2);          // desired pin, rows, cols
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
String colorWeRead = "";
int detectedMagField = 0;
int nums[6];


void setup() {
  Serial.begin(9600); //start the serial monitor so we can view the output
  Serial2.begin(9600);
  servoLeft.attach(11);                      // Attach left signal to pin 13
  servoRight.attach(12);                    // Attach left signal to pin 12
  servoLeft.writeMicroseconds(1500);         // 1.5 ms stay still sig, pin 13
  servoRight.writeMicroseconds(1500);  
  pinMode(2, INPUT); //Set the Hall Effect Sensor as an INPUT to pin 2
  Serial.begin(9600);
  lcd.init();
  delay(1000);
  lcd.backlight();
  lcd.clear();
  Serial.print("setup");
  lcd.print("setup done");
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
  }

  float red, green, blue;                   //color detection portion
  delay(60);
  tcs.getRGB(&red, &green, &blue);
  colorWeRead = returnColor(red, green, blue);    //save color read in variable to be printed to lcd later
}





void loop() {
 
  while(true){
    int qti1 = RCTime(lineSensor1);     //Setup qtis
    int qti2 = RCTime(lineSensor2);     
    Serial.println(qti1);         //210 is threshold for white/black detection
    Serial.println(qti2);         //120 is threshold for white/black detection
    Serial.println();

    if(qti2 > 35 && qti1 > 30){           //both black, stop and exit while loop
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
      Serial.println("Stopping");
      delay(1000);
      break;
    }else if(qti2 < 35 && qti1 < 30){      //neither black, turn right
      servoLeft.writeMicroseconds(1570);
      servoRight.writeMicroseconds(1500);
      //delay(300);
      Serial.println("Turning");
    }else{                                  //one black one not, move forward
      servoLeft.writeMicroseconds(1550);
      servoRight.writeMicroseconds(1450);
      Serial.println("Moving forward");
    }
    delay(10);
  }

  Serial.println("follow loop end");

  detectedMagField = readMagField();
 lcd.clear();
 lcd.println(colorWeRead + " , " + detectedMagField);   //print to lcd color and 1 or 0 for magnetic field presence
 if(detectedMagField == 1){
    char outgoing = 4;
    Serial2.print(4);
    nums[3] = 1;
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
    Serial2.print(4);
    delay(5);
  }
  lcd.clear();
  

while (true) {
    detectedMagField = readMagField();
    Serial.println(detectedMagField);
    delay(1000);
    // If we receive something from the XBee
    if (Serial2.available()) {
      // Read what we got so can clear the channel
      char incoming = Serial2.read();
      Serial.println(incoming);
      if (!(incoming == '⸮')) {
          int tempNum = String(incoming).toInt()-1;
          if(tempNum <=5) {
            nums[tempNum] = 1;
            Serial.print("incoming-");
            Serial.println(incoming);
            int count = 0;
            for (int x = 0; x<6; x++) {
              if (nums[x] == 1) {
                count++;
              }
            }
            lcd.setCursor(0,0);
            lcd.print(colorWeRead + " , " + detectedMagField + ", "+ count);
            lcd.setCursor(0,1);
            lcd.print(nextChallenge(count));
          }
      }
    }
    delay(10);
  }

  

}

String nextChallenge(int count){
  if(count == 0) {
    return "Nitrogen Cycle  ";
  } else if(count==1){
    return "Health Inform   ";
  } else if(count==2){
    return "Better Medicine ";
  } else if(count==3){
    return "Virtual Reality ";
  } else if(count==4){
    return "Sci Discovery   ";
  } else if(count==5){
    return "Reverse Brain   ";
  } else if(count==6){
    return "Advance Learning";
  }
  return "Shouldnt be here";
}


//Defines funtion 'RCTime' to read value from QTI sensor
long RCTime(int sensorIn) { //reads the decay time of the capacitor to determine light level
  
  long duration = 0;
  pinMode(sensorIn, OUTPUT); // Sets pin as OUTPUT
  digitalWrite(sensorIn, HIGH); // Pin HIGH
  delay(1); // Waits for 1 millisecond
  pinMode(sensorIn, INPUT); // Sets pin as INPUT
  digitalWrite(sensorIn, LOW); // Pin LOW

  while(digitalRead(sensorIn)) { // Waits for the pin to go LOW
    duration++;

  }
return duration; // Returns the duration of the pulse
}

String returnColor(float r, float g, float b){
  if(r > 165.0) return "Asia"; //red
  else if (g > 115.0) return "NA"; //green
  else if (b > 105.0) return "Europe"; //blue
  else if (r > 97.0 && b > 80.0) return "Australia"; //purple
  else if (g > 100.0 && r > 100.0) return "Africa"; //yellow
  else return "SA"; //gray

  }

int readMagField(){
                                                    //hall effect sensor, magnetic field detection portion
 if(digitalRead(2) == LOW){ //If magnet present
  //detectedMagField = 1;                           //save info in variable to be printed to lcd later
  nums[3] = 1;
  //Serial.println("1");//Write "detect" on the serial monitor
  //lcd.clear();
  //lcd.println("1");
  return 1;
 }
 else if(digitalRead(2) == HIGH){
  //detectedMagField = 0;                            //save info in variable to be printed to lcd later
  //Serial.println("0");
  //lcd.clear();
  //lcd.println("0");
  return 0;
 }
}

