//LEDs: Pin 3,4
//Pieps: Pin 5
//Taster IO: Pin 6
//Taster Tap: Pin 7

int LED_L=3;
int LED_R=4;
int Piep=5;
int t;
int bpm=60;
int poti= A0;
int bPm;
int IO=6;
int go=0;
int action=0;
int tap=7;
bool isTapping=true;
double timeLos = 0;
double timeStop = 0;
double timeTap = 0;
int bpmOld=0;
bool dreh=true;


void setup() {
  
  pinMode(LED_L,OUTPUT);
  pinMode(LED_R,OUTPUT);
  pinMode(Piep,OUTPUT);
  pinMode(IO, INPUT);
  pinMode(tap, INPUT);
  Serial.begin(9600);



}

void loop() {

  bpm=analogRead(A0); //Werte einlesen
  go=digitalRead(IO);

    
  if(go){

    if(!action){
      action=1;
    }
    else{
      action=0;
      delay(1000);
    }
  }
  
  bpm=map(bpm, 0, 1023, 50, 250); //Werte auf 50-250 mappen.

  if(bpm!=bpmOld){
    dreh=true;
  }
  
  bpmOld=bpm;

  if(dreh){         //Wenn man dreht
     t=60000/bpm;  //Umrechnung bpm in ms.
  }
 


  if(digitalRead(tap)&&!action){    //tap in
    
    if(digitalRead(tap)){
      timeStop=millis();
      timeTap=timeStop-timeLos;
      timeLos=millis();
      delay(100);
      dreh=false;
    }

  t=timeTap;
   
  }

Serial.println(60000/t);
  if(action){

  digitalWrite(LED_L,1);
  digitalWrite(Piep,1);
  delay(100);
  digitalWrite(Piep,0);
  delay(t-100);
  digitalWrite(Piep,1);
  digitalWrite(LED_L,0);
  digitalWrite(LED_R,1);
  delay(100);
  digitalWrite(Piep,0);
  delay(t-100);
  digitalWrite(LED_R,0);
    
  }
  
  
  
 
}
