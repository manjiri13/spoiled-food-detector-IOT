# spoiled-food-detector-IOT

Hardware Components Required :
Arduino Uno R3,
MQ4 Methane sensor,
Esp8266-01 wifi module,
Breadboard,
Jumper wires,
Resistor

Software Required :
Arduino IDE 1.8.13,
Thingspeak

Languages used :
CPP and
Matlab

steps:

1)To send the data to the cloud and display them on the web, we used THINGSPEAK.Following are the steps to begin with it -
STEP 1 : Sign up for Thingspeak.For creating account go to http://www.thingspeak.com/
STEP 2 : Creating a new channel.to create a new channel  select My channel then create a new channel enter the details and select save the channel.
STEP 3 : Get your API keys.after creating ,open your channel and select the API keys option.Note down the API key.This unique key is used to send the data from the microcontroller to the web.

2) Connecting ESP8266 to wifi

3) Uploading the code and serial monitor and getting sensor data on thingspeak channel.(my Channel ID: 1223151)

4) Generating alert key on thingspeak ,creating a matlab analysis and writing matlab code to send email and adding the alert key to matlab code also adding conditions to send the email to react.

5) Email sent when sensor data > 570
