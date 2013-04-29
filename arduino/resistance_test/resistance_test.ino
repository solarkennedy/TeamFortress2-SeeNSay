int spinner_pin = 5;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V
float current_value = 0;




void setup()
{
  Serial.begin(115200);             // Setup serial
  digitalWrite(13, HIGH);         // Indicates that the program has intialized
}

void loop()
{
  spinner_detect();
}

void spinner_detect() {
  int raw = 0;
  int Vin = 5;           // variable to store the input voltage
  float Vout = 0;        // variable to store the output voltage
  float R1 = 1000;         // variable to store the R1 value
  float R2 = 0;          // variable to store the R2 value
  float buffer = 0;      // buffer variable for calculation
  float oldR = 0;
  int certainty = 0;  //How certain we are
  const int certainty_threshold = 5; //How certain we should be before we call it
  float total=0;
  const int numReadings = 10;
  
  while (certainty < certainty_threshold) {
    total=0;
    for (int thisReading = 0; thisReading < numReadings; thisReading++)
      total += analogRead(spinner_pin);
    raw = total/numReadings;    // Reads the Input PIN
    Vout = (5.0 / 1023.0) * raw;    // Calculates the Voltage on th Input PIN
    buffer = (Vin / Vout) - 1;
    R2 = normalize_resistor(R1 / buffer); //Who knows what kind of hot glue is on the contacts
    if (oldR == R2) {
      certainty++;
    } else {
      (certainty == 0) || certainty--;  
    }
    oldR = R2;

  }
  
  if (R2 != 0 && R2 != current_value) {
    current_value = R2;
    //Serial.print("Voltage: ");      //
   // Serial.println(Vout);           // Outputs the information
    Serial.print("R2: ");           //
    Serial.println(R2);             //
  }
  
    
}



float normalize_resistor(float input) {
  // Manually normalize the input values coming from the analog pin
  if (input < 110) 
    return 0;
   else if (input >= 110 && input <275) 
    return 220;
   else if (input >= 275 && input <400) 
    return 330;
   else if (input >= 400 && input <575) 
    return 470;   
   else if (input >= 575 && input <840) 
    return 680;
   else if (input >= 840 && input <1600) 
    return 1000;
   else if (input >= 1600 && input <2750) 
    return 2200;    
   else if (input >= 2750 && input <4000) 
    return 3300;
   else if (input >= 4000 && input <7350) 
    return 4700;   
   else if (input >= 7350 && input <15000) 
    return 10000;
   else 
    return 0;
}

