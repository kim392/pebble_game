#include <time.h>
#pragma once

#define NUMBER_SPRITES 2
  
typedef struct{
  int is24Pass; // boolean
  int catch_hours;
  float lati;
  float longi;
  int monster;
} catch_t;

void catch_init(catch_t *);
void catch_timer(catch_t *, TextLayer *);
void catch_decide(catch_t *, TextLayer *);
// void catch_destroy(catch_t *);