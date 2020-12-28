import telnetlib
from time import sleep

exe = r'setmac_hex'  # file path
host = '192.168.1.1'
user = 'root'
password = 'Pon521'

tn = telnetlib.Telnet(host)

tn.read_until(b'Login: ')
tn.write(user.encode('ascii') + b'\n')
if password:
    tn.read_until(b'Password: ')
    tn.write(password.encode('ascii') + b'\n')
tn.write(b'> /var/tmp/setmac_hex\n')
tn.write(b'chmod +x /var/tmp/setmac_hex\n')

with open(exe, 'rb') as f:
    while (_bytes := f.read(20)):  # seems writing 20 bytes each time could be most stable
        data = ''
        for byte in _bytes:
            data += '\\x' + bytes([byte]).hex()
        tn.write(b'echo -ne "' + data.encode('ascii') + b'" >> /var/tmp/setmac_hex\n')
        sleep(0.1)

tn.write(b'exit\n')
print(tn.read_all().decode('ascii'))
