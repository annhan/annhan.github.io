---
layout: default
title: 
---
   ````
   enum State_t {
        AXIS_STATE_UNDEFINED = 0,           //<! will fall through to idle
        AXIS_STATE_IDLE = 1,                //<! disable PWM and do nothing
        AXIS_STATE_STARTUP_SEQUENCE = 2, //<! the actual sequence is defined by the config.startup_... flags
        AXIS_STATE_FULL_CALIBRATION_SEQUENCE = 3,   //<! run all calibration procedures, then idle
        AXIS_STATE_MOTOR_CALIBRATION = 4,   //<! run motor calibration
        AXIS_STATE_SENSORLESS_CONTROL = 5,  //<! run sensorless control
        AXIS_STATE_ENCODER_INDEX_SEARCH = 6, //<! run encoder index search
        AXIS_STATE_ENCODER_OFFSET_CALIBRATION = 7, //<! run encoder offset calibration
        AXIS_STATE_CLOSED_LOOP_CONTROL = 8,  //<! run closed loop control
        AXIS_STATE_LOCKIN_SPIN = 9,       //<! run lockin spin
        AXIS_STATE_ENCODER_DIR_FIND = 10,
        AXIS_STATE_HOMING = 11,   //<! run axis homing function
    };
    State_t& current_state_ = task_chain_.front();
    std::array<State_t, 10> task_chain_ = { AXIS_STATE_UNDEFINED };
    std::fill(task_chain_.begin(), task_chain_.end(), AXIS_STATE_UNDEFINED);
    std::rotate(task_chain_.begin(), task_chain_.begin() + 1, task_chain_.end());
    task_chain_[pos++] = AXIS_STATE_MOTOR_CALIBRATION;
    ```
