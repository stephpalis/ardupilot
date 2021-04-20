#include "Defender.h"

Defender::Defender() {
    spoof_state.last_safe_time_ms = AP_HAL::millis();
}

// ==============================================================================================================
// FUNCTIONS FOR GPS
// ==============================================================================================================

int16_t Defender::get_gps_velocity_x() {
    return gps_state.velocity_x;
}

int16_t Defender::get_gps_velocity_y() {
    return gps_state.velocity_y;
}

int16_t Defender::get_gps_velocity_z() {
    return gps_state.velocity_z;
}

int16_t Defender::get_gps_ground_speed() {
    return gps_state.ground_speed;
}

int16_t Defender::get_gps_altitude() {
    return gps_state.altitude;
}

// ==============================================================================================================
// FUNCTIONS FOR INHIBITED EKF
// ==============================================================================================================

int16_t Defender::get_inhibited_velocity_x() {
    return inhibited_state.velocity_x;
}

int16_t Defender::get_inhibited_velocity_y() {
    return inhibited_state.velocity_y;
}

int16_t Defender::get_inhibited_velocity_z() {
    return inhibited_state.velocity_z;
}

int16_t Defender::get_inhibited_ground_speed() {
    return inhibited_state.ground_speed;
}

int16_t Defender::get_inhibited_altitude() {
    return inhibited_state.altitude;
}

// ==============================================================================================================
// FUNCTIONS FOR UNINHIBITED EKF
// ==============================================================================================================

int16_t Defender::get_uninhibited_velocity_x() {
    return uninhibited_state.velocity_x;
}

int16_t Defender::get_uninhibited_velocity_y() {
    return uninhibited_state.velocity_y;
}

int16_t Defender::get_uninhibited_velocity_z() {
    return uninhibited_state.velocity_z;
}

int16_t Defender::get_uninhibited_ground_speed() {
    return uninhibited_state.ground_speed;
}

int16_t Defender::get_uninhibited_altitude() {
    return uninhibited_state.altitude;
}

// ==============================================================================================================
// FUNCTIONS FOR THRESHOLDS
// ==============================================================================================================

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

bool Defender::is_altitude_threshold_exceeded() {
    return spoof_state.altitude_diff > THRESHOLD_ALT_CM;
}

// ==============================================================================================================
// FUNCTIONS FOR SPOOFING
// ==============================================================================================================

void Defender::update_spoofing_state() {
    spoof_state.ground_speed_diff = std::abs(gps_state.ground_speed - inhibited_state.ground_speed);
    spoof_state.velocity_x_diff = std::abs(gps_state.velocity_x - inhibited_state.velocity_x);
    spoof_state.velocity_y_diff = std::abs(gps_state.velocity_y - inhibited_state.velocity_y);
    spoof_state.velocity_z_diff = std::abs(gps_state.velocity_z - inhibited_state.velocity_z);
    spoof_state.altitude_diff = std::abs(gps_state.altitude - initial_gps_altitude - inhibited_state.altitude);

    // update last safe threshold time if thresholds are not exceeded
    if (!is_threshold_count_exceeded()) {
        spoof_state.last_safe_time_ms = AP_HAL::millis();
    }
}

bool Defender::is_threshold_count_exceeded() {
    int count_exceeded = 0;
    if (spoof_state.ground_speed_diff >= THRESHOLD_GS_CM) {
        count_exceeded++;
    }
    if (spoof_state.velocity_x_diff >= THRESHOLD_VX_CM) {
        count_exceeded++;
    }
    if (spoof_state.velocity_y_diff >= THRESHOLD_VY_CM) {
        count_exceeded++;
    }
    if (spoof_state.velocity_z_diff >= THRESHOLD_VZ_CM) {
        count_exceeded++;
    }
    if (spoof_state.altitude_diff >= THRESHOLD_ALT_CM) {
        count_exceeded++;
    }

    return (count_exceeded >= THRESHOLD_DIFF_COUNT);
}

bool Defender::is_spoofing_detected() {
    // ==============================================================================================================
    // CHECK FOR PROLONGED DETECTION
    // ==============================================================================================================
    bool below_time_threshold = (AP_HAL::millis() - spoof_state.last_safe_time_ms) < THRESHOLD_SPF_MS;
    if (below_time_threshold) {
        return false;
    }

    // ==============================================================================================================
    // CHECK FOR VALID GPS DATA
    // ==============================================================================================================
    if (EXPECT_GPS_DATA) {
        bool no_gps_data = (gps_state.ground_speed == 0 &&
                            gps_state.velocity_x == 0 &&
                            gps_state.velocity_y == 0 &&
                            gps_state.velocity_z == 0 &&
                            gps_state.altitude == 0);
        if (no_gps_data) {
            return false;
        }
    }

    return true;
}

void Defender::set_initial_gps_altitude(int16_t alt) {
    initial_gps_altitude = alt;
}

void Defender::set_gps_state(int16_t gs, int16_t vx, int16_t vy, int16_t vz, int16_t alt) {
    gps_state.ground_speed = gs;
    gps_state.velocity_x = vx;
    gps_state.velocity_y = vy;
    gps_state.velocity_z = vz;
    gps_state.altitude = alt;
}

void Defender::set_uninhibited_state(int16_t gs, int16_t vx, int16_t vy, int16_t vz, int16_t alt) {
    uninhibited_state.ground_speed = gs;
    uninhibited_state.velocity_x = vx;
    uninhibited_state.velocity_y = vy;
    uninhibited_state.velocity_z = vz;
    uninhibited_state.altitude = alt;
}

void Defender::set_inhibited_state(int16_t gs, int16_t vx, int16_t vy, int16_t vz, int16_t alt) {
    inhibited_state.ground_speed = gs;
    inhibited_state.velocity_x = vx;
    inhibited_state.velocity_y = vy;
    inhibited_state.velocity_z = vz;
    inhibited_state.altitude = alt;
}