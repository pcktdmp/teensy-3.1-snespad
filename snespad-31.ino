/*
  snespad-31

  Copyright (C) 2014  Serge van Namen <serge@se-cured.org>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITSNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <SNESpad.h>

// Marco's for button states.
#define BUTTON_PRESSED(state, btn) ((state) & (btn)) 
#define CURRENTLY_PRESSED(btn) BUTTON_PRESSED(state, btn)
#define PREVIOUSLY_PRESSED(btn) BUTTON_PRESSED(prev_state, btn) 

#define DEBUGGING 1

// debugging
#ifdef DEBUGGING
#define DEBUG(...) Serial.println(state, BIN) 
#else 
#define DEBUG(...)
#endif
 
// Generic Joystick/Gamepad mapping for the SNES buttons.
#define BUTTON_A 3
#define BUTTON_B 2
#define BUTTON_Y 1
#define BUTTON_X 4


#define BUTTON_UP 0
#define BUTTON_RIGHT 90
#define BUTTON_DOWN 180
#define BUTTON_LEFT 270
#define BUTTON_PAD_UNPRESSED -1 

#define BUTTON_UP_RIGHT 45
#define BUTTON_UP_LEFT 315
#define BUTTON_DOWN_RIGHT 135
#define BUTTON_DOWN_LEFT 225

#define BUTTON_SELECT 9
#define BUTTON_START 10

#define BUTTON_L 5
#define BUTTON_R 6

// here be the latch, data and clock
// be sure your soldering is correct.
SNESpad controller = SNESpad(1,0,2);

int state = 0;
int prev_state = 0;

void setup() {
#ifdef DEBUGGING
  Serial.begin(9600);
#endif
}


void loop() {
  
  // by default the Joystick.{button,hat} call 
  // directly sends the button presses to the OS,
  // this is not what we want.
  Joystick.useManualSend(true);
  
  state = controller.buttons();
  
  //DEBUG();
  
  if (CURRENTLY_PRESSED(SNES_A)){

    Joystick.button(BUTTON_A, 1);

  }
  else if (PREVIOUSLY_PRESSED(SNES_A)) {
    Joystick.button(BUTTON_A, 0);
  }

  if (CURRENTLY_PRESSED(SNES_B)){

    Joystick.button(BUTTON_B, 1);

  }
  else if (PREVIOUSLY_PRESSED(SNES_B)) {
    Joystick.button(BUTTON_B, 0);
  }

  if (CURRENTLY_PRESSED(SNES_Y)){

    Joystick.button(BUTTON_Y, 1);

  }
  else if (PREVIOUSLY_PRESSED(SNES_Y)) {
    Joystick.button(BUTTON_Y, 0);
  }

  if (CURRENTLY_PRESSED(SNES_X)){

    Joystick.button(BUTTON_X, 1);

  }
  else if (PREVIOUSLY_PRESSED(SNES_X)) {
    Joystick.button(BUTTON_X, 0);
  }


 // Here some nasty if statements for compatibility of 
 // gamepads. If a combination of directions is pressed send 
 // the right Joystick.hat angle, else just parse them as 'normal'
 // direction buttons.

  if (CURRENTLY_PRESSED(SNES_UP) && CURRENTLY_PRESSED(SNES_RIGHT)) {
    
   Joystick.hat(BUTTON_UP_RIGHT);
  
  }else if (CURRENTLY_PRESSED(SNES_UP) && CURRENTLY_PRESSED(SNES_LEFT)) {
  
   Joystick.hat(BUTTON_UP_LEFT);
  
  }else if (CURRENTLY_PRESSED(SNES_DOWN) && CURRENTLY_PRESSED(SNES_LEFT)) {
  
   Joystick.hat(BUTTON_DOWN_LEFT);
   
  }else if (CURRENTLY_PRESSED(SNES_DOWN) && CURRENTLY_PRESSED(SNES_RIGHT)) {
  
   Joystick.hat(BUTTON_DOWN_RIGHT);
  
  // No directional combinations are pressed in this state,
  // handle them as normal directional presses.
  
  }else{
   
    if (CURRENTLY_PRESSED(SNES_UP)){

      Joystick.hat(BUTTON_UP);
      Joystick.send_now();
      
    }
    
    if (CURRENTLY_PRESSED(SNES_DOWN)){

    Joystick.hat(BUTTON_DOWN);

    }
  
   if (CURRENTLY_PRESSED(SNES_LEFT)){
  
      Joystick.hat(BUTTON_LEFT);
  
    }
  
    if (CURRENTLY_PRESSED(SNES_RIGHT)){
  
      Joystick.hat(BUTTON_RIGHT);
      Joystick.send_now();
      
    }

  }

  if (CURRENTLY_PRESSED(SNES_START)){

    Joystick.button(BUTTON_START, 1);

  }
  else if (PREVIOUSLY_PRESSED(SNES_START)) {
    
    Joystick.button(BUTTON_START, 0);
    
  }

  if (CURRENTLY_PRESSED(SNES_SELECT)){

    Joystick.button(BUTTON_SELECT, 1);

  }
  else if (PREVIOUSLY_PRESSED(SNES_SELECT)) {
    Joystick.button(BUTTON_SELECT, 0);
  }

  if (CURRENTLY_PRESSED(SNES_L)){

    Joystick.button(BUTTON_L, 1);

  }
  else if (PREVIOUSLY_PRESSED(SNES_L)) {
    Joystick.button(BUTTON_L, 0);
  }

  if (CURRENTLY_PRESSED(SNES_R)){

    Joystick.button(BUTTON_R, 1);

  }
  else if (PREVIOUSLY_PRESSED(SNES_R)) {
    Joystick.button(BUTTON_R, 0);
  }
  
  
  // keep a previous state to simulate button release.
  prev_state = state;
    
  if (!(CURRENTLY_PRESSED(SNES_LEFT) || CURRENTLY_PRESSED(SNES_RIGHT) || CURRENTLY_PRESSED(SNES_UP) || CURRENTLY_PRESSED(SNES_DOWN))) {
    
     Joystick.hat(BUTTON_PAD_UNPRESSED);
  }
  
  
  Joystick.send_now();
 
}
