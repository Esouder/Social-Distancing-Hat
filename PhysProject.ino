int distance0;
int distance1;
int distance2;
int distance3;
int trig_pins [4] = {8,5,3,1};
int echo_pins [4] = {7,6,4,2};

const int red = 11;
const int green = 10;
const int blue = 9;


long distance_get(int echo, int trig){
  long duration;
  long distance;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  if(distance == 4){
    distance = 500;
  }
  return distance;
}
void RGB_colour(int r,int g, int b) {
  analogWrite(red,r);
  analogWrite(green,g);
  analogWrite(blue,b);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(12, INPUT_PULLUP);
  pinMode(A5, OUTPUT);
  for(int i=0; i<=3; i++){
    pinMode(trig_pins[i], OUTPUT);
    pinMode(echo_pins[i], INPUT);
  }
  
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  distance0 = distance_get(echo_pins[0],trig_pins[0]);
  distance1 = distance_get(echo_pins[1],trig_pins[1]);
  distance2 = distance_get(echo_pins[2],trig_pins[2]);
  distance3 = distance_get(echo_pins[3],trig_pins[3]);
  //toggle this for testing mode
  distance1 = 500;
  distance2 = 500;
  distance3 = 500;
    
  int button = digitalRead(12);
  if((distance0<= 100)||(distance1<= 100)||(distance2<= 100)||(distance3<= 100)){
    RGB_colour(255,0,0);
    if(button==true){
      digitalWrite(A5,1);
    }
  } else if((distance0<= 200)||(distance1<= 200)||(distance2<= 200)||(distance3<= 200)){
    RGB_colour(255,100,0);
  } else {
    RGB_colour(0,255,50);
  }

  
  delay(100);
  digitalWrite(A5,0);
  Serial.println("distances:");
  Serial.println(distance0);
  Serial.println(distance1);
  Serial.println(distance2);
  Serial.println(distance2);
  Serial.println("button:");
  Serial.println(button);

}
