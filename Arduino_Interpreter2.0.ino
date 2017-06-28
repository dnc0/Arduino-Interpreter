/* Arduio Interpreter 2.0
 * Revision 1.1
 * Jun 27 of 2017
 * 
 * A basic I/O commands interpreter for Arduino
 * 
 */

//Global VARs
String command=""; //Storage the command
String parameter=""; //Storare the parameter for command
bool debug=true;//If true send debug messages
bool msg=true;//if true send informations of commands received

//Functions prototype
void read_serial(void); //Save the commands and parameters received by the serial
void work(void); //Verifies that the command is valid and performs actions

void setup() {
  Serial.begin(9600); //Start the serial
}

void loop() {
  if(Serial.available()) { //if receiving somethin on serial...
    read_serial();
    //Debug messages
    if (debug) Serial.println("Reciving...");//DEBUG MSG
    if (debug){Serial.print("Command: "); Serial.println(command);}//DEBUG MSG
    if (debug){Serial.print("parameter: "); Serial.println(parameter);}//DEBUG MSG
    work();
    
  }// END recive
}//END main loop


// - - - Functions - - -
void read_serial(void) { //Save the commands and parameters received by the serial
  command = "";//clear command value
  parameter="";//clear parameter value
  boolean isCommand=true;//Used for determinate the text is a command or parameter
  char letter; //Storage a current letter
  while(Serial.available()>0) { //While recive something throught the serial
    letter=Serial.read(); //save the current letter
    if(letter ==' ') { //if the current letter is space, the next letter is the parameter
      isCommand=false;
    }
    if((letter !='\n') && (isCommand==true)){//if the current letter it is not new line and not detected space, the next letter is the command
      command.concat(letter);
    }
    if((letter !='\n') && (isCommand==false)){//if the current letter it is not new line and detected space, the next letter is the parameter
      parameter.concat(letter);
    }
    delay(50); //delay for new read
  }
}

void work(void){
  if(command=="on") { //if command is on, set the pin informed by parameter
      pinMode(parameter.toInt(),OUTPUT);
      digitalWrite(parameter.toInt(),HIGH); 
      if(msg){ Serial.print("the pin "); Serial.print(parameter.toInt()); Serial.println(" is on");} //msg
    }
    else if(command=="off"){ //if command is off, clear the pin informed by parameter
      pinMode(parameter.toInt(),OUTPUT);
      digitalWrite(parameter.toInt(),LOW); 
      if(msg){ Serial.print("the pin "); Serial.print(parameter.toInt()); Serial.println(" is off");} //msg
     }
    else if((command=="debug")||(command=="DEBUG")){ //if command is debug, the parameter swap the flag debug
      debug = parameter.toInt();
      Serial.print("Debug is "); Serial.println(debug);
    }
    else if((command=="msg")||(command=="MSG")){ //if command is msg, the parameter swap the flag msg
      msg=parameter.toInt();
      Serial.print("msg's is "); Serial.print(msg);
    }
    else {
      Serial.println("Unknown command");
    }
}

