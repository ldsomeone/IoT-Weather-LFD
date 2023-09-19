#include <math.h>
#include <WiFi.h>
#include <aREST.h>
#include <DHT.h>

#define DHTPIN 26
#define DHTTYPE DHT11



// Create aREST instance
aREST rest = aREST();

DHT dht(DHTPIN, DHTTYPE, 15);

// WiFi parameters
const char* ssid = "xxxx";
const char* password = "xxxx";
//Static IP address configuration
// P connections
#define LISTEN_PORT 80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);


const int trigPin = 5;
const int echoPin = 18;




//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
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

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("hi");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

}




void loop() {

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Prints the temperature in celsius
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