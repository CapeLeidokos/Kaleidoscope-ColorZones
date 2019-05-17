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

#pragma once

#include "Kaleidoscope.h"
#include "Kaleidoscope-XKeymaps.h"

#define COLOR_ZONES_STACKED(...)                                               \
   XKEYMAPS_GENERIC(                                                           \
      color_zones,                                                             \
      uint8_t,                                                                 \
      0,                                                                       \
      0,                                                                       \
      XKEYMAP_STACKED_GENERIC(                                                 \
         uint8_t,                                                              \
         0 /* keymap id */,                                                    \
         __VA_ARGS__                                                           \
      )                                                                        \
   )                                                                           \
   namespace kaleidoscope {                                             __NL__ \
   namespace plugin {                                                   __NL__ \
   namespace color_zones {                                              __NL__ \
                                                                        __NL__ \
      uint8_t zoneIDFromKeyAddr(uint8_t row, uint8_t col) {             __NL__ \
         return kaleidoscope::xkeymaps::color_zones::valueFromKeymap(0, row, col);__NL__ \
      }                                                                 __NL__ \
   } /* namespace color_zones */                                        __NL__ \
   } /* namespace plugin */                                             __NL__ \
   } /* namespace kaleidoscope */

#define COLOR_ZONES_MEMBER(ROW, COL, INDEX)                                    \
   XKEYMAP_SPARSE_ENTRY(ROW, COL, INDEX)
   
#define COLOR_ZONES_SPARSE(...)                                                \
   XKEYMAPS_GENERIC(                                                           \
      color_zones,                                                             \
      uint8_t,                                                                 \
      0,                                                                       \
      0,                                                                       \
      XKEYMAP_SPARSE_GENERIC(                                                  \
         uint8_t,                                                              \
         0 /* keymap id */,                                                    \
         DEFAULT_INDEX,                                                        \
         __VA_ARGS__                                                           \
      )                                                                        \
   )                                                                           \
   namespace kaleidoscope {                                             __NL__ \
   namespace plugin {                                                   __NL__ \
   namespace color_zones {                                              __NL__ \
                                                                        __NL__ \
      uint8_t zoneIDFromKeyAddr(uint8_t row, uint8_t col) {             __NL__ \
         return kaleidoscope::xkeymaps::color_zones::valueFromKeymap(0, row, col);__NL__ \
      }                                                                 __NL__ \
   } /* namespace color_zones */                                        __NL__ \
   } /* namespace plugin */                                             __NL__ \
   } /* namespace kaleidoscope */
   
namespace kaleidoscope {
namespace plugin {
namespace color_zones {
   
uint8_t zoneIDFromKeyAddr(uint8_t row, uint8_t col);

} // namespace color_zones
   
class ColorZones : public LEDMode {
    
   public:
      
      void setZoneColor(uint8_t zone_id, cRGB color);

      void shutOffZone(uint8_t zone_id) {
         setZoneColor(zone_id, CRGB(0, 0, 0));
      }
      
      EventHandlerResult onSetup();
      
      virtual void onActivate(void);
      
   private:
      
      cRGB key_colors_[ROWS][COLS];
};

} // namespace plugin
} // namespace kaleidoscope

extern kaleidoscope::plugin::ColorZones ColorZones;
