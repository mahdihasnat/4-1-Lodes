


import random



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

# print("ESC_BYTE=",ESC_BYTE , "type" , type(ESC_BYTE))

class SeperatedConnection(ConnectionDecorator):

	def __init__(self, conn):
		super().__init__(conn)
		self.data = []
		self.esc_flag = False
		self.row_data = []

	def send(self,data) -> None:
		# print("SeperatedConnection data:",data)
		# print("len(data)=",len(data))
		modified_data = []
		for i in data:
			# i = chr(i).encode('utf-8')
			i=bytes([i])
			# print("i=",i)
			if i == ESC_BYTE or i == RECORD_SEPARATOR_BYTE:
				modified_data.append(ESC_BYTE)
			
			modified_data.append(i)
		modified_data.append(RECORD_SEPARATOR_BYTE)

		# print("modified data:", modified_data)
		super().send(b''.join(modified_data))


	def recv(self) -> bytes:
		
		while True:
			while self.row_data:
				d = self.row_data.pop(0)
				# d=chr(d).encode('utf-8')
				d=bytes([d])
				# print("d=",d)
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
			
			self.row_data = list(super().recv())
			# print(self.row_data)
			if not self.row_data:
				return b''

from aes import AES

import pickle

PADDING_BYTE = b'\x00'
class SecureSender(ConnectionDecorator):
	
	def __init__(self,conn,rsa_instance):
		super().__init__(conn)
		self.rsa_instance = rsa_instance

	def send(self,data:bytes)->None:
		# print("data to send: ", data)
		data_len = len(data)

		x = pickle.dumps(data_len)
		# print("data len to send :",x)
		# print("len(x)=",len(x))
		super().send(x)

		self.new_aes_key()
		key_len = len(self.my_aes_key)

		# encrypt the key with rsa
		enc_key = self.rsa_instance.encrypt_bytes(self.my_aes_key)

		super().send(pickle.dumps(enc_key))

		aes = AES(self.my_aes_key)
		pos = 0
		while pos < data_len:
			chunk_len = min(data_len-pos,key_len)
			super().send(aes.encrypt(data[pos:pos+chunk_len] + PADDING_BYTE*(key_len-chunk_len))) 
			pos += chunk_len
		
	
	def recv(self)->bytes:
		return super().recv()
	
	def new_aes_key(self):
		# generate random bytes of length 16
		self.my_aes_key = random.getrandbits(128)\
						.to_bytes(16,byteorder='big')

class SecureReceiver(ConnectionDecorator):

	def __init__(self,conn,rsa_instance):
		super().__init__(conn)
		self.rsa_instance = rsa_instance

	def send(self,data:bytes)->None:
		super().send(data)

	def recv(self)->bytes:
		x = super().recv()
		if x == b'':
			return b''
		# print("len data received: ", x)
		data_len = pickle.loads(x)
		# print("data_len=",data_len)

		enc_aes_key = pickle.loads(super().recv())

		aes_key = self.rsa_instance.decrypt_bytes(enc_aes_key)

		key_len = len(aes_key)

		aes = AES(aes_key)
		# print("key len:",key_len)
		# print("data len:",data_len)
		pos = 0
		data = b''
		while pos < data_len:
			chunk_len = min(data_len-pos,key_len)
			# print("chunk len:",chunk_len)
			x = super().recv()
			# print("x len:",len(x))
			data += aes.decrypt(x)[:chunk_len]
			pos += chunk_len
		
		return data
		