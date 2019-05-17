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
COLOR_ZONES(
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

Via the remote control interface, using the `focus-test` tool (only available for unixoid OS) colors can be assigned to the individual 
zones, e.g.

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

## Requirements

Kaleidoscope-ColorZones relies on [Kaleidoscope-XKeymaps](https://github.com/CapeLeidokos/Kaleidoscope-XKeymaps.git) for the definition of color zones.
