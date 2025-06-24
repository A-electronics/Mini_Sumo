/*
 * Minisumo chasis Pololu con orugas
 *Información sensores: 
Sensor de linea QRE 
blanco==0
Negro/aire==1
sensor de distancia modulo IR
Detección en 0
sin objeto ==1
_________
Revisar tatami (fondo negro se detecta 1)para que se mantega activo hasta que salga
si es blanco.
*/

//Declarar pines:
uint8_t M1=4;
uint8_t PWM1=5;
uint8_t PWM2=6;
uint8_t M2=7;
uint8_t front=3;      //sensor IR
uint8_t left=8;       //sensor IR
uint8_t Dir= 0;       // para saber hacia donde giraba; neutral 0,izq. 1 y der. 2
uint8_t Push=180;     //para aumentar velocidad si objetivo persiste
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

    if(digitalRead(Line)==1){
      if(digitalRead(front)==0 && digitalRead(left)==1){

      Avanzar(Push,Push);
      delay(25);
      Push +=10;
      if(Push > 230){Push=230;}
      //Dir=0;
      }

      if(digitalRead(left)==0 && digitalRead(front)==1){      
      do{
        GiroI(165,165);
        }while(digitalRead(front)==1);
        Push=180;
      }

      if(digitalRead(left)==1 && digitalRead(front)==1){      
      do{
        GiroD(165,165);
        }while(digitalRead(front)==1 && digitalRead(left)==1);
        delay(300);
        Push=180;
      }      

      if(digitalRead(left)==0 && digitalRead(front)==0){      
        Stop();
        Push=180;       
      }
    }//detección tatami

    else {
      Reversa(170,170);
      delay(680);
    }
      
      }//loop

//**************************************************
//*****************Subrutinas:**********************
//**************************************************
void Avanzar(uint8_t Speed1, uint8_t Speed2){
  //Serial.println("Attack");
  //delay(100);     //solo para serial
  digitalWrite(M1,LOW);
  digitalWrite(M2,LOW);
  analogWrite(PWM1,Speed1);
  analogWrite(PWM2,Speed2);
  }

void Reversa(uint8_t Speed1, uint8_t Speed2){
  digitalWrite(M1,HIGH);
  digitalWrite(M2,HIGH);
  analogWrite(PWM1,Speed1);
  analogWrite(PWM2,Speed2);
  }

//girar derecha
void GiroD(uint8_t Speed1, uint8_t Speed2){
  //Serial.println("Right");
  //delay(100);
  digitalWrite(M1,LOW);
  digitalWrite(M2,HIGH);
  analogWrite(PWM1,Speed1);
  analogWrite(PWM2,Speed2);  
}


//girar izquierda
void GiroI(uint8_t Speed1, uint8_t Speed2){
  //Serial.println("Left");
  //delay(100);
  digitalWrite(M1,HIGH);
  digitalWrite(M2,LOW);
  analogWrite(PWM1,Speed1);
  analogWrite(PWM2,Speed2);  
}

void Stop (){
  //Serial.println("Stop");
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
//    if(digitalRead(left)==0){
//      Serial.println("left");
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
