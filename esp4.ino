#include <SoftwareSerial.h>
#define RX 2
#define TX 3
#define mq4 a0
int food;
String AP = "//  wifi NAME";    
String PASS = "// wifi PASSWORD"; 
String API = " // Write API KEY";  
String HOST = "api.thingspeak.com";
String PORT = "80";
String field = "field1";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
SoftwareSerial esp8266(RX,TX); 
 
  
void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand((char*)"AT",5,"OK");
  sendCommand((char*)"AT+CWMODE=1",5,"OK");
  sendCommand((char*)"AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
}

void loop() {
  getSensorData();
 valSensor = food;
 String getData = "GET /update?api_key="+ API +"&"+ field +"="+String(valSensor);
sendCommand((char*)"AT+CIPMUX=1",5,"OK");
 sendCommand((char*)"AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand((char*)"AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp8266.println(getData);delay(1500);countTrueCommand++;
 sendCommand((char*)"AT+CIPCLOSE=0",5,"OK");
}

int getSensorData(){
  float sensor_volt; //Define variable for sensor voltage
  float RS_air; //Define variable for sensor resistance
  float R0; //Define variable for R0
  float sensorValue; //Define variable for analog readings
  for (int x = 0 ; x < 500 ; x++) //Start for loop
  {
    sensorValue = sensorValue + analogRead(A0); //Add analog values of sensor 500 times
  }
  sensorValue = sensorValue / 500.0; //Take average of readings
  sensor_volt = sensorValue * (5.0 / 1023.0); //Convert average to voltage
  RS_air = ((5.0 * 10.0) / sensor_volt) - 10.0; //Calculate RS in fresh air
  R0 = RS_air / 4.6; //Calculate R0
  Serial.print("R0 = "); //Display "R0"
  Serial.println(R0); //Display value of R0
  delay(1000); //Wait 1 second
float c= 1.105;
 float m = -0.36848;
   //Define variable for sensor voltage
  float RS_gas; //Define variable for sensor resistance 
  float ratio; //Define variable for ratio
 //Read analog values of sensor 
  sensor_volt = sensorValue*(5.0/1023.0); //Convert analog values to voltage
  RS_gas = ((5.0*10.0)/sensor_volt)-10.0; //Get value of RS in a gas
  ratio = RS_gas/R0;  // Get ratio RS_gas/RS_air
  double ppm_log = (log10(ratio)-c)/m; //Get ppm value in linear scale according to the the ratio value 
  float ppm = pow(10, ppm_log); //Convert ppm value to log scale

  delay(200);   
  food=analogRead(A0);
  Serial.print("methane:");
  Serial.print(ppm);
  return ppm; // Replace with your own sensor code
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
