/*
 * Adam Ali
 * 12.7.2016
 * CSIS 10C final project
 */
#include <LiquidCrystal.h>

#define BUTTON_PIN6 6
#define BUTTON_PIN7 7
#define BUTTON_PIN8 8
#define BUTTON_PIN9 9
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String lcdColors[4] = {"Red", "Blue", "Green", "Yellow"}, gameSequence[50];
int gameSeqPointer = 0, playerSeqPointer = 0, priorButton6State = LOW, priorButton7State = LOW, priorButton8State = LOW, priorButton9State = LOW;
bool welcomeScreen = false;

void setup() {

  Serial.begin(9600);
  preCompileSequence();
  lcd.begin(16, 2);
  pinMode(BUTTON_PIN6, INPUT);
  pinMode(BUTTON_PIN7, INPUT);
  pinMode(BUTTON_PIN8, INPUT);
  pinMode(BUTTON_PIN9, INPUT);

}
void loop() {
  if (welcomeScreen == false) {
    getReady();
  }
  inputChecks();
  playerSeqPointer = 0; //setting the player cursor back to 0 (for the repetition of the color pattern)
  printSequence(); //prints the sequence and adds a level. This only happens if the players gets all the patterns right. Otherwise, if they press the wrong button
                   //and lose, the player will encounter a "you lose" screen and the game will fully reset.
  Serial.println(" ");
}

/*
 * Initializes the gameSequence array with 50 random colors. The while loop makes it so that there are no two adjacent indexes that contain the same color.
 */
void preCompileSequence() {
  String randomCol;
  for (int i = 0; i < 50; i++) {
    randomCol = lcdColors[random(0, 4)];
    if (i == 0) {
      gameSequence[i] =  randomCol;
    } else {
      while (randomCol == gameSequence[i - 1]) {
        randomCol = lcdColors[random(0, 4)];
      }
      gameSequence[i] = randomCol;
    }
  }
}

/*
 * prints the sequence up to the current pointer (level) of the game.
 */
void printSequence() {
  delay(300);
  lcd.clear();
  for (int i = 0; i <= gameSeqPointer; i++) {
    lcd.setCursor(5, 0);
    lcd.print(gameSequence[i]);
    delay(300);
    lcd.clear();
    delay(250);
  }
  gameSeqPointer++;
}

/*
 * Called when the player pressed a button that doesn't match up with the current pointer's actual color.
 */
void youLose() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You Lose :(");
  delay(5000);
  lcd.clear();
  welcomeScreen = false;
  playerSeqPointer = 0;
  gameSeqPointer = 0;
  preCompileSequence();
  loop();
}
/*
 * Welcome screen that is triggered only when welcomeScreen == false.
 */
void getReady() {
  lcd.setCursor(5, 0);
  lcd.print("3...");
  delay(1000);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("2...");
  delay(1000);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("1...");
  delay(1000);
  printSequence();
  welcomeScreen = true;
}

void inputChecks() {
  /*
   * This method, using a giant while loop around every button debounce algorithm, checks each input, plugs the player cursor (playerSeqPointer) into the gameSequence array, and checks to see if it matches up. 
   * If you go up to the preCompileSequence method, you will see that there are no two indexes that are adjacent that contain the same color. Thus, this current method works without error.
   * an example of this:
   * Say your sequence is blue green
   * your gameSeqPointer would be 2 and your playerpointer would be 0;
   * at gameSequence[playerPointer], it would be blue. So if blue button is pressed, it adds one to the playerPointer and so you have to press the green button to kill the loop and call printSequence
   */
  while (playerSeqPointer < gameSeqPointer) {
    //////////////////////////////////
    int button6State = digitalRead(BUTTON_PIN6); // read pin
    delay(1);
    if (button6State != priorButton6State) {
      priorButton6State = button6State;
      if (button6State == 0) {

        if (gameSequence[playerSeqPointer] == "Yellow") {
          Serial.print(gameSequence[playerSeqPointer]);
          playerSeqPointer++;
        } else {
          youLose();
        }
      }
    }
    //////////////////////////////////
    int button7State = digitalRead(BUTTON_PIN7); // read pin
    delay(1);
    if (button7State != priorButton7State) {
      priorButton7State = button7State;
      if (button7State == 0) {
        if (gameSequence[playerSeqPointer] == "Green") {
          Serial.print(gameSequence[playerSeqPointer]);
          playerSeqPointer++;
        } else {
          youLose();
        }
      }
    }
    //////////////////////////////////
    int button8State = digitalRead(BUTTON_PIN8); // read pin
    delay(1);
    if (button8State != priorButton8State) {
      priorButton8State = button8State;
      if (button8State == 0) {
        if (gameSequence[playerSeqPointer] == "Blue") {
          Serial.print(gameSequence[playerSeqPointer]);
          playerSeqPointer++;
        } else {
          youLose();
        }
      }
    }
    //////////////////////////////////
    int button9State = digitalRead(BUTTON_PIN9); // read pin
    delay(1);
    if (button9State != priorButton9State) {
      priorButton9State = button9State;
      if (button9State == 0) {
        if (gameSequence[playerSeqPointer] == "Red") {
          Serial.print(gameSequence[playerSeqPointer]);
          playerSeqPointer++;
        } else {
          youLose();
        }
      }
    }
    //////////////////////////////////
  }
}

