# Smart Watering App

## an IoT project

![Yellow-Umbrella](public/assets/yellow-umbrella.png)

### Development Roadmap

- [x] Setup repos - GitHub
- [x] setup ESP32 - Arduino IDE
- [x] Install dependencies - aREST.h and DHT.h
- [x] Test ESP32 - get json data via wifi
- [x] Initialize Node.js environment
- [x] setup server.js with express
- [x] set index route and views
- [x] link ESP32 to Node app with fetch


### Initializing a Node.js Environment

1. Ensure that Node.js and NPM are installed on your system:
    > node --version

    > npm --version

2. In terminal, inside the project directory:
    > npm init -y

3. This will add a package.json file

4. Install dependencies
    > npm install express ejs express-ejs-layouts

5. Install development dependencies
    > npm install --save-dev dotenv nodemon
    

### Coding

1. Code the Adrduino -. 
    >  Taking the reading from the ultrasonic sensor and dht-11 weather sensor

    > LED code - vary the colour based on the temperature. I.e. if it is hot red is displayed, if it is cold, blue is displayed and so on.

2. Add code to create rest api and webserver
    
3. Setup code to host the server

4. Make an index page for the website
     > Seup with head/footer and css
     
     > Put the readings from the sensors onto the webpage
   


### Worklog and Commits

Date | Commit Message | Version
:-----|:----------------:|:--------:
25.08.23 | initial setup | 0.1.0
7.09.23 | adding ultrasonic sensor and coding website  | 0.1.1
14.09.23 | adding navbar to the website and adding an ouptup | 0.1.2

### References

- [Web Page Layouts](https://www.youtube.com/watch?v=3C_22eBWpjg)
- [JS Native Fetch](https://www.youtube.com/watch?v=MBqS1kYzwTc)
- [HR-S04 Information](https://components101.com/sensors/ultrasonic-sensor-working-pinout-datasheet)
- [Tutorial for Ultrasonic Sensor](https://www.instructables.com/Ultrasonic-Water-Level-Indicator-Using-HC-SR04-Ard/)
- [About te DHT-11 Senor and How to Set Up](https://components101.com/sensors/dht11-temperature-sensor)
- [About the RGD LED](https://www.circuitbread.com/tutorials/how-rgb-leds-work-and-how-to-control-color)
- 


