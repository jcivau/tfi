/*
 * Mediciones de humedad
 * No regue en un día = +-880
 * Ni bien termino de regar baja a +-883 con aspersor; bajo a 800 despues de un largo tiempo.
 * No regue dos días, Chopi bajo a 776. Se visualiza humeda la tierra. Marte marco 788.
 * Altura Planta = Sin nada 55cm.
 * Tallo de 3cm de Rucula = 43cm. (Nose si lo detecta.)
 */

//LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// ----- Temperaura y humedad -----
#include "DHT.h" // Para sensor de temperatura y humedad
#define DHTTYPE DHT22

const int DHTPin = 2;     // Conectado a Digital 2 "Amarillo"
DHT dht(DHTPin, DHTTYPE);

// ----- Varios -----
int ledAzul = 11; // ENCHUFO led
float vuelta = 300000; // Cada cuanto se ejecuta el código; 1000 = 1s
int lecturas = 0;


// ----- Humedad Suelo -----
// En lugar de alimentar el sensor a través de los pines de 3.3V o 5V,
// usaremos un pin digital para alimentar el sensor. Esto puede
// evitar la corrosión del sensor cuando se encuentra en el suelo.

int soilPin = A0;   // ENCHUFO SIGNAL ANALOGICO "Blanco"
int soilPower = 8;  // ENCHUFO DIGITAL VCC "Azul"
                    // ENCHUFO GND "Negro"

int val_humedad;            // Almaceno el valor de la humedad
int comparo_humedad = 776;  // Lo comparo con este dato
int error = 0; // Errores del DTH22

//----- Ultrasonido Tacho AGUA --------
int val_distancia;  //Almaceno la distancia
int large = 100;    // Valores a comparar en centimetros
int small = 10;

const int pintrigger = 10; // ENCHUFO pin Trigger "GRIS"
const int pinecho = 11;    // ENCHUFO DIGITAL pinEcho "AZUL"
                          // GND "MARRON"
                          // VCC BLANCO 5v

int faltaAgua = 15; // Vamos a usarlo para la alerta de falta de agua

//----- Ultrasonido Altura Planta--------
int val_distancia2;         //Almaceno la distancia
const int pintrigger2 = 12; // ENCHUFO pin Trigger "ROJO"
const int pinecho2 = 13;    // ENCHUFO DIGITAL pinEcho "MARRON"
                            // GND "MARRON"
                            // VCC BLANCO 5v
                          
//----- Relay -----
int bomba = 5;              // Pin5 es el COM3 del Relay

int riegos = 0;
int poco = 1000;            // Cantidad de segundos a regar
int un_toque = 3000;        // Cantidad de segundos a regar
int bastante = 5000;        // Cantidad de segundos a regar

//LCD Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() 
{
  Serial.begin(9600);       // open serial over USB
  pinMode(ledAzul, OUTPUT);

  // LCD
  lcd.init();       //Inicializar el LCD
  lcd.backlight();  //Encender la luz de fondo.
  //lcd.print("TFI Julian Civau"); // Mensaje de Inicio

  // HUMEDAD
  pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT Sensor Humedad
  digitalWrite(soilPower, LOW);//Establezca en LOW para que no pase corriente por el sensor

  // ULTRASONIDO - CONFIGURAR PINES DE ENTRADA Y SALIDA
  pinMode(pinecho, INPUT);
  pinMode(pintrigger, OUTPUT);

  // RELAY
  pinMode(bomba, OUTPUT);

  // DTH22 Humedad y Temperatura Digital
  dht.begin();
}

void loop() 
{

//Leo la Humedad del suelo
val_humedad = readSoil();
Serial.print("Valor Humedad del suelo: ");
Serial.println(val_humedad);

//Altura planta > Ultrasonido > Distancia
val_distancia2 = readDistancia2();
Serial.print("Distancia PLANTA val_distancia2: ");
Serial.print(val_distancia2);
Serial.println(" cm");

//Tacho de Agua > Ultrasonido > Distancia
val_distancia = readDistancia();
Serial.print("Distancia AGUA val_distancia: ");
Serial.print(val_distancia);
Serial.println(" cm");

// Reading temperature or humidity takes about 250 milliseconds!
float h = dht.readHumidity();
float t = dht.readTemperature();

if (isnan(h) || isnan(t)) {
  Serial.println("Falla en el sensor DTH22");
  error++;
  //return;
}

Serial.print("Humedad aire: ");
Serial.print(h);
Serial.print(" % ");
Serial.print("; Temperatura: ");
Serial.print(t,0);
Serial.print(" *C ");
Serial.print("; Error: ");
Serial.println(error);
Serial.print("Lecturas: ");
Serial.println(lecturas);
Serial.print("Riegos: ");
Serial.println(riegos);
Serial.println("***");

// LOGICA DEL PROGRAMA

if (val_distancia <= faltaAgua){
    Serial.println("Tengo Agua");

    if  (val_humedad < comparo_humedad){
      Serial.println("NECESITO Agua");

      prender_bomba(2000);
      
      }else Serial.println("NO QUIERO Agua");

      //Impresiones por pantalla
      lcd.clear();
      lcd.setCursor(0, 0); //Set cursor > Col row
      lcd.print("T:");
      lcd.print(t,0);
      
      lcd.print(" ");
      lcd.print("HS:");
      lcd.print(val_humedad);
      
      lcd.print(" ");
      lcd.print("E:");
      lcd.print(error);
      
      //lcd.setCursor(8, 0); //Set cursor > Col row
      //lcd.print("H: ");
      //lcd.print(h);
      //lcd.print("%");
      
      lcd.setCursor(0, 1); //Set cursor > Col row
      lcd.print("R:");
      lcd.print(riegos);

      lcd.print(" ");
      lcd.print("A:");
      lcd.print(val_distancia);
      
      lcd.print(" ");
      lcd.print("L:");
      lcd.print(lecturas);
 
    
  }else {
     Serial.println("No tengo agua");
     lcd.clear();
     lcd.setCursor(0, 0); //Set cursor > Col row
     lcd.print("NO TENGO AGUA");
     lcd.setCursor(0, 1); //Set cursor > Col row
     lcd.print("Recargar!");
    }

Serial.println("***");

delay(vuelta);// Tiempo cada cuanto pega la vuelta, declarado arriba.
lecturas++;
}

// ----- FUNCIONES -----

//Enciendo la bomba
void prender_bomba(int tiempo)//Recibo en tiempo la variable declarada arriba.
{
  Serial.println("ENCIENDO Bomba");
  digitalWrite(bomba, HIGH);
  delay(tiempo);
  Serial.println("APAGO Bomba");
  digitalWrite(bomba, LOW);
  riegos++;
  }

//Funcion para obtener la humedad del suelo
int readSoil()
{
    int val = 0;                    // valor para almacenar el valor de humedad en la funcion
    digitalWrite(soilPower, HIGH);  // "On" Enciende el sensor
    delay(10);                      // wait 10 milliseconds - Espera 10 segundos
    val = analogRead(soilPin);      // Read the SIG value form sensor - Lee el valor
    digitalWrite(soilPower, LOW);   // Apaga el sensor
    return val;                     // Devuelve el valor
}

//Leer ditancia cantidad de agua en el tacho
int readDistancia()
{
  // Variables para calculos
  unsigned int tiempo, distancia;

  // ENVIAR PULSO DE DISPARO EN EL PIN "TRIGGER" 
  digitalWrite(pintrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pintrigger, HIGH);
  // EL PULSO DURA AL MENOS 10 uS EN ESTADO ALTO
  delayMicroseconds(10);
  digitalWrite(pintrigger, LOW);

  // MEDIR EL TIEMPO EN ESTADO ALTO DEL PIN "ECHO" EL PULSO ES PROPORCIONAL A LA DISTANCIA MEDIDA
  tiempo = pulseIn(pinecho, HIGH);

  // LA VELOCIDAD DEL SONIDO ES DE 340 M/S O 29 MICROSEGUNDOS POR CENTIMETRO
  // DIVIDIMOS EL TIEMPO DEL PULSO ENTRE 58, TIEMPO QUE TARDA RECORRER IDA Y VUELTA UN CENTIMETRO LA ONDA SONORA
  distancia = tiempo / 58;

  // Devuelvo el valor de la distancia
  return distancia;
  }

//Leer distancia altura planta
int readDistancia2()
{
  // Variables para calculos
  unsigned int tiempo2, distancia2;

  // ENVIAR PULSO DE DISPARO EN EL PIN "TRIGGER" 
  digitalWrite(pintrigger2, LOW);
  delayMicroseconds(2);
  digitalWrite(pintrigger2, HIGH);
  // EL PULSO DURA AL MENOS 10 uS EN ESTADO ALTO
  delayMicroseconds(10);
  digitalWrite(pintrigger2, LOW);

  // MEDIR EL TIEMPO EN ESTADO ALTO DEL PIN "ECHO" EL PULSO ES PROPORCIONAL A LA DISTANCIA MEDIDA
  tiempo2 = pulseIn(pinecho2, HIGH);

  // LA VELOCIDAD DEL SONIDO ES DE 340 M/S O 29 MICROSEGUNDOS POR CENTIMETRO
  // DIVIDIMOS EL TIEMPO DEL PULSO ENTRE 58, TIEMPO QUE TARDA RECORRER IDA Y VUELTA UN CENTIMETRO LA ONDA SONORA
  distancia2 = tiempo2 / 58;

  // Devuelvo el valor de la distancia
  return distancia2;
  }
