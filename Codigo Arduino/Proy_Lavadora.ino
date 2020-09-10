
const char a = 13;
const char b = 12;
const char c = 11;
const char d = 10;
const char e = 9;
const char f = 8;
const char g = 7;
const char p = 6;

const char startPin = A0;
const char stopPin = A1;
const char potPin = A2;
const char infraredPin = A3;

const char valvePin = 4;
const char buzzerPin = 5;

int waterTime = 0;
int regresiveCount;

unsigned long pastTime = 0;
unsigned long tenMS = 0;
unsigned long oneS = 0;
unsigned long previousTime = 0;
unsigned long fiveHundredMS = 0;

char Start = 0;
char Stop = 0;
char counter = 0;
char finalCounter = 0;
bool buzzer = false;





void setup() {

  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(e,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(p,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);

  pinMode(startPin,INPUT);
  pinMode(stopPin,INPUT);
  pinMode(potPin,INPUT);
  pinMode(infraredPin,INPUT);
  pinMode(buzzerPin,OUTPUT);
  pinMode(valvePin,OUTPUT);

  digitalWrite(valvePin,HIGH);
  
  Serial.begin(9600);

}

void loop() {

  if((millis() - tenMS) >= 10){
    tenMS = millis();
    if(digitalRead(startPin)){
        if(waterTime != 0) Start = 1;
      }
    if(digitalRead(stopPin) && Start){
        Start = 0;
        Stop = 1;
        digitalWrite(valvePin,HIGH);
      }
    if((analogRead(infraredPin)>920) && Start) digitalWrite(buzzerPin,HIGH);
    else digitalWrite(buzzerPin,LOW);
    }

   
   
  
  
  if(Start==1){
      if((millis() - oneS) >= 1000){
      oneS = millis();

      digitalWrite(valvePin,LOW);
      
      waterTime = regresiveCountt(waterTime);
      if(waterTime == 0) {
          Start = 0;
          Stop = 1;
          buzzer = true;
          digitalWrite(valvePin,HIGH);
          waterTime = potToDisplay();
        }
      }
    }
   else{
      waterTime = potToDisplay(); //potenciometro
    }

    while(Stop){
      if((millis() - fiveHundredMS) >= 500){
        fiveHundredMS = millis();

        switchParpadeo(finalCounter);
        
        finalCounter = finalCounter + 1;
        if(finalCounter > 8){
          finalCounter = 0;
          buzzer = false;
          Stop = 0;
          }
        }
      }
    Display(waterTime);
}

int potToDisplay(){
    char segundos = 0;
    char minutos = 0;
    float potValue = analogRead(potPin);
    char numeroDeMinutos = 40;
    int multiplo;
    multiplo = map(potValue, 0, 1023, 0, 2*numeroDeMinutos);

    for(int i=0; i<multiplo; i++){
        segundos = segundos + 30;
        if(segundos >= 60) {
            minutos = minutos + 1;
            segundos = 0;
          }
      }
    return minutos*100 + segundos;
  }

void Display(int waterTime){
    int totalNumber[4];
    int unidades = 0;
    int decenas = 0;
    int centenas = 0;
    int millar = 0;
    
    millar = waterTime/1000;
    centenas = (waterTime - millar*1000)/100;
    decenas = (waterTime - millar*1000 - centenas*100)/10;
    unidades = waterTime - millar*1000 - centenas*100 - decenas*10;

    totalNumber[3] = millar;
    totalNumber[2] = centenas;
    totalNumber[1] = decenas;
    totalNumber[0] = unidades;
    

    if(millis() - previousTime >= 4){
        setNumberToDisplay(totalNumber[counter],counter);
        counter = counter + 1;
        if(counter>3) counter = 0;
        previousTime  = millis();      
      }
    
  }


int regresiveCountt(int WaterTime){
    int segundos;
    int minutos;
    minutos = WaterTime/100;
    segundos = WaterTime - minutos*100 - 1;
    if(segundos < 0){
        minutos = minutos - 1;
        segundos = 59;
      }
    return minutos*100 + segundos;
  }

void switchParpadeo(char FinalCounter){
    switch(FinalCounter){
          case 0:
            setNothing();
            if(buzzer) digitalWrite(buzzerPin,LOW);
            break;
          case 1:
            setCeros();
            if(buzzer) digitalWrite(buzzerPin,HIGH);
            break;
          case 2:
            setNothing();
            if(buzzer) digitalWrite(buzzerPin,LOW);
            break;
          case 3:
            setCeros();
            if(buzzer) digitalWrite(buzzerPin,HIGH);
            break;
          case 4:
            setNothing();
            if(buzzer) digitalWrite(buzzerPin,LOW);
            break;
          case 5:
            setCeros();
            if(buzzer) digitalWrite(buzzerPin,HIGH);
            break;
          case 6:
            setNothing();
            if(buzzer) digitalWrite(buzzerPin,LOW);
            break;
          case 7:
            setNothing();
            break;
          }
  }



////////////////////////////////
void setNumberToDisplay(char numberToDisplay,char Position){
    switch (numberToDisplay){
        case 0:
          set0(Position);
          break;
        case 1:
          set1(Position);
          break;
        case 2:
          set2(Position);
          break;
        case 3:
          set3(Position);
          break;
        case 4:
          set4(Position);
          break;
        case 5:
          set5(Position);
          break;
        case 6:
          set6(Position);
          break;
        case 7:
          set7(Position);
          break;
        case 8:
          set8(Position);
          break;
        case 9:
          set9(Position);
          break;
        default:
          setNothing();
          break;  
      }
  }

void set0(char Display){
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,LOW);

    Multiplexor(Display);
  }

void set1(char Display){
    digitalWrite(a,LOW);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);

    Multiplexor(Display);
  }

void set2(char Display){
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,LOW);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,LOW);
    digitalWrite(g,HIGH);

    Multiplexor(Display);
  }
  
void set3(char Display){
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,HIGH);

    Multiplexor(Display);
  }
  
void set4(char Display){
    digitalWrite(a,LOW);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);

    Multiplexor(Display);
  }

void set5(char Display){
    digitalWrite(a,HIGH);
    digitalWrite(b,LOW);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);

    Multiplexor(Display);
  }
  
void set6(char Display){
    digitalWrite(a,HIGH);
    digitalWrite(b,LOW);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);

    Multiplexor(Display);
  }

void set7(char Display){
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);

    Multiplexor(Display);
  }

void set8(char Display){
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);

    Multiplexor(Display);
  }

void set9(char Display){
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);

    Multiplexor(Display);
  }

void setNothing(){
    char Multiplexor[4] = {A4,A5,2,3};
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
    digitalWrite(Multiplexor[3],LOW);
    digitalWrite(Multiplexor[2],LOW);
    digitalWrite(Multiplexor[1],LOW);
    digitalWrite(Multiplexor[0],LOW);
  }

void setCeros(){
    char Multiplexor[4] = {A4,A5,2,3};
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,LOW);
    digitalWrite(Multiplexor[3],LOW);
    digitalWrite(Multiplexor[2],LOW);
    digitalWrite(Multiplexor[1],LOW);
    digitalWrite(Multiplexor[0],LOW);
  }


void Multiplexor(char num){
    char Multiplexor[4] = {A4,A5,2,3};
    digitalWrite(Multiplexor[3],HIGH);
    digitalWrite(Multiplexor[2],HIGH);
    digitalWrite(Multiplexor[1],HIGH);
    digitalWrite(Multiplexor[0],HIGH);
    digitalWrite(Multiplexor[num],LOW);
    if(num==2) digitalWrite(p,HIGH);
    else digitalWrite(p,LOW);
}
  


