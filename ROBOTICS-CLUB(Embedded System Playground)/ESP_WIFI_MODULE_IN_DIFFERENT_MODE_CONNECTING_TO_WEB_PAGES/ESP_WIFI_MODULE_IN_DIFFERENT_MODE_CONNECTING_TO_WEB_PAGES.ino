// simple WIFI & Web SERVER with ESP-32 
#include <WiFi.h>
// wifi library for ESP-32 
// FOR ESP-8266 or NodeMCU you Can USE 
// #include <ESP8266WiFi.h>
// credentials of your HOtspot to setup connections
const char* ssid = "*Your SSID*";         /*Enter Your SSID*/
const char* password = "*Your Password*"; /*Enter Your Password*/
// 80 is Standard Port for HTTP
WiFiServer server(80); /* Instance of WiFiServer with port number 80 */
String request;
// request is string variable , will store incoming HTTP request from client
#define  LED 21

int LED_Status; 

WiFiClient client;
// client is instance of WIFIClient will represent the Connected CLients
void setup() 
{
// baud rate for seria; communication useful for debuging
Serial.begin(115200);
pinMode(LED, OUTPUT);
digitalWrite(LED, LOW);
Serial.print("Connecting to: ");
Serial.println(ssid);
WiFi.mode(WIFI_STA);
// set WIFI mode to station mode
// connecting to an access point 
WiFi.begin(ssid, password);
// attempt to connect With specific WIFI n/w
while(WiFi.status() != WL_CONNECTED)
{
Serial.print(".");
delay(100);
}
Serial.print("\n");
Serial.print("Connected to Wi-Fi ");
Serial.println(WiFi.SSID());
// SSID of connected N/w will print
delay(1000);
server.begin(); /* Start the HTTP web Server */
Serial.print("Connect to IP Address: ");
Serial.print("http://");
Serial.println(WiFi.localIP());
// will print IP address of ESP 32 which we can use to connect it From Web SErver
}

void html (){
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");
client.println();
// function send HTTP header to client,AS request successfull

  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<head>");
    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    client.println("<style>");
      client.println("html { font-family: Roboto; display: inline-block; margin: 0px auto; text-align: center;}");
      client.println(".button {background-color: #4CAF50; border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer;");
      client.println("text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer;}");
      client.println(".button_ON {background-color: white; color: black; border: 2px solid #4CAF50;}");
      client.println(".button_OFF {background-color: white; color: black; border: 2px solid #f44336;}");
    client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h2>ESP32 WiFi Station Mode</h2>");
  client.println("<p>Click to Turn ON and OFF the LED</p>");
// by this you can create client web server and in server you can introduce HTML & CSS

  if(LED_Status == LOW) 
  {
    client.print("<p><a href=\"/LED_ON\n\"><button class=\"button button_ON\">ON</button></a></p>"); 
  } 
 
  else
  {
    client.print("<p><a href=\"/LED_OFF\n\"><button class=\"button button_OFF\">OFF</button></a></p>"); 
  } 
 
  client.println("</body>");
 client.println("</html>");     
}
// web server m jo HTML css s button bney h to kab ON or OFF hongey 

void loop()
{
  client = server.available();
  if(!client)
  {
    return;
  }

  while (client.connected())
  {
    if (client.available())
    {
      char c = client.read();
      request += c;

      if (c == '\n')
      {
        if (request.indexOf("GET /LED_ON") != -1) 
        {
          Serial.println("LED in ON");
          digitalWrite(LED, HIGH);
          LED_Status = HIGH;
        }

        if (request.indexOf("GET /LED_OFF") != -1)
        {
          Serial.println("LED in OFF");
          digitalWrite(LED, LOW);
          LED_Status = LOW;
        }
        html();
        break;
    }
    }
  }

  delay(1);
  request="";
  client.stop();

// Already done IS WIFI station Mode 
// WIFI IN Station, Access Point & MultiWiFi Mode  
// IF you want to connect your ESP with Most Stable signal while
// continously switching back and froth depending on intensity of signal
// simply add this library with old one

#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifi_multi;
// declaring MultiWifi instances 
uint16_t connectTimeOutPerAP=5000;
// timeout Which will be used to try and connect with each WIFI channel
void setup()
{
  //Start the serial communication with the computer
  Serial.begin(115200);
  delay(100);
  Serial.println();
  //Adding the WiFi networks to the MultiWiFi instance
  wifi_multi.addAP(ssid1,password1);
  wifi_multi.addAP(ssid2,password2);
  wifi_multi.addAP(ssid3,password3); 
Serial.print("Connecting to Wi-Fi...");
  while(wifi_multi.run(connectTimeOutPerAP)!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
void loop()
{
  //Monitor the WiFi connection before performing any operation
  if(wifi_multi.run()==WL_CONNECTED)
  {
    //ESP8266 is connected to an Access Point
    Serial.print("Connected to ");
    Serial.print(WiFi.SSID());
    Serial.println("...");
    delay(1000);
  }
  else
{
    Serial.print("WiFi Disconnected!!!");
    Serial.print("Establishing a connection with a nearby Wi-Fi...");
    while(wifi_multi.run(connectTimeOutPerAP)!=WL_CONNECTED)
    {
      Serial.print(".");
      delay(1000);
    }
    Serial.println();
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }

  
  
  
  // ____________ ACCESS POINT MODE ________________
  
  
  // lets do something intresting anc create you ESP WIFI aS access point 
#include <ESP8266WiFi.h> 
 
const char* ap_ssid = "ESP8266"; //Access Point SSID
const char* ap_password= "embedded-robotics"; //Access Point Password
uint8_t max_connections=8;//Maximum Connection Limit for AP
int current_stations=0, new_stations=0;
 
void setup()
{
  //Start the serial communication channel
  Serial.begin(115200);
  Serial.println();
   
  //Setting the AP Mode with SSID, Password, and Max Connection Limit
  if(WiFi.softAP(ap_ssid,ap_password,1,false,max_connections)==true)
  {
    Serial.print("Access Point is Creadted with SSID: ");
    Serial.println(ap_ssid);
    Serial.print("Max Connections Allowed: ");
    Serial.println(max_connections);
    Serial.print("Access Point IP: ");
    Serial.println(WiFi.softAPIP());
  }
  else
  {
    Serial.println("Unable to Create Access Point");
  }
}
 
void loop()
{
  //Continuously check how many stations are connected to Soft AP and notify whenever a new station is connected or disconnected
 
  new_stations=WiFi.softAPgetStationNum();
   
  if(current_stations<new_stations)//Device is Connected
  {
    current_stations=new_stations;
    Serial.print("New Device Connected to SoftAP... Total Connections: ");
    Serial.println(current_stations);
  }
   
  if(current_stations>new_stations)//Device is Disconnected
  {
    current_stations=new_stations;
    Serial.print("Device disconnected from SoftAP... Total Connections: ");
    Serial.println(current_stations);
  }
   
}