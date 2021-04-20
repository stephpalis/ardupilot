#include "Copter.h"

void Copter::handle_spoofing() {
    if (!failsafe.spoofing) {
        set_failsafe_spoofing(true);
    }
}

void Copter::clear_spoofing() {
    if (failsafe.spoofing) {
        set_failsafe_spoofing(false);
    }
}

void Copter::init_defender() {
    int32_t gps_alt_raw;
    bool is_valid_alt = gps.location().get_alt_cm(Location::AltFrame::ABSOLUTE, gps_alt_raw);  // cm
    int16_t gps_alt = (int16_t)(gps_alt_raw);
    if (!is_valid_alt) {
        gcs().send_text(MAV_SEVERITY_CRITICAL, "Bad GPS Altitude");
    }

    defender.set_initial_gps_altitude(gps_alt);
    gcs().send_text(MAV_SEVERITY_CRITICAL, "Setting GPS Initial Altitude: %d cm", gps_alt);
}