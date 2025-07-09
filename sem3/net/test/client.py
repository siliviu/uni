# Enunt: Clientul trimite serverului doua numere. Serverul le primeste, le afiseaza pe ecran si trimite clientului suma lor.
#
# Rulare in doua terminale diferite:
# python server.py
# python client.py
from datetime import datetime
import time
# import datetime
import socket

TCP_IP = "127.0.0.1"
TCP_PORT = 1678
MESSAGE = "ORA"
OFFSET_TIME = 2

# Connect and create socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

# Send request
s.send(bytes("ORA", "utf-8") + b'\0')
print("Am trimis la server:", MESSAGE)

# Receive date as string
data = str(s.recv(1024))
string = str(data)

# Convert from C string to Python int
string = string[2:]
new_str = ""
for x in string:
    if x == '\\':
        break
    new_str+=x
min=int(new_str)


print("Am primit de la server:", min)
print("Ora (aproximata la minut) este:",datetime.utcfromtimestamp(min*60+60*60*OFFSET_TIME))

s.close()

