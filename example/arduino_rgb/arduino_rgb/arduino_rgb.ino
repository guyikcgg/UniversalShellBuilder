// Included headers

// Pin definitions
const int   red_pin = 11;
const int green_pin = 10;
const int  blue_pin =  9;
const int flash_pin =  2;

// Setup of the board
void setup() {
  // Start serial port at 9600 bps
  Serial.begin(9600);
  
  while (!Serial) {
    // Wait for serial port to connect. 
    // Needed for native USB port only
  }

  
  pinMode(   red_pin, OUTPUT );
  pinMode( green_pin, OUTPUT );
  pinMode(  blue_pin, OUTPUT );
  pinMode( flash_pin, OUTPUT );
}

// Main loop
void loop() {
  unsigned long time_elapsed, time_last;
  time_last = micros();
  
  // Read from serial and execute commands
  if (Serial.available() > 0) {
  }
  
  // Perform lighting tasks

  // Make sure that every iteration is at least 10ms long
  time_elapsed = micros()-time_last;
  if (time_elapsed < 10000) delay(10000-time_elapsed);
}
