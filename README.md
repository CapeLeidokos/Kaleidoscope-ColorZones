# Kaleidoscope-ColorZones

Define groups of keys (zones) and dynamically assign them LED colors.

## Example

The following example sketch is part of this plugin as `example/test.ino`.

```cpp
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
// Assign remote control request IDs 0 and 1 to two methods of the
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
```

This example demonstrates how two color zones 1 and 2 can be defined by means
of assigning color zone IDs to keys in a keymap-like fashion.

Via the remote control interface, colors can be assigned to the individual zones, e.g. as follows. This uses the `focus-test` tool that lives in the `bin` directory of the Kaleidoscope repo (currently only available for Linux/MacOS).

```
# Assign red (rgb = 255 0 0) to keys of zone 1
#
focus-test remote_control 0 1 255 0 0

# Assign green (rgb = 0 255 0) to keys of zone 2
#
focus-test remote_control 0 2 0 255 0 

# Clear keys of zone 2 (LEDs to black)
#
focus-test remote_control 1 2 

# Clear keys of zone 1 (LEDs to black)
#
focus-test remote_control 1 1
```

The command syntax of the `focus-test` command to assign LED colors by zone is.

```
focus-test remote_control 0 <zone ID> <R> <G> <B>
```
The first argument `0` reflects the remote control request ID.

To clear a zone, only the zone ID has to be passed as second argument (after the remote control request ID).

```
focus-test remote_control 1 <zone ID>
```

See the README of [Kaleidoscope-RemoteControl](https://github.com/CapeLeidokos/Kaleidoscope-RemoteControl.git) for more information on remote controlling Kaleidoscope.

## Color zones sparse definitions

If only few keys are supposed to be part of color zones, the definition using
`COLOR_ZONES_STACKED` would waste quite a lot of PROGMEM. 
In such a case it makes more sense to use the `COLOR_ZONES_SPARSE` function macro
instead of `COLOR_ZONES_STACKED`, e.g. as follows.

```cpp
...
COLOR_ZONES_SPARSE(
   COLOR_ZONES_MEMBER(0, 2, 3) // row = 0, col = 2, zone id = 3
   COLOR_ZONES_MEMBER(1, 2, 3) // row = 1, col = 2, zone id = 3
   COLOR_ZONES_MEMBER(3, 2, 1) // row = 3, col = 2, zone id = 1
   ...
)
```
Any keys that are not assigned a value in the sparse definition will have
zone ID 0 assigned automatically.

## Requirements

Kaleidoscope-ColorZones relies on [Kaleidoscope-XKeymaps](https://github.com/CapeLeidokos/Kaleidoscope-XKeymaps.git) for the definition of color zones.
