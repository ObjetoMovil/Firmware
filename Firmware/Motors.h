
  const int SPEED1 = 150;
  const int SPEED2 = 200;
  const int SPEED3 = 254;

  //Setup de motores.
  void setupMotors();

  //Selector principal de movimientos.
  void setMovement(char type, char motor, int speed, int mTime, int angle, int radio, char orientation1, char orientation2);
  
  //Movimientos.
  void moveMotorA(int speed, char orientation);
  void moveMotorB(int speed, char orientation);
  void moveMotorC(int speed, char orientation);
  void moveMotorD(int speed, char orientation);
  void stopMotors();

  //Evaluar el estado el hilo simulado
  void setStopMotors();

  //Obtener valores en base a parametros.
  int getSpeedValue(int speed);
  int getOrientationValue(char orientation);

  //Establecer valores para simulacion de hilo.
  void setThreadInterval(int mTime);

  //Simulacion de hilos para ejecutar los movimientos.
  void basicMovement(char motor, int mTime, int speed, char orientation);
  void straightMovement(int mTime, int speed, char orientation);
  void diagonalMovement(int mTime, int speed, int angle);
  void curvedMovement(int radio, int speed, char orientation1, char orientation2);
