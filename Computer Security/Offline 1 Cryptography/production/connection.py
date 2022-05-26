


from random import random



class Connection():

	def send(self,data) -> None:
		pass

	def recv(self) -> bytes:
		pass

	def close(self) -> None:
		pass


CHUNK_SIZE = 1024

class SocketConnection(Connection):

	def __init__(self,conn):
		self.conn = conn

	def send(self,data) -> None: 
		# send data with chunk size
		i = 0
		n = len(data)
		while i < len(data):
			sz = min(CHUNK_SIZE,n-i)
			self.conn.sendall(data[i:i+sz])
			i+=sz
		# self.conn.sendall(data)

	def recv(self) -> bytes:
		# try:
		return self.conn.recv(CHUNK_SIZE)
		# except ConnectionResetError:
		# 	return b''

	def close(self) -> None:
		self.conn.close()


class ConnectionDecorator(Connection):
	
	def __init__(self,conn):
		self.conn = conn

	def send(self,data) -> None:
		self.conn.send(data)

	def recv(self) -> bytes:
		return self.conn.recv()

	def close(self) -> None:
		self.conn.close()

# define esc with b'\x1b'
ESC_BYTE = b'\x1b'
RECORD_SEPARATOR_BYTE = b'\x1e'

print("ESC_BYTE=",ESC_BYTE , "type" , type(ESC_BYTE))

class SeperatedConnection(ConnectionDecorator):

	def __init__(self, conn):
		super().__init__(conn)
		self.data = []
		self.esc_flag = False
		self.row_data = []

	def send(self,data) -> None:
		# print("in fuunction send: SeperatedConnection")
		modified_data = []
		for i in data:
			i = chr(i).encode()
			if i == ESC_BYTE or i == RECORD_SEPARATOR_BYTE:
				modified_data.append(ESC_BYTE)
			
			modified_data.append(i)
		modified_data.append(RECORD_SEPARATOR_BYTE)

		# print("modified data:", modified_data)
		self.conn.send(b''.join(modified_data))


	def recv(self) -> bytes:
		
		while True:
			while self.row_data:
				d = self.row_data.pop(0)
				d=chr(d).encode('utf-8')
				# print(d)
				# print(len(d))
				# print(RECORD_SEPARATOR_BYTE )
				if self.esc_flag:
					self.data.append(d)
					self.esc_flag = False
				elif d == RECORD_SEPARATOR_BYTE:
					# found end of record
					x = b''.join(self.data)
					self.data=[]
					return x
				elif d == ESC_BYTE:
					self.esc_flag = True
				else:
					self.data.append(d)
			
			self.row_data = list(self.conn.recv())
			# print(self.row_data)
			if not self.row_data:
				return b''

from .aes import AES

import pickle
class SecureSender(ConnectionDecorator):
	
	def __init__(self,conn):
		super().__init__(conn)

	def send(self,data:bytes)->None:
		self.super().send(pickle.dumps(len(data)))

		self.new_aes_key()
		key_len = len(self.my_aes_key)

		self.super().send(self.my_aes_key)

		aes = AES(self.my_aes_key)
		pos = 0
		data_len = len(data)
		while pos < data_len:
			chunk_len = min(data_len-pos,key_len)
			self.super().send(aes.encrypt(data[pos:pos+chunk_len]))
			pos += chunk_len
		
	
	def recv(self)->bytes:
		return self.super().recv()
	
	def new_aes_key(self):
		self.my_aes_key = random.randbytes(16)

class SecureReceiver(ConnectionDecorator):

	def __init__(self,conn):
		super().__init__(conn)

	def send(self,data:bytes)->None:
		return self.super().send(data)

	def recv(self)->bytes:
		pass