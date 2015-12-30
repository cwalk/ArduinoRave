/*
  rave.ino
  Clayton Walker
  2015
*/

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

//RGB LED pins
int ledDigitalOne[] = {9, 10, 11}; //the three digital pins of the digital LED 
                                   //9 = redPin, 10 = greenPin, 11 = bluePin

const boolean ON = LOW;     //Define on as LOW (this is because we use a common 
                            //Anode RGB LED (common pin is connected to +5 volts)
const boolean OFF = HIGH;   //Define off as HIGH

//Predefined Colors
const boolean REDD[] = {ON, OFF, OFF};    
const boolean GREENN[] = {OFF, ON, OFF}; 
const boolean BLUEE[] = {OFF, OFF, ON}; 
const boolean YELLOW[] = {ON, ON, OFF}; 
//const boolean CYAN[] = {OFF, ON, ON}; 
//const boolean MAGENTA[] = {ON, OFF, ON}; 
//const boolean WHITEE[] = {ON, ON, ON}; 
//const boolean BLACK[] = {OFF, OFF, OFF}; 

//An Array that stores the predefined colors (allows us to later randomly display a color)
//const boolean* COLORS[] = {REDD, GREENN, BLUEE, YELLOW, CYAN, MAGENTA, WHITEE, BLACK};
const boolean* COLORS[] = {REDD, GREENN, BLUEE, YELLOW};

void setup() 
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("Rave Party!!!!!!");
    lcd.setCursor(0,1);
    lcd.print("We love 2 Rave!!");
    for(int i = 0; i < 3; i++){
      pinMode(ledDigitalOne[i], OUTPUT);   //Set the three LED pins as outputs
    }
}

void breath(unsigned char color)
{

    for(int i=0; i<255; i++)
    {
        lcd.setPWM(color, i);
        //delay(5);
    }

    delay(50);
    for(int i=254; i>=0; i--)
    {
        lcd.setPWM(color, i);
        //delay(5);
    }

    //delay(500);
}

int count=0;

void raveRed(){
    setColor(ledDigitalOne, REDD);
    //randomColor();
    breath(REG_RED);
}

void raveGreen(){
  setColor(ledDigitalOne, GREENN);
    //randomColor();
    breath(REG_GREEN);
}

void raveBlue(){
  setColor(ledDigitalOne, YELLOW);
    //randomColor();
    breath(REG_BLUE);
    //randomColor();
}

void loop() 
{   
    if (count==0){
      delay(500);
    }
    // scroll 13 positions (string length) to the left
    // to move it offscreen left:
    //13
    for (int positionCounter = 0; positionCounter < 16/3; positionCounter++) {
        // scroll one position left:
        lcd.scrollDisplayLeft();
        raveRed();
        lcd.scrollDisplayLeft();
        raveGreen();
        lcd.scrollDisplayLeft();
        raveBlue();
        // wait a bit:
        //delay(150);
    }

    // scroll 29 positions (string length + display length) to the right
    // to move it offscreen right:
    //29
    for (int positionCounter = 0; positionCounter < 32/3; positionCounter++) {
        // scroll one position right:
        lcd.scrollDisplayRight();
        raveRed();
        lcd.scrollDisplayRight();
        raveGreen();
        lcd.scrollDisplayRight();
        raveBlue();
        // wait a bit:
        //delay(150);
    }

    // scroll 16 positions (display length + string length) to the left
    // to move it back to center:
    //16
    for (int positionCounter = 0; positionCounter < 16/3; positionCounter++) {
        // scroll one position left:
        lcd.scrollDisplayLeft();
        raveRed();
        lcd.scrollDisplayLeft();
        raveGreen();
        lcd.scrollDisplayLeft();
        raveBlue();
        // wait a bit:
        //delay(150);
    }

    // delay at the end of the full loop:
    //delay(1000);
    count++;
}

void turnOff(){
  setColor(ledDigitalOne, BLUEE);
}

void randomColor(){
  int rand = random(0, sizeof(COLORS) / 2);  //get a random number within the range of colors
  setColor(ledDigitalOne, COLORS[rand]);  //Set the color of led one to a random color
  //delay(100);
}

/* Sets an led to any color
   led - a three element array defining the three color pins (led[0] = redPin, led[1] = greenPin, led[2] = bluePin)
   color - a three element boolean array (color[0] = red value (LOW = on, HIGH = off), color[1] = green value, color[2] =blue value)
*/
void setColor(int* led, boolean* color){
 for(int i = 0; i < 3; i++){
   digitalWrite(led[i], color[i]);
 }
}

/* A version of setColor that allows for using const boolean colors
*/
void setColor(int* led, const boolean* color){
  boolean tempColor[] = {color[0], color[1], color[2]};
  setColor(led, tempColor);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
