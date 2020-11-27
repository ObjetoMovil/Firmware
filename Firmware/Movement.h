/*
 * Estructura a utilizar para la recepcion
 * de datos por medio de radiofrecuencia.
 */
struct Movement{
  char type;
  char motor;  
  int speed;
  int mTime;
  int angle;
  int radio;
  char orientation1;
  char orientation2; 
};
