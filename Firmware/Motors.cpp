/*
 * motorA  Adelante-Izquierda
 * motorB  Adelante-Derecha
 * motorC  Atras-Izquierda
 * motorD  Atras-Derecha
 */

  #include <Arduino.h>
  #include <AFMotor.h>
  #include "Motors.h"
  #include "TransceiverB.h"
  
  AF_DCMotor motorA(1);
  AF_DCMotor motorB(2);
  AF_DCMotor motorC(3);
  AF_DCMotor motorD(4);

  unsigned long previousMillis = 0;
  unsigned long interval = 0;
  boolean isMoving;

  /* 
   *  Procedimiento encargado de iniciarlizar los motores.
   */
  void setupMotors(){
    motorA.run(RELEASE);
    motorB.run(RELEASE);
    motorC.run(RELEASE);
    motorD.run(RELEASE);
  }

  /**
   * Procedimiento encargado de llamar al procedimiento de movimiento correspondiente en base al valor 
   * del parametro type recibido.
   */
  void setMovement(char type, char motor, int speed, int mTime, int angle, int radio, char orientation1, char orientation2){
    switch(type){
      case 'B': basicMovement(motor, mTime, speed, orientation1); break;
      case 'C': curvedMovement(radio, speed, orientation1, orientation2); break;
      case 'D': diagonalMovement(mTime, speed, angle); break;
      case 'S': straightMovement(mTime, speed, orientation1); break;
    }
  }  
 
  /**
   * Procedimiento que ejecuta el movimiento del motor A
   * @param mTime Distancia a recorrer por el motor.
   * @param speed Indicador del nivel de velocidad a establecer.
   * @param orientation Orientacion que tendra el movimiento.
   */
  void moveMotorA(int speed, char orientation){
    motorA.setSpeed(getSpeedValue(speed));
    motorA.run(getOrientationValue(orientation)); 
  }

  /**
   * Procedimiento que ejecuta el movimiento del motor B
   * @param mTime Distancia a recorrer por el motor.
   * @param speed Indicador del nivel de velocidad a establecer.
   * @param orientation Orientacion que tendra el movimiento.
   */
  void moveMotorB(int speed, char orientation){
    motorB.setSpeed(getSpeedValue(speed));
    motorB.run(getOrientationValue(orientation));
  }

  /**
   * Procedimiento que ejecuta el movimiento del motor C
   * @param mTime Distancia a recorrer por el motor.
   * @param speed Indicador del nivel de velocidad a establecer.
   * @param orientation Orientacion que tendra el movimiento.
   */
  void moveMotorC(int speed, char orientation){
    motorC.setSpeed(getSpeedValue(speed));
    motorC.run(getOrientationValue(orientation));
  }

  /**
   * Procedimiento que ejecuta el movimiento del motor D
   * @param mTime Distancia a recorrer por el motor.
   * @param speed Indicador del nivel de velocidad a establecer.
   * @param orientation Orientacion que tendra el movimiento.
   */
  void moveMotorD(int speed, char orientation){
    motorD.setSpeed(getSpeedValue(speed));
    motorD.run(getOrientationValue(orientation));
  }

  /**
   * Procedimiento que detiene los 4 motores
   */
  void stopMotors(){
      motorA.run(RELEASE);
      motorB.run(RELEASE);
      motorC.run(RELEASE);
      motorD.run(RELEASE);
  }

  /*
   * Procedimiento encargado de evaluar si la varaible isMoving tiene un valor true, de se asi alguno de los 
   * motores esta en movimiento. Se evalua si el intervalo de tiempo establecido para que se mueva el motor ya
   * se ha cumplido, de ser asi se llama al procedimiento stopMotors() para detenerlo, de lo contrario no se 
   * ejecuta ninguna accion.
   */
  void setStopMotors(){
    if(isMoving){
      if((millis() - previousMillis) >= interval){
        stopMotors();
        sendExecutedMovement();
        isMoving = false;  
      }  
    }  
  }

  /**
   * Funcion que retorna el nivel de velocidad en base al parametro que se recibe.
   * @param speed Valor que indica el nivel de velocidad a retornar.
   * @return Nivel de velocidad.
   */
  int getSpeedValue(int speed){
    switch(speed){
      case 1: return SPEED1; 
      case 2: return SPEED2;
      case 3: return SPEED3;     
    }
  }

  /**
   * Funcion que retorna la orientacion del giro del motor en base al parametro que se recibe.
   * @param orientation Caracter que indica la orientacion a retornar.
   * @return Orientacion de giro.
   */
  int getOrientationValue(char orientation){
    switch(orientation){
      case 'A': return FORWARD;
      case 'B': return BACKWARD;
      case 'U': return FORWARD;
      case 'D': return BACKWARD;
    }
  }

  /*
   * Procedimiento que establece varoles de la varaibles utilizadas para 
   * la simulacion de un hilo.
   */
  void setThreadInterval(int mTime){
    previousMillis = millis();
    interval = mTime*1000;
    isMoving = true;
  }

  /* 
   * Procedimiento encargado de llamar al metodo de movimiento del motor correspondiente segun el parametro
   * motor. Este procedimiento inicia la simulacion de un  hilo para realizar el movimiento durante el tiempo 
   * contenido en la varaible mTime y al finalizar este tiempo detiene todos los motores..
   */
  void basicMovement(char motor, int mTime, int speed, char orientation){
    sendExecutingMovement();
    switch(motor){
        case 'A': 
          moveMotorA(speed, orientation); 
          break;
        case 'B': 
          moveMotorB(speed, orientation); 
          break;
        case 'C': 
          moveMotorC(speed, orientation); 
          break;
        case 'D':
          moveMotorD(speed, orientation); 
          break;
    }
    setThreadInterval(mTime);
  }

  /**
   * Procedimiento encargado de realizar un movimiento recto. Inicia la simulacion de un hilo.
   */
  void straightMovement(int mTime, int speed, char orientation){
    sendExecutingMovement();
    moveMotorA(speed, orientation);
    moveMotorB(speed, orientation);
    moveMotorC(speed, orientation);
    moveMotorD(speed, orientation);
    setThreadInterval(mTime);
  }

  /**
   * Procedimiento encargado de realizar un movimiento en diagonal.
   */
  void diagonalMovement(int mTime, int speed, int angle){
    sendNotSupportedMovement();
    //Not suported yet
  }

  /**
   * Procedimiento encargado de realizar un movimiento curvo
   */
  void curvedMovement(int radio, int speed, char orientation1, char orientation2){ 
    sendNotSupportedMovement();
    //Not suported yet.
  }  
