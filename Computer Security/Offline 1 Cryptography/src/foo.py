from ctypes import cdll
import ctypes
from re import L
lib = cdll.LoadLibrary('./libfoo.so')

class Foo(object):
	def __init__(self,x):
		lib.Foo_new.restype = ctypes.c_void_p
		self.obj = lib.Foo_new(ctypes.c_char_p(x))

	def bar(self):
		lib.Foo_bar(self.obj)
	
	def __del__(self):
		lib.Foo_del(self.obj)
	


f = Foo("abc".encode())
print(type(f))
f.bar() #and you will see "Hello" on the screen
