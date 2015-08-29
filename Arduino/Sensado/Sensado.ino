long lonRango = 2; // este es el rongo por el que se disparará la salida 2 y pasa a estado lógico 1
long ultimamedicion; // contiene el valor de la última medición que disparó a lógico 1, la salida 2
int ciclo = 0; // 1=alto 0=bajo
int cambiodeciclo = 0;
int picodetension;
int valledetension = 1023;
double Tiempo1;
double Tiempo2;
long contadorciclo;
bool imprimir = false;
int I;
#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 7, 5, 4, 3, 2);
void setup() {
  I = 0;
  Serial.begin(9600);
  pinMode(A1, INPUT); // Se establece el pin analógico 1 como pin de lectura de datos.
}

void loop() {

  long sensorValue = analogRead(A1); // Se vuelca a la varibla sensorValue el valor de la tensión medida por el pin 0 analógico

  if (micros() > Tiempo2 + 1000000 && imprimir == true) // Muestra por el puerto serie los resultados, transcurrido un segundo
  {
    Tiempo2 = micros()-1000000; //SE ASIGNA A LA VARIABLE CONTADORVISUALIZACIÓN EL TIEMPO EN MICROSENGUNDOS QUE LLEVA EL PROGRAMA EN EJECUCIÓN
    // AQUÍ SE IMPRIME EN EL PUERTO SERIE LOS RESULTADOS
    lcd.clear();
    lcd.print("FQ:");
    lcd.print(contadorciclo/((Tiempo2 - Tiempo1)/1000000));
    lcd.print("CC:");
    lcd.print(contadorciclo);
    lcd.print(" SV:");
    lcd.print(sensorValue);
    //    lcd.print(" R:");
    //    lcd.print(lonRango);    
    lcd.print(" M:");
    lcd.print(micros());

    //picodetension = sensorValue; //SE ASIGNA A LA VARIABLE PICODETENSIÓN EL VALOR DE LA TENSIÒN LEIDA POR EL PUERTO ANALÓGICO CERO
    //valledetension = sensorValue; //SE ASIGNA A LA VALLEDETENSION EL VALOR DE LA TENSIÒN LEIDA POR EL PUERTO ANALÓGICO CERO
    contadorciclo = 0; // SE PONE A CERO LOS CICLOS CONTADOS O HERCIOS.
    imprimir = false;
    //Tiempo1 = sensorValue; //Se comenta esta línea por que, aparentemente, no sirve para nada.
    lonRango = (2 + ((picodetension - valledetension) / 50)); // SE CALCULA EL GANGO MÁS ADECUADO PARA LA SEÑAL, CON EL FIN, DE REDUCIR ERRORES EN SEÑALES CON RUIDO DE FONDO
    Tiempo1 = 0;
    Tiempo2 = 0;
  }

  if (sensorValue >= ( ultimamedicion + lonRango) ) // La salida 2 pasa a 1 logico si la tensión medida en la entrada analógica 1 es mayor que la anterior lectura + latensión de lonRango
  {
    imprimir = true;
    lcd.clear();
    /*
    lcd.print("R:");
     lcd.print(lonRango);
     lcd.print(" P:");
     lcd.print(picodetension);
     lcd.print(" V:");
     lcd.print(valledetension);
     */
    lcd.print("Sensando");
    ultimamedicion = sensorValue;  // SE ASIGANA A LA VARIABLE ULTIMAMEDICION EL VALOR LEIDO POR LA ENTRADA ANALÓGICA CERO
    ciclo = 1;

    if (sensorValue > picodetension) // SI LA TENSIÓN MEDIDA POR LA ENTRADA CERO, ES LA MAYOR DETECTADA, SE ASIGNA A LA VARIABLE PICODETENSIÓN EL VALOR LEYDO POR AL ENTRADA CERO ANALÓGICA
    {
      picodetension = sensorValue; // SE ASIGNA EL VALOR LEiDO POR LA ENTRADA CERO ANALÓGICA A LA VARIABLE PICODETENSIÓN.
    }

  }



  if (sensorValue <= ( ultimamedicion - lonRango)) // La salida 2 pasa a 1 lógico si la tensión medida en la entrada analógica 0 es menor que la anterior lectura - la tensión de lonRango

  {
    imprimir = true;
    lcd.clear();
    /*
    lcd.print("R:");
     lcd.print(lonRango);
     lcd.print(" P:");
     lcd.print(picodetension);
     lcd.print(" V:");
     lcd.print(valledetension);
     */
    lcd.print("Sensando");
    ultimamedicion = sensorValue; // SE ASIGNA A LA VARIABLE ULTIMAMEDICIÓN LA LECTURA MEDIDA POR EL PUERTO ANALÓGICO CERO
    ciclo = 0; // EL CICLO SE PONE A CERO, ES DECIR, QUE EL VOLTAJE EMPIEZA A BAJAR DESDE EL PICO DE TENSIÓN MÁS ALTA

    if (sensorValue <= valledetension) // SE CUMPLE LA CONDICIÓN SI LA TENSIÓN DETECTADA POR EL PUERTO ANALÓGICO CERO ES MENOR QUE LA CONTENIDA EN LA VARIABLE VALLEDETENSIÓN
    {
      valledetension = sensorValue; //Se asigna a la variable valledetensión el valor medido por la entrada analógica cero
    }

  }


  if (ciclo == 1 && cambiodeciclo == 0)

  {
    cambiodeciclo = 1;
    contadorciclo++;
    if (Tiempo1 == 0)
    {
      Tiempo1 = micros(); 
    }
    Tiempo2 = micros();

    I++;
  }

  if (ciclo == 0 && cambiodeciclo == 1)

  {
    cambiodeciclo = 0;
  }


}


