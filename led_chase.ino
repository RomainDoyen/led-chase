
//LEDS
const int pinLed[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };  //déclaration et initialisation du tableau 
//qui va contenir les pins correspondent au leds

//avec les valeurs des pins et un timer
int val = 0;
int timer = 100;

//variable bouton
#define button 2
volatile bool basculer = false;

//Potentiometre
#define potPin A0 // Lecture du pin A0 sur lequel est branché le potentiomètre 
int potValue = 0; // valeur lue dans le pin A0
int valPWM = 0; // valeur du PWM du potentiometre

void setup() {    
  Serial.begin(9600);
  initialisationButton();
  initialisationInteruption();
  //Boucle d'initialisation des modes et mise à 0V
  for (int i = 0; i < 8; i++){ // i va nous servir pour parcourir le tableau des pins 
      //correspondent aux leds
    pinMode(pinLed[i], OUTPUT); //on utilise et initialise les valeurs du tableau
  }
}

void loop() {
  ////////////////////////////////////////////LEDS/////////////////////////////////////////////////////////////
  //on allume les 8 LED (ici en utilisant une boucle) et on change de mode par le potentiometre
  //
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if(basculer){ //test des préconditions
    eteint();
    if(Potent() >= val && Potent() < val){
      for(int i = 0; i < 8; i++){
        digitalWrite(pinLed[i], HIGH); 
        delay(timer);
        digitalWrite(pinLed[i], LOW);
        delay(timer);
      }
   } else {
      for(int i = 0; i < 8; i++){
        digitalWrite(pinLed[i], LOW); 
        delay(timer);
        digitalWrite(pinLed[i], HIGH);
        delay(timer);
      }
   }
  } else {
    allumee();
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

int Potent(){
  //////////////////////////////////////////////////POTENTIOMETRE//////////////////////////////////////////////////////
  potValue = analogRead(potPin); // Valeur du potentiomètre
  valPWM = map(potValue, 0, 1023, 0, 255); // Remise à l'échelle entre 0 et 254
  for(int i = 0; i < 8; i++){
     analogWrite(pinLed[i], valPWM); // Ecrit sur la sortie PWM la valeur remise à l'échelle
  }
  //Serial.println(valPWM); // Pour connaître la valeur envoyée à la sortie PWM
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////Fonction allumer et eteint/////////////////////////////
void eteint(){
  for(int i = 0; i < 8; i++){
    digitalWrite(pinLed[i], LOW);
  }
}

void allumee(){
  for(int i = 0; i < 8; i++){
    digitalWrite(pinLed[i], HIGH);
  }
}
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////Initialisation du button et interruption///////////////////////
void initialisationButton(){
  pinMode(button, INPUT_PULLUP); //Resistance de pullup pour l'antirebond
}

void initialisationInteruption(){
  attachInterrupt(digitalPinToInterrupt(button), bascule, RISING);// Info pour le compilateur: à conserver
    //RISING détecte le passage entre LOW et HIGH et fais une interruption a ce moment
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////Fonction bascule///////////////////////////////////
void bascule(){
  basculer = !basculer;
  //Serial.println("interruption");
  if(basculer){//test des préconditions soit led eteint() ou bien allumee()
    eteint();
  } else {
    allumee();
  }
}
//////////////////////////////////////////////////////////////////////////////////
