// File created from src/fingerprint_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID CLIENT_FINGERPRINT = "CLIENT_FINGERPRINT";

namespace {

const char* values[] = {
    "CLIENT_FINGERPRINT", "client=%1 requested options=%2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

