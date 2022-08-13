#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); 
#include <Servo.h>
Servo myservo;
const int coin = 2;
const int buttonPin = 8; 
boolean insert = false;
int pulse = 0;
int clk = 0;
int impulscnt =0;
int credits = 0;
int buttonState = 0;
int pos = 0; 
int price;
void setup() {
  // put your setup code here, to run once:

  
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), coinInterrupt, FALLING);
  delay(100);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Price: 10 Pesos");
  lcd.setCursor(0,1);
  lcd.print("Credits: 0/10");
  pinMode(buttonPin, INPUT);
  myservo.attach(9);
  price = 10;
}

//interrupt
void coinInterrupt() {
  pulse++ ;
  impulscnt = impulscnt+1;
  insert = true;
  clk = 0;
}


// for the  credits of the user how much the user inserted in the coin acceptor
void creditsmeth(){
    String str_credits = String(credits);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Price: 10 Pesos");
    lcd.setCursor(0,1);
    lcd.print("Credits:" + str_credits +  "/10");
    }
void display_errorrr(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Insufficient");
    lcd.setCursor(0,1);
    lcd.print("Credit");
    }


void loop() {
  // put your main code here, to run repeatedly:
  clk = clk+1;
  Serial.print("clock = ");
  Serial.print(clk);
  Serial.print("Impulse:"); 
  Serial.println(impulscnt); 
  
  if (clk >= 30 and insert == true and impulscnt == 1) {
    insert = false;
    Serial.println("coin detected 1 peso");
    impulscnt = 0;
    credits = credits + 1;
    creditsmeth();

    delay(1000);
  }
  if (clk >= 30 and insert == true and impulscnt == 5) {
    insert = false;
    Serial.println("coin detected 5 pesos");
    impulscnt = 0;
    credits = credits + 5;
    creditsmeth();
    delay(1000);
  }
  if (clk >= 30 and insert == true and impulscnt == 10) {
    insert = false;
    Serial.println("coin detected 10 pesos");
    credits = credits + 10;
    impulscnt = 0;
    creditsmeth();
    
    delay(1000);
    
  }

  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH  && credits >= price) {
    credits = credits-price;
    creditsmeth();
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
  }                     // waits 15ms for the servo to reach the position
  }
   
  else if (buttonState == HIGH  && credits < price) {
    display_errorrr();
    delay(2000);
    creditsmeth();
    
  } 
}
