const int inputPin = 2;       // Input and interrupt pin from 555 timer
volatile unsigned long pulseCount = 0;
unsigned long duration = 10000; // Duration for counting pulses in milliseconds

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Configure the input pin
  pinMode(inputPin, INPUT);

  // Attach interrupt to count pulses
  attachInterrupt(digitalPinToInterrupt(inputPin), countPulse, RISING);
}

void loop() {
  // Reset the pulse count
  pulseCount = 0;

  // Record the start time
  unsigned long startTime = millis();

  // Wait for the specified duration
  while (millis() - startTime < duration) {
    // Do nothing, just wait
  }

  // Calculate frequency
  float frequency = pulseCount * (1000.0 / duration); // Frequency in Hz

  // Print the frequency to the Serial Monitor
  //Serial.print("Frequency: ");
  //Serial.println(frequency);
  //Serial.println(" Hz");

  // Convert frequency to humidity using the lookup table
  float humidity = convertFrequencyToHumidity(frequency);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  //Serial.println(" %");

  // Wait for a while before the next reading
  //delay(1000);
}

void countPulse() {
  pulseCount++;
}

// Function to convert frequency to humidity using the lookup table
float convertFrequencyToHumidity(float frequency) {
  // Define the lookup table
  const int RH[] = {10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95};
  const float Fout[] = {7155, 7080, 7010, 6945, 6880, 6820, 6760, 6705, 6650, 6600, 6550, 6500, 6450, 6400, 6355, 6305, 6260, 6210};
  
  // Find the two surrounding values
  int i;
  for (i = 0; i < sizeof(Fout) / sizeof(Fout[0]) - 1; i++) {
    if (frequency > Fout[i]) break;
  }

  // Linear interpolation
  float humidity;
  if (i == 0) {
    humidity = RH[0];
  } else if (i == sizeof(Fout) / sizeof(Fout[0])) {
    humidity = RH[sizeof(RH) / sizeof(RH[0]) - 1];
  } else {
    float freq1 = Fout[i];
    float freq2 = Fout[i - 1];
    float rh1 = RH[i];
    float rh2 = RH[i - 1];
    humidity = rh1 + (frequency - freq1) * (rh2 - rh1) / (freq2 - freq1);
  }
  
  return humidity;
}
