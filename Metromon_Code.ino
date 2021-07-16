//LEDs: Pin 3,4
//Pieps: Pin 5
//Taster IO: Pin 6
//Taster Tap: Pin 7
//Taster +: Pin 2
//Taster -: Pin 8

int plus=8;
int minus=2;
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
int bpmOld=0;
int bpmPot=0;
bool isTapping=true;
bool dreh=true;
double timeLos = 0;
double timeStop = 0;
double timeTap = 0;




void setup() {
  
  pinMode(LED_L,OUTPUT);
  pinMode(LED_R,OUTPUT);
  pinMode(Piep,OUTPUT);
  pinMode(IO, INPUT);
  pinMode(tap, INPUT);
  pinMode(plus, INPUT);
  pinMode(minus, INPUT);
  Serial.begin(9600);



}

void loop() {
  
  go=digitalRead(IO);
  bpmPot=analogRead(A0); //Werte einlesen
  bpmPot=map(bpmPot, 0, 1023, 50, 250); //Werte auf 50-250 mappen.

 if(bpmPot!=bpmOld){
  bpm=bpmPot;
 }

 bpmOld=bpmPot;

    
  if(go){

    if(!action){
      action=1;
    }
    else{
      action=0;
      delay(1000);
    }
  }


 if(!action){   //Wenn Taster Plus oder Minus gedrückt werden bpm verändern
  if(digitalRead(plus)){
    bpm++;
    t=60000/bpm;
    dreh=false;
    delay(200);

  }

   if(digitalRead(minus)){
    bpm--;
    t=60000/bpm;
    dreh=false;
    delay(200);
  }
  
 }
  


  if(digitalRead(tap)&&!action){    //tap in
    
    if(digitalRead(tap)){
      timeStop=millis();
      timeTap=timeStop-timeLos;
      timeLos=millis();
      delay(200);
      dreh=false;
      bpm=60000/timeTap;
    }

     
  }


Serial.println(bpm);

  if(action){
  t=60000/bpm;
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
