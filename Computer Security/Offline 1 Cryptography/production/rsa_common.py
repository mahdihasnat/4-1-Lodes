from rsa import RSA
import pickle

def write_private_key(rsa_instance:RSA):
	with open(".Don’t Open this", "wb") as f:
		# print("pk :",pickle.dumps(rsa_instance.get_private_key()))
		f.write(pickle.dumps(rsa_instance.get_private_key()))


def read_private_key()->RSA:
	with open(".Don’t Open this", "rb") as f:
		key = pickle.loads(f.read())
		return key