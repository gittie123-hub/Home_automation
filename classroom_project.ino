#include <SoftwareSerial.h> //Library for serial connection with ESP
#include <ThingSpeak.h>
SoftwareSerial espSerial(2, 3); // (RX TX)
String wifiname = "D-Link"; // hotspot name
String passwd = "koushik.sriram0904"; // password
String sendData =
"GET/channels/1118118/fields/1.json?api_key=FPSPU7NS9HP1OPAV&results=2";
String output = ""; //Initialize a null string variable
#define Relay1 6
#define Relay2 7
unsigned long counterChannelNumber = 1118118; // Channel ID
const char * myCounterReadAPIKey = "FPSPU7NS9HP1OPAV"; // Read API Key 12
const int FieldNumber1 = 1;
void setup()
{
pinMode(Relay1,OUTPUT);
pinMode(Relay2,OUTPUT);
Serial.begin(9600);
espSerial.begin(9600);
espcommand("AT+RST"); // restart the module
espcommand("AT+CWMODE=1"); // CLIENT MODE
espcommand("AT+CWJAP=\""+wifiname +"\",\""+ passwd +"\"");
while(!espSerial.find("OK"))
{
 Serial.println("not connected");
}
}
void loop() {
espcommand("AT+CIPMUX=0");
espcommand("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
espcommand("AT+CIPSEND=76");
long val = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1,
myCounterReadAPIKey);
//statusCode = ThingSpeak.getLastReadStatus();
//if (statusCode == 200)
Serial.println(val);
if(val == 1){
digitalWrite(Relay1,HIGH); // LIGHT WILL OFF
}
if(val == 0){
digitalWrite(Relay1,LOW); // LIGHT WILL GLOW
}
else{
digitalWrite(Relay1,HIGH);
}
// else{
// Serial.print("or No internet!");
// }
delay(1000);
}
void espcommand(String command)
{
Serial.print("AT command =");
Serial.print(command); // funtion to write into serial monitor automatically.
espSerial.println(command);
delay(1000);
}
