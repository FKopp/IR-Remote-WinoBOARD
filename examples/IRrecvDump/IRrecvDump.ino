/*
 * IRremote: IRrecvDump - dump details of IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 * JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
 * LG added by Darryl Smith (based on the JVC protocol)
 */

#include <IRremote.h>

/* 
*  Default is Arduino pin D5. 
*  You can change this to another available Arduino Pin.
*  Your IR receiver should be connected to the pin defined here
*/
int RECV_PIN = 3; 

IRrecv irrecv(RECV_PIN);

decode_results results;

String incoming = "";

void setup()
{
  SerialUSB.begin(115200);
   irrecv.enableIRIn(); // Start the receiver
}


void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    SerialUSB.print("Unknown encoding: ");
  }
  else if (results->decode_type == NEC) {
    SerialUSB.print("Decoded NEC: ");

  }
  else if (results->decode_type == SONY) {
    SerialUSB.print("Decoded SONY: ");
  }
  else if (results->decode_type == RC5) {
    SerialUSB.print("Decoded RC5: ");
  }
  else if (results->decode_type == RC6) {
    SerialUSB.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {
    SerialUSB.print("Decoded PANASONIC - Address: ");
    SerialUSB.print(results->address, HEX);
    SerialUSB.print(" Value: ");
  }
  else if (results->decode_type == LG) {
    SerialUSB.print("Decoded LG: ");
  }
  else if (results->decode_type == JVC) {
    SerialUSB.print("Decoded JVC: ");
  }
  else if (results->decode_type == AIWA_RC_T501) {
    SerialUSB.print("Decoded AIWA RC T501: ");
  }
  else if (results->decode_type == WHYNTER) {
    SerialUSB.print("Decoded Whynter: ");
  }
  SerialUSB.print(results->value, HEX);
  SerialUSB.print(" (");
  SerialUSB.print(results->bits, DEC);
  SerialUSB.println(" bits)");
  SerialUSB.print("Raw (");
  SerialUSB.print(count, DEC);
  SerialUSB.print("): ");

  for (int i = 1; i < count; i++) {
    if (i & 1) {
      SerialUSB.print(results->rawbuf[i]*USECPERTICK, DEC);
    }
    else {
      SerialUSB.write('-');
      SerialUSB.print((unsigned long) results->rawbuf[i]*USECPERTICK, DEC);
    }
    SerialUSB.print(" ");
  }
  SerialUSB.println();
}

void loop() {
  if (irrecv.decode(&results)) {
    SerialUSB.println("RESULT:");
    //SerialUSB.println(results.value, HEX);
    incoming = String(results.value, HEX);
    //SerialUSB.println(incoming);
     if (incoming == "40bd00ff") {
     SerialUSB.println("Taste 1");
     }
     
    dump(&results);
    irrecv.resume(); // Receive the next value
    
   
    }
  }

