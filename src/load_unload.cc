// load_unload.cc
#include <hooks/hooks.h>

using namespace isc::hooks;
using namespace isc::data;

std::string opt_fmt_ptr;

extern "C" {


int load(LibraryHandle& handle) {
    ConstElementPtr opt_fmt = handle.getParameter("opt_fmt");
       // String handling example
    if (!opt_fmt) {
        // Handle missing 'mail' parameter here.
        return (1);
    }
    if (opt_fmt->getType() != Element::string) {
        // Handle incorrect 'mail' parameter here.
        return (1);
    }
    std::string opt_fmt_str = opt_fmt->stringValue();
    opt_fmt_ptr = opt_fmt_str;
    
	return (0);
}
int unload() {
    return (0);
}
}
