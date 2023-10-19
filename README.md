# Smart Watering App

## An IoT project

<br>

### Table of Contents
- [Description](#Description)
- [Components Used](#Components-Used)
- [Prerequisites](#Prerequisites)
- [Wiring](#Wiring)
- [Installations](#Installations)
- [Setting Up A Github Repository](#Setting-Up-A-Github-Repository)
- [Starting Node.js](#Node.js)
- [Coding](#Coding)
- [Worklog](#Worklog-and-Commits)
- [References](#References)

<br>

### Description and Purpose:

Overview: This project uses an ESP-32, DHT-11 (Weather) Sensor and HR-S04 (Ultrasonic) Sensor to take readings on the weather and capacity of a water tank. This data is transfered over WiFi to the server so that you can check the weather and how much water is left in your tank at any time. This is useful so you can manage your water use and this project is the start of a fully automated watering system. This is because there is the potential to develop this idea a lot further with a rain-sensor model, soil moisture or an irrigation controller. 

Purpose: This is designed to be the start of a fully automated IoT watering system.

Usage: This project is intended so that the ultrasonic sensor is placed on top of a water tank (with a powersource) and taking in data once every few minutes. It, combined with the weather sensor will transmit data over the WiFi to the server where you can chech the status at any time. It is also possible to do so while away or on holidays so that your garden will stay looking great!

Important: All of the code has been commented for easy understanding. In the firmware folder, in the arduino code (.ino) file, you will have to change the network name and password to whatever you want (your WiFi) because otherwise this project will not work.

<br>
<br>

<img src="public/assets/Water_Tank.png" width="350px" >


<br>

### Components Used
This project used two different sensor imputs and a transducer output:
- an ESP-32 - This is a microchip that we have used to send information to, and recieve information from, the sensors. This has integrated Wi-Fi and connects to our node application to provide real time data.

- HR-S04 (Ultrasonic Sensor) - Ultrasonic sensors can be used in many situations. For us, it is used to calculate the how much water is left in a water tank by finding the distance from the top of the water tank to the level of the water. This distance is then converted into a percentage of the maximum capacity. The calculations used are for a sample water tank.

- DHT-11 (Weather Sensor) - This is a weather sensor that will provide both the temperature and humidity.

- RGB LED Light - In my project, this is the output that is used to display the a colour based on the temperature. For example, if it is cold, blue will be showing. If it is hot, red will be displayed.

<br>


### Prerequisites
Installation Guides Below.
- Components (Listed Above) with breadboard and cables

- Arduino IDE - for the backend coding

- VS Code - for setting up the server and webpages

- Github - for repository (see below for how to set up)

<br>

### Wiring 
The wiring diagrams for the components are seen below, however, because this project uses all of these components, the wiring is slightly differnt. Also, in the .ino file, the specific pins for wiring is different to those in the diagrams so you will need to change the pin number on the file or change where the wire go on your ESP-32.

DHT-11 and ESP-32:
<br>
<img src="public/assets/ESP32-DHT11-Wiring.png" width="450" height="300">
<br>

Ultrasonic Sensor with ESP-32:
<br>
<img src="public/assets/ESP32-Ultrasonic-Sensor-Wiring.png" width="450" height="300">
<br>

RGB LED With and ESP-32:
<br>
<img src="public/assets/ESP32-with-RGB-LED-Wiring.jpg" width="450" height="300">
<br>

My Fully-Wired Smart Watering App:
<br>
<img src="public/assets/Wired_ESP-32.jpg" width="350" height="390">
<br>

<img src="public/assets/ESP-Wiring1.jpg" width="350" height="300">
<br>

<img src="public/assets/ESP-Wiring2.jpg" width="350" height="400">
<br>
<br>


### Installations
Installing the three programs below are necessary for this project.

- Arduino: [Setting Up The Arduino IDE](https://www.arduino.cc/en/software)
Follow installation guide then install the following libraries: aREST Library, DHT Sensor Library and Adafruit Unified Sensor Library

- VS Code [Setting Up VS Code](https://code.visualstudio.com/download)
Follow the installation guide above

- Node JS [Setting Up Node Js](https://nodejs.org/en)
Download via the link above

<br>

### Setting Up A Github Repository
Setting up a GitHub repository can be very, very useful so you have a record of your code.
<br>
Follow the guide to setup a repository by forking this repo: [How to Fork a GitHub Repository](https://docs.gitlab.com/ee/user/project/repository/forking_workflow.html)

<br>

### Development Roadmap

- [x] Setup repos - GitHub
- [x] setup ESP32 - Arduino IDE
- [x] Install dependencies - aREST.h and DHT.h
- [x] Test ESP32 - get json data via wifi
- [x] Initialize Node.js environment
- [x] setup server.js with express
- [x] set index route and views
- [x] link ESP32 to Node app with fetch

<br>

### Node.js 

This [article](https://www.w3schools.com/nodejs/nodejs_intro.asp) discusses what Node JS is, how/when to use it and some basic programming in Node.

1. Ensure that Node.js and NPM are installed on your system:
    > use 'node --version'

    > and 'npm --version'

2. In terminal, inside the project directory:
    > npm init -y

3. This will add a package.json file

4. Install dependencies
    > npm install express ejs express-ejs-layouts

5. Install development dependencies
    > npm install --save-dev dotenv nodemon
    
<br>

### Coding

1. Code the Adrduino -. 
    >  Taking the reading from the ultrasonic sensor and dht-11 weather sensor

    > LED code - vary the colour based on the temperature. I.e. if it is hot red is displayed, if it is cold, blue is displayed and so on.

2. Add code to create rest api and webserver
    > Get the JSON data via WiFi
    
4. Setup code to host the server
   > Index routes and views
   > Then an 'about page' with another route

6. Styling webpage 
     > Seup with head/footer and css
     
     > Put the readings from the sensors onto the webpage

<br>

### Worklog and Commits

Date | Commit Message | Version
:-----|:----------------:|:--------:
25.08.23 | initial setup of weather sensor and arduino script | 0.1.0
7.09.23 | adding ultrasonic sensor and coding the server/website  | 0.1.1
14.09.23 | adding navbar to the website and adding an ouptup | 0.1.2
21.09.23 | adding an 'about' page and coding the extra routes | 0.1.3
07.10.23 | updating repository and completing readme.md | 0.1.4

<br>

### References

- The Website Architech (2021) How to Layout a Webpae [https://www.youtube.com/watch?v=3C_22eBWpjg](https://www.youtube.com/watch?v=3C_22eBWpjg)
- Fireship (2021) JS Native Fetch. [https://www.youtube.com/watch?v=MBqS1kYzwTc](https://www.youtube.com/watch?v=MBqS1kYzwTc)
- W3 Schools (2023) Node JS Introduction. [https://www.w3schools.com/nodejs/nodejs_intro.asp](https://www.w3schools.com/nodejs/nodejs_intro.asp)
- Components 101 (2021) HC-SR04 Ultrasonic Sensor. [https://components101.com/sensors/ultrasonic-sensor-working-pinout-datashee](https://components101.com/sensors/ultrasonic-sensor-working-pinout-datasheet)
- Instructables (2021) Water Level Indicator Using a HC-SR04 [https://www.instructables.com/Ultrasonic-Water-Level-Indicator-Using-HC-SR04-Ard/](https://www.instructables.com/Ultrasonic-Water-Level-Indicator-Using-HC-SR04-Ard/)
- Components 101 (2021) DHT-11 Temperature Sensor. [https://components101.com/sensors/dht11-temperature-sensor](https://components101.com/sensors/dht11-temperature-sensor)
- Circuit Bread (2019) How LED's Work and How to Control Their Color. [https://www.circuitbread.com/tutorials/how-rgb-leds-work-and-how-to-control-color](https://www.circuitbread.com/tutorials/how-rgb-leds-work-and-how-to-control-color)
- LogRocket (2021) How to Use EJS to Template Your Node Application. [https://blog.logrocket.com/how-to-use-ejs-template-node-js-application/](https://blog.logrocket.com/how-to-use-ejs-template-node-js-application)

