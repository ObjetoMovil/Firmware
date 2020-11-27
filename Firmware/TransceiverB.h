  const byte R_ADDRESS[6] = "00001";
  const byte W_ADDRESS[6] = "00002";

  void setupTransceiverB();
  void setEmmiter();
  void setReceiver();
  void getData();
  void sendExecutingMovement();
  void sendExecutedMovement();
  void sendNotSupportedMovement();
  

  /*
   * Pines de conexion de antena nRF24L01 a arduino mega:
   * Rojo    3.3V
   * Negro    GND
   * Verde    49   CSN  
   * Azul     48   CE
   * Blanco   50   MISO
   * Narnaja  51   MOSI
   * Amarillo 52   SCK
   */
