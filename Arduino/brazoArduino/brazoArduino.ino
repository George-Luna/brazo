#include <Servo.h>
#include <Stepper.h>
#define STEPS 4096
#define NUMSTEPS 100
//#define DEBUG(a) Serial.println(a);
char dato,cor,autoProceso;
Servo hombro, codo, pinza, base,mune;
int phombro, pcodo, ppinza, pbase,pmune,valor=0,vmune=0,vcodo=0,vhombro=0,vbase=1024,valorbase=0, contador=0;

Stepper myStepper(STEPS, 5, 6, 7, 8);

const int PIN_HOMBRO = 13;
const int ANG_MIN_HOMBRO=30;
const int POSICION_INICIAL_HOMBRO=70;
const int ANG_MAX_HOMBRO=130;

const int PIN_CODO = 12;
const int ANG_MIN_CODO=0;
const int POSICION_INICIAL_CODO=70;
const int ANG_MAX_CODO=120;
              
const int PIN_PINZA = 10;
const int ANG_MIN_PINZA=20;
const int POSICION_INICIAL_PINZA=60;
const int ANG_MAX_PINZA=100;


const int PIN_MUNE = 9;
const int ANG_MIN_MUNE=0;
const int POSICION_INICIAL_MUNE=80;
const int ANG_MAX_MUNE=180;


const int ANG_MIN_BASE=0;
const int POSICION_INICIAL_BASE=2048;
const int ANG_MAX_BASE=4096;


const int PASO_ANGULO = 10;

void setup()
{
  hombro.attach(PIN_HOMBRO);
  codo.attach(PIN_CODO);
  pinza.attach(PIN_PINZA);
  //base.attach(PIN_BASE);
  mune.attach(PIN_MUNE);
  inicializarServos();
   myStepper.setSpeed(5);
   pinMode(4, OUTPUT); //led rojo
   pinMode(3, OUTPUT); //led verde
   pinMode(2, OUTPUT); //buzzer pin
    pinMode(11, OUTPUT); //button
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(2), inicial, HIGH);
}

void inicializarServos(){
     // Leer posicion inicial
    phombro=hombro.read();
    pcodo=codo.read();
    ppinza=pinza.read();
    pbase=base.read();
    pmune=mune.read();
   
    //Escribir posicion inicial
    hombro.write(POSICION_INICIAL_HOMBRO);
    codo.write(POSICION_INICIAL_CODO);
    pinza.write(POSICION_INICIAL_PINZA);
    base.write(POSICION_INICIAL_BASE);
    mune.write(POSICION_INICIAL_MUNE);
}

void inicial(){
    //autoProceso='a';
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
    while(digitalRead(2) == HIGH)
    
{

    phombro=hombro.read();
    pcodo=codo.read();
    ppinza=pinza.read();
    pbase=base.read();
    pmune=mune.read();
   
    hombro.write(phombro);
    codo.write(pcodo);
    pinza.write(ppinza);
    base.write(pbase);
    mune.write(pmune);
}
 digitalWrite(4, LOW);  
 digitalWrite(3, HIGH); 
  }

void loop()
{

  if (Serial.available() > 0){
      dato=Serial.read();
      switch(dato)
      {
        //Hombro -------------------------------------------
        case 'w': 
        {
        Serial.println("Hombro");
        Serial.println(phombro);
          if((hombro.read()+PASO_ANGULO)>ANG_MAX_HOMBRO){
                Serial.println("No hago nada");
                break;
            } else {
                  int temp = hombro.read();
                  phombro=hombro.read()+PASO_ANGULO;
                  for(int i = temp;i<=phombro;i++){
                  hombro.write(i);
                  delay(15);
                  }
                  }           

          break;  
        }
        //----------------------------------posicion inicial
                case 'y': 
        {

          autoProceso='a';
          digitalWrite(3, LOW);
          hombro.write(POSICION_INICIAL_HOMBRO);
          codo.write(POSICION_INICIAL_CODO);
          pinza.write(POSICION_INICIAL_PINZA);
          mune.write(POSICION_INICIAL_MUNE);         

          break;  
        }
        case 's': 
        {
        Serial.println("Hombro");
        Serial.println(phombro);
          if((hombro.read()-PASO_ANGULO)<ANG_MIN_HOMBRO){
                Serial.println("No hago nada");
                break;
            } else {
                  int temp = hombro.read();
                  phombro=hombro.read()-PASO_ANGULO;
                  for(int i = temp;i>=phombro;i--){
                  hombro.write(i);
                  }
                  }    
              
          break;  
        }
        
    
        //-----------------------------pinza 60°
         case '2': 
        {
        Serial.println("pinza 70°");
            
            valor=60;
           
          break;  
        }
          //-----------------------------pinza 30°
         case '1': 
        {
        Serial.println("pinza 35°");
           
                        
            valor=35;
              
          break;  
        }
           //-----------------------------pinza 90°
             case '3': 
        {
        Serial.println("pinza 100°");
           
                valor=90;        
             // pinza.write(valor);
              //delay(500);
              //pinza.write(0);
            
              
          break;  
        }
         //-----------------------------muneca 30°
         case '4': 
        {
        Serial.println("muneca 30°");
           
            vmune=30;            
              
          break;  
        }
          //-----------------------------muneca 60°
         case '5': 
        {
        Serial.println("muneca 60°");
           
                        
             vmune=60;
            
              
          break;  
        }
           //-----------------------------muneca 90°
             case '6': 
        {
        Serial.println("muneca 90°");
           
                vmune=90;        
             
            
              
          break;  
        }
        //-----------------------------muneca 120°
             case '7': 
        {
        Serial.println("muneca 120°");
           
                vmune=120;        
             
            
              
          break;  
        }
        //-----------------------------muneca 150°
             case '8': 
        {
        Serial.println("muneca 150°");
          
                vmune=150;        
             
            
              
          break;  
        }
        //-----------------------------muneca 180°
             case '9': 
        {
        Serial.println("muneca 180°");
           
                vmune=180;        
             
            
              
          break;  
        }
          //-----------------------------codo 0°
         case 'j': 
        {
        Serial.println("codo 0°");
           
            vcodo=0;
           
          break;  
        }
          //-----------------------------codo 35°
         case 'k': 
        {
        Serial.println("codo 35°");
           
                        
            vcodo=35;
              
          break;  
        }
           //-----------------------------codo 70°
             case 'l': 
        {
        Serial.println("codo 70°");
          
                vcodo=70;        
             // pinza.write(valor);
              //delay(500);
              //pinza.write(0);
            
              
          break;  
        }
  //-----------------------------hombro 70°
         case 'f': 
        {
        Serial.println("hombro 70°");

            vhombro=70;
           
          break;  
        }
          //-----------------------------hombro 100°
         case 'g': 
        {
        Serial.println("hombro 100°");
    
                        
            vhombro=100;
              
          break;  
        }
           //-----------------------------hombro 120°
             case 'h': 
        {
        Serial.println("hombro 120°");
            // Serial.print(int(dato));
            // int value=int(dato);
                vhombro=120;        
             // pinza.write(valor);
              //delay(500);
              //pinza.write(0);
            
              
          break;  
        }

//170.67->30° 256->45°
 //-----------------------------base 30°
         case 'z': 
        {
            Serial.println("base 30°");   
            valorbase=170;            
              
          break;  
        }
          //-----------------------------base 60°
         case 'x': 
        {
        Serial.println("base 60°");   
                        
             valorbase=341;
            
              
          break;  
        }
           //-----------------------------base 90°
             case 'c': 
        {
    Serial.println("base 90°");   
                valorbase=512;        
             
            
              
          break;  
        }
        //-----------------------------base 120°
             case 'v': 
        {
        Serial.println("base 120°");   
                valorbase=682;        
             
            
              
          break;  
        }
        //-----------------------------base 150°
             case 'b': 
        {
       Serial.println("base 150°");   
                valorbase=853;        
             
            
              
          break;  
        }
        //-----------------------------base 180°
             case 'r': 
        {
        Serial.println("base 180°");   
                valorbase=1024;        
             
            
              
          break;  
        }


      case 'q': 
        {
        Serial.println("Codo");
        Serial.println(pcodo);
          if((codo.read()+PASO_ANGULO)>ANG_MAX_CODO){
                Serial.println("No hago nada");
                break;
            } else {
                  int temp = codo.read();
                  pcodo=codo.read()+PASO_ANGULO;
                  for(int i = temp;i<=pcodo;i++){
                  codo.write(i);
                  delay(15);
                  }
                  }           

          break;  
        }
        case 'e':
        {
          Serial.println("Codo");
          Serial.println(pcodo);
          if((codo.read()-PASO_ANGULO)<ANG_MIN_CODO){
                  Serial.println("No hago nada");
                  break;
                } else {
                  int temp = codo.read();
                  pcodo=codo.read()-PASO_ANGULO;
                  for(int i = temp;i>=pcodo;i--){
                  codo.write(i);
                  delay(15);
                  }
                  
                  }
              
          break;  
        }
        // Pinza -------------------------------------------
        case 'p': 
        {
        Serial.println("Pinsa");
        Serial.println(ppinza);
          if((pinza.read()+PASO_ANGULO)>ANG_MAX_PINZA){
                Serial.println("No hago nada");
                break;
            } else {
                  int temp = pinza.read();
                  ppinza=pinza.read()+PASO_ANGULO;
                  for(int i = temp;i<=ppinza;i++){
                  pinza.write(i);
                  delay(15);
                  }
                  
                  }           

          break;  
        }    
        case 'o': 
        {
           Serial.println("Pinsa");
        Serial.println(ppinza);
          if((pinza.read()-PASO_ANGULO)<ANG_MIN_PINZA){
                  Serial.println("No hago nada");
                  break;
                } else {
                  int temp = pinza.read();
                  ppinza=pinza.read()-PASO_ANGULO;
                  for(int i = temp;i>=ppinza;i--){
                  pinza.write(i);
                  delay(15);
                  }
                  }
              
          break;  
        }

         // Muneca-------------------------------------------
        case 'm': 
        {
        Serial.println("Muneca");
        Serial.println(pmune);
          if((mune.read()+PASO_ANGULO)>ANG_MAX_MUNE){
                Serial.println("No hago nada");
                break;
            } else {
                  int temp = mune.read();
                  pmune=mune.read()+PASO_ANGULO;
                  for(int i = temp;i<=pmune;i++){
                  mune.write(i);
                  delay(15);
                  }
                  }           

          break;  
        }    
        case 'n': 
        {
          Serial.println("Muneca");
        Serial.println(pmune);
          if((mune.read()-PASO_ANGULO)<ANG_MIN_MUNE){
                  Serial.println("No hago nada");
                  break;
                } else {
                  int temp = mune.read();
                  pmune=mune.read()-PASO_ANGULO;
                  for(int i = temp;i>=pmune;i--){
                  mune.write(i);
                  delay(15);
                  }
                  }
              
          break;  
        }
      
        //Base -------------------------------------------
        case 'a': 
        {
        Serial.println("Base mov izq");
              int valorPos=200;

             for(int i=0;i<=valor;i++){
             myStepper.step(i);
              delay(50);
               }          

          break;  
        } 
        case 'd': 
        {
          Serial.println("Base mov derecha");
         
             int valor=-200;

             for(int i=0;i>=valor;i--){
             myStepper.step(i);
              delay(50);
                 }
              
          break;  
        }



        case 'i': 
        {
          delay(100);
          autoProceso='y'; 
          
              
//              
          break;  
        }

        
         //Parar Robot -------------------------------------------

        default: {
          Serial.println("Caracter no valido");
          break;
        }
      }
  }
      if (autoProceso == 'y'){
         digitalWrite(3, HIGH);
         for (int i = hombro.read(); i<=vhombro; i++)
            {
              hombro.write(i);
              delay(50);
            }
             delay(500);
           
           for (int i = codo.read(); i>=vcodo; i--)
            {
              codo.write(i);
              delay(50);

            }
              delay(500);

          for (int i = pinza.read(); i<=valor; i++)
            {
              pinza.write(i);
              delay(50);
            }
              delay(2000);

            for (int i = pinza.read(); i>=ANG_MIN_PINZA; i--)
            {
              pinza.write(i);
              delay(50);
            }
              delay(500);

           for (int i = codo.read(); i<=POSICION_INICIAL_CODO; i++)
            {
              codo.write(i);
              delay(50);
            }
              delay(500);

           for (int i = hombro.read(); i>=POSICION_INICIAL_HOMBRO; i--)
            {
              hombro.write(i);
              delay(50);
            }
              delay(500);

          //AQUI LA BASE
          delay(2000);


            for (int i = hombro.read(); i<=vhombro; i++)
            {
              hombro.write(i);
              delay(50);
            }
              delay(500);
              
           for (int i = codo.read(); i>=vcodo; i--)
            {
              codo.write(i);
              delay(50);
            }
              delay(500);

           for (int i = pinza.read(); i<=valor; i++)
            {
              pinza.write(i);
              delay(50);
            }
              delay(2000);


      //AQUI LA BASE
          delay(2000);


          for (int i = codo.read(); i<=POSICION_INICIAL_CODO; i++)
            {
              codo.write(i);
              delay(50);
            }
              delay(500);

           for (int i = hombro.read(); i>=POSICION_INICIAL_HOMBRO; i--)
            {
              hombro.write(i);
              delay(50);
            }
                    //AQUI LA BASE
          delay(2000);

               digitalWrite(3, LOW);
        }

}
