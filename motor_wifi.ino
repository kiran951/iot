#include <ESP8266WiFi.h>
#include <Servo.h>
Servo myservo;  
const char* ssid     = "Redmi";
const char* password = "easycall";
WiFiServer server(80);
String header;
String lightState = "off";
String fanState = "off";
const int light = D2;
const int fan = D5;

void setup() 
{
 
  Serial.begin(9600);
  
  pinMode(light, OUTPUT);
  pinMode(fan, OUTPUT);
  digitalWrite(light, LOW);
  digitalWrite(fan, LOW);
  myservo.attach(D3);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
  int pos;
  WiFiClient client = server.available();   
  if (client) 
  {                             
    Serial.println("New Client.");         
    String currentLine = "";               
    while (client.connected()) 
    {            
      if (client.available()) 
      {            
        char c = client.read();            
        Serial.write(c);                    
        header += c;
        if (c == '\n') 
        {                    
          if (currentLine.length() == 0) 
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
           
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("Light on");
              lightState = "on";
              digitalWrite(light, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("Light off");
              lightState = "off";
              digitalWrite(light, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("Fan on");
              fanState = "on";
              digitalWrite(fan, HIGH);
              for (pos = 0; pos <= 180; pos += 1) 
              { 
                   myservo.write(pos);              
                   delay(1);                       
              }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(1);                       // waits 15ms for the servo to reach the position
  }
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("Fan off");
              fanState = "off";
              digitalWrite(fan, LOW);
          
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Smart Home Automation</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<p>LIGHT - State " + lightState + "</p>");
            // If the lightState is off, it displays the ON button       
            if (lightState=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">LIGHT ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">LIGHT OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>FAN - State " + fanState + "</p>");
          
            if (fanState=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">FAN ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">FAN OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
