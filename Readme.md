For working with Arduino Inputs to provide easier, faster access to standard data processing and calibration routines

This is originally put together by A. Quitmeyer from Comingle.io  2015 - Public Domain
with additional hacking on some open source simple examples by 
Julian Vidal   https://github.com/poisa/Calibrator   and Rob Tillaart

here's an example showing how to use with a regular arduino example that just reads from an analog input pin
  
```arduino
/*
 Basic Read Analog Input from a Pin Example
 */

#include <InputProcessor.h>

InputProcessor in0(30, A2); // setup the input processor to have 30 samples, and read from analog pin 2

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // calibrate for 3 seconds
  in0.calibrate(3000);
}

// the loop routine runs over and over again forever:
void loop() {

  //getting your values that are already scaled and calibrated is this easy
  int  mycalibratedvalue = in0.update();

  //getting a value that is smoothed by the rolling average, and calibrated is also easy!
  int mycalibratedandsmoothedvalue = in0.getscaledAverage();

}
```
it gets even more interesting though when you feed it an arbitrary function! It really opens up your possibilities! (your arbitrary function can even be the output of a different input processor to go into different levels of processing!

```arduino
/*
Read and process input from an arbitrary function
 */

#include <InputProcessor.h>

// setup the input processor to have 30 samples
InputProcessor in0(30);  // note there is no second argument because that would be for a pin


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // calibrate for 3 seconds
  in0.calibrate(3000, myarbitraryfunction);  //feed it a second argument pointing to this value you have
  //doesn't make as much sense with a static value, but could depend on your use case, or maybe you wouldn't want to calibrate
}

//your arbitrary function needs to return an int!
int myarbitraryfunction(){
  
//Doig some custom processing with inputs
return analogRead(A0)+analogRead(A1);

}

// the loop routine runs over and over again forever:
void loop() {

  //getting your values that are already scaled and calibrated is this easy
  int  mycalibratedvalue = in0.update(myarbitraryfunction);

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

```
