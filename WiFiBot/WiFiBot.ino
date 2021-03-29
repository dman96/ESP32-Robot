/*
***************************************************
Created by Dave Mandyam
***************************************************

This code allows the ESP32 to host an HTML webpage. The webpage allows one to control a robot using keyboard keys (Set to WASD Keys). The webpage accepts requests made by a keyboard using an asynchronous javascript communication method.
Asynchronous javascript, or AJAX, allows client requests to be made and fulfilled independantly of other requests and responses. Consequently, requests can be fulfilled in real-time without requiring page reloads. When a key is pressed,
the request is read by the ESP32. Based on the requested key, a command is sent to an UNO through the serial port. To use this code, one needs to assign serial pins on the ESP32 to communicate with the Arduino UNO. Additionally, a user 
needs to specify network credentials to allow the ESP32 to connect to a network. For this project, a static IP address is used because the robot will is powered using an external power source. 

Please note AJAX is supported in the following browsers:
- Mozilla Firefox 1.0+
- Safari 1.2+
- Internet Explorer 5+
- Opera 7.6+
- Google Chrome

If you have any questions, feel free to contact me at davem1996@gmail.com
 */

//#define TXD2 *Enter Pin*
//#define RXD2 *Enter Pin*

#include <WiFi.h>

//Declare Network Credentials
const char* ssid = "............";
const char* password = "..........";

//Creating Server and Client Objects
WiFiServer server(80);
WiFiClient client;

//Assign a Static IP Address for Server (Feel free to change the IP Address if Desired)
IPAddress local_IP(192, 168, 1, 18);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);


//Auxiliary Variables to Store Commands and Requests
String header;
char command;


void setup() {

  //Begin both serial connections
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  //Configuring and starting the WiFi Network to the Static IP
  Serial.println("Configuring WiFi Network");
  WiFi.config(local_IP, gateway, subnet);
  Serial.println("WiFi Network Configured");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //Connecting to WiFi Network
  Serial.print("Connected to: ");
  Serial.print(ssid);
  Serial.print("\n");
  Serial.println(WiFi.localIP());

  //Begin Server
  server.begin();


}

void loop() {

  //Make the server listen for clients
  client = server.available();

  //Check if a client has connected
  if (client) {
    Serial.println("New Client Connected");

  //While a client is connected, we will read its request
    while (client.connected()) {
      while (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
      }

     //Depending on the button we press, we assign a specific command
     if (header.indexOf("GET /F") >= 0) {
        command = 'F';
      }

      else if (header.indexOf("GET /B") >= 0) {
        command = 'B';
      }

      else if (header.indexOf("GET /L") >= 0) {
        command = 'L';
      }

      else if (header.indexOf("GET /R") >= 0) {
        command = 'R';
      }

      else if (header.indexOf("GET /O") >= 0) {
        command = 'O';
   }

   //The server will return a successful response and the webpage//
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type: text/html");
      client.println("Connection: keep-alive");
      client.println();

      client.println("<!DOCTYPE HTML>");
      client.println("<html>");

      //Page Head and Style
      client.println("<head>");
      client.println("<meta name=\"viewport\", content=\"width=device-width, initial-scale=1\", charset=\"UTF-8\">");
      client.println("<style> html");
      client.println("{font-family: Helvetica; text-align: center;};");
      client.println("</style>");
      client.println("<style> h1");
      client.println("{font-size: 24};");
      client.println("</style>");

      //Calling the Javascript Program to Produce the AJAX Framework
      //Key Pressed Down
      client.println("<script>");
      client.println("var commandStatus = 1;");
      client.println("document.addEventListener(\"keydown\",function (evnt){");

      client.println("if (evnt.keyCode==\"87\" && commandStatus)");
      client.println("{sendData(\"F\"); commandStatus=0;}");

      client.println("else if (evnt.keyCode==\"83\" && commandStatus)");
      client.println("{sendData(\"B\"); commandStatus=0;}");

      client.println("else if (evnt.keyCode==\"68\" && commandStatus)");
      client.println("{sendData(\"R\"); commandStatus=0;}");

      client.println("else if (evnt.keyCode==\"65\" && commandStatus)");
      client.println("{sendData(\"L\"); commandStatus=0;}");

      client.println("});");

      //Key Released
      client.println("document.addEventListener(\"keyup\", function(evnt){");
      client.println("if (evnt.keyCode == \"65\"||evnt.keyCode == \"68\"||evnt.keyCode == \"83\"||evnt.keyCode == \"87\")");
      client.println("{sendData(\"O\"); commandStatus = 1;}");

      client.println("});");


      //AJAX Request and Response Framework
      client.println("function sendData(moveCmnd) {");
      client.println("var xhttp = new XMLHttpRequest();");
      client.println("xhttp.onreadystatechange = function () {");
      client.println("if (xhttp.readyState == 4 && xhttp.status == 200)");
      client.println("{}");
      client.println("};");
      client.println("xhttp.open(\"GET\", \"/\"+moveCmnd, true);");
      client.println("xhttp.send();");
      client.println("}");
      client.println("</script>");

      client.println("<title>WiFi Controlled Robot</title>");
      client.println("</head>");


      //Presenting the Body of the HTML Page
      client.println("<body>");
      client.println("<h1>WiFi Controlled Robot Server</h1>");

      client.println("<p>This server allows you to wirelessly manipulate a four-wheeled mobile robot. Use the WASD keys to move the robot according to the directional instructions below. Movement is acheived by using AJAX.</p>");

      client.println("<ul>");
      client.println("<li>W=Forward</li>");
      client.println("<li>A=Turn Left</li>");
      client.println("<li>S=Reverse</li>");
      client.println("<li>D=Turn Right</li>");
      client.println("</ul>");

      client.println("</body>");
      client.println("</html>");
      client.println();
      break;
    }

   //We pass a command through a secondary serial port of the ESP32 to an Arduino
    switch (command) {
      case 'F':
        Serial2.write("F");
        break;

      case 'B':
        Serial2.write("B");
        break;

      case 'L':
        Serial2.write("L");
        break;

      case 'R':
        Serial2.write("R");
        break;

      case 'O':
        Serial2.write("O");
        break;
    }

    //Close the connection
    Serial.println("Client Disconnected");
    header = "";
    client.stop();
  }
}
