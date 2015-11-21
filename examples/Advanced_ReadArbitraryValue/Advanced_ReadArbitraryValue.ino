/*
Read and process analog input from an arbitrary value (that you can update)
 */

#include <InputProcessor.h>

// setup the input processor to have 30 samples
InputProcessor in0(30);  // note there is no second argument because that would be for a pin

int myarbitraryvalue = 100;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // calibrate for 3 seconds
  in0.calibrate(3000, myarbitraryvalue);  //feed it a second argument pointing to this value you have
  //doesn't make as much sense with a static value, but could depend on your use case, or maybe you wouldn't want to calibrate
}

// the loop routine runs over and over again forever:
void loop() {

//Doig some arbitrary processing to the value
myarbitraryvalue = analogRead(A0)+analogRead(A1); 

  //getting your values that are already scaled and calibrated is this easy
  int  mycalibratedvalue = in0.update(myarbitraryvalue);

  //getting a value that is smoothed by the rolling average, and calibrated is also easy!
  int mycalibratedandsmoothedvalue = in0.getscaledAverage();

  //for demo reasons this will list a lot of the other values you can get
  inputSerialMessages();

}

void inputSerialMessages() {

  Serial.print (in0.rawValue);
  Serial.print(", scale ");
  Serial.print (in0.scaledValue);
  Serial.print(", buffavg ");
  Serial.print (in0.getAverage());
  Serial.print(", buffavgscaled ");
  Serial.print (in0.getscaledAverage());
  Serial.print(", sum ");
  Serial.print (in0.getBuffSum());

  Serial.print(", avgdiff ");
  Serial.print (in0.getAvgDiff());


  Serial.print(", custom offset ");
  Serial.print (in0.offset);
  Serial.print(", offsetavgdiff ");
  Serial.print (constrain(in0.getoffsetAvgDiff() * 5, 0, 255));

  Serial.print(", calmin ");
  Serial.print (in0.min);
  Serial.print(", calMax ");
  Serial.println (in0.max);

  Serial.print(", STDEV ");
  Serial.print (in0.getSTDEV());
}

