#define Vref 3.27 //as measured on nodeMCU 3.3v output
#define INPUTPin A0
//#define SUPPLYPin 5
#define Resolution 1023.2
#define PhPerStep 59.16 // Sensor steps per PH point
#define SensorCenter 488
#define ScaleMax 598 // Vinegar (should be Salinic Acid)
#define ScaleMin 411 // Sink declogger
#define ScaleCenter 7
#define SensorCalibration 1000
float ScaleSize = ScaleMin+ScaleMax; // or does this give the resolution in stead? probably..
int PHValue;
int sensorValue;
unsigned long int avgValue;     //Store the average value of the sensor feedback
int i=0;

void setup()
{
    Serial.begin(9600);
    pinMode(INPUTPin, INPUT);
//    pinMode(SUPPLYPin, OUTPUT);
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
    Serial.println("\n\n\n");
    Serial.print(" the PH value is: ");
    Serial.print(PHValue);
    Serial.println("° PH");
    delay(5000);

}

float CalcPH() {
    Serial.print(" ");
    Serial.print(ScaleCenter-SensorCalibration);
    Serial.print("*(");
    Serial.print(sensorValue-SensorCenter);
    Serial.print(")*");
    Serial.print(Vref/PhPerStep/Resolution);
    Serial.println(" = ");
    Serial.print(" ");
    Serial.print(ScaleCenter);
    Serial.print("-");
    Serial.print(SensorCalibration);
    Serial.print("*(");
    Serial.print(sensorValue);
    Serial.print("-");
    Serial.print(SensorCenter);
    Serial.print(")*");
    Serial.print(Vref);
    Serial.print("/");
    Serial.print(PhPerStep);
    Serial.print("/");
    Serial.print(Resolution);
    Serial.println(" = ");
    PHValue = ScaleCenter-SensorCalibration*(sensorValue-SensorCenter)*Vref/PhPerStep/Resolution;
    Serial.println(round(PHValue));//PHValue= sensorValue*(Vref/Resolution);
}
