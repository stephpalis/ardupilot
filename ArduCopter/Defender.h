#pragma once

#include <stdio.h>
#include <cmath>

#include <AP_HAL/AP_HAL.h>

#ifndef THRESHOLD_GS_CM
//#define THRESHOLD_GS_CM 109
#define THRESHOLD_GS_CM 184
#endif

#ifndef THRESHOLD_VX_CM
//#define THRESHOLD_VX_CM 115
#define THRESHOLD_VX_CM 190
#endif

#ifndef THRESHOLD_VY_CM
//#define THRESHOLD_VY_CM 74
#define THRESHOLD_VY_CM 149
#endif

#ifndef THRESHOLD_VZ_CM
//#define THRESHOLD_VZ_CM 40
#define THRESHOLD_VZ_CM 115
#endif

#ifndef THRESHOLD_SPF_MS
#define THRESHOLD_SPF_MS 2000
#endif

#ifndef THRESHOLD_DIFF_COUNT
#define THRESHOLD_DIFF_COUNT 3
#endif

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
    struct SensorState {
        int16_t ground_speed;
        int16_t velocity_x;
        int16_t velocity_y;
        int16_t velocity_z;
    } gps_state, inhibited_state, uninhibited_state;
};
