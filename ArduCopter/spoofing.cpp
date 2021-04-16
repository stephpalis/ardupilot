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