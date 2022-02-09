
#include <WiFi.h>   //declaring library to include functions of wi-fi

String  ClientRequest;  //runs throughout the program
IPAddress staticIP303_10(192,168,1,10);   //Static IPs are declared
IPAddress gateway303_10(192,168,1,1);
IPAddress subnet303_10(255,255,255,0);
WiFiServer server(80);  //Server has been decared (ESP32)

WiFiClient client;    //Client has been declared (Mobile device)

String myresultat; 

String ReadIncomingRequest()  //This function will read all the HTTP request coming from the client and assign it to a local variable named myresultat
{
while(client.available()) {
ClientRequest = (client.readStringUntil('\r'));
 if ((ClientRequest.indexOf("HTTP/1.1")>0)&&(ClientRequest.indexOf("/favicon.ico")<0)){
myresultat = ClientRequest;
}
}
return myresultat;
}

void setup()
{
ClientRequest = "";   //Initialising the clientrequest to empty string

Serial.begin(9600);   //The serial monitor is set up which will run on a baud rate of 9600

pinMode(21, OUTPUT);  //Declaring the output pins
pinMode(23, OUTPUT);
pinMode(25, OUTPUT);
pinMode(27, OUTPUT);
pinMode(2, OUTPUT);
digitalWrite(21,HIGH);  //Initialising the pins to OFF state
digitalWrite(23,HIGH);
digitalWrite(25,HIGH);
digitalWrite(27,HIGH);
  WiFi.disconnect();
  delay(3000);
  Serial.println("START");  //ESP32 will start establishing the wifi connection
  WiFi.begin("esp32","Tiwariji");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");    //Connection established
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  server.begin();

}

//End of setup loop

void loop()
{   client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); } //loop till client is not available
    ClientRequest = (ReadIncomingRequest());  //Reading request coming from the client
    ClientRequest.remove(0, 5);               //Removing previous requests placed at 0th index
    ClientRequest.remove(ClientRequest.length()-9,9);   //Removing request which are beyond the limits 
    if (ClientRequest == "r10") {     //Giving conditions for the relay
      digitalWrite(21,HIGH);
    Serial.print("Relay 1 OFF\n");
    }
    if (ClientRequest == "r11") {
      digitalWrite(21,LOW);
    Serial.print("Relay 1 ON\n");
    }
    if (ClientRequest == "r20") {
      digitalWrite(23,HIGH);
    Serial.print("Relay 2 OFF\n");
    }
    if (ClientRequest == "r21") {
      digitalWrite(23,LOW);
    Serial.print("Relay 2 ON\n");
    }
    if (ClientRequest == "r30") {
      digitalWrite(25,HIGH);
      Serial.print("Relay 3 OFF\n");
    }
    if (ClientRequest == "r31") {
      digitalWrite(25,LOW);
      Serial.print("Relay 3 ON\n");

    }
    if (ClientRequest == "r40") {
      digitalWrite(27,HIGH);
      Serial.print("Relay 4 OFF\n");

    }
    if (ClientRequest == "r41") {
      digitalWrite(27,LOW);
      Serial.print("Relay 4 ON\n");

    }
    if (ClientRequest == "test") {
      digitalWrite(2,HIGH);     //Pin 2 has been assigned to the Wifi Led
      delay(3000);              //LED will blink for 3 secs
      digitalWrite(2,LOW);
      Serial.print("Test conection succesfull\n");
    }
    if(!(WiFi.status() == WL_CONNECTED))
    {
      Serial.print("Wifi disconnected\n");
      delay(3000);
      Serial.print("Setting up again\n");     //If wifi connection is disconnected, the ESP32 will retry to establish the connection
        WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("esp32","Tiwariji");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  server.begin();

    }
    client.println("HTTP/1.1 200 OK");          //Conditions to print on the client's end as a feedback
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("OK");
    client.println("</html>");
    client.stop();
    delay(1);
    client.flush();

}
