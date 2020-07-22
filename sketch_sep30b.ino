#include "Ultrasonic.h"
#include "NewPing.h"

int enA = 6;
int right1 = 3;
int right2 = 2;

int enB = 5;
int left1 = 7;
int left2 = 4;

int echoL = 13;
int echoR = 9;
int echoFr = 11;
int echoFrL = 12;
int echoFrR = 10;

int rx = 0;
int tx = 1;

int trig = 8;

void setup()
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);

  pinMode(echoL, INPUT);
  pinMode(echoFrL, INPUT);
  pinMode(echoFr, INPUT);
  pinMode(echoFrR, INPUT);
  pinMode(echoR, INPUT);
  pinMode(trig, OUTPUT);

  pinMode(rx, OUTPUT);
  pinMode(tx, OUTPUT);

  Serial.begin(9600);
}

void poLivomyBortiky1();
void var4();
void poPravomyBortiky();
int sensor(int echo);
int sensor1(int echo);
void naVpravo();
void naVlivo();
void vlivo();
void vpravo();
void vpered();
void nazad();
void var5();
void var6L();
void var6R();
void var41();
void var42();
void var43();
void naStop();
void vperedP();
void var7();
int maxlng = 800;
int SVPERED = 120;
boolean bortik = true; //true - left, false - right

void f();
void loop() {
  delay(100);
  //poLivomyBortiky1();
  //poPravomyBortiky();
  //var4();

  int n = 0;
  Serial.println("opa");
  if(Serial.available() > 0){
    int c = Serial.read();
    
    if(c == 'v'){
      char *c1 = (char *)n;
      for(int i = 0; i < 4; i++){
        c = Serial.read();
        *c1 = c; c1++;
      }
    }
    Serial.print("prishlo: c = ");
    Serial.println(c);
    
    
  }
}


void var5() {
  if (sensor(echoFrR) > 70 && sensor(echoFr) < 70) {
    naVpravo();
    while (true) {
      int i2 = sensor(echoFr);
      if (i2 > 31) return;;
    }
  }
}
void var4() { //Р±РѕСЂС‚С‹Рє СЃРїРµСЂРµРґС‹ 1 = vlivo 2 = vpravo
  int i = sensor(echoFr);
  //delay(200);.
  //if(i > 3000) {
  //  nazad();
  //  delay(100);
  //}
  if (i < 40 ) {
    naStop();
    delay(1000);
    int l = sensor(echoL);
    int r = sensor(echoR);
    while (l < 1 || l > 1000 ) {
      vpered();
      delay(100);
      l = sensor(echoL);
    }
    while (r < 1 || r > 1000 ) {
      vpered();
      delay(100);
      r = sensor(echoR);
    }
    if ( l < r) {
      naVpravo();

      while (true) {
        int i2 = sensor(echoFr);
        if (i2 > 40) return;
      }
    }
    if (r < l) {
      naVlivo();
      while (true) {
        int i2 = sensor(echoFr);
        if (i2 > 40) return;
      }
    }

  }
}

void var43() {
  if (sensor(echoFr) < 3) {
    nazad();
    delay(100);
  }
  if (sensor(echoFrL) < 10) {
    vpravo();
    delay(100);
    while (true) {
      int i2 = sensor(echoFr);
      if (i2 > 50) return;
    }
    if (sensor(echoFrR) < 10) {
      vlivo();
      delay(100);
      while (true) {
        int i2 = sensor(echoFr);
        if (i2 > 50) return;
      }
    }
  }
}

void var42() {
  if (sensor(echoFrL) < 4) {
    vpravo();
    while (true) {
      if (sensor(echoFrL) > 10) return;
    }
    return;
  }

  if (sensor(echoFrR) < 4) {
    vlivo();
    while (true) {
      if (sensor(echoFrR) > 10) return;
    }
    return;
  }

}

void var41() {
  int i = sensor(echoFr);

  if (i == 0)return;
  if (i < 10) {
    nazad();
    delay(1000);
  }
}

void chooseBortik() {
  int ir = sensor(echoR);
  int il = sensor(echoL);
  if (ir > il)
    bortik = true;
  else bortik = false;
}
int ir = 0;
int il = 0;
int livo3 = 0;
int livo31 = 0;
void poLivomyBortiky1() { //РєСѓСЂСѓРІР°РЅРЅСЏ РїРѕ Р»С–РІРѕРјСѓ Р±РѕСЂС‚С–РєСѓ
  int i = sensor(echoL);
  //int i1 = il;//sensor(echoL);
  //if (i1 == 0 || i1 > 1000) i1 = livo31;
  if (i == 0 || i > 1000) {
    i = livo3;
  }
  if (i == livo3) {
    vpered();
    return;
  }
  if (i > livo3) {
    vlivo();
    livo3 = i;
    //livo31 = i1;
    return;
  }
  if (i < livo3) {
    vpravo();
    livo3 = i;
    //livo31 = i1;
    return;
  }
  livo3 = i;
  //livo31 = i1;
}
int pravo3 = 0;
int pravo31 = 0;
void poPravomyBortiky() { //РєСѓСЂСѓРІР°РЅРЅСЏ РїРѕ Р»С–РІРѕРјСѓ Р±РѕСЂС‚С–РєСѓ
  int i = sensor(echoR);
  //int i1 = ir;//sensor(echoR);
  if (i == 0 || i > 1000) {
    i = pravo3;
  }
  //if (i1 == 0 || i1 > 1000) i1 = pravo31;
  if (i == pravo3 ) {
    vpered();
    return;
  }
  if (i > (pravo3)) {
    vpravo();
    pravo3 = i;
    //pravo31 = i1;
    return;
  }
  if (i < (pravo3) ) {
    vlivo();
    pravo3 = i;
    //pravo31 = i1;
    return;
  }
  pravo3 = i;
  //pravo31 = i1;
}

void naStop() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);
}

void naVpravo() {
  analogWrite(enA, 0);//60
  analogWrite(enB, 240);//120
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  delay(100);
}

void naVlivo() {
  analogWrite(enA, 240);//120
  analogWrite(enB, 0);//60
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);
  delay(100);//10
}

void vpered() {
  //Serial.println("vpered");
  analogWrite(enA, SVPERED);//live
  analogWrite(enB, SVPERED);//prave
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);
  delay(30);//100
}

void nazad() {
  Serial.println("nazad");
  analogWrite(enA, 100);
  analogWrite(enB, 100);
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  delay(100);
}

void vlivo() {
  //Serial.println("vlivo");
  analogWrite(enA, 30);
  analogWrite(enB, 150);
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);
  delay(30);//30

}

void vpravo() {
  //Serial.println("vpravo");
  analogWrite(enA, 150); //СЃРєРѕСЂРѕСЃС‚СЊ vpered
  analogWrite(enB, 30);
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);
  delay(30);//20
}

int sensor(int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(1);//2
  digitalWrite(trig, HIGH);
  delayMicroseconds(1);//10
  digitalWrite(trig, LOW);
  //delayMicroseconds(10);
  long duration = pulseIn(echo, HIGH);
  //Serial.println("duration");
  long distance_cm = duration / 29 / 2 ;
  return distance_cm;
}

void print1() {
  Serial.print("echoR = ");
  Serial.println(sensor(echoR));
  delay(10);
  //Serial.print("echoFrR = ");
  //Serial.println(sensor(echoFrR));
  delay(10);
  Serial.print("echoFr = ");
  Serial.println(sensor(echoFr));
  delay(10);
  //Serial.print("echoFrL = ");
  //Serial.println(sensor(echoFrL));
  delay(10);
  Serial.print("echoL = ");
  Serial.println(sensor(echoL));
  delay(500);
}









