#include <Arduino.h>
#include <Servo.h>

#include "action.h"
#include "config.h"

Servo servos[NUM_SERVOS];

uint8_t current_pos[NUM_SERVOS] = { 0 };
uint32_t start_time[NUM_SERVOS] = { 0 };
uint32_t travel_time[NUM_SERVOS] = { 0 };
uint8_t start_pos[NUM_SERVOS] = { 0 };
uint8_t target_pos[NUM_SERVOS] = { 0 };

const uint16_t NUM_ACTIONS = sizeof(actions) / sizeof(action_t);
uint8_t activated[NUM_ACTIONS] = { 0 };

void init_servo_pos() {
  for (uint8_t i = 0; i < NUM_SERVOS; i++) {
    servos[i].write(HOME_POSITION[i]);
    current_pos[i] = HOME_POSITION[i];
  }
}

void setup() {
  for (uint8_t i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(PINS_SERVOS[i]);
    init_servo_pos();
  }

  Serial.begin(115200);
}

void loop() {
  static uint32_t sequence_start_time = millis();
  uint32_t cur_time = millis();

  if ((cur_time - sequence_start_time) > RESET_TIME) {
    sequence_start_time = cur_time;

    memset(activated, 0, sizeof(activated));
    init_servo_pos();
  }

  for (uint8_t i = 0; i < NUM_ACTIONS; i++) {
    if (activated[i]) {
      continue;
    }

    if ((cur_time - sequence_start_time) < actions[i].start_time) {
      continue;
    }

    const action_t &action = actions[i];

    start_time[action.servo_num] = cur_time;
    travel_time[action.servo_num] = action.time_to_take;
    start_pos[action.servo_num] = current_pos[action.servo_num];
    target_pos[action.servo_num] = action.target_angle;

    activated[i] = 1;
  }

  for (uint8_t i = 0; i < NUM_SERVOS; i++) {
    // this servo has finished its movement
    if ((cur_time - start_time[i]) > travel_time[i]) {
      continue;
    }

    if (travel_time[i] == 0) {
      continue;
    }

    int16_t change = (((int32_t) target_pos[i] - start_pos[i]) * (int32_t) (cur_time - start_time[i]) / (int16_t) travel_time[i]);

    current_pos[i] = start_pos[i] + change;
    servos[i].write(current_pos[i]);
    Serial.print("t=");
    Serial.print(cur_time);
    Serial.print(" Servo ");
    Serial.print(i);
    Serial.print(": angle=");
    Serial.println(current_pos[i]);
  }
}
