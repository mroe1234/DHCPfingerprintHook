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
The configuration for Kea is pretty simple as it does not take any parameters.  There is an optional parameter
to set the style of option logging.  The choice is between "dec" (decimal), and "hex" (hexadecimal).  If
no option is provided it will default to decimal.

```    
"hooks-libraries": [
      {
          "library": "/usr/local/lib/kea/hooks/libfingerprint.so",
          "parameters": {
              "opt_fmt": "hex"
          }
      }

    ],
```

Once configured Kea should start logging lines that look something like this:

```
INFO  [kea-dhcp4.fingerprint/27634.139948128566272] CLIENT_FINGERPRINT client=00:50:56:bf:ba:d4 requested options=36:32:0c:37:3c:3d
```
## Support
Feedback and PRs are absolutely welcome.  Enjoy.