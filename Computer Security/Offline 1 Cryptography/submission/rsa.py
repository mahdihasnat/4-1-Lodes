from ast import arg
import prime
import modular
import random
import time

class RSA():

	def new_rsa(k):
		"""
			Create a new RSA keypair with k bit length
		"""
		r = RSA()
		r.p = prime.prime_gen(k//2)
		r.q = prime.prime_gen(k//2)
		while r.p == r.q:
			print(" p == q")
			q = prime.prime_gen(k/2)
		r.n = r.p*r.q
		r.phi = (r.p-1)*(r.q-1)
		r.gen_ed()
	
		return r
	
	def __init__(self):
		pass

	def __init__(self,*args):
		if len(args)==2:
			self.d = args[0]
			self.n = args[1]

	def gen_ed(self):
		while True:
			self.e = random.randint(2, self.phi-1)
			try:
				self.d =modular.modinv(self.e,self.phi)
				break
			except:
				pass
				# print("e generated is not coprime")
	
	def get_private_key(self):
		return (self.d,self.n)
	
	def get_public_key(self):
		return (self.e,self.n)

	def encrypt_str(self,msg):
		return [ self.encrypt(ord(c)) for c in msg ]
	def decrypt_str(self,cipher):
		return ''.join([ chr(self.decrypt(c)) for c in cipher ])

	def encrypt(self,plain):
		return pow(plain,self.e,self.n)
	
	def decrypt(self,cipher):
		return pow(cipher,self.d,self.n)

	def encrypt_bytes(self,bs):
		return [ self.encrypt(b) for b in bs ]
	
	def decrypt_bytes(self,cipher):
		return b''.join([ bytes([self.decrypt(c)]) for c in cipher])

def simulation(k,text):
	
	print("{:3d}".format(k),end=' ')
	start = time.time()
	r  = RSA.new_rsa(k)
	print("{:.9f}".format(time.time()-start),end=' ')

	start = time.time()
	enc = r.encrypt_str(text)
	print("{:.9f}".format(time.time()-start),end=' ')

	start = time.time()
	dec = r.decrypt_str(enc)
	print("{:.9f}".format(time.time()-start),end='\n')

	return dec

def perf(msg):
	print("Key Key-GenTime EncTime    DecTime")
	for k in [16,32,64,128]:
		assert(simulation(k,msg)==msg)

if __name__ == '__main__':


	k=int(input("Enter K:"))
	msg = input("Enter message:")

	r = RSA.new_rsa(k)
	print("Private key:",r.get_private_key())
	print("Public key:",r.get_public_key())

	enc = r.encrypt_str(msg)

	r2 = RSA(r.get_private_key()[0],r.get_public_key()[1])

	print("Encrypted:",enc)
	print("Decrypted:",r2.decrypt_str(enc))

	perf(msg)