#include <widgets.h>
#include <wino.h>

#include <IRremote.h>

IRsend irsend;

// Use pin 12 as the IR led pin
void setup()
{
  SerialUSB.begin(9600);
  pinMode( 4, OUTPUT );
}

void loop() {
  digitalWrite( 4, HIGH );
  irsend.sendSony(0xa90, 12);
  digitalWrite( 4, LOW );
	delay(200); //5 second delay between each signal burst
}
