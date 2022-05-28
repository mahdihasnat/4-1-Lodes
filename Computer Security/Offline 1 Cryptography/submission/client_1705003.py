import socket
from time import sleep
import connection_1705003
from rsa_1705003 import RSA
import rsa_common

from files_1705003 import file_path

def msg_recv(conn):

	txt = conn.recv()
	print("Received:",txt)

	with open(file_path("Don’t Open this/tmp.txt"),"w") as f:
		f.write(txt.decode('utf-8'))

def file_recv(conn):
	
	file_name = conn.recv().decode('utf-8')
	print("file name = ",file_name)

	# import pickle
	# x = conn.recv()
	# # print("x=",x)
	# file_size = pickle.loads(x)
	# print("file size = ",file_size)

	file = file_path("Don’t Open this/"+file_name)
	print("Starting to receive file:",file_name)
	sz = 0
	with open(file ,'wb') as f:
		while True:
			data = conn.recv()
			
			if not data:
				break
			sz+=len(data)
			f.write(data)
	print(sz,"bytes saved to ",file_name)

import sys

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = int(sys.argv[1])

s= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.settimeout(None)
sleep(0.2)
private_key = rsa_common.read_private_key()
print("Private key:",private_key)
rsa = RSA(private_key[0],private_key[1])

c=connection_1705003.SocketConnection(s)
c=connection_1705003.SeperatedConnection(c)
c=connection_1705003.SecureReceiver(c,rsa)
# c=connection.SecureSender(c)

# msg_recv(c)
file_recv(c)