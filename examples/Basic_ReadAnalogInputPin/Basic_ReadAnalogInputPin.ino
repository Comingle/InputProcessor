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

