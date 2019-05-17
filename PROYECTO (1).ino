/*
FRECUENCIMETRO

 Este frecuencímetro puede leer frecuencias de 1Hz a 3Khz.
 
 El error puede rondar el +/- 1Hz.

 Con respecto al supresor de sonido, el arduino tiene un delay natural en torno a 35ms por tanto con ese procesamiento tan lento
 el conseguir una "cancelación" perfecta del sonido en muy difícil.

 Muestra las lecturas a través del puerto serie a intervalos de 1 segundo.
 

CONEXIONADO

 El pin analógico CERO, es el pin de entrada de frecuencias. 
 

*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>



LiquidCrystal_I2C lcd(0x27, 16, 2);
long rango=2; // este es el rango por el que se disparará la salida 2 y pasa a estado lógico 1
long ultimamedicion; // contiene el valor de la última medición que disparó a lógico 1, la salida 2
int ciclo=0; // 1=alto 0=bajo
int cambiodeciclo=0;
int picodetension;
int valledetension=1023;
long contadorvisualizacion;
long contadorciclo;
const int pinZumbador = 13;
int i;
//int N=0;
//int Nf;

void setup() {
 //Inicializamos la pantalla lcd
// lcd.begin();
 //Mensaje en el lcd
 lcd.backlight();
 lcd.setCursor(0,0);
 lcd.print("Detectando freq");
 lcd.setCursor(0,1);
 lcd.print("Hz= ");

 Serial.begin(9600);
 pinMode(A0, INPUT); // Pin analógico 0 como pin de lectura de datos.
}

void loop() {
 
 long sensorValue = analogRead(A0); // Se vuelca a la varible sensorValue el valor de la tensión medida por el pin 0 analógico
 
   if (micros()>contadorvisualizacion+1000000) // Muestra por el puerto serie los resultados, transcurrido un segundo en el if se expresa en ms
   
   {
     
        // AQUÍ SE IMPRIME EN EL PUERTO SERIE LOS RESULTADOS, CICLOS CONTADOS = HERCIOS

        //Serial.print(" Hz=");
        Serial.println(contadorciclo);
        /*if(contadorciclo==0)
        {
              noTone(pinZumbador);
        }
        Nf=N+contadorciclo;
        if(Nf==2*N)
        {
              delay((1/contadorciclo)/2);
              tone(pinZumbador, contadorciclo);
       }
       else
       {
          noTone (pinZumbador);
       }
   */
        //REALIZAMOS UNA SUPRESIÓN DE SONIDO A 1000Hz
        if(contadorciclo==1000)
        {
          lcd.setCursor (0,0);
          lcd.print("Anulando freq...");
          lcd.setCursor(0,1);
          lcd.print("Desfasando 180º");
          for(i=0;i<10;i=i++){
          delayMicroseconds(((1/contadorciclo)/2)*1000 + (i*100));
          tone(pinZumbador, contadorciclo);
          unsigned int sample;
          unsigned long startMillis= millis();
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
   unsigned int peakToPeak=1024;
            while (peakToPeak>50)
          {
       sample = analogRead(A0);
      if (sample < 1024)
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // Actualizar máximo
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // Actualizar mínimo
         }
      }
      peakToPeak = signalMax - signalMin;
   }
//   unsigned int peakToPeak = signalMax - signalMin;
  
          }
        }
        else{
          noTone(pinZumbador);
        }
        
        lcd.setCursor(5,1);
        lcd.print("    ");//SOBREESCRIBE EL DATO ANTERIOR CON ESPACIOS EN BLANCO
        lcd.setCursor(5,1);
        lcd.print(contadorciclo);
        rango=(2+((picodetension-valledetension)/5)); // SE CALCULA EL RANGO MÁS ADECUADO PARA LA SEÑAL, CON EL FIN, DE REDUCIR ERRORES EN SEÑALES CON RUIDO DE FONDO
        contadorvisualizacion=micros();//SE ASIGNA A LA VARIABLE CONTADORVISUALIZACIÓN EL TIEMPO EN MICROSENGUNDOS QUE LLEVA EL PROGRAMA EN EJECUCIÓN
        picodetension=sensorValue;//SE ASIGNA A LA VARIABLE PICODETENSIÓN EL VALOR DE LA TENSIÒN LEIDA POR EL PUERTO ANALÓGICO CERO
        valledetension=sensorValue;//SE ASIGNA A LA VALLEDETENSION EL VALOR DE LA TENSIÒN LEIDA POR EL PUERTO ANALÓGICO CERO
        contadorciclo=0; // SE PONE A CERO LOS CICLOS CONTADOS O HERCIOS.
      
   }



 if (sensorValue >= ( ultimamedicion+rango) ) // La salida 2 pasa a 1 logico si la tensión medida en la entrada analógica 0 es mayor que la anterior lectura + latensión de RANGO

 {

   ultimamedicion = sensorValue;  // SE ASIGANA A LA VARIABLE ULTIMAMEDICION EL VALOR LEIDO POR LA ENTRADA ANALÓGICA CERO 
   ciclo=1;
   
   if (sensorValue>picodetension) // SI LA TENSIÓN MEDIDA POR LA ENTRADA CERO, ES LA MAYOR DETECTADA, SE ASIGNA A LA VARIABLE PICODETENSIÓN EL VALOR LEYDO POR AL ENTRADA CERO ANALÓGICA
   
   {
   picodetension=sensorValue; // SE ASIGNA EL VALOR LEYDO POR LA ENTRADA CERO ANALÓGICA A LA VARIABLE PICODETENSIÓN.
   }
   
 }
   

 
 if (sensorValue <= ( ultimamedicion-rango))  // La salida 2 pasa a 1 lógico si la tensión medida en la entrada analógica 0 es menor que la anterior lectura - la tensión de RANGO

 {

   ultimamedicion = sensorValue; // SE ASIGNA A LA VARIABLE ULTIMAMEDICIÓN LA LECTURA MEDIDA POR EL PUERTO ANALÓGICO CERO
   ciclo=0; // EL CICLO SE PONE A CERO, ES DECIR, QUE EL VOLTAJE EMPIEZA A BAJAR DESDE EL PICO DE TENSIÓN MÁS ALTA
   
   if (sensorValue<valledetension) // SE CUMPLE LA CONDICIÓN SI LA TENSIÓN DETECTADA POR EL PUERTO ANALÓGICO CERO ES MENOR QUE LA CONTENIDA EN LA VARIABLE VALLEDETENSIÓN
   {
   valledetension=sensorValue; //Se asigna a la variable valledetensión el valor medido por la entrada analógica cero
   }
   
 }
   
 
if (ciclo==1 && cambiodeciclo==0)
   
   {
     cambiodeciclo=1;
     contadorciclo++;
   }
   
if (ciclo==0 && cambiodeciclo==1)
   
   {
     cambiodeciclo=0;
   }
     
}
