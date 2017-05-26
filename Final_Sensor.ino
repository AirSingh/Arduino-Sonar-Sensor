#include <Time.h>
#include <TimeLib.h>
#include <SD.h>
#include <stdio.h>
#include <SPI.h>


unsigned long time;
int d;
const int anPin1 = 0; // This will make the arduino board read analog voltage from sensor #1
const int anPin2 = 1; // This will make the arduino board read analog voltage from sensor #2
const int chipselect = 8; // The chip select pin on the SD shield is attached to deigital pin 8 (D8)
File sensorfile; // Defines a variable "sensorfile" using the File command 

int triggerPin1 = 2;   // The trigger pin(RX) on sensor #1 is defined.
long distance1, distance2; // these variables represent the distance measured by the sensors. 

// //This part of the code is to initialize the system and define the output variables.
void setup()  
{
Serial.begin(9600);// sets the serial port to 9600

// Open serial communications and wait for port to open:


 while (!Serial) {
  ; // wait for serial port to connect. Needed for Leonardo only
    // This step will make sure that serial port is open.
}


// 
// If the correct port is open, the chipselect pin and output pins for
// Micro SD socket are set as outputs.

Serial.print("Initializing SD card...");
// chip select pin and digital pin(D10), trigger pin(RX) and digital pin(D3)
// are set to be output.  
  pinMode(chipselect, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(triggerPin1, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipselect)) {
    Serial.println();
    Serial.println("Card failed, or not present");
    return; // This will stop the code/function if the card is not detected.
  }
  Serial.println("card initialized."); // If card is detected, this statement will be displayed 
                                       //to let the user know the chip is detected and the system
                                       // is functioning properly thus far.
    if (sensorfile) {
     sensorfile.println('\n');
     sensorfile.println("NEW TEST:");
     sensorfile.println('\n');
  }
  sensorfile.close();
}

//This part of the code is used to power up the sensors.
void start_sensor(){ // creates a function named start_sensor
  digitalWrite(triggerPin1,HIGH);
  delay(1);
  digitalWrite(triggerPin1,LOW);
  // In order to activate the sensors follwing steps are performed due to the code:
// The triggerPin1 is set to high, activating the digital pin (D2).
 // As the digital pin(D2) is activated, The trigger pin (RX) on sensor #1 gets a signal to go.  
 // Sensor #1 begins to measure distance.
 // After a short delay, the triggerPin1  is set to low.
 //The echo pin (TX) on sensor #1 sends a signal to the trigger pin (RX) on sensr #2 
 // Sensor #2 then begins to measure distance.

}


// This part of the code is to simply convert the voltage reading obtained from the sensor 
//  to inches.
void read_sensors(){ // creates a function named read_sensors
  /*
  Scale factor is (Vcc/512) per inch. A 5V supply yields ~9.8mV/in
  Arduino analog pin goes from 0 to 1024, so the value has to be divided by 2 to get the actual inches
  */
  distance1 = analogRead(anPin1)/2; // Measurement reading obtaines from sensor #1
  distance2 = analogRead(anPin2)/2; // Measurement reading obtained from sensor #2
}


void led1() {
 if (distance1>(distance2 + 1)){ // This function will make the Led light up when the sensor #1 reading
                   // is less than sensor #2(base line).
    digitalWrite(5,HIGH); //lights up the led by setting the digital pin #3 high.
    delay(300);
    digitalWrite(5, LOW); // turns off the led.
    delay (300);
    
} 
  
}

/*void led2()
{
  if (distance2==10){ // This function will make the Led light up when the sensor #1 reading
                   // is less than sensor #2(base line).
    digitalWrite(7,HIGH); //lights up the led by setting the digital pin #3 high.
    delay(2000);
    digitalWrite(7, LOW); // turns off the led.
    delay(2000);
    digitalWrite(7,HIGH); //lights up the led by setting the digital pin #3 high.
    delay(2000);
    digitalWrite(7, LOW); // turns off the led.
    delay(2000);
  }
}
*/
// This part of the code is to display the readings in the debug screen.
void print_all(){ //creates a function named print_all

if (distance1>(distance2 + 1)) {

  Serial.print('\n');
  Serial.print("Sensor 1 Reading:");
  Serial.print(" ");
  Serial.print(distance1); // prints the measurements obtained from sensor #1
  Serial.print("in");
  Serial.print(" |");
  Serial.print(" ");
  Serial.print("Sensor 2 Reading:");
  Serial.print(" ");
  Serial.print(distance2); // prints the measurements obtaines from sensor #2
  Serial.print("in");
  Serial.print(" ");
  Serial.print('\n');  
  Serial.print("Crack Detected at Time: ");
  d=distance1-distance2;
  time = millis()/1000;
  //prints time since program started
  Serial.print('\n');
  Serial.println(time);Serial.print("seconds");
  Serial.print('\n');
  Serial.print('\n');  
  Serial.print("With depth of:");
  Serial.print('\n');
  Serial.println(d);
    Serial.print("inches");
    delay(300);          // The readings from the sensors will be displayed every second.

led1();
}


else 
{
  Serial.print("Sensor 1 Reading:");
  Serial.print(" ");
  Serial.print(distance1); // prints the measurements obtained from sensor #1
  Serial.print("in");
  Serial.print(" |");
  Serial.print(" ");
  Serial.print("Sensor 2 Reading:");
  Serial.print(" ");
  Serial.print(distance2); // prints the measurements obtaines from sensor #2
  Serial.print("in");
  Serial.print(" ");
  Serial.print('\n');
  Serial.print("No Crack Surface");
 
  Serial.println();
  delay(300);          // The readings from the sensors will be displayed every second.

led1();
}
}

// The following codes written in the loop function will conitnously function.
void loop() {
 
  
  start_sensor(); // calls in functions created earlier
  read_sensors();
   //led2();
   print_all();
   led1();
   
    sensorfile= SD.open("gymtest.txt", FILE_WRITE); // the comman SD.open with the FILE_WRITE 
  //command creates a text file within the SD card named readings.         

  if (sensorfile) {     // If a file is successfully created, this if statement is initiated.  


  if (distance1>(distance2 + 1)) {
  print_all(); // calls in the function created earlier.
  sensorfile.print('\n');
  sensorfile.print("Sensor 1 Reading:"); 
  sensorfile.print(" ");
  sensorfile.print(distance1);// these function will write the values obtaines from the 
                              //sensors to the gymtest.txt file.
    sensorfile.print("in");
  sensorfile.print(" ");
  sensorfile.print(" ");
  sensorfile.print("Sensor 2 Reading:");
  sensorfile.print(" ");
  sensorfile.print(distance2);
  sensorfile.print("in");
  sensorfile.print(" ");
  sensorfile.print("- Crack detected");
  sensorfile.println();
   sensorfile.print('\n');  
  sensorfile.print("Crack Detected at Time (s): ");
  time = millis()/1000;
  //prints time since program started
  sensorfile.print('\n');
  sensorfile.println(time);
  sensorfile.print('\n');  
  sensorfile.print("With depth (in):");
  sensorfile.println(d);
  sensorfile.print('\n');
  sensorfile.print('\n');
  led1();
  }

  else {

  print_all(); // calls in the function created earlier.  
  sensorfile.print("Sensor 1 Reading:"); 
  sensorfile.print(" ");
  sensorfile.print(distance1);// these function will write the values obtaines from the 
                              //sensors to the readings.txt file.
  sensorfile.print("in");
  sensorfile.print(" ");
  sensorfile.print(" ");
  sensorfile.print("Sensor 2 Reading:");
  sensorfile.print(" ");
  sensorfile.print(distance2);
  sensorfile.print("in");
  sensorfile.print(" ");
  sensorfile.print('\n');
  sensorfile.print("- No Crack Surface");
  sensorfile.println('\n');
  }
  sensorfile.close(); // this function will close the  created file and save all the 
                      // information written durign the loop.
  delay(300);
  }
}
  
  

