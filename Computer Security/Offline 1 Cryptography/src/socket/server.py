import socket
import pickle
from time import sleep
import connection
# create socket and bind to port

HOST = '127.0.0.1'
PORT = 65332

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
	s.bind((HOST, PORT))
	s.listen(100)
	conn,addr = s.accept()
	with conn:
		c = connection.SocketConnection(conn)
		c = connection.SeperatedConnection(c)
		print('Connected by', addr)
		while True:
			data = c.recv()
			# print("data= ",data , " sz " , len(data))
			if not data:
				break
			# print(type(data))
			c.send(data)
	conn.close()