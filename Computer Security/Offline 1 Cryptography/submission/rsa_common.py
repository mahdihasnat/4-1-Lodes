from rsa_1705003 import RSA
import pickle
from files import file_path


def write_private_key(rsa_instance:RSA):
	with open(file_path("Don’t Open this/.pk"), "wb") as f:
		# print("pk :",pickle.dumps(rsa_instance.get_private_key()))
		f.write(pickle.dumps(rsa_instance.get_private_key()))


def read_private_key()->RSA:
	with open(file_path("Don’t Open this/.pk"), "rb") as f:
		key = pickle.loads(f.read())
		return key