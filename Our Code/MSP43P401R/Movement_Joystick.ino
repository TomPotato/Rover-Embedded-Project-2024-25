#define BUTTON1   P5_1  // S1 //J4.33
#define BUTTON2   P3_5  // S2 //J4.32
#define JOY_X     A15   //J1.2
#define JOY_Y     A9    //J3.26
#define LED_RED   P2_6  //J4.39
#define LED_GREEN P2_4  //J4.38
#define LED_BLUE  P5_6  //J4.37
#include <String.h>
void setup() {
    Serial.begin(115200);  // Start Serial communication with PC
    //set pins  as input with pullup
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);
    // Set pins as output for led
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    // switching off the led at the begining(LOW output)
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);

}

void loop() {
    int x = analogRead(JOY_X);  // Read X-axis joystick
    int y = analogRead(JOY_Y);   // Read Y-axis joystick
    char movement = check_coordinates(x, y); 
    
    //command from msp to arduino 
    
    Serial.println(movement);  // Send movement command fron joystick
    //command from buttons
    if (digitalRead(BUTTON1) == LOW) {
        Serial.println('P');  // LED ON
    }
    if (digitalRead(BUTTON2) == LOW) {
        Serial.println('W');  // LED OFF
    }
    
    //receive------------------------------------
    //command from arduino to msp
    if(Serial.available()> 0 )
    {
      String cmd = Serial.readStringUntil('\n');
      cmd.trim(); // eliminate spaces and newline

      // show the Roboto LED status on MSP by using the MSP LED
      if (cmd == "LED ON") {
      // LED RGB ON
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_BLUE, HIGH);

      Serial.println("LED ON");
      }
      else if (cmd == "LED OFF") {
      // LED RGB OFF 
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);

      Serial.println("LED OFF");
      }
      else {
      // Unknown command
      Serial.print("Unknown command: ");
      Serial.println(cmd);
      }

    }
   
    delay(565);  // best delay to minimize latency 565

}


// Function to determine movement direction
char check_coordinates(int x, int y) {
    int centerX = 481;
    int centerY = 500;
    int threshold = 450; // Adjust sensitivity
    if (x > centerX + threshold) return 'R';  // Move Right
    if (x < centerX - threshold) return 'L';  // Move Left
    if (y > centerY + threshold) return 'F';  // Move Forward
    if (y < centerY - threshold) return 'B';  // Move Backward
    return 'S'; //Stationary
}
