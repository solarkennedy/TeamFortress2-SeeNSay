int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V
int raw = 0;           // variable to store the raw input value
int Vin = 5;           // variable to store the input voltage
float Vout = 0;        // variable to store the output voltage
float R1 = 1000;         // variable to store the R1 value
float R2 = 0;          // variable to store the R2 value
float buffer = 0;      // buffer variable for calculation
float oldR = 0;
const int numReadings = 10;

int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average


void setup()
{
  Serial.begin(9600);             // Setup serial
  digitalWrite(13, HIGH);         // Indicates that the program has intialized
}

void loop()
{
  total=0;
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    total += analogRead(analogPin); 
    
  raw = total/numReadings;    // Reads the Input PIN
  Vout = (5.0 / 1023.0) * raw;    // Calculates the Voltage on th Input PIN
  buffer = (Vin / Vout) - 1;
  R2 = round(R1 / buffer /10) * 10; //round to the nearest 10
  if (R2 != oldR) {
    Serial.print("Voltage: ");      //
    Serial.println(Vout);           // Outputs the information
    Serial.print("R2: ");           //
    Serial.println(R2);             //
    oldR = R2;
  }
  delay(1000);
}
