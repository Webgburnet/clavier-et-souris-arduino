#include <ps2.h>

/*
 * an arduino sketch to interface with a ps/2 mouse.
 * Also uses serial protocol to talk back to the host
 * and report what it finds.
 */

/*
 * Pin 6 is the mouse data pin, pin 5 is the clock pin
 * Feel free to use whatever pins are convenient.
 */
PS2 mouse(5, 6);

/*
 * initialize the mouse. Reset it, and place it into remote
 * mode, so we can get the encoder data on demand.
 */
void mouse_init()
{
  mouse.write(0xff);  // reset
  mouse.read();  // ack byte
  mouse.read();  // blank */
  mouse.read();  // blank */
  mouse.write(0xf0);  // remote mode
  mouse.read();  // ack
  delayMicroseconds(100);
}

void setup()
{
  Serial.begin(9600);
  mouse_init();
}

/*
 * get a reading from the mouse and report it back to the
 * host via the serial line.
 */
void loop()
{
  char mstat;
  char mx;
  char my;

  /* get a reading from the mouse */
  mouse.write(0xeb);  // give me data!
  mouse.read();      // ignore ack
  mstat = mouse.read();
  mx = mouse.read();
  my = mouse.read();

  if(mstat==9)
  {
    Serial.println("Left Click");
  }
  else if(mstat==10)
  {
    Serial.println("Right Click");
  }
  else if(mstat==11)
  {
    Serial.println("Left Click + Right Click");
  }
  else if(mstat==12)
  {
    Serial.println("Center Click");
  }
  else if(mstat==13)
  {
    Serial.println("Center Click + Left Click");
  }
  else if(mstat==14)
  {
    Serial.println("Center Click + Right Click");
  }
  else if(mstat==15)
  {
    Serial.println("Center Click + Left Click + Right Click");
  }

  /* send the data back up */
  Serial.print("Data=");
  Serial.print(mstat,DEC);
  Serial.print("\t0b");
  Serial.print(mstat, BIN);
  Serial.print("\t0x");
  Serial.print(mstat, HEX);
  Serial.print("\tX=");
  Serial.print(mx, DEC);
  Serial.print("\tY=");
  Serial.print(my, DEC);
  Serial.println();
//  delay(20);  /* twiddle */
}
