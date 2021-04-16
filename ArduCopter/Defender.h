#pragma once

#include <stdio.h>
#include <cmath>

#include <AP_HAL/AP_HAL.h>

// whether or not to send sensor data messages
//#ifndef DEF_SEND_DATA
//#define DEF_SEND_DATA
//#endif

// whether or not to send spoofing detection messages
#ifndef DEF_SEND_SPF
#define DEF_SEND_SPF
#endif

class Defender {
public:
    Defender();

    // GPS data
    int16_t get_gps_velocity_x();
    int16_t get_gps_velocity_y();
    int16_t get_gps_velocity_z();
    int16_t get_gps_ground_speed();

    // EKF inhibited data
    int16_t get_inhibited_velocity_x();
    int16_t get_inhibited_velocity_y();
    int16_t get_inhibited_velocity_z();
    int16_t get_inhibited_ground_speed();

    // EKF uninhibited data
    int16_t get_uninhibited_velocity_x();
    int16_t get_uninhibited_velocity_y();
    int16_t get_uninhibited_velocity_z();
    int16_t get_uninhibited_ground_speed();

    // thresholds
    bool is_ground_speed_threshold_exceeded();
    bool is_velocity_x_threshold_exceeded();
    bool is_velocity_y_threshold_exceeded();
    bool is_velocity_z_threshold_exceeded();
    bool is_threshold_count_exceeded();

    // spoofing
    bool is_spoofing_detected();
    void update_spoofing_state();

    void set_gps_state(int16_t gs, int16_t vx, int16_t vy, int16_t vz);
    void set_uninhibited_state(int16_t gs, int16_t vx, int16_t vy, int16_t vz);
    void set_inhibited_state(int16_t gs, int16_t vx, int16_t vy, int16_t vz);

    struct SpoofState {
        int16_t ground_speed_diff;
        int16_t velocity_x_diff;
        int16_t velocity_y_diff;
        int16_t velocity_z_diff;
        uint32_t last_safe_time_ms;
    } spoof_state;

private:
//    const uint16_t THRESHOLD_ADD = 75;
//    const uint16_t THRESHOLD_GS_CM = (109 + THRESHOLD_ADD);
//    const uint16_t THRESHOLD_VX_CM = (115 + THRESHOLD_ADD);
//    const uint16_t THRESHOLD_VY_CM = (74 + THRESHOLD_ADD);
//    const uint16_t THRESHOLD_VZ_CM = (40 + THRESHOLD_ADD);
//    const uint16_t THRESHOLD_SPF_MS = 2000;
//    const uint16_t THRESHOLD_DIFF_COUNT = 3;
//    const bool EXPECT_GPS_DATA = true;

    const uint16_t THRESHOLD_GS_CM = 20;
    const uint16_t THRESHOLD_VX_CM = 20;
    const uint16_t THRESHOLD_VY_CM = 20;
    const uint16_t THRESHOLD_VZ_CM = 20;
    const uint16_t THRESHOLD_SPF_MS = 2000;
    const uint16_t THRESHOLD_DIFF_COUNT = 2;
    const bool EXPECT_GPS_DATA = false;

    struct SensorState {
        int16_t ground_speed;
        int16_t velocity_x;
        int16_t velocity_y;
        int16_t velocity_z;
    } gps_state, inhibited_state, uninhibited_state;
};
