import processing.serial.*;

int x = 65, ancho = 700, alto = 600;
boolean p = true;
int cFondo = 240; //Color fondo
String medida;
float temp, definitivo;

PrintWriter datos;
Serial puerto;
Graf g = new Graf(ancho, alto, cFondo);


void setup (){
 
  size(600, 700);
  background(cFondo);
  println(Serial.list());
 

  puerto = new Serial(this, "COM1", 9600);
  


  fill(0, 0, 255);
  text("Frecuencia (Hz): ", 20, 40);
  text("Tiempo", ancho / 2, alto - 20);
  g.cuadricula();
 
}

void draw(){

  String inString = puerto.readStringUntil('\n'); 
   if (inString != null){
      inString = trim(inString);
      float val = float(inString);           
      g.puntos(x, val, p); 
      p = false;
      x = x + 20;
      if (x > ancho - 60) 
      {
         x = 60;
         g.borra();
         g.cuadricula();
         p = true;
       }        
    }
}    

void keyPressed() {//Presionar 'ESC' para salir
    datos.flush();  
    datos.close();  
    exit();  
}
