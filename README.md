# SFP GPON ONU
Some stuff about SFP GPON ONU modules (GPON sticks).

## Modules using RTL8672 & RTL9601C chipset

> Including: V-SOL V2801F, C-Data FD511GX-RM0, OPTON GP801R, BAUDCOM BD-1234-SFM, CPGOS03-0490 v2.0, EXOT - EGS1, NanTianWeiShi, Ubiquiti U-Fiber Instant, ODI newer model, etc.

If your ISP uses hexadecimal GPON PLOAM password (idONT), although the normal WebUI and `flash / xmlconfig / mib` command doesn't allow you to set a hexadecimal password containing unprintable characters (for example a password for Movistar Spain: `0xF2021030405678000000`), but there is still a way to use it since `/bin/omci_app` still accepts and will work well with hexadecimal password as an argument value in command line.

1. Flash a custom firmware (you can find information about customizing firmware [here](https://gist.github.com/Anime4000/522b021d0c43e8d6134e95c42603ed2f#modify-firmware)) with an already modified script in step 2, or flash a firmware including a text editor like `vi`, some modules' firmwares may already have one. If you couldn't find a way to flash, maybe `sed` can also do the trick by replacing string.

2. Edit the script `/etc/runomci.sh`, find the argument part `$gpon_ploam_pwd_set` in the last line (it should start with `omci_app -s $gpon_sn...`) or in the middle of file `gpon_ploam_pwd_set="-p $gpon_ploam_pwd"`. Change it to `"$(echo -ne '\xf2\x02\x10...')"` which is your escaped hexadecimal password. For example, if your idONT is *0xF2021030405678000000*, it should be `"$(echo -ne '\xf2\x02\x10\x30\x40\x56\x78\x00\x00\x00')"`.

3. Done! (For some ISPs, you may also need to enable the OMCI fake ok option by `flash set OMCI_FAKE_OK 1` or similar command.)

Example for step 2: if the original last line in your runomci.sh looks like this (on a NanTianWeiShi module, shouldn't be very different on other modules):
```bash
omci_app -s $gpon_sn -f $(get_omci_log_format) -m $(get_omci_dual_mgmt_mode) -d $(get_omci_dbg_level) -t $(get_omci_dev_type) $gpon_ploam_pwd_set $gpon_loid_set $gpon_loidPwd_set $(get_omci_cus_conf) $(get_omci_iot_vlan_cfg) $(get_omci_veip_slot_id_conf) $(get_omci_voice_vendor) &
```

the final result should be like this:
```bash
omci_app -s $gpon_sn -f $(get_omci_log_format) -m $(get_omci_dual_mgmt_mode) -d $(get_omci_dbg_level) -t $(get_omci_dev_type) -p "$(echo -ne '\xf2\x02\x10\x30\x40\x56\x78\x00\x00\x00')" $gpon_loid_set $gpon_loidPwd_set $(get_omci_cus_conf) $(get_omci_iot_vlan_cfg) $(get_omci_veip_slot_id_conf) $(get_omci_voice_vendor) &
```

## DFP-34X-2C2 / DFP-34G-2C2

### Conclusion

After communicating with the developer from ODI, it is confirmed that the first model (with `PON STICK V01` printed on PCB near the SFP connector) is **IMPOSSIBLE** to use a hexadecimal GPON PLOAM password even with it set in tagparam using my program, due to the implementations of `/lib/libdb.so` and `/bin/gpon_omci` won't use it correctly. And ODI is not planning to release an upgraded firmware in the future (they have already developed a newer model with hex password support). Therefore, this model can't be used with ISPs like Movistar Spain.

### (**USELESS**) Set hexadecimal GPON password
(There is a pre-built binary available in [releases](https://github.com/zry98/SFP-GPON-ONU/releases/latest))

1. Set up a cross-compilation environment with [crosstool-ng](https://crosstool-ng.github.io/docs/)
  - Use the `ct-ng.config` in the repo, or config it as `arm-unknown-linux-uclibcgnueabi` in the samples, with CPU set to `arm9tdmi`.
2. Compile the dummy libtagparamuserapi.so with command like `arm-unknown-linux-uclibcgnueabi-gcc -shared -o libtagparamuserapi.so libtagparamuserapi.c`.
3. Compile the program with command like `arm-unknown-linux-uclibcgnueabi-gcc -std=c99 libtagparamuserapi.so -s -o setmac_hex setmac_hex.c`.
4. Set up a TFTP server in the same subnet, telnet to stick and get the executable with commands like `tftp -r setmac_hex -l /var/tmp/setmac_hex -g 192.168.1.2 69 && chmod +x /var/tmp/setmac_hex`.
5. Run command like `/var/tmp/setmac_hex 1 2178 "f2 01 80 01 02 03 04 00 00 00"` to set GPON password
6. Run `setmac 2 2178` or `/var/tmp/setmac_hex 2 2178` to verify the result.
