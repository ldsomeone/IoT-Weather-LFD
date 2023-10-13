#include <math.h> //includes the math library
#include <WiFi.h> //includes the WiFI library
#include <aREST.h> //includes the aREST library
#include <DHT.h> //includes the dht (weather sensor) library

#define DHTPIN 26  //defines (as a constant) pin 26 to the dht
#define DHTTYPE DHT11  //we have a DHT-11 (as opposed to a dht-22)

const int PIN_RED   = 2; //Red LED on pin 9
const int PIN_GREEN = 4; //Green LED on pin 10
const int PIN_BLUE  = 16; //Blue LED on Pin 11
 

// Create aREST instance
aREST rest = aREST();

//Sets the DHT Pin 
DHT dht(DHTPIN, DHTTYPE, 15);

// Sets the WiFi parameters
const char* ssid = "Proxima";
const char* password = "centauri";
//Static IP address configuration
// P connections
#define LISTEN_PORT 80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

//Sets the pins for the ultrasonic sensor - the trigger (that sends out the sound wave) and the echo pin (that revieces the sound wave)
const int trigPin = 5;
const int echoPin = 18;


 
//variables to hold our color intensities
int red;
int green;
int blue;

/* This function "Set Color" will set the color of the LED
   rather than doing it over and over in the loop. */
void setColor(int R, int G, int B) {
  analogWrite(PIN_RED,   R);
  analogWrite(PIN_GREEN, G);
  analogWrite(PIN_BLUE,  B);
}

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define PI 3.141592653


// Variables to be exposed to the API
long duration;
float distanceCm;
int radius = 100;
int maxDepth = 200;
float currentWaterTankCapacity;
float percentageOfMaxCapacity;
char* location = "Al Fresco";
float temperature;
float humidity;

// Declare functions to be exposed to the API
int ledControl(String command);




void setup(void) {

  Serial.begin(115200); // Starts the serial communication

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  dht.begin();


  //set all three LED pins to output mode
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);
  
  // Init variables and expose them to REST API
  rest.variable("percentageOfMaxCapacity", &percentageOfMaxCapacity);
  rest.variable("location", &location);
  rest.variable("temperature", &temperature);
  rest.variable("humidity", &humidity);

  // Give name and ID to device
  rest.set_id("140");
  rest.set_name("alpha-102");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  IPAddress ip(192, 168, 1, 140);     //set static ip
  IPAddress gateway(192, 168, 1, 1);  //set getteway
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
  IPAddress subnet(255, 255, 255, 0);  //set subnet
  WiFi.config(ip, gateway, subnet);

  // while (WiFi.status() != WL_CONNECTED) {  //while the wifi on the esp-32 is not connected, it will print '.'
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println("");
  // Serial.println("WiFi connected"); //prints to the serial monitor the message

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

}




void loop() {

  temperature = dht.readTemperature(); //sets our temperature variables to the reading off the sensor
  humidity = dht.readHumidity();

  if (temperature <= 17.0) {  // If in the cold temperature range
      setColor(15, 3, 252);  // Display Dark Blue
    } else if (temperature <= 20.0) {  // If in cold-mderate temperature range
      setColor(137, 207, 240);  // then show light Blue
    } else if (temperature <= 23.0) {  // if in the moderate temperature range
      setColor(0, 255, 0);  // then show green
    } else if (temperature <= 26.0) {  // if in the moderate-hot temperature range
      setColor(256, 110, 0);  // then show orange   
    } else {  // if in the hot temperature range
      setColor(255, 0, 0);  // then show red
    }

  // Prints the temperature in celsius and the humidity
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);


  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in cm
  distanceCm = duration * SOUND_SPEED/2;
  
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  //converts the distance to a percentage of the water tank capacity
  currentWaterTankCapacity = (PI * radius * radius * distanceCm);
  percentageOfMaxCapacity = ((PI * radius * radius * maxDepth) - currentWaterTankCapacity) / (PI * radius * radius * maxDepth) * 100;

  Serial.print("Percentage of Max Capacity: ");
  Serial.println(percentageOfMaxCapacity);

  //change this to more like 10 seconds?
  delay(5000);

    // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  rest.handle(client);
  //Serial.println("called");
}



// Custom function accessible by the API
int ledControl(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(6, state);
  return 1;
}