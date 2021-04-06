#include "Defender.h"

Defender::Defender() {
    spoof_state.last_safe_time_ms = AP_HAL::millis();
}

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
    return spoof_state.ground_speed_diff > THRESHOLD_GS_CM;
}

bool Defender::is_velocity_x_threshold_exceeded() {
    return spoof_state.velocity_x_diff > THRESHOLD_VX_CM;
}

bool Defender::is_velocity_y_threshold_exceeded() {
    return spoof_state.velocity_y_diff > THRESHOLD_VY_CM;
}

bool Defender::is_velocity_z_threshold_exceeded() {
    return spoof_state.velocity_z_diff > THRESHOLD_VZ_CM;
}

void Defender::update_spoofing_state() {
    spoof_state.ground_speed_diff = std::abs(gps_state.ground_speed - sensor_state.ground_speed);
    spoof_state.velocity_x_diff = std::abs(gps_state.velocity_x - sensor_state.velocity_x);
    spoof_state.velocity_y_diff = std::abs(gps_state.velocity_y - sensor_state.velocity_y);
    spoof_state.velocity_z_diff = std::abs(gps_state.velocity_z - sensor_state.velocity_z);

    if (!is_spoofing_detected()) {
        spoof_state.last_safe_time_ms = AP_HAL::millis();
    }
}

bool Defender::is_spoofing_detected() {
    bool time_exceeds = (AP_HAL::millis() - spoof_state.last_safe_time_ms) > THRESHOLD_SPF_SEC;

    bool diffs_exceed = (spoof_state.ground_speed_diff > THRESHOLD_GS_CM ||
                         spoof_state.velocity_x_diff > THRESHOLD_VX_CM ||
                         spoof_state.velocity_y_diff > THRESHOLD_VY_CM ||
                         spoof_state.velocity_z_diff > THRESHOLD_VZ_CM);

    bool hasGPSData = (gps_state.ground_speed != 0 ||
                       gps_state.velocity_x != 0 ||
                       gps_state.velocity_y != 0 ||
                       gps_state.velocity_z != 0);

    return hasGPSData && time_exceeds && diffs_exceed;
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