#g++ -I /usr/local/include/kea
#  -L /usr/local/lib -fpic -shared 
#  -o libfingerprint.so 
# load_unload.cc buffer4_receive.cc version.cc fingerprint_log.cc fingerprint_messages.cc
# -lkea-dhcpsrv -lkea-dhcp++ -lkea-hooks -lkea-log -lkea-util -lkea-exceptions

#UPDATE PATHS IF DIFFERENT
KEA_MSG_COMPILER ?= kea-msg-compiler
KEA_INCLUDE ?= /usr/local/include/kea/
KEA_LIB ?= /usr/local/lib

OBJECTS = src/load_unload.o src/version.o src/buffer4_receive.o src/fingerprint_log.o src/fingerprint_messages.o src/multi_threading_compatible.o
DEPS = $(OBJECTS:.o=.d)
CXXFLAGS = -I $(KEA_INCLUDE) -fpic -shared
LDFLAGS = -L $(KEA_LIB) -shared -lkea-dhcpsrv -lkea-dhcp++ -lkea-hooks -lkea-log -lkea-util -lkea-exceptions

libfingerprint.so: $(OBJECTS)
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $(OBJECTS)

%.o: %.cc
	$(CXX) -MMD -MP -c $(CXXFLAGS) -o $@ $<

clean:
	rm -f src/*.o
	rm -f src/*.d
	rm -f fingerprint.so

-include $(DEPS)