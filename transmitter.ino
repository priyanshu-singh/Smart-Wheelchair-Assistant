

#include <VirtualWire.h>

int xPin=0;
int yPin=1;

int ledPin=13;//led on pin 13 is ON except when transmitter is parallel to the ground

void setup() 
{
  vw_setup(2000);//Bits per second
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);//Initialise the serial connection debugging
}

void loop() 
{
  int xval=analogRead(xPin);
  int yval=analogRead(yPin);
  
  //Serial.print("xval=");
  //Serial.println(xval);
  
  //Serial.print("yval=");
  //Serial.println(yval); 
  
  //delay(1000); //used to display values after 1s delay
  
  //Serial.print("\n");
  
  if ((xval>266 && xval<329) && (yval>325&& yval<328)) //stationary or stop(transmitter parallel to ground)
  {
    digitalWrite(ledPin,LOW);
    send("f");
    Serial.println("forward");
   
  } 
  else 
  { 
    if ((xval>334 && xval<375) && (yval>330 && yval<335)) //forward(transmitter tilted forward)
    {
      digitalWrite(ledPin,HIGH);
      send("a");
       Serial.println("back");
      
    }
    if ((xval>326 && xval<328) && (yval>264 && yval<324)) //backward(transmitter tilted backward)
    {
      digitalWrite(ledPin,HIGH);
      send("l");
       Serial.println("left");
      
    }
    if ((xval>330 && xval<332) && (yval>336 && yval<391)) //left(transmitter tilted to left)
    {
      digitalWrite(ledPin,HIGH);
      send("r");
       Serial.println("right");
       
     }
     
  }
  //delay(1000);
  
}


void send(char *message)//send function definition
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}
