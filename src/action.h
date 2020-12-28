#ifndef ACTION_H
#define ACTION_H

typedef struct {
  uint8_t servo_num;
  uint32_t start_time;   // time in ms to start this action at
  uint32_t time_to_take; // time in ms to take to move from current to target_angle
  uint8_t target_angle;  // 0 - 180
} action_t;

#endif
