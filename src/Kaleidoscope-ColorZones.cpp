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

#include "Kaleidoscope-ColorZones.h"
#include "Kaleidoscope-LEDControl.h"

namespace kaleidoscope {
namespace plugin {
namespace color_zones {
   
__attribute__((weak)) 
uint8_t zoneIDFromKeyAddr(uint8_t row, uint8_t col) {
   return 0;
}

} // namespace color_zones

EventHandlerResult ColorZones::onSetup() {
   
   for(uint8_t row = 0; row < ROWS; ++row) {
      for(uint8_t col = 0; col < COLS; ++col) {
         key_colors_[row][col] = CRGB(0, 0, 0);
      }
   }
   
   return EventHandlerResult::OK;
}
   
void ColorZones::setZoneColor(uint8_t zone_id, cRGB color) {
   
   bool is_active = true;
   if (::LEDControl.get_mode() != this) {
      is_active = false;
   }
   
   bool changes_happened = false;
   for(uint8_t row = 0; row < ROWS; ++row) {
      for(uint8_t col = 0; col < COLS; ++col) {
         
         uint8_t key_zone_id = color_zones::zoneIDFromKeyAddr(row, col);
         
         if(key_zone_id == zone_id) {
            
            key_colors_[row][col] = color;
            
            if(is_active) {
               ::LEDControl.setCrgbAt(row, col, color);
            }
            changes_happened = true;
         }
      }
   }
   
   if(is_active && changes_happened) {
      ::LEDControl.syncLeds();
   }
}

void ColorZones::onActivate(void) {
   
   for(uint8_t row = 0; row < ROWS; ++row) {
      for(uint8_t col = 0; col < COLS; ++col) {
         ::LEDControl.setCrgbAt(row, col, key_colors_[row][col]);
      }
   }
   
   ::LEDControl.syncLeds();
}

} // namespace plugin
} // namespace kaleidoscope

kaleidoscope::plugin::ColorZones ColorZones;
