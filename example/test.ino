/* Kaleidoscope-ColorZones
 * Copyright (C) 2019 noseglasses (shinynoseglasses@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-ColorZones.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-RemoteControl.h"
#include "Kaleidoscope-FocusSerial.h"

// Every color zone is define by a unique ID. Every key is assigned the 
// zone it belongs to.
//
COLOR_ZONES_STACKED(
   0, 0, 0, 0, 0, 0, 0,
   0, 1, 1, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 0,
   0, 0, 0, 2, 2, 2, 0,
   0, 0, 0, 0,
   0,

   0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0,
   0 
)

// Remote control zone coloring.
// Assign remote control request ids 0 and 1 to two methods of the
// ColorZones plugin.
//
#define REMOTE_CONTROL(OP) \
   OBJECT_METHOD(OP, 0, ::ColorZones, setZoneColor) \
   OBJECT_METHOD(OP, 1, ::ColorZones, shutOffZone)
   
REMOTE_CONTROL_INIT(REMOTE_CONTROL) 

KALEIDOSCOPE_INIT_PLUGINS(
   Focus, // Required by RemoteControl
   RemoteControl,
   LEDControl,
   ColorZones
);

void setup() {  
   Kaleidoscope.setup();
}

void loop() {
  Kaleidoscope.loop();
}
