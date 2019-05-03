 import controlP5.*;             //Importamos la biblioteca controlP5 para el cuadro de texto
 import processing.serial.*;     //Importamos la biblioteca para la comunicación con el puerto serie
 
 Serial puerto;                  //Inicializamos la variables
 ControlP5 cp5;
 
 void setup () 
 {
   fullScreen(1000, 620);             //Determinamos el tamaño de la ventana y el color del fondo
   background(0,255,0);
   
   puerto= new Serial(this,"COM3",9600); //Establecemos la comunicacion con el puerto serie COM3
   puerto.bufferUntil('\n');             //Decimos que espere a encontrarse un salto de linea para iniciar la funcion serialEvent
  
   PFont font = createFont("Agency FB",20); //Fuente para el cuadro de texto

  
   cp5 = new ControlP5(this);
  
   cp5.addTextfield(" ")              //Colocamos el cuadro de texto y marcamos sus atributos
       .setFont(font)                 //Fuente
       .setSize(200,40)               //Tamaño
       .setPosition(20,100)           //Posición
       .setFocus(true)                //Permitimos que los cambios se tengan en cuenta      
       .setColorValue(#080000)
       .setColorActive(#080000)         //Color del borde del cuadro de texto
       .setColorBackground(#FFFFFF)     //Color del fondo del cuadro de texto
       ;
 }
 //Recibir datos frecuencia del Arduino  
  if(puerto.available() > 0) // si hay algún dato disponible en el puerto
   { 
     valor=puerto.read();//Lee el dato y lo almacena en la variable "valor"
   }
   //Visualizamos la frecuencia con un texto
   text("Frec =",390,200);
   text(valor, 520, 200);
   text("Hz",547,200);
 
