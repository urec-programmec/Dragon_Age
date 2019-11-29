
#include <CustomStepper.h>            // Подключаем библиотеку управления шаговым двигателем. По умолчанию настроена на двигатель 28BYJ-48-5V
CustomStepper krilo_1 (10, 11, 12, 13);
CustomStepper krilo_2 (6, 7, 8, 9);
CustomStepper fire (18, 19, 20, 21);
CustomStepper neft (14, 15, 16, 17);

int exe = 1,end_1=1,state=1,c=0,stat_fir = 1;
int open_close_1 = 32, open_close_2 = 36, fir = 34;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Ready! Send + - or .");
  krilo_1.setRPM(12);                 // Устанавливаем кол-во оборотов в минуту
  krilo_1.setSPR(4075.7728395);       // Устанавливаем кол-во шагов на полный оборот. Максимальное значение 4075.7728395
  krilo_2.setRPM(12);                 
  krilo_2.setSPR(4075.7728395);       
  fire.setRPM(12);                 
  fire.setSPR(4075.7728395);       
  neft.setRPM(12);                 
  neft.setSPR(4075.7728395);       


  pinMode(5, OUTPUT);
  digitalWrite(5,HIGH);
  pinMode(open_close_1,INPUT_PULLUP);
  pinMode(open_close_2,INPUT_PULLUP);
  pinMode(fir,INPUT_PULLUP);
    
}

void loop()
{

  

  if (!digitalRead(open_close_1)== HIGH  and state == 1  and end_1 == 1){    
    c = 1;
    state = 2;
    krilo_2.setDirection(CW);     
    krilo_2.rotate(3);
    krilo_1.setDirection(CCW);     
    krilo_1.rotate(3);
    
    digitalWrite(5,LOW);
    
  }
  if (!digitalRead(open_close_2)== HIGH and state == 2 and end_1 == 2){

    digitalWrite(5,LOW);
    krilo_2.setDirection(CW);     
    krilo_2.rotate(3);
    krilo_1.setDirection(CCW);     
    krilo_1.rotate(3);
    state = 1;
  }
  if (!digitalRead(fir)== HIGH){
    
    fire.setDirection(CW);     
    fire.rotateDegrees(440);
    exe=2;
    
  }
    
  if (!krilo_1.isDone() and !krilo_2.isDone() ){            
      krilo_2.run();  
      krilo_1.run();  
   }  
   else if (c==1){
    
    if (end_1 == 1)
    end_1=2;
    else 
    end_1=1;
    delay(3000);
    digitalWrite(5,HIGH);
   
     
   }
      
  if(!fire.isDone()){
    fire.run();
  }
  else if (exe==2){
    fire.setDirection(CCW);     
    fire.rotateDegrees(440);
    exe=1;
    neft.setDirection(CW);
    neft.rotateDegrees(140);
    stat_fir=2;
  }
  if (!neft.isDone()){
    neft.run();
  }
  else if (stat_fir == 2){
    stat_fir=1;
    neft.setDirection(CCW);
    neft.rotateDegrees(140);
  }
 
   
    
/*
  buttonState = digitalRead(30);
  if (!buttonState == HIGH){
  digitalWrite(LED_BUILTIN,HIGH);
  }
  else 
  digitalWrite(LED_BUILTIN,LOW);
  /*
  if(buttonState == HIGH){
    digitalWrite(13,HIGH);
    
    digitalWrite(12,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);
    stepper.setDirection(CCW);     
    stepper.rotate(3);  
    
  }
  else {
    digitalWrite(13,LOW);
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
  } 
  if (Serial.available())
  {
    
    char b = Serial.read();            
    if (b == '-'){
      stepper.setDirection(CCW);     
      stepper.rotate(3);  
    }      
    else if (b == '+'){
      stepper.setDirection(CW);      
      stepper.rotate(3);  
    }      
    else if (b == '.'){
      stepper.setDirection(STOP);      
    }              
  }
      
   if (!stepper.isDone()){
      
      stepper.run();  
   }
   */ 
    
}
