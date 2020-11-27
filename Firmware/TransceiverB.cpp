  #include <Arduino.h>
  #include <SPI.h>
  #include <nRF24L01.h>
  #include <RF24.h>
  #include "TransceiverB.h"
  #include "Movement.h"
  #include "Motors.h"

  #define CE_PIN 48
  #define CSN_PIN 49

  typedef struct Movement Movement;

  RF24 transceiver(CE_PIN, CSN_PIN);
  Movement movement;

  /*
   * Procedimiento que inicializa el transceptor B
   */
  void setupTransceiverB(){
    Serial.begin(9600);
    transceiver.begin(); 
    transceiver.setChannel(115); 
    transceiver.setPALevel(RF24_PA_MAX);     //RF24_PA_MIN,/ RF24_PA_LOW,/ RF24_PA_HIGH,/ RF24_PA_MAX
    transceiver.setDataRate(RF24_250KBPS);   //RF24_1MBPS,/ RF24_2MBPS,/ RF24_250KBPS  
    transceiver.openWritingPipe(W_ADDRESS);
    transceiver.openReadingPipe(1, R_ADDRESS);
    transceiver.setPALevel(RF24_PA_MIN);  
  }

  /*
   * Procedimiento que establece el transceptor como emisor.
   */
  void setEmmiter(){
    transceiver.stopListening();  
  }

  /*
   * Procedimiento que establece el transceptor como receptor.
   */
  void setReceiver(){
    transceiver.startListening();
  }

  /*
   * Procedimiento que recibe datos a traves de radio frecuencia y llama al metodo
   * setMovement enviando como parametros los datos recibidos, para sentenciar el
   * movimiento a realizar.
   */
  void getData(){
    setReceiver();
    if (transceiver.available()) {
      transceiver.read(&movement, sizeof(movement));
      setMovement(movement.type, movement.motor, movement.speed, movement.mTime, movement.angle, movement.radio, movement.orientation1, movement.orientation2);
    }  
  }

  /*
   * Procedimientos encargados de enviar datos a traves de radio frecuencia.
   * Los datos a enviar hacia el transceptor A consiste en un array de tipo 
   * char que contiene un mensaje, el transceptor A esta configurado para recibir 
   * una longitud maxima de 50. Si se desea enviar un array mas grande se debe de 
   * modificar esta longitud dentro del codigo TransceiverA.
   */
  void sendExecutingMovement(){
    delay(10);
    setEmmiter();
    char data[] = "Ejecutando movimiento";
    transceiver.write(&data, sizeof(data));
  }

  void sendExecutedMovement(){
    delay(10);
    setEmmiter();
    char data[] = "Movimiento finalizado";
    transceiver.write(&data, sizeof(data));
  }

  void sendNotSupportedMovement(){
    delay(10);
    setEmmiter();
    char data[] = "Movimiento no soportado";
    transceiver.write(&data, sizeof(data));
  }
