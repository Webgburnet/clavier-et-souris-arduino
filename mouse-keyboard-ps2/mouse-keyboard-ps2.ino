/*  PS2Keyboard library example
  
  PS2Keyboard now requries both pins specified for begin()

  keyboard.begin(data_pin, irq_pin);
  
  Valid irq pins:
     Arduino Uno:  2, 3
     Arduino Due:  All pins, except 13 (LED)
     Arduino Mega: 2, 3, 18, 19, 20, 21
     Teensy 3.0:   All pins, except 13 (LED)
     Teensy 2.0:   5, 6, 7, 8
     Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
     Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
     Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
     Sanguino:     2, 10, 11
  
  for more information you can read the original wiki in arduino.cc
  at http://www.arduino.cc/playground/Main/PS2Keyboard
  or http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
  
  Like the Original library and example this is under LGPL license.
  
  Modified by Cuninganreset@gmail.com on 2010-03-22
  Modified by Paul Stoffregen <paul@pjrc.com> June 2010
*/
   
#include <PS2Keyboard.h>
#include <ps2.h>

const int DataPin = 4;
const int IRQpin =  3;
PS2 mouse(5, 6);

PS2Keyboard keyboard;

String phrase;
String cmd;
boolean saut_ligne = false;
boolean retour =false;

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

void setup() {
  //keyboard.begin(DataPin, IRQpin, PS2Keymap_US);
  //keyboard.begin(DataPin, IRQpin, PS2Keymap_German);
  keyboard.begin(DataPin, IRQpin, PS2Keymap_French);
  //keyboard.begin(DataPin, IRQpin, PS2Keymap_Spanish);
  //keyboard.begin(DataPin, IRQpin, PS2Keymap_Italian);
  //keyboard.begin(DataPin, IRQpin, PS2Keymap_UK);
  mouse_init();
  Serial.begin(9600);
  Serial.println("International Keyboard + Mouse Test:");
}

void loop() {
  char c; 
  char mstat;
  char mx;
  char my;
  
  if (keyboard.available()) {
    
    // read the next key
    c = keyboard.read();
    
    if(retour==true)
    {
      Serial.println();
      retour=false;
    }
    // check for some of the special keys
    if (c == PS2_ENTER) {
      Serial.println();
      saut_ligne=true;
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
      cmd="[ESC]";
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
      cmd="[Del]";
    }else if (c == PS2_BACKSPACE) {
      Serial.print("[BCKS]");
      cmd="[BCKS]";
    } else if (c == PS2_F1) {
      Serial.print("[F1]");
    } else if (c == PS2_F2) {
      Serial.print("[F2]");
    } else if (c == PS2_F3) {
      Serial.print("[F3]");
    } else if (c == PS2_F4) {
      Serial.print("[F4]");
    } else if (c == PS2_F5) {
      Serial.print("[F5]");
    } else if (c == PS2_F6) {
      Serial.print("[F6]");
    } else if (c == PS2_F7) {
      Serial.print("[F7]");
    } else if (c == PS2_F8) {
      Serial.print("[F8]");
    } else if (c == PS2_F9) {
      Serial.print("[F9]");
    } else if (c == PS2_F10) {
      Serial.print("[F10]");
    } else if (c == PS2_F11) {
      Serial.print("[F11]");
    } else if (c == PS2_F12) {
      Serial.print("[F12]");   
    } else {
      // otherwise, just print all normal characters
      Serial.print(c);

      if(saut_ligne==true)
      {
        phrase=phrase+'\n'+c;
        saut_ligne=false;
      }
      else
      {
        phrase=phrase+c;
      }
    }
  }
  if(cmd=="[ESC]")
  {
    Serial.println();
    Serial.println(phrase);
    cmd="0";
  }
  else if(cmd=="[Del]")
  {
    Serial.println();
    Serial.println("Tous le texte effacer !");
    phrase="";
    Serial.println(phrase);
    cmd="0";
  }

  /* get a reading from the mouse */
  mouse.write(0xeb);  // give me data!
  mouse.read();      // ignore ack
  mstat = mouse.read();
  mx = mouse.read();
  my = mouse.read();

  //Button click on mouse
  if(mstat==9)
  {
    Serial.print("[Left Click]");
    retour=true;
  }
  else if(mstat==10)
  {
    Serial.print("[Right Click]");
    retour=true;
  }
  else if(mstat==11)
  {
    Serial.print("[Left Click + Right Click]");
    retour=true;
  }
  else if(mstat==12)
  {
    Serial.print("[Center Click]");
    retour=true;
  }
  else if(mstat==13)
  {
    Serial.print("[Center Click + Left Click]");
    retour=true;
  }
  else if(mstat==14)
  {
    Serial.print("[Center Click + Right Click]");
    retour=true;
  }
  else if(mstat==15)
  {
    Serial.print("[Center Click + Left Click + Right Click]");
    retour=true;
  }

  if(mx!=0 || my!=0)
  {
      Serial.print("X=");
      Serial.print(mx, DEC);
      Serial.print("\tY=");
      Serial.print(my, DEC);
      Serial.println();
  }
  
  /* send the data back up */
//  Serial.print("Data=");
//  Serial.print(mstat,DEC);
//  Serial.print("\t0b");
//  Serial.print(mstat, BIN);
//  Serial.print("\t0x");
//  Serial.print(mstat, HEX);
//  Serial.print("\tX=");
//  Serial.print(mx, DEC);
//  Serial.print("\tY=");
//  Serial.print(my, DEC);
//  Serial.println();
//  delay(20);  /* twiddle */
  
}
