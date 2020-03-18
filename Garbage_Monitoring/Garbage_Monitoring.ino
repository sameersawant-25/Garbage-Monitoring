#define DEBUG true
SoftwareSerial esp8266(11,12);      /* This will make the pin 11 of arduino as RX pin and
pin 12 of arduino as the TX pin Which means that you have to connect the TX from the esp8266
to the pin 10 of arduino and the Rx from the esp to the pin 11 of the arduino*/
const int MOISTURE_LEVEL = 200;
/* Moisture sensor output values
# 0  ~300     dry trash

# 300~700     humid trash

# 700~950     in water or liquid */


const int buzz =10; //pin for the moisture sensor

int led_pin5=5;

int led_pin6=6;

int led_pin7=7;

 

int sensor_pin =A0; // moisture sensor

int output_value ; // to disply the the out put of the moisture sensor

 

const int trigPin = 13;            // Making the arduino's pin 9 as the trig pin of ultrasonic sensor

const int echoPin = 8;            // Making the arduino's pin 10 as the echo pin of the ultrasonic sensor

// defining two variable for measuring the distance

long duration;

int distance;
void setup()
{
  Serial.begin(57600);         // Setting the baudrate at 57600

  esp8266.begin(115200);        // Set the baudrate according to you esp's baudrate. your esp's baudrate might be different from mine
  pinMode(buzz, OUTPUT);

  //digitalWrite(led_pin, HIGH);
  delay(300);
  digitalWrite(buzz, LOW);

  pinMode(led_pin5, OUTPUT);
  digitalWrite(led_pin5, LOW);

  pinMode(led_pin6, OUTPUT);
  digitalWrite(led_pin6, LOW);

  pinMode(led_pin7, OUTPUT);
  digitalWrite(led_pin7, LOW);

  sendData("AT+RST\r\n",2000,DEBUG);            // command to reset the module

  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // This command will turn on the server on port 80

  void check_distance();

}

void loop()
{
{

digitalWrite(trigPin, LOW);   // Making the trigpin as low

delayMicroseconds(2);         // delay of 2us

digitalWrite(trigPin, HIGH); // making the trigpin high for 10us to send the signal

delayMicroseconds(10);

digitalWrite(trigPin, LOW);  

duration = pulseIn(echoPin, HIGH);  // reading the echopin which will tell us that how much time the signal takes to come back

distance= duration*0.034/2;         // Calculating the distance and storing in the distance variable

  


int moisture = analogRead(sensor_pin); // This will read the anolog value form the moisture sensor 


Serial.print( moisture);
  
 
check_distance();

 
    if(moisture < MOISTURE_LEVEL)

    {

        //LedState(HIGH);
            //digitalWrite(led_pin, LOW); // if the garbage is moist it will set the pin high and yellow LED will glove/ bizzer will blow
        digitalWrite(buzz, LOW);

    }
    else

    {

            //digitalWrite(led_pin, HIGH); // if the garbage is moist it will set the pin high and yellow LED will glove/ bizzer will blow
digitalWrite(buzz, HIGH);
            //        LedState(LOW);

    }
 

 

      delay(1000);  

 

  if(esp8266.available())         // This command will that check if the esp is sending a message

  {   

    if(esp8266.find("+IPD,"))

    {

     delay(1000);

     int connectionId = esp8266.read()-48; /* We are subtracting 48 from the output because the read() function returns

                                            the ASCII decimal value and the first decimal number which is 0 starts at 48*/

     String webpage = "<h1><b><marquee>IOT Garbage Monitoring System</marquee><b></h1><img src= 'C://Users//ADMIN//Desktop//Search.png' height ='120px' width = '120px' align='middel'>";
 
       webpage += "<p><h2>";  

       if (distance<7 )

       {

        webpage+= "<i> Trash can is Full</i>";

        if(moisture < MOISTURE_LEVEL)

        {

        webpage+="<br>trash is moist";

        }

        else

        {

          webpage+=" <br> Trash is dry";

          }

       }

        else  {
              

                    webpage+= "<i> Trash can is Empty</i>";

/*          if(moisture < MOISTURE_LEVEL)

          {

        webpage+="<br>trash is moist";

        }

        else

        {

          webpage+=" <br> Trash is dry";

          }*/

        }

       webpage += "</h2></p></body>"; 

     String cipSend = "AT+CIPSEND=";

     cipSend += connectionId;

     cipSend += ",";

     cipSend +=webpage.length();

     cipSend +="\r\n";

     sendData(cipSend,1000,DEBUG);

     sendData(webpage,1000,DEBUG);    

     String closeCommand = "AT+CIPCLOSE=";

     closeCommand+=connectionId;

     closeCommand+="\r\n";

     sendData(closeCommand,3000,DEBUG);

    }

  }

}}

String sendData(String command, const int timeout, boolean debug)

{

    String response = "";   

    esp8266.print(command);

    long int time = millis();

    while( (time+timeout) > millis())

    {

      while(esp8266.available())

      {

        char c = esp8266.read();

        response+=c;

      } 

    }

    if(debug)

    {

      Serial.print(response);

    }

    return response;

 }


  if (distance > 7 && distance < 18)

  {

    digitalWrite(led_pin6, HIGH);//pin no 6 will be high if the distnace is less than the 7cm and the yellow LED will glove
    digitalWrite(led_pin5, LOW);
    digitalWrite(led_pin7, LOW);
   }
