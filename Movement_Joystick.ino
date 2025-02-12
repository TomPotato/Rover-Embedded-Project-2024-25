// MSP432 Joystick to WiFi via Serial (Energia)

void setup() {
    Serial.begin(9600);  // Start Serial communication with PC
}

void loop() {
    int x = analogRead(A15);  // Read X-axis joystick
    int y = analogRead(A9);   // Read Y-axis joystick

    // Print raw ADC values to Serial Monitor

    char movement = check_coordinates(x, y);  
    Serial.println(movement);  // Send movement command

    delay(600);  // Slow down printing
}


// Function to determine movement direction
char check_coordinates(int x, int y) {
    int centerX = 481;  // Adjusted based on your readings
    int centerY = 491;  
    int threshold = 300; // Adjust sensitivity
    if (x > centerX + threshold) return 'R';  // Move Right
    if (x < centerX - threshold) return 'L';  // Move Left
    if (y > centerY + threshold) return 'F';  // Move Forward
    if (y < centerY - threshold) return 'B';  // Move Backward
    return 'S';  // Stationary
}
