import socket
import pickle
from time import sleep
import connection
from rsa import RSA
import rsa_common
from files import file_path
# create socket and bind to port

HOST = '127.0.0.1'
PORT = 65332

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
	s.bind((HOST, PORT))
	s.listen(1)
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

		text = "123"*100
		c.send(text.encode('utf-8'))

		sleep(0.5)

		text2 = ""

		with open(file_path("Don’t Open this/tmp.txt"),"r") as f:
			text2 = f.read()
		
		print("Match : ",text == text2)

	
	conn.close()