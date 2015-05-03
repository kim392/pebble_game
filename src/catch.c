#include <pebble.h>
#include <time.h>
#include "catch.h"
  
void catch_init(catch_t *cptr)
{
  cptr->is24Pass = 0;
  cptr->catch_hours = 0;
  cptr->lati = 0;
  cptr->longi = 0;
  cptr->monster = 0;
}
  
void catch_timer(catch_t *cptr, TextLayer * text_layer)
{
  char daybuf[10];
  char houbuf[10];
  // Get current time
  time_t current_time;
  time (&current_time);
  struct tm * timeinfo = localtime (&current_time);
    
    strftime (houbuf,80,"%H",timeinfo);
    strftime (daybuf,80,"%e",timeinfo);
    
    int temp_hours = atoi(houbuf);
    int temp_days = atoi(daybuf);
    temp_hours += temp_days * 24;
    
    int diff_hours = temp_hours - cptr->catch_hours;
    
    if(diff_hours >= 24 || cptr->catch_hours == 0)
    {
      cptr->is24Pass = 1;
      cptr->catch_hours = temp_hours;
      text_layer_set_text(text_layer, "24 hours passed!"); // Can Catch!
    }
    else
    {
      cptr->is24Pass = 0;
      text_layer_set_text(text_layer, ""); // Can't
    }  
}

void catch_decide(catch_t * cptr, TextLayer * text_layer)
{
  int lat = cptr->lati;
  int sum = 0;
  for(int i=0; i < lat; i++)
      sum += i;
  if(sum % NUMBER_SPRITES == 0){
    cptr->monster = 0;
  text_layer_set_text(text_layer, "Caught Monster #1!");
  }
  else if(sum % NUMBER_SPRITES == 1){
    cptr->monster = 1;
  text_layer_set_text(text_layer, "Caught Monster #2!");
  }
  // until 6
  else if (sum % NUMBER_SPRITES == NUMBER_SPRITES - 1){
    cptr->monster = NUMBER_SPRITES - 1;
  text_layer_set_text(text_layer, "Caught Monster #3!");
  }
}