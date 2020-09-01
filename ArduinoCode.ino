//set up global variables
int distance0;
int distance1;
int distance2;
int distance3;
//set up pin arrays
int trig_pins [4] = {8,5,3,1};
int echo_pins [4] = {7,6,4,2};

//set up colour pin variables
const int red = 11;
const int green = 10;
const int blue = 9;

//define function to get distance
long distance_get(int echo, int trig){
  //define local variables
  long duration;
  long distance;
  //send a signal to the sensor on the trigger pin
  digitalWrite(trig, LOW);
  //wait 2 microseconds
  delayMicroseconds(2);
  // Sets the trigger pin on high state for 10 micro seconds then turns it off
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // Reads the echo pin and returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  // calculate the distance
  distance= duration*0.034/2;
  //error handeling for weird overflow errors, I think.
  //don't read too much into this. It was a weird hack that I would try to avoid, but I wrote this code over the period of an evening while also building the thing.
  if(distance == 4){
    distance = 500;
  }
  //return the distance
  return distance;
}
//define function to change RGB LED colour
void RGB_colour(int r,int g, int b) {
  //hopefully self-explanitory
  analogWrite(red,r);
  analogWrite(green,g);
  analogWrite(blue,b);
}
 // setup code goes here and runs once (built in arduino function)
void setup() {
 //sets up all the pins
  //rgb led pins
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  //button pin, uses internal resistor so I didn't have to put one in.
  pinMode(12, INPUT_PULLUP);
  //buzzer pin
  pinMode(A5, OUTPUT);
  //for loop to set up sensor pins 
  //to be honest pretty proud of this bit
  for(int i=0; i<=3; i++){
    pinMode(trig_pins[i], OUTPUT);
    pinMode(echo_pins[i], INPUT);
  }
  //begins serial output for testing/debug purposes
  //could be removed to make performance a little better
  Serial.begin(9600);


}
// main code goes here to run repeatedly (built in arduino function)
void loop() {
  //gets distance from the four sensors
  distance0 = distance_get(echo_pins[0],trig_pins[0]);
  distance1 = distance_get(echo_pins[1],trig_pins[1]);
  distance2 = distance_get(echo_pins[2],trig_pins[2]);
  distance3 = distance_get(echo_pins[3],trig_pins[3]);
  //toggle this for testing mode
  //sets all but the front sensor to be a safe distance
    //distance1 = 500;
    //distance2 = 500;
    //distance3 = 500;
  
  //checks to see if the button has been pressed
  int button = digitalRead(12);
  //checks to see if any of the senors are in the RED condition
  if((distance0<= 100)||(distance1<= 100)||(distance2<= 100)||(distance3<= 100)){
    //sets the RGB led to red
    RGB_colour(255,0,0);
    //checks to see if the mute button is NOT being pressed
    if(button==true){
      //sets buzzer to on
      digitalWrite(A5,1);
    }
    //if it's not in RED state, checks to see if it's in orange state
  } else if((distance0<= 200)||(distance1<= 200)||(distance2<= 200)||(distance3<= 200)){
    //sets RGB LED to orange
    RGB_colour(255,100,0);
  } else {
    //if its not RED or ORANGE, it must be green
    //in bright light the green shows up as blue
    RGB_colour(0,255,50);
  }

  //little bit of a wait (mostly for buzzer), 0.1 seconds
  delay(100);
  //sets buzzer to off, whether or not it was on
  digitalWrite(A5,0);
  //serial output, for testing purposes.
  //I suppose you could also use this for data logging but why?
  Serial.println("distances:");
  Serial.println(distance0);
  Serial.println(distance1);
  Serial.println(distance2);
  Serial.println(distance2);
  Serial.println("button:");
  Serial.println(button);

}
