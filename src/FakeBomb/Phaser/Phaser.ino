// Airsoft Bomb v1.0.0
// 
// Made by jamabrandao João Brandão
// License: CC-BY-SA 3.0

/*
 * Phaser 1.0.0
 *
 * The Phaser is a fake airsoft bomb. It has 3 game modes
 * search and destroy, sabotage and domination.
 * It uses RFID cards to release the disarm code.
 *
 * 
 */
 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "Pitches.h"

#pragma GCC diagnostic ignored "-Wwrite-strings"

#define tonepin 8      // Buzzer Pin
#define TickSound 1000
#define TockSound 500

#define btNext 'D'   // Next button
#define btPrev 'C'   // Previous button
#define btEnter '*'  // Enter button
#define btCancel '#' // Cancel button

/********************* VARIABLES ************************/

// Pin 13 has an LED connected on most Arduino boards.
const byte ledPin = 13;

// SOUND TONES
boolean soundEnable = true;

// Keyboard
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {4, 3, 2, A1}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, A2}; // Connect to the column pinouts of the keypad

// Game control variables
boolean sdStatus = false; // Is Search and Destroy game
boolean saStatus = false; // Is Sabotage game
boolean doStatus = false; // for Demolition game
boolean baStatus = false; // Is Battery check
boolean stStatus = false; // Is Settings
boolean start = true;
boolean defusing;
boolean cancel;

// TIME DEFAULTS
byte time[4];
int GAMEHOURS = 0;        // Default hours of the game
int GAMEMINUTES = 45;     // Default minutes of the game
int BOMBMINUTES = 4;      // Default bomb minutes before explosion
int ACTIVATESECONDS = 5;  // Default time to bomb activation

/*********************************************************/

// Initialize the library with the numbers of the interface pins
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  // Initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);

  // Initialize the buzzer pin as an output.
  pinMode(tonepin, OUTPUT);
  
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight
  
  // Clear lcd and set cursor to 0,0
  cls();  
  
  lcd.setCursor(1, 0);
  lcd.print("AIRSOFT SYSTEM");  
  lcd.setCursor(2, 1);
  lcd.print("PHASER v1.0.0");
  delay(2000);
  
  // Clear lcd and set cursor to 0,0
  cls();
  
  lcd.print("COPYRIGHT 2018");
  lcd.setCursor(0, 1);
  lcd.print("Joao Brandao");
  delay(2000);
  
  lcd.clear();
  
  lcd.setCursor(4, 0);
  lcd.print("A INICIAR");
  
  lcd.setCursor(6, 1);
  lcd.print("EM 3");
  beep(NOTE_D7, 20);
  delay(1000); 
  
  lcd.setCursor(6, 1);
  lcd.print("EM 2");
  beep(NOTE_D7, 20);
  delay(1000);
    
  lcd.setCursor(6, 1);
  lcd.print("EM 1");
  beep(NOTE_D7, 20);
  delay(1000);
  beep(NOTE_DS7, 20);
  
  // Configure the bars of progress bar
  createArrowAndProgressBars();
  
  // Clear lcd and set cursor to 0,0
  cls();
}

void loop() {
  mainMenu();
}

/******************* MAIN HELPERS **************************/

void createArrowAndProgressBars() {
   byte bar1[8] = {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
  };
  byte bar2[8] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
  };
  byte bar3[8] = {
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
  };
  byte bar4[8] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
  };
  byte bar5[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
  };
  byte up[8] = {
    B00000,
    B00100,
    B01110,
    B11111,
    B11111,
    B00000,
    B00000,
  };

  byte down[8] = {
    B00000,
    B00000,
    B11111,
    B11111,
    B01110,
    B00100,
    B00000,
  };
  
  lcd.createChar(0, bar1);
  lcd.createChar(1, bar2);
  lcd.createChar(2, bar3);
  lcd.createChar(3, bar4);
  lcd.createChar(4, bar5);
  lcd.createChar(5, up);
  lcd.createChar(6, down);
}
