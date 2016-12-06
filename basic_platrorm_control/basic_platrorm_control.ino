#define L_FWD 5
#define L_BACK 6
#define R_FWD 10
#define R_BACK 11

void setup() {
  pinMode (L_FWD, OUTPUT);
  pinMode (R_FWD, OUTPUT);
  pinMode (L_BACK, OUTPUT);
  pinMode (R_BACK, OUTPUT);

  Serial.begin (9600);
  if (Serial.available()) Serial.println ("Connection established");
  Serial.setTimeout (50); 
}

void loop() {
  while (Serial.available()) 
  {
    int spd = Serial.parseInt();
    int dir = Serial.parseInt();
    
    if (Serial.read() != '\n') 
    { 
      Serial.println("Invalid input");
      spd = 0; dir = 0;
    }
    else
    {
      Serial.print(spd); Serial.print(' '); Serial.print(dir); Serial.print('\n');
    if (spd>255 || spd <-255 || dir >255 || dir <-255) {
      Serial.println("Invalid values");
      spd = 0; dir = 0;
    }

     if (spd>0) {
        if (dir>0) {
          analogWrite (R_FWD, spd);
          analogWrite (L_FWD, spd-dir);
          analogWrite (R_BACK, LOW);
          analogWrite (L_BACK, LOW);}
       
        else {
          analogWrite (L_FWD, spd);
          analogWrite (R_FWD, spd+dir);
          analogWrite (R_BACK, LOW);
          analogWrite (L_BACK, LOW);}
      
     }
     else if (spd<0) {
      if (dir>0) {
        analogWrite (R_BACK, spd);
        analogWrite (L_BACK, spd-dir);
        analogWrite (L_FWD, LOW);
        analogWrite (R_FWD, LOW);}
      
      else {
        analogWrite (L_BACK, spd);
        analogWrite (R_BACK, spd+dir);
        analogWrite (L_FWD, LOW);
        analogWrite (R_FWD, LOW);}
      
     }
     else if (spd == 0) {
      if (dir>0) {
        analogWrite(L_FWD, dir);
        analogWrite(R_BACK, dir);
        analogWrite(L_BACK, LOW);
        analogWrite(R_FWD, LOW);
        
      }
      else if (dir<0) {
        analogWrite(R_FWD, -dir);
        analogWrite(L_BACK, -dir);
        analogWrite(R_BACK, LOW);
        analogWrite(L_FWD, LOW);
      }
      else if (dir == 0) {
        Serial.println ("Stopping");
        analogWrite (R_BACK, LOW);
        analogWrite (L_BACK, LOW);
        analogWrite (L_FWD, LOW);
        analogWrite (R_FWD, LOW);
        
      }
     }
    }
  }
}
 



