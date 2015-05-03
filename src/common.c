#include <pebble.h>
#include "common.h"
#include "sprite.h"

#define ANIMATION_SETTING true
    
Window *catchSelect;
Window *eatAnimation;

void goToCatch() {
  window_stack_push(catchSelect, ANIMATION_SETTING);
}

void goToEat() {
    window_stack_push(eatAnimation, ANIMATION_SETTING);
}