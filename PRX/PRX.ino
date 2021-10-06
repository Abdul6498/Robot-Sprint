#define ENA1 2
#define ENB1 3
#define ENA2 4
#define ENB2 5
#define INA1 22
#define INB1 23
#define INA2 26
#define INB2 27
#define INA3 30
#define INB3 31
#define INA4 34
#define INB4 35
#define kick 9
int dutycycleA = 85;
int dutycycleB = 50;    //slow motor use high rpm
int dutycycleC = 50;
int dutycycleD = 85;    //slow motor use high rpm


#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p receiver(7,8);//CSN,CE

void setup(){
  pinMode(ENA1,OUTPUT);
  pinMode(ENB1,OUTPUT);
  pinMode(ENA2,OUTPUT);
  pinMode(ENB2,OUTPUT);
  pinMode(INA1, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(INB2, OUTPUT);
  pinMode(INA3, OUTPUT);
  pinMode(INB3, OUTPUT);
  pinMode(INA4, OUTPUT);
  pinMode(INB4, OUTPUT);
  pinMode(kick, OUTPUT);
  delay(150);
  Serial.begin(115200);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(90);
  receiver.RXaddress("Hello");
  receiver.init();
}

char character;
void loop(){ 
  if(receiver.available()){
    receiver.read();
    receiver.rxPL(character);
    Serial.print(character);
    Serial.println();   
     if(character == 'w')
     {
    Serial.println("Move Forward");
    move_forward();
     }
    
    else if(character == 's')
    {
    Serial.println("Move BACK");
       move_back();
    }
    
    else if(character == 'a')
    {
      Serial.println("Move left");
    move_left();
    }
    
    else if(character == 'd')
    {
      Serial.println("Move Right");
    move_right();
    }
    
    else if(character == 'j')
    {
      Serial.println("Move anticlkwise");
    move_anticlkwise();
    }
    
    else if(character == 'l')
    {
    Serial.println("Move Clockwise");
    move_clkwise();
    }
    
    else if(character == 'e')
    {
      Serial.println("Move 45*");
    move_forward45();
    }
    
    else if(character == 'q')
    {
      Serial.println("Move 135*");
    move_forward135();
    }
    
    else if(character == 'c')
    {
      Serial.println("Move 45*back");
    move_back315();
    }
    else if(character == 'z')
    {
      Serial.println("Move 135*back");
    move_back225();
    }
    
    else if(character == 'k')
    {
      Serial.println("Kick ball");
    kick_ball();
    }
    
    else if(character == 'm')
    {
    Serial.println("STOP KICK");
    stop_kick();
    }
    
    else if(character == 'b' || 'x')
    {
      Serial.println("Break current logic");
    stop_robot();
    }
  } 
}

//    MOTORS NAME AND place
//          KICK
//        C~~~~~~~~D
//       !!        !!
//       !!        !!
//        A~~~~~~~~B
//1 for clockwise 2 for anti clockwise
void move_forward()
{
  motorA(2 , dutycycleA); 
  motorB(1 , dutycycleA);
  motorC(2 , dutycycleA);
  motorD(1 , dutycycleA);        
}

void move_back()
{
  motorA(1 , dutycycleA); 
  motorB(2 , dutycycleB);
  motorC(1 , dutycycleC);
  motorD(2 , dutycycleD);          
}

void move_left()
{
  motorA(2 , dutycycleA);  
  motorB(2 , dutycycleB);
  motorC(1 , dutycycleC);
  motorD(1 , dutycycleD);        

}

void move_right()
{
  motorA(1 , dutycycleA);
  motorB(1 , dutycycleB);
  motorC(2 , dutycycleC);
  motorD(2 , dutycycleD);        
}

void move_forward45()
{
  motorA(3 , 00);
  motorB(1 , dutycycleB);
  motorC(2 , dutycycleC);
  motorD(3 , 00);        

}

void move_forward135()
{
  motorA(2 , dutycycleA);
  motorB(3 , 00);
  motorC(3 , 00);
  motorD(1 , dutycycleD);        
}

void move_back225()
{
  motorA(3 , 00);
  motorB(2 , dutycycleB);
  motorC(1 , dutycycleC);
  motorD(3 , 00);          
}

void move_back315()
{
  motorA(1 , dutycycleA);
  motorB(3 , 00);
  motorC(3 , 00);
  motorD(2 , dutycycleD);        
}

void stop_robot()
{
  motorA(3 , 00);
  motorB(3 , 00);
  motorC(3 , 00);
  motorD(3 , 00);          
}

void move_clkwise()
{
  motorA(1 , dutycycleA);
  motorB(1 , dutycycleB);
  motorC(1 , dutycycleC);
  motorD(1 , dutycycleD);        
}

void move_anticlkwise()
{
  motorA(2 , dutycycleA);
  motorB(2 , dutycycleB);
  motorC(2 , dutycycleC);
  motorD(2 , dutycycleD);        
}

void kick_ball()
{
  digitalWrite(kick,HIGH);
}

void stop_kick()
{
  digitalWrite(kick,LOW);
}

void motorA(int mode, int percent)
{
  
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int duty = map(percent, 0, 100, 0, 255);
  
  switch(mode)
  {
       case 1:  //turn clockwise
      //setting IN1 high connects motor lead 1 to +voltage
      digitalWrite(INA1, HIGH);   
      
      //setting IN2 low connects motor lead 2 to ground
      digitalWrite(INB1, LOW);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENA1, duty);  
      
      break;
      
    case 2:  //turn counter-clockwise
      //setting IN1 low connects motor lead 1 to ground
      digitalWrite(INA1, LOW);   
      
      //setting IN2 high connects motor lead 2 to +voltage
      digitalWrite(INB1, HIGH);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENA1, duty);  
      
      break;
      
    case 3:  //brake motor
      //setting IN1 low connects motor lead 1 to ground
      digitalWrite(INA1, LOW);   
      
      //setting IN2 high connects motor lead 2 to ground
      digitalWrite(INB1, LOW);  
      
      //use pwm to control motor braking power 
      //through enable pin
      analogWrite(ENA1, duty);  
      
      break;
  }
}
//**********************************************************


//******************   Motor B control   *******************
  void motorB(int mode, int percent)
{
  
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int duty = map(percent, 0, 100, 0, 255);
  
  switch(mode)
  {
    case 1:  //turn clockwise
      //setting IN3 high connect 
      //setting IN1 high connects motor lead 1 to +voltage
      digitalWrite(INA2, HIGH);   
      
      //setting IN2 low connects motor lead 2 to ground
      digitalWrite(INB2, LOW);
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENB1, duty);  
      
      break;
      
    case 2:  //turn counter-clockwise
      //setting IN3 low connects motor lead 1 to ground
      digitalWrite(INA2, LOW);   
      
      //setting IN4 high connects motor lead 2 to +voltage
      digitalWrite(INB2, HIGH);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENB1, duty);  
      
      break;
      
    case 3:  //brake motor
      //setting IN3 low connects motor lead 1 to ground
      digitalWrite(INA2, LOW);   
      
      //setting IN4 high connects motor lead 2 to ground
      digitalWrite(INB2, LOW);  
      
      //use pwm to control motor braking power 
      //through enable pin
      analogWrite(ENB1, duty);  
      
      break;
  }
}
//**********************************************************


//******************   Motor C control   *******************
  void motorC(int mode, int percent)
{
  
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int duty = map(percent, 0, 100, 0, 255);
  
  switch(mode)
  {
    case 1:  //turn clockwise
      //setting IN3 high connect 
      //setting IN1 high connects motor lead 1 to +voltage
      digitalWrite(INA3, HIGH);   
      
      //setting IN2 low connects motor lead 2 to ground
      digitalWrite(INB3, LOW);
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENA2, duty);  
      
      break;
      
    case 2:  //turn counter-clockwise
      //setting IN3 low connects motor lead 1 to ground
      digitalWrite(INA3, LOW);   
      
      //setting IN4 high connects motor lead 2 to +voltage
      digitalWrite(INB3, HIGH);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENA2, duty);  
      
      break;
      
    case 3:  //brake motor
      //setting IN3 low connects motor lead 1 to ground
      digitalWrite(INA3, LOW);   
      
      //setting IN4 high connects motor lead 2 to ground
      digitalWrite(INB3, LOW);  
      
      //use pwm to control motor braking power 
      //through enable pin
      analogWrite(ENA2, duty);  
      
      break;
  }
}
//**********************************************************


//******************   Motor D control   *******************
  void motorD(int mode, int percent)
{
  
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int duty = map(percent, 0, 100, 0, 255);
  
  switch(mode)
  {
    case 1:  //turn clockwise
      //setting IN3 high connect 
      //setting IN1 high connects motor lead 1 to +voltage
      digitalWrite(INA4, HIGH);   
      
      //setting IN2 low connects motor lead 2 to ground
      digitalWrite(INB4, LOW);
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENB2, duty);  
      
      break;
      
    case 2:  //turn counter-clockwise
      //setting IN3 low connects motor lead 1 to ground
      digitalWrite(INA4, LOW);   
      
      //setting IN4 high connects motor lead 2 to +voltage
      digitalWrite(INB4, HIGH);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENB2, duty);  
      
      break;
      
    case 3:  //brake motor
      //setting IN3 low connects motor lead 1 to ground
      digitalWrite(INA4, LOW);   
      
      //setting IN4 high connects motor lead 2 to ground
      digitalWrite(INB4, LOW);  
      
      //use pwm to control motor braking power 
      //through enable pin
      analogWrite(ENB2, duty);  
      
      break;
  }
}

