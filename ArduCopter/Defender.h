#pragma once

#include <stdio.h>
#include <cmath>

#include <AP_HAL/AP_HAL.h>

#ifndef THRESHOLD_GS_CM
#define THRESHOLD_GS_CM 109
#endif

#ifndef THRESHOLD_VX_CM
#define THRESHOLD_VX_CM 115
#endif

#ifndef THRESHOLD_VY_CM
#define THRESHOLD_VY_CM 74
#endif

#ifndef THRESHOLD_VZ_CM
#define THRESHOLD_VZ_CM 40
#endif

#ifndef THRESHOLD_SPF_SEC
#define THRESHOLD_SPF_SEC 2
#endif

class Defender {
public:
    Defender();

    int16_t get_gps_velocity_x();

    int16_t get_gps_velocity_y();

    int16_t get_gps_velocity_z();

    int16_t get_sd_velocity_x();

    int16_t get_sd_velocity_y();

    int16_t get_sd_velocity_z();

    int16_t get_gps_ground_speed();

    int16_t get_sd_ground_speed();

    bool is_spoofing_detected();

    bool is_ground_speed_threshold_exceeded();

    bool is_velocity_x_threshold_exceeded();

    bool is_velocity_y_threshold_exceeded();

    bool is_velocity_z_threshold_exceeded();

    void set_gps_state(int16_t gs, int16_t vx, int16_t vy, int16_t vz);

    void set_sensor_state(int16_t gs, int16_t vx, int16_t vy, int16_t vz);

    void update_spoofing_state();

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
    } gps_state, sensor_state;
};
