import ctypes
import os

os.system("g++ -c -fPIC aes.cpp -o aes.o")
os.system("g++ -shared -Wl,-soname,libaes.so -o libaes.so  aes.o")
lib = ctypes.cdll.LoadLibrary('./libaes.so')
lib.AES_init()

class AES(object):

	def __init__(self,x):
		lib.AES_new.argtypes = [
			ctypes.c_char_p,
			ctypes.c_int
		]
		self.obj = lib.AES_new(x.encode('utf-8'), len(x))

	def encrypt(self,x):
		lib.AES_encrypt.restype = ctypes.c_char_p
		
		lib.AES_encrypt.argtypes = [
			ctypes.c_void_p,
			ctypes.c_char_p, 
			ctypes.c_int
		]
		
		r = lib.AES_encrypt(
							self.obj, 
							x.encode('utf-8'), 
							len(x)
							)
		return r
	
	def decrypt(self,x):
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

		return r.decode('utf-8')

	def __del__(self):
		lib.AES_delete(self.obj)



a = AES("Thats my Kung Fu")
s = "Two One Nine Two"
en = a.encrypt(s)
print("en= ",en)
print("len en = ",len(en))
print( a.decrypt(en) )
