class Graf {

  int nX, nY, colF;
  float coordAntX, coordAntY;
  Graf (int x, int y, int cF){
    nX = x;
    nY = y; 
    colF  = cF;
  }
  void cuadricula(){
    stroke(0);   
    for (int  j = 60 ; j <= nX - 60; j = j + 20){
      line (j, 60, j, nY - 60);      } // Vert
    for (int  j = 60 ; j <= nY - 60; j = j + 20){
      line (60, j, nX - 60, j);} // Horiz
 
  }
  
  void borra(){
    fill(colF); // Color del fondo
    noStroke();
    rectMode(CORNERS);
    rect(50 , 50, nX , nY - 30 ); 
  }
  void puntos(int x, float nValor, boolean primera){
      
      fill(255,255,255);
      rectMode(CORNERS); 
      rect(140,25,200,45);//Borra lectura anterior
      fill (0,0,255);
      text(nValor, 140, 40);
      fill(0, 0, 255);
      float v = map(nValor, 0, 1200, nY - 60, 60); //Mapeo inverso entre 
                                                   //los margenes sup e inf.    
      ellipse(x, v, 5, 5);
      //Une los dos puntos con una linea excepto en la primera lectura.
      if (primera == false){ 
        line (coordAntX, coordAntY, x, v);
        
      }
        coordAntX = x;
        coordAntY = v;          
  }


}
