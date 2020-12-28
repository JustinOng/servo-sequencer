#ifndef CONFIG_H
#define CONFIG_H

#include "action.h"

#define NUM_SERVOS 2

// pins that the servos are connected to
// in this case, servo 0 is pin 2, servo 1 is pin 3
const uint8_t PINS_SERVOS[NUM_SERVOS] = { 2, 3 };
// initial home position for the corresponding servos
// on sequence start, the servos will be set to this position, between 0 to 180
const uint8_t HOME_POSITION[NUM_SERVOS] = { 90, 60 };

// whether to return to home at the start of sequence
// if uncommented: returns to home at the start of sequence
// if commented: returns to home only upon powerup initially
#define HOME_AT_SEQUENCE_START

// time in milliseconds after which the sequence will restart
const uint32_t RESET_TIME = 10000;

// list of actions to make
/*
  each action consists of the following:
  - servo_num: which servo to move (this is not the pin number)
  - start_time: time in milliseconds at which to start ths movement
  - time_to_take: time in milliseconds to take to complete this move
  - target_angle: angle (0 to 180) to move to

  eg the following, at sequence time 0, will start a move to angle 180 over 500ms
    .servo_num = 0,
    .start_time = 0,
    .time_to_take = 500,
    .target_angle = 180
*/
const action_t actions[] = {
  {
    .servo_num = 0,
    .start_time = 0,
    .time_to_take = 3000,
    .target_angle = 40
  },
  {
    .servo_num = 0,
    .start_time = 3000,
    .time_to_take = 1000,
    .target_angle = 140
  },
  {
    .servo_num = 1,
    .start_time = 0,
    .time_to_take = 4000,
    .target_angle = 70
  },
  {
    .servo_num = 1,
    .start_time = 4000,
    .time_to_take = 4000,
    .target_angle = 50
  }
};

#endif
