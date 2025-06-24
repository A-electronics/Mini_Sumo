/*
 * Minisumo chasis impreso
 *Información sensores: 
Sensor de linea QRE 
blanco==0
Negro/aire==1
sensor de distancia Sharp 
GP2Y0D810Z0F 10 cm.
Detección en 0
sin objeto ==1
Dos sensores al frente y 1 a la derechada.
_________
Revisar tatami (fondo negro se detecta 1)para que se mantega activo;
si es blanco hace reversa.
*/

//Declarar pines:
uint8_t M1=4;
uint8_t PWM1=5;
uint8_t PWM2=6;
uint8_t M2=7;
uint8_t front1=3;      //sensor IR
uint8_t front2=8;       //sensor IR
uint8_t right=9;       //sensor IR
uint8_t Dir= 0;       // para saber hacia donde giraba; neutral 0,izq. 1 y der. 2
uint8_t Push=125;     //para aumentar velocidad si objetivo persiste
uint8_t Line=2;       //Pin de sensor línea en fondo negro debe trabajar y abortar en blanco

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(M1,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(M2,OUTPUT);
  delay(10);
  digitalWrite(M1,LOW);
  digitalWrite(PWM1,LOW);
  digitalWrite(PWM2,LOW);
  digitalWrite(M2,LOW);
  Serial.println("Inicio");
  delay(3000);

}

void loop() {
  // put your main code here, to run repeatedly:

    if(digitalRead(Line)== HIGH){
      if((digitalRead(front1)==0 || digitalRead(front2)==0) && digitalRead(right)==1 && digitalRead(Line)== 1){
    //if((digitalRead(front1)==0 || digitalRead(front2)==0) && digitalRead(right)==1){
      Avanzar(Push,Push);
      delay(25);
      Push +=10;
      if(Push > 230){Push=230;}
      //Dir=0;
      }

      if(digitalRead(right)==0 && digitalRead(front1)==1 && digitalRead(front2)==1){      
      do{
        GiroD(85,93);
        delay(25);
        GiroD(0,0);
        delay(3);        
        }while((digitalRead(front1)==1 && digitalRead(front2)==1) && digitalRead(Line)== 1);
        //}while((digitalRead(front1)==1 && digitalRead(front2)==1));
        Push=125;
      }

      if(digitalRead(right)==1 && digitalRead(front1)==1 && digitalRead(front2)==1 && digitalRead(Line)== 1){      
      //if(digitalRead(right)==1 && digitalRead(front1)==1 && digitalRead(front2)==1){      
      do{
        GiroI(85,93);
        delay(25);
        GiroI(0,0);
        delay(3);        
        }while(digitalRead(front1)==1 && digitalRead(front2)==1 && digitalRead(right)==1);
        delay(300);
        Push=125;
      }      

      if(digitalRead(right)==0 && digitalRead(front1)==0 && digitalRead(front2)==0){      
        Stop();
        Push=125;       
      }
    }//detección tatami

    else {
      Reversa(130,130);
      Push=125;
      delay(680);
    }
      
      }//loop

//**************************************************
//*****************Subrutinas:**********************
//**************************************************
void Avanzar(uint8_t Speed1, uint8_t Speed2){
  Serial.println("Attack");
  //delay(100);     //solo para serial
  digitalWrite(M1,LOW);
  digitalWrite(M2,LOW);
  analogWrite(PWM1,Speed1);
  analogWrite(PWM2,Speed2);
  }

void Reversa(uint8_t Speed1, uint8_t Speed2){
  Serial.println("Reverse");
  digitalWrite(M1,HIGH);
  digitalWrite(M2,HIGH);
  analogWrite(PWM1,Speed1);
  analogWrite(PWM2,Speed2);
  }

//girar derecha
void GiroD(uint8_t Speed1, uint8_t Speed2){
  Serial.println("Right");
  //delay(100);
  digitalWrite(M1,HIGH);
  digitalWrite(M2,LOW);
  analogWrite(PWM1,Speed1);
  analogWrite(PWM2,Speed2);  
}


//girar izquierda
void GiroI(uint8_t Speed1, uint8_t Speed2){
  Serial.println("left");
  //delay(100);
  digitalWrite(M1,LOW);
  digitalWrite(M2,HIGH);
  analogWrite(PWM1,Speed1);
  analogWrite(PWM2,Speed2);  
}

void Stop (){
  Serial.println("Stop");
  delay(100);
  digitalWrite(M1,LOW);
  digitalWrite(M2,LOW);
  analogWrite(PWM1,0);
  analogWrite(PWM2,0);    
  }



  //para leer estado de sensores
//      if(digitalRead(front)==0){
//      Serial.println("front");
//      delay(400);      
//      }
//
//    if(digitalRead(right)==0){
//      Serial.println("right");
//      delay(400);      
//      }

//test de motores y polaridad:
//      Avanzar(150,150);
//      delay(1000);
//      Stop();
//      delay(1000);      
//      GiroD(150,150);
//      delay(1000);
//      Stop();
//      delay(1000);
