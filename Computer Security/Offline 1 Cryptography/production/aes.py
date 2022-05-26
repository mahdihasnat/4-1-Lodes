import ctypes
import os

os.system("g++ -c -fPIC aes.cpp -o aes.o")
os.system("g++ -shared -Wl,-soname,libaes.so -o libaes.so  aes.o")
lib = ctypes.cdll.LoadLibrary('./libaes.so')
lib.AES_init()

class AES(object):

	def __init__(self,x:bytes):
		lib.AES_new.argtypes = [
			ctypes.c_char_p,
			ctypes.c_int
		]
		self.obj = lib.AES_new(x, len(x))

	def encrypt(self,x:bytes)->bytes:
		lib.AES_encrypt.restype = ctypes.c_char_p
		
		lib.AES_encrypt.argtypes = [
			ctypes.c_void_p,
			ctypes.c_char_p, 
			ctypes.c_int
		]
		
		r = lib.AES_encrypt(
							self.obj, 
							x, 
							len(x)
							)
		return r
	
	def decrypt(self,x:bytes)->bytes:
		lib.AES_decrypt.restype = ctypes.c_char_p
		
		lib.AES_decrypt.argtypes = [ 
			ctypes.c_void_p,
			ctypes.c_char_p, 
			ctypes.c_int
		]
		
		r = lib.AES_decrypt(self.obj,
							x,
							ctypes.c_int(len(x))
							)

		return r

	def __del__(self):
		lib.AES_delete(self.obj)


if __name__ == '__main__':
	a = AES("Thats my Kung Fu".encode())
	s = "Two One Nine Two"
	en = a.encrypt(s.encode())
	print("en= ",en)
	print("len en = ",len(en))
	print( a.decrypt(en).decode() )
