//Arduino Code - Rotary Encoder w push button

#include <BfButton.h>
#include <SoftwareSerial.h>

SoftwareSerial LCD(10,11);
int btnPin=3; //GPIO #3-Push button on encoder
int DT=4; //GPIO #4-DT on encoder (Output B)
int CLK=5; //GPIO #5-CLK on encoder (Output A)
BfButton btn(BfButton::STANDALONE_DIGITAL, btnPin, true, LOW);

int counter = 0;
int angle = 0; 
int aState;
int aLastState;  

void clearScreen()
{
  //clears the screen, you will use this a lot!
  LCD.write(0xFE);
  LCD.write(0x01); 
}

void selectLineOne()
{ 
  //puts the cursor at line 0 char 0.
  LCD.write(0xFE); //command flag
  LCD.write(128); //position
}

void selectLineTwo()
{ 
  //puts the cursor at line 0 char 0.
  LCD.write(0xFE); //command flag
  LCD.write(192); //position
}

//Button press hanlding function
void pressHandler (BfButton *btn, BfButton::press_pattern_t pattern) {
  switch (pattern) {
    case BfButton::SINGLE_PRESS:
      Serial.println("Single push");
      break;
      
    case BfButton::DOUBLE_PRESS:
      Serial.println("Double push");
      counter = 0;
      clearScreen();
      selectLineTwo();
      LCD.print ("RESET BABY");
      break;
      
    case BfButton::LONG_PRESS:
      Serial.println("Long push");
      break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  LCD.begin(9600);
  delay(500);
  Serial.println(angle);
  pinMode(CLK,INPUT_PULLUP);
  pinMode(DT,INPUT_PULLUP);
  
  aLastState = digitalRead(CLK);

  //Button settings
  btn.onPress(pressHandler)
  .onDoublePress(pressHandler) // default timeout
  .onPressFor(pressHandler, 1000); // custom timeout for 1 second
}

void loop() {
  // put your main code here, to run repeatedly:

  //Wait for button press to execute commands
  btn.read();
  
  aState = digitalRead(CLK);

  //Encoder rotation tracking

  
  if (aState != aLastState){  
    clearScreen();
     if (digitalRead(DT) != aState) { 
       counter ++;
       angle ++;
     }
     else {
       counter--;
       angle --;
     }

     if (counter >=100 ) {
       counter =100;
     }

     if (counter <=-100 ) {
       counter =-100;
     }

    // if (aLastCount > counter) {
    //   digitalWrite(LaserPin, HIGH);
    // } else {
    //   digitalWrite(LaserPin, LOW);
    // }     
    if ((counter <= 1) && (counter >= -1)) {
      selectLineOne();
      LCD.print ("Home");
      selectLineTwo();
      LCD.print(abs(counter));
    } else if ((counter >= 2) && (counter <= 20)) {
      selectLineOne();
      LCD.print("Low LEFT");
      selectLineTwo();
      LCD.print(counter);
    } else if ((counter >= 21) && (counter <= 60)) {
      selectLineOne();
      LCD.print("Medium LEFT");    
      selectLineTwo();
      LCD.print(counter);
    } else if ((counter >= 61) && (counter <= 100)) {
      selectLineOne();
      LCD.print("High LEFT");  
      selectLineTwo();
      LCD.print(counter);
    } else if ((counter <= -2) && (counter >= -20)) {
      selectLineOne();
      LCD.print("Low RIGHT");
      selectLineTwo();
      LCD.print(abs(counter));
    } else if ((counter <= -21) && (counter >= -60)) {
      selectLineOne();
      LCD.print("Medium RIGHT");
      selectLineTwo();
      LCD.print(abs(counter));
    } else if ((counter <= -61) && (counter >= -100)) {
      selectLineOne();
      LCD.print("High RIGHT");
      selectLineTwo();
      LCD.print(abs(counter));
    } 

    Serial.println(counter); 
  }   
  aLastState = aState;
  //Serial.println(aState);
  //Serial.println(aLastCount);
}