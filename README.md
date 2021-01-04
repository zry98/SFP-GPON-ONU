# DFP-34X-2C2
Some stuff about GPON Stick DFP-34X-2C2 / DFP-34G-2C2

## Conclusion

After communicating with the developer from ODI, it is confirmed that the current version (with `PON STICK V01` printed on PCB near the SFP connector) is **IMPOSSIBLE** to use a hexadecimal GPON PLOAM password even with it set in tagparam using this program, due to the implementations of /lib/libdb.so and /bin/gpon_omci. And ODI is not planning to release an upgraded firmware in the future (they have already developed a newer model with hex password support).

Therefore, this product can not be used with ISPs like Movistar Spain.

## (**USELESS**) Set hexadecimal GPON password
(There is a pre-built binary available in releases)

1. Set up a cross-compilation environment with [crosstool-ng](https://crosstool-ng.github.io/docs/)
  - Use the `ct-ng.config` in the repo, or config it as `arm-unknown-linux-uclibcgnueabi` in the samples, with CPU set to `arm9tdmi`
2. Compile the dummy libtagparamuserapi.so with command like `arm-unknown-linux-uclibcgnueabi-gcc -shared -o libtagparamuserapi.so libtagparamuserapi.c`
3. Compile the program with command like `arm-unknown-linux-uclibcgnueabi-gcc -std=c99 libtagparamuserapi.so -s -o setmac_hex setmac_hex.c`
4. Set up a TFTP server in the same subnet, telnet to stick and get the executable with commands like `tftp -r setmac_hex -l /var/tmp/setmac_hex -g 192.168.1.2 69 && chmod +x /var/tmp/setmac_hex`
5. Run command like `/var/tmp/setmac_hex 1 2178 "f2 01 80 01 02 03 04 00 00 00"` to set GPON password
6. Run `setmac 2 2178` or `/var/tmp/setmac_hex 2 2178` to verify the result
