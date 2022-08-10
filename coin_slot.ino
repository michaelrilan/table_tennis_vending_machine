#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); 
const int coin = 2;
boolean insert = false;
int pulse = 0;
int clk = 0;
int impulscnt =0;
int credits = 0;
String staticMessage = "Oleng 4 Sale";
String scrollingMessage = "Tingi tingi Bili na kayo";
const int col = 20;
void scrollMessage(int row, String message, int delayTime, int col) {
  for (int i=0; i < col; i++) {
    message = " " + message;  
  } 
  message = message + " "; 
  for (int position = 0; position < message.length(); position++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(position, position + col));
    delay(delayTime);
  }
}
void setup() {
  // put your setup code here, to run once:

  
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), coinInterrupt, FALLING);
  delay(100);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
 // lcd.setCursor(0,0);
 // lcd.print(initMessage);
//  lcd.setCursor(0,1);
 // lcd.print("konichiwaa");
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
  if (credits>=10){
    credits = credits-10;
    }
  }


void loop() {
  // put your main code here, to run repeatedly:
   lcd.setCursor(0, 0);
  lcd.print(staticMessage);
  scrollMessage(1, scrollingMessage, 250, 20);
  clk = clk+1;
  Serial.print("clock = ");
  Serial.print(clk);
  Serial.print("Impulse:"); 
  Serial.println(impulscnt); 
  
  if (clk >= 30 and impulscnt == 1) {
    insert = false;
    Serial.println("coin detected 1 peso");
    impulscnt = 0;
    credits = credits + 1;
    delay(1000);
  }
  if (clk >= 30 and insert == true and impulscnt == 5) {
    insert = false;
    Serial.println("coin detected 5 pesos");
    impulscnt = 0;
    credits = credits + 5;
    delay(1000);
  }
  if (clk >= 30 and insert == true and impulscnt == 10) {
    insert = false;
    Serial.println("coin detected 10 pesos");
    credits = credits + 10;
    impulscnt = 0;
    delay(1000);
  }
}
