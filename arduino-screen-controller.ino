/* 
  Arduino Screen Controller
  =========================
 
  Processing code for Ardunio Leonardo to send a text string when a button is pressed.
  
  - Adapted by Gordon Turner from code by Tom Igoe.
  - Reference:
      http://www.arduino.cc/en/Tutorial/KeyboardButton
 
  - A push button attached to digital pin 5.
  - 10-kilohm resistor attached from pin 4 to ground.
  
  - NOTE: Please be careful what the device is plugged into and what has focus, or bad things can happen.

  - 2015-10-28 Changes to remove state, simply behaves as keyboard.
  
 */

// OSX:
//char ctrlKey = KEY_LEFT_GUI;

// Windows and Linux:
char ctrlKey = KEY_LEFT_CTRL;  

// Input pin for the screen toggle push button.
const int screenToggleButtonPin = 2;

// Input pin for the refresh push button.
const int refreshButtonPin = 4;

// Input pin for the screen toggle light sensor.
const int screenToggleLightSensorPin = A0;


// Storing previous state of the screen toggle push button.
int previousScreenToggleButtonState = HIGH;

// Storing previous state of the refresh push button.
int previousRefreshButtonState = HIGH;

// Storing previous state of the screen toggle light sensor.
int previousScreenToggleLightSensorState = LOW;
 
// Pin 13 has an LED connected on most Arduino boards.
int led = 13;


void setup() 
{ 
  // Set the screen toggle push button pin as an input.
  pinMode(screenToggleButtonPin, INPUT_PULLUP);
  
  // Set the screen toggle push button pin as an input.
  pinMode(refreshButtonPin, INPUT_PULLUP);
  
  // Set the screen toggle light sensor pin as an input.
  pinMode(screenToggleLightSensorPin, INPUT_PULLUP);
  
  // Set the led pin as an output.
  pinMode(led, OUTPUT);
  
  // Start up the keyboard.
  Keyboard.begin();
  
  // Read the screen toggle light sensor and set initial value.
  previousScreenToggleLightSensorState = analogRead(screenToggleLightSensorPin);
    
  Serial.print("setup value of previousScreenToggleLightSensorState: ");
  Serial.println(previousScreenToggleLightSensorState);
}


void loop() 
{

  //
  // Handle screen toggle button.
  //


  // Read the screen toggle light sensor.
  int screenToggleLightSensorState = analogRead(screenToggleLightSensorPin);
  
  // Read the screen toggle push button.
  int screenToggleButtonState = digitalRead(screenToggleButtonPin);
  
  // If the button state has changed.
  if ((screenToggleButtonState != previousScreenToggleButtonState) && (screenToggleButtonState == HIGH)) 
  {
    // Turn the led on to indicate button press processed and key combination sent.
    digitalWrite(led, HIGH);
    
    deviceToggle();
    
    // Save the current light sensor state, so that the light from the screen doesn't trigger a toggle.
    previousScreenToggleLightSensorState = screenToggleLightSensorState;
    
    // Wait, blocking more button presses and then turn the led off.
    digitalWrite(led, LOW);
  }
  
  // Save the current button state.
  previousScreenToggleButtonState = screenToggleButtonState;
  
  
  //
  // Handle screen toggle light sensor.
  //

  
  int diff = previousScreenToggleLightSensorState - screenToggleLightSensorState;
  
  // If the light level has changed enough, toggle the device status.
  if( diff > 200 )
  {
    Serial.println("Light sensor state has brightened, turning on.");
    
    Serial.print("    previousScreenToggleLightSensorState: ");
    Serial.println(previousScreenToggleLightSensorState);
    
    Serial.print("    screenToggleLightSensorState: ");
    Serial.println(screenToggleLightSensorState);
    
    deviceOn();
    
    // Save the current light sensor state.      
    previousScreenToggleLightSensorState = screenToggleLightSensorState;
    
  }
  else if( diff < -200 )
  {
    Serial.println("Light sensor state has dimmed, turning off.");
    
    Serial.print("    previousScreenToggleLightSensorState: ");
    Serial.println(previousScreenToggleLightSensorState);
    
    Serial.print("    screenToggleLightSensorState: ");
    Serial.println(screenToggleLightSensorState);
    
    deviceOff();
    
    // Save the current light sensor state.      
    previousScreenToggleLightSensorState = screenToggleLightSensorState;
  }

  
  //
  // Handle screen refresh push button.
  //


  // Read the refresh push button.
  int refreshButtonState = digitalRead(refreshButtonPin);

  // If the refresh button state has changed.
  if ((refreshButtonState != previousRefreshButtonState) && (refreshButtonState == HIGH)) 
  {
    // Turn the led on to indicate button press processed and key combination sent.
    digitalWrite(led, HIGH);

    Serial.println("Refresh button pressed.");
      
    // Send a control-r key combination.
    Keyboard.press(ctrlKey);
    Keyboard.press('r');
    delay(50);
    Keyboard.releaseAll();
    
    digitalWrite(led, LOW);
  }
  
  // Save the current button state.
  previousRefreshButtonState = refreshButtonState;

}


void deviceOff() 
{
  Serial.println("Sending device off");
    
  // Send a WINDOWS-0 key combination.
  //  Keyboard.press(KEY_LEFT_GUI);
  //  Keyboard.press('0');
  // Send Control 0
  Keyboard.press(ctrlKey);
  Keyboard.press('0');
  delay(50);
  Keyboard.releaseAll();  
}


void deviceOn() 
{
  Serial.println("Sending device on");
    
  // Send a WINDOWS-1 key combination.
  //  Keyboard.press(KEY_LEFT_GUI);
  //  Keyboard.press('1');
  // Send Control 1
  Keyboard.press(ctrlKey);
  Keyboard.press('1');
  delay(50);
  Keyboard.releaseAll();  
}


void deviceToggle() 
{
  Serial.println("Sending device toggle");
    
  // Send a WINDOWS-3 key combination.
  //  Keyboard.press(KEY_LEFT_GUI);
  //  Keyboard.press('3');
  // Send Control 2
  Keyboard.press(ctrlKey);
  Keyboard.press('2');
  delay(50);
  Keyboard.releaseAll();  
}

