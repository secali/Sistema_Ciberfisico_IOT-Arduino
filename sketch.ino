#include <Wire.h>
#define SLAVE_ADDRESS 0x04  
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
const byte PINTEMP=0;

struct STemperatura{
  byte pin;
  unsigned long last_ms;
  double temp;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
STemperatura sensor;

void sendData(){
  Wire.write(byte(sensor.temp));
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  Wire.begin(SLAVE_ADDRESS);
  //Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  sensor.pin=PINTEMP;
  pinMode(sensor.pin, INPUT);
  sensor.last_ms=0;
  sensor.temp=0;
}

void loop() {
  unsigned long curr_ms=millis();
  if(curr_ms - sensor.last_ms >= 5000){
    sensor.last_ms=curr_ms;

    float val=analogRead(sensor.pin);
    float va=val*(5.0/1023.0);
    float grados=(va-0.5)/0.01;
    Serial.println(grados);
    sensor.temp=grados;
    sendData();

    /*unsigned estacion;
    if(sensor.temp<15){
      estacion=3; //invierno
    
    }else if(sensor.temp>=15 && sensor.temp<20){
      estacion=2; //oto�o
      
    }else if(sensor.temp>=20 && sensor.temp<=25){
      estacion=0;   //primavera
    }else estacion=1; //verano
  
    get_s+=estacion;
    //FALTA ENVIAR LOS DATOS AL SERVIDOR */ 
  }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------