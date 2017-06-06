int hallPin[]={2,3,4};
int allstates[]={0,0,0};
//boolean complete = false;

int lock = 8;       //control pin for relay
int mainLed = 13;    //unlocked LED
int ledpin1=9;      //status led of magnet sensed
int ledpin2=10;      //status led of magnet sensed
int ledpin3=11;      //status led of magnet sensed
int statePin=LOW;   //variable for reading state of each sensor


void setup(){
  pinMode(hallPin[0],INPUT);
  pinMode(hallPin[1],INPUT);
  pinMode(hallPin[2],INPUT);
  pinMode(ledpin1,OUTPUT);
  pinMode(ledpin2,OUTPUT);
  pinMode(ledpin3,OUTPUT);  
  pinMode(lock,OUTPUT);
  pinMode(mainLed,OUTPUT);
  Serial.begin(9600);
  
}

void loop(){
  digitalWrite(lock,LOW);             //make sure lock begins locked
  for(byte i = 0 ; i<3 ; i++){        //for each sensor
  statePin=digitalRead(hallPin[i]);   //read the sensor
  Serial.print(statePin);
  checkstate(statePin,i);             //check the state of the sensor
  }
  delay(500);
  //puzzle();
  if(complete()){                     //if the puzzle is complete
    Serial.println("UNLOCK");
    digitalWrite(lock,HIGH);          //unlock the lock
    digitalWrite(mainLed,HIGH);       //show the lock is open with led
    delay(10000);                     //wait 10 seconds
    digitalWrite(lock,LOW);           //relock the lock
    digitalWrite(mainLed,LOW);        //show the lock is closed with led
  }
  //Serial.println("loop");
}
void checkstate(int state,int index){     //take state if sensor pin and sensor number
  //Serial.println("checkstate called");
 if( state==HIGH){                        //if the magnet is NOT present
  digitalWrite(index+9,LOW);              //show the magnet is NOT sensed with led  
  allstates[index]=0;                     //set the puzzle array to blank
 }
 else{
  digitalWrite(index+9,HIGH);              //show the magnet is NOT sensed with led  
  allstates[index]=1;                     //count a magnet in present over the sensor
 }
}
boolean complete(){                       //check to see if all magnets are present
  //complete=true;
  Serial.println("===============");
  for(int i = 0; i < 3; i++){             //for each part of the puzzle
    
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(allstates[i]);

    if(allstates[i]==0){                  //if any magnets are NOT prsent
      return false;
    }
  }
  //Serial.println(complete);
  return true;
}
