
import socket
import pickle
from time import sleep
import connection_1705003
from rsa_1705003 import RSA
import rsa_common
from files_1705003 import file_path
# create socket and bind to port


def msg_send(conn,msg):

	c.send(text.encode('utf-8'))

	sleep(0.5)

	text2 = ""

	with open(file_path("Don’t Open this/tmp.txt"),"r") as f:
		text2 = f.read()
	
	print("Match : ",text == text2)

def file_send(conn,rpath):
	"""
		read file and send using connection
	"""
	file = file_path(rpath)

	import os
	file_name = os.path.basename(file)
	print("file_name = ",file_name)

	conn.send(file_name.encode('utf-8'))

	file_size = os.path.getsize(file)
	print("file_size = ",file_size)

	# import pickle
	# x = pickle.dumps(file_size)
	# # print("x = ",x)
	# conn.send(x)

	FILE_CHUNK_SIZE=1000
	# tot = (file_size+FILE_CHUNK_SIZE-1)/FILE_CHUNK_SIZE

	with open(file,"rb") as f:
		while True:
			data = f.read(FILE_CHUNK_SIZE)
			if not data:
				break
			# print("len(data) = ",len(data))
			conn.send(data)
			# tot-=1


import sys

# print(sys.argv)
HOST = '127.0.0.1'
PORT = int(sys.argv[1])

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
	s.bind((HOST, PORT))
	s.listen(1)
	conn,addr = s.accept()
	
	
	rsa = RSA.new_rsa(32)
	rsa_common.write_private_key(rsa)
	print("Private key:",rsa.get_private_key())

	c = connection_1705003.SocketConnection(conn)
	c = connection_1705003.SeperatedConnection(c)
	# c = connection.SecureReceiver(c)
	
	c = connection_1705003.SecureSender(c,rsa)
	
	print('Connected by', addr)

	text = "123"*100
	# msg_send(c,text)
	file_send(c,"CV Mahdi.pdf")
	conn.close()

	