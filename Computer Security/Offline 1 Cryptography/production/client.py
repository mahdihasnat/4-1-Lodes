

import pickle
import socket
from time import sleep
import connection


HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 65332  # The port used by the server

s= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
c=connection.SocketConnection(s)
c=connection.SeperatedConnection(c)
t = b"a\x1b\x1e"*100

c.send(t)
c.send(t)
data = c.recv()
print("len(data)=",len(data))
data = c.recv()
print("len(data)=",len(data))
c.close()
# sleep(1)


# print(f"Received {data!r}")