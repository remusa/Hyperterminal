
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

// importar librerias requeridas
import processing.serial.*;

// objeto puerto  
Serial puerto;

// índice de los separadores de datos 
int indexOfa = 0;
int indexOfb = 0;

// variables 
String data = "";

String red = "";
String green = "";
String blue = "";

int red2 = 0; 
int green2= 0;
int blue2= 0;

void setup()
{
  size(300, 300);
  puerto = new Serial(this, "COM5", 9600); 
  puerto.bufferUntil('.');
}

void draw()
{
  // cambiar el color de fondo de la ventana por el color percibido por el sensor  
  background(red2, green2, blue2);
}

/**
 * Captura la información enviada por el puerto serie
 */
void serialEvent(Serial puerto)
{
  data = puerto.readStringUntil('.');
  data = data.substring(0, data.length() - 1);
  
  indexOfa = data.indexOf("a");
  red = data.substring(0, indexOfa);
     
  indexOfb = data.indexOf("b");
  green = data.substring(indexOfa+1, indexOfb);

  blue  = data.substring(indexOfb+1, data.length());
  
  red2 = Integer.parseInt(trim(red));
  green2 = Integer.parseInt(trim(green));
  blue2 = Integer.parseInt(trim(blue));
  
  // debugging =)
  println("Red", "\t", "Green", "\t", "Blue");
  println(red2, "\t", green2, "\t", blue2, "\n");
}



