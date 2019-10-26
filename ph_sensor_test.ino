#define Vref 6.45 //as measured on nodeMCU 3.3v output
#define INPUTPin A0
//#define SUPPLYPin 16
#define Resolution 1023
#define PhPerStep 35.17
#define SensorCenter 578
#define ScaleCenter 7

float PHValue;
int sensorValue;
unsigned long int avgValue;     //Store the average value of the sensor feedback
int i=0;

void setup()
{
    Serial.begin(9600);
    pinMode(INPUTPin, INPUT);
//    pinMode(SUPPLYPin, OUTPUT);
//    analogWrite(SUPPLYPin, HIGH);
}
void loop()
{
    long sensorSum;
    int buf[10];                //buffer for read analog
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(INPUT);//Connect the PH Sensor to INPUT port
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        int temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
       avgValue=0;
 
      for(int i=2;i<8;i++)                      //take the average value of 6 center sample
      avgValue+=buf[i];
    
     sensorValue =   avgValue/6;
     
     Serial.println();
     Serial.print("Sensor Value: ");
     Serial.println(sensorValue);
//     Serial.print(" of ");
//     Serial.println(Resolution);
    CalcPH();
    Serial.print(" the PH value is: ");
    Serial.print(PHValue);
    Serial.println("° PH");
    delay(1000);

}

float CalcPH() {
//  PHValue = (sensorValue/14)/(Resolution/PhPerStep);
    Serial.print(" ");
    Serial.print(ScaleCenter-1000);
    Serial.print("*(");
    Serial.print(sensorValue-SensorCenter);
    Serial.print(")*");
    Serial.print(Vref/PhPerStep/Resolution);
    Serial.print(" = ");
    
  PHValue = ScaleCenter-1000*(sensorValue-SensorCenter)*Vref/PhPerStep/Resolution;
 Serial.print(PHValue);//PHValue= sensorValue*(Vref/Resolution);
}
