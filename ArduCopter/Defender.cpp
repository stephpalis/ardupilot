#include "Defender.h"

int16_t Defender::get_gps_velocity_x() {
    return gps_state.velocity_x;
}

int16_t Defender::get_gps_velocity_y() {
    return gps_state.velocity_y;
}

int16_t Defender::get_gps_velocity_z() {
    return gps_state.velocity_z;
}

int16_t Defender::get_sd_velocity_x() {
    return sensor_state.velocity_x;
}

int16_t Defender::get_sd_velocity_y() {
    return sensor_state.velocity_y;
}

int16_t Defender::get_sd_velocity_z() {
    return sensor_state.velocity_z;
}

int16_t Defender::get_gps_ground_speed() {
    return gps_state.ground_speed;
}

int16_t Defender::get_sd_ground_speed() {
    return sensor_state.ground_speed;
}

bool Defender::is_ground_speed_threshold_exceeded() {
    return spoof_state.ground_speed_exceeded;
}

bool Defender::is_velocity_x_threshold_exceeded() {
    return spoof_state.velocity_x_exceeded;
}

bool Defender::is_velocity_y_threshold_exceeded() {
    return spoof_state.velocity_y_exceeded;
}

bool Defender::is_velocity_z_threshold_exceeded() {
    return spoof_state.velocity_z_exceeded;
}

void Defender::update_spoofing_state() {
    spoof_state.ground_speed_exceeded = std::abs(gps_state.ground_speed - sensor_state.ground_speed) > THRESHOLD_GS_CM;
    spoof_state.velocity_x_exceeded = std::abs(gps_state.velocity_x - sensor_state.velocity_x) > THRESHOLD_VX_CM;
    spoof_state.velocity_y_exceeded = std::abs(gps_state.velocity_y - sensor_state.velocity_y) > THRESHOLD_VY_CM;
    spoof_state.velocity_z_exceeded = std::abs(gps_state.velocity_z - sensor_state.velocity_z) > THRESHOLD_VZ_CM;
}

bool Defender::is_spoofing_detected() {
    update_spoofing_state();

    return spoof_state.ground_speed_exceeded ||
           spoof_state.velocity_x_exceeded ||
           spoof_state.velocity_y_exceeded ||
           spoof_state.velocity_z_exceeded;
}

void Defender::set_gps_state(int16_t gs, int16_t vx, int16_t vy, int16_t vz) {
    gps_state.ground_speed = gs;
    gps_state.velocity_x = vx;
    gps_state.velocity_y = vy;
    gps_state.velocity_z = vz;
}

void Defender::set_sensor_state(int16_t gs, int16_t vx, int16_t vy, int16_t vz) {
    sensor_state.ground_speed = gs;
    sensor_state.velocity_x = vx;
    sensor_state.velocity_y = vy;
    sensor_state.velocity_z = vz;
}