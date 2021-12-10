# ISC Kea for DHCP Fingerprint Logger

This is a hook library to augment the logging of Kea to include a log line with the options a client requests in a DHCPREQUEST packet.  This information can be used to fingerprint a device or operating system.  


## Building
There is a rudimentary Makefile included.  The default parameters were set with the assumption that kea was compiled from source into /usr/local/.  If this is not correct for your system, you must update the paths in the following statements:

```
KEA_INCLUDE ?= /usr/local/include/kea/
KEA_LIB ?= /usr/local/lib
```
Once these paths are correct, just run ```make``` and it will create ```libfingerprint.so```.  Copy ```libfingerprint.so``` to the hooks directory (ex: ```/usr/local/lib/kea/hooks/```).

## Configuration for Kea
The configuration for Kea is pretty simple as it does not take any parameters.
```    
"hooks-libraries": [
      {
          "library": "/usr/local/lib/kea/hooks/libfingerprint.so"
      }
    ],
```

Once configured Kea should start logging lines that look something like this:

```
INFO  [kea-dhcp4.fingerprint/23626.140526963117056] LOG_CLIENT_FINGERPRINT client hwtype=1 00:50:56:bf:ba:d4 requested options in the following order 53 54 50 12 55 60 61 255
```
## Support
Feedback and PRs are absolutely welcome.  Enjoy.