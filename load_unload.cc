// load_unload.cc
#include <hooks/hooks.h>

using namespace isc::hooks;
// "Interesting clients" log file handle definition.
std::fstream interesting;
extern "C" {
int load(LibraryHandle&) {
	return (0);
}
int unload() {
    if (interesting) {
        interesting.close();
    }
    return (0);
}
}