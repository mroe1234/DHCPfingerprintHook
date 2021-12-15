// pkt_receive4.cc
#include <hooks/hooks.h>
#include <dhcp/pkt4.h>
#include <string>
#include <log/message_initializer.h>
#include <log/macros.h>
#include "fingerprint_log.h"
#include <iomanip>
using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::log;
using namespace isc::fingerprint;

string option_format = "dec";

extern "C" {

int load(LibraryHandle& handle) {
    ConstElementPtr opt_fmt = handle.getParameter("opt_fmt");
       // String handling example
    if (!opt_fmt) {
        return (0);
    }
    if (opt_fmt->getType() != Element::string) {
        // Handle incorrect 'mail' parameter here.
        return (1);
    }
    option_format = opt_fmt->stringValue();
	return (0);
}

int unload() {
    return (0);
}

string int_to_hex (int num) {
	std::stringstream stream;
	stream << std::setw(2) << std::setfill('0') << std::hex << num;
	return (stream.str());
}
//Scans the packet buffer for the magic cookie to know where the options start
//99,130,83,99 is the decimal representation of the cookie
//There is a potential bug, I believe almost entirely hypothetical that if there is a 99
//right before the actual magic cookie, this will fail.
//returns the position of the first option
size_t find_magic_cookie(OptionBuffer& buf) {
	size_t offset = 0;
	while (offset < buf.size()) {		
		if (buf[offset++] == 99) {
			if (buf[offset++] == 130) {
				if(buf[offset++] == 83) {
					if(buf[offset++] == 99){
						return (offset);
					}
				}
			}
		}
    }

return (offset);
}
int pkt4_receive(CalloutHandle& handle) {
    
    // A pointer to the packet is passed to the callout via a "boost" smart
    // pointer. The include file "pkt4.h" typedefs a pointer to the Pkt4
    // object as Pkt4Ptr.  Retrieve a pointer to the object.
    Pkt4Ptr query4_ptr;
    handle.getArgument("query4", query4_ptr);
    // Point to the hardware address.
    HWAddrPtr hwaddr_ptr = query4_ptr->getHWAddr();

    OptionBuffer buf;
    buf = query4_ptr->data_;
    //If this is not a request packet, we can skip the rest.
    if (query4_ptr->getType() != 3){
    	return(0);
    	}
    	
    //I used libdhcp++.cc ~line 459 as a model for this code, as I am just collecting the
    //option types, I don't care about some of the safeties.
    size_t offset = find_magic_cookie(buf);
	string option_list;
    while (offset < buf.size()) {

    	uint8_t opt_type = buf[offset++];
    	uint8_t opt_len =  buf[offset++];
    	if (opt_type == 255) {
    		//cout << "last option\n";
     		//last option
     		//not really an 'option perse' so not adding it
     		break;
     	}
     	
     	//option 53 is message type, not really an 'option' either.
		if (opt_type == 53) {
			//cout << "DHCP message type, not an option.\n";
			offset = offset+opt_len;
     		continue;
     	}

     	if (opt_type == 0) {
     		//cout << "Skipping for option 0\n";
     		continue;
     	}
    	if (offset + 1 > buf.size()) {
    		//out of bounds option ignore and end
    	}
    	if (offset + opt_len > buf.size()) {
    		//out of bound option, ignore and end
    	}
    	offset = offset+opt_len;
    	//concatenates all of the options into a string for logging
    	string option = to_string(opt_type);
    	if (option_format == "hex") {
    		option = int_to_hex(int(opt_type));
    	}
    	option_list = option_list +option+":";
	}
	//associates the HW address with options requested for fingerprinting
	option_list.pop_back();
	LOG_INFO(fingerprint_logger, CLIENT_FINGERPRINT).arg(query4_ptr->getHWAddr()->toText(false)).arg(option_list);
    return (0);
};

}
