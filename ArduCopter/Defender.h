#pragma once

#include <stdio.h>
#include <cmath>

#ifndef THRESHOLD_GS_CM
#define THRESHOLD_GS_CM 133
#endif

#ifndef THRESHOLD_VX_CM
#define THRESHOLD_VX_CM 151
#endif

#ifndef THRESHOLD_VY_CM
#define THRESHOLD_VY_CM 65
#endif

#ifndef THRESHOLD_VZ_CM
#define THRESHOLD_VZ_CM 7
#endif

class Defender {
public:
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

private:
    struct SensorState {
        int16_t ground_speed;
        int16_t velocity_x;
        int16_t velocity_y;
        int16_t velocity_z;
    } gps_state, sensor_state;

    struct SpoofState {
        bool ground_speed_exceeded;
        bool velocity_x_exceeded;
        bool velocity_y_exceeded;
        bool velocity_z_exceeded;
    } spoof_state;
};
