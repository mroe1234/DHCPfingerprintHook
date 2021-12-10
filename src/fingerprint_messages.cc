// File created from fingerprint_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID LOG_CLIENT_FINGERPRINT = "LOG_CLIENT_FINGERPRINT";

namespace {

const char* values[] = {
    "LOG_CLIENT_FINGERPRINT", "client %1 requested options in the following order%2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

