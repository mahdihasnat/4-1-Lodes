import socket
from time import sleep
import connection
from rsa import RSA
import rsa_common

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
t = b"abc"*10001

c.send(t)
c.send(t)
data = c.recv()
print("data=",data)
print("len(data)=",len(data))
data = c.recv()
print("len(data)=",len(data))
c.close()
	# sleep(1)

	

# print(f"Received {data!r}")