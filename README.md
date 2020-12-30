# DFP-34X-2C2
Some stuff about GPON Stick DFP-34X-2C2 / DFP-34G-2C2

## Set hexadecimal GPON password
(There is a pre-built binary available in releases)

- Set up a cross-compilation environment with [crosstool-ng](https://crosstool-ng.github.io/docs/)
  - Use the `ct-ng.config` in the repo, or config it as `arm-unknown-linux-uclibcgnueabi` in the samples, with CPU set to `arm9tdmi`
- Compile the dummy libtagparamuserapi.so with command like `arm-unknown-linux-uclibcgnueabi-gcc -shared -o libtagparamuserapi.so libtagparamuserapi.c`
- Compile the program with command like `arm-unknown-linux-uclibcgnueabi-gcc -std=c99 libtagparamuserapi.so -s -o setmac_hex setmac_hex.c`
- Set up a TFTP server in the same subnet, and get the executable on stick with commands like `tftp -r setmac_hex -l /var/tmp/setmac_hex -g 192.168.1.2 69 && chmod +x /var/tmp/setmac_hex`
- Telnet to stick and run command like `/var/tmp/setmac_hex 1 2178 "f2 01 80 01 02 03 04 00 00 00"` to set GPON password
- Run `setmac 2 2178` or `/var/tmp/setmac_hex 2 2178` to verify the result
