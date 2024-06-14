// C++ code
//
//Arduino Code:
/*
 * Program for gesture control
 * Controlled using Python
 */

long time_taken;
int dist,distL,distR;

void setup() {
  Serial.begin(9600); 
}

//Function to calculate distance
long calculate_distance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the distance in centimeter.
  dist = 2.54*0.006783*pulseIn(echoPin, HIGH);
  return dist;
}

void loop() {
  
  distL = calculate_distance(8, 7); //get distance of left sensor
  distR = calculate_distance(4, 2); //get distance of right sensor
  
  //Serial.println(distL);
  //Serial.println(distR);
  
  // L                    R
  // 0- 5: Play/Pause     0-5
  // 5-15: Vup/Vdown      Near to Far/Far to Near
  //15-25: Brightness     Near to Far
  //25-35: Forward/Rewind Near to Far/Far to Near
  //

  //Play/Pause
  if ((distL > 0 && distL <= 5) && (distR > 0 && distR <= 5)) //Detect both hands
  {
    Serial.println("Play/Pause");
    delay (1000);
  }


  //Volume Up/Volume Down
  if (distL > 5 && distL <= 15)
  {
    delay(500); //Hand Hold Time
    distL = calculate_distance(8, 7); //get distance of left sensor
    if (distL > 5 && distL <= 15)
    {
      while(distL > 5 && distL <= 15)
      {
        distR = calculate_distance(4, 2); //get distance of right sensor
        if (distR < 15) //Hand pushed in 
        {
          if (distR < 5)
          {
            break; //to break
          }
          Serial.println ("Volume-Down"); 
          delay (500);
        }
        if (distR >= 15) //Hand pulled out
        {
          if (distR >= 30)
          {
            break; //to break
          }
          Serial.println ("Volume-Up");
          delay (500);
        }
      }
    }
  }


  //Fast Foward/Rewind
  if (distL > 15 && distL <= 25)
  {
    delay(1000); //Hand Hold Time
    distL = calculate_distance(8, 7); //get distance of left sensor
    if (distL > 15 && distL <= 25)
    {
      while(distL > 15 && distL <= 25)
      {
        distR = calculate_distance(4, 2); //get distance of right sensor
        if (distR < 15) //Hand pushed in 
        {
          if (distR < 5)
          {
            break; //to exit
          }
          Serial.println ("Rewind"); 
          delay (1500);
        }
        if (distR >= 15) //Hand pulled
        {
          if (distR >= 30)
          {
            break; //to exit
          }
          Serial.println ("Fast-Forward");
          delay (1500);
        }
      }
    }
  }


  //Next/Previous
  if (distL > 25 && distL <= 35)
  {
    delay(1500); //Hand Hold Time
    distL = calculate_distance(8, 7); //get distance of left sensor
    if (distL > 25 && distL <= 35)
    {
      while(distL > 25 && distL <= 35)
      {
        distR = calculate_distance(4, 2); //get distance of right sensor
        if (distR < 15) //Hand pushed in 
        {
          if (distR < 5)
          {
            break; //to exit
          }
          Serial.println ("Previous"); 
          delay (2500);
        }
        if (distR >= 15) //Hand pulled out
        {
          if (distR >= 30)
          {
            break; //to exit
          }
          Serial.println ("Next");
          delay (2500);
        }
      }
    }
  }

delay(100);
}
