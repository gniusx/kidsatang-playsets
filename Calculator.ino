#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


// Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Configure the 4x4 keypad
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Connect keypad rows to Arduino pins
byte colPins[COLS] = {5, 4, 3, 2}; // Connect keypad columns to Arduino pins
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String input = "";
float firstNum, secondNum;
char op;
bool isFirstNumSet = false;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("Kidsatang");
  delay(2000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key >= '0' && key <= '9') {
      input += key;
      lcd.setCursor(0, 1);
      lcd.print(input);
    } else if (key == 'C') {
      clearAll();
    } else if (key == '+' || key == '-' || key == '*' || key == '/') {
      if (!isFirstNumSet && input != "") {
        firstNum = input.toFloat();
        op = key;
        isFirstNumSet = true;
        input = "";
        lcd.clear();
        lcd.print(firstNum);
        lcd.print(op);
      }
    } else if (key == '=') {
      if (isFirstNumSet && input != "") {
        secondNum = input.toFloat();
        calculate();
      }
    }
  }
}

void calculate() {
  float result = 0.0;

  switch (op) {
    case '+': result = firstNum + secondNum; break;
    case '-': result = firstNum - secondNum; break;
    case '*': result = firstNum * secondNum; break;
    case '/': 
      if (secondNum != 0) result = firstNum / secondNum; 
      else lcd.print("Error: Div0");
      return;
  }
  
  lcd.clear();
  lcd.print("Result:");
  lcd.setCursor(0, 1);
  lcd.print(result);

  delay(5000);
  clearAll();
}

void clearAll() {
  input = "";
  firstNum = secondNum = 0;
  isFirstNumSet = false;
  lcd.clear();
  lcd.print("Kidsatang");
}
