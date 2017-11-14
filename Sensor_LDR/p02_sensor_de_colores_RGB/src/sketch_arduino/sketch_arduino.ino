/**
 * Proyecto: Sensor de colores RGB de bajo costo
 * Utiliza una fotorresistencia (LDR) de sulfuro de cadmio (CdS)
 * para detectar colores de objetos
 *
 * Sitio Web: http://www.developer.netau.net/wp
 * 
 * Autor: Carlos R. Primorac (2015)
 * 
 * Este programa es software libre: puedes copiarlo y redistribuirlo modificado o 
 * sin modificar bajo los términos de la Licencia Pública General GNU v3 publicada 
 * por la Fundacion del Software Libre.
 * 
 */

// array PINes de salida a los terminales del LED RGB
int ledArray[] = {5, 7, 8};

// PIN de entrada del terminal del sensor (LDR)
int ldrPin = 0;

// pausa entre balanceo blanco/negro
int balancePausa = 5000;

// pausa entre lecturas 
int lecturaPausa = 50;

// array de enteros para almacenar lecturas
int colorArray[] = {0, 0, 0};
int blancoArray[] = {0, 0, 0};
int negroArray[] = {0, 0, 0};

void setup() 
{
  Serial.begin(9600);
  pinMode(ledArray[0], OUTPUT);
  pinMode(ledArray[1], OUTPUT);
  pinMode(ledArray[2], OUTPUT); 
  balancear();
}

void loop() 
{
  detectarColor();
  // debugging monitor serie Arduino
  imprimir(colorArray[0], colorArray[1], colorArray[2]);  
}

/**
 * Balanceo del sensor
 */ 
void balancear()
{
  /** 
   * Balanceo de color blanco
   * Colocar tarjeta color blanco
   */
   // debugging
   //Serial.println("Colocar la tarjeta blanca ...");
   delay(balancePausa);  
   // obtener la lectura para cada color del LED
   for (int i = 0; i <=2; i++) {
     digitalWrite(ledArray[i], HIGH);
     delay(lecturaPausa); 
     blancoArray[i] = analogRead(ldrPin); // almacenar lectura
     digitalWrite(ledArray[i], LOW);
     delay(lecturaPausa);  
   }
   // debugg monitor serie Arduino
   imprimir(blancoArray[0], blancoArray[1], blancoArray[2]); 

  /**
   * Balanceo de color negro
   * Colocar tarjeta color negro
   */
   // debugging
   //Serial.println("Colocar la tarjeta negra.");
   delay(balancePausa); 
   for (int i=0; i <=2; i++) {
     digitalWrite(ledArray[i], HIGH);
     delay(lecturaPausa); 
     negroArray[i] = analogRead(ldrPin); // almacenar lectura
     digitalWrite(ledArray[i], LOW);
     delay(lecturaPausa);
   }
   imprimir(negroArray[0], negroArray[1], negroArray[2]); 
   delay(balancePausa); 
   //Serial.println("Sensor balanceado.");
}
  
/**  
 * Procesar las medidas del sensor 
 */
void detectarColor() 
{
  for (int i = 0; i<=2; i++) {
    digitalWrite(ledArray[i], HIGH);
    delay(lecturaPausa);
    colorArray[i] = analogRead(ldrPin); // obtener lectura color
    float diferenciaGrises = blancoArray[i] - negroArray[i]; // diferencia de grises
    //Serial.println(colorArray[i]);
    //Serial.println(diferenciaGrises);
    colorArray[i] = ((colorArray[i]-negroArray[i])/diferenciaGrises) * 255; // normalizar
    digitalWrite(ledArray[i], LOW);
    delay(lecturaPausa);
  }  
} 
  
/**
 * Imprime la salida formateada en el monitor serie
 * para su lectura en Processing
 */ 
void imprimir(int arg1, int arg2, int arg3) 
{
  Serial.print(arg1);
  Serial.print("a");
  Serial.print(arg2);
  Serial.print("b");
  Serial.print(arg3);
  Serial.println(".");
  delay(100);
}
