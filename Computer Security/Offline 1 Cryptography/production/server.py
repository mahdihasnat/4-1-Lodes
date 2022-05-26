import socket
import pickle
from time import sleep
import connection
from rsa import RSA
import rsa_common
# create socket and bind to port

HOST = '127.0.0.1'
PORT = 65332

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
	s.bind((HOST, PORT))
	s.listen(100)
	conn,addr = s.accept()
	with conn:
		
		rsa = RSA.new_rsa(32)
		rsa_common.write_private_key(rsa)
		print("Private key:",rsa.get_private_key())

		c = connection.SocketConnection(conn)
		c = connection.SeperatedConnection(c)
		# c = connection.SecureReceiver(c)
		
		c = connection.SecureSender(c,rsa)
		
		print('Connected by', addr)
	
		while True:
			data = c.recv()
			if not data:
				break
			print("data= ",data , " sz " , len(data))
			# print(type(data))
			c.send(data)
	
	conn.close()