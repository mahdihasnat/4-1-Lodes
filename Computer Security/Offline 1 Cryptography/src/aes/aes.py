import ctypes
import os

os.system("g++ -c -fPIC aes.cpp -o aes.o")
os.system("g++ -shared -Wl,-soname,libaes.so -o libaes.so  aes.o")
lib = ctypes.cdll.LoadLibrary('./libaes.so')


class AES(object):
	def __init__(self,x):
		self.obj = lib.AES_new(ctypes.c_char_p(x.encode()))

	def encrypt(self,x):
		lib.AES_encrypt.restype = ctypes.c_char_p
		# y = x.ctypes.data_as(ctypes.POINTER(ctypes.c_char))
		# print(y)
		r = lib.AES_encrypt(self.obj,ctypes.c_char_p(x.encode()))
		# print(r)
		# print(type(r))
		return "".join(map(chr,r))
	
	def __del__(self):
		lib.AES_delete(self.obj)

a = AES("Thats my Kung Fu")
s = "Two One Nine Two"

print( a.encrypt(s) )
print(s)