import socket
from time import sleep
import connection
from rsa import RSA
import rsa_common

from files import file_path

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 65332  # The port used by the server

s= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.settimeout(None)
sleep(0.2)
private_key = rsa_common.read_private_key()
print("Private key:",private_key)
rsa = RSA(private_key[0],private_key[1])

c=connection.SocketConnection(s)
c=connection.SeperatedConnection(c)
c=connection.SecureReceiver(c,rsa)
# c=connection.SecureSender(c)

txt = c.recv()
print("Received:",txt)

with open(file_path("Don’t Open this/tmp.txt"),"w") as f:
	f.write(txt.decode('utf-8'))
