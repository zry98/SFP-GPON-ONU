# DFP-34X-2C2
Some stuff about GPON Stick DFP-34X-2C2 / DFP-34G-2C2

## Set hexadecimal GPON password

- Set up a cross-compilation environment with [crosstool-ng](https://crosstool-ng.github.io/docs/)
  - Use the `ct-ng.config` in the repo, or config it as `arm-unknown-linux-uclibcgnueabi` in the samples, with CPU set to `arm9tdmi`
- Compile libtagparamuserapi.so with command like `arm-unknown-linux-uclibcgnueabi-gcc -shared -o libtagparamuserapi.so libtagparamuserapi.c`
- Compile the program with command like `arm-unknown-linux-uclibcgnueabi-gcc -std=c99 libtagparamuserapi.so -s -o setmac_hex setmac_hex.c`
- Send compiled executable to the stick through telnet using the python script `telnet_send.py`
- Telnet to the stick and run command like `/var/tmp/setmac_hex 1 2178 "f2 01 80 01 02 03 04 00 00 00"` (replace the hex string in quotes) to set GPON password
- Run `setmac 2 2178` or `/var/tmp/setmac_hex 2 2178` to verify the result
