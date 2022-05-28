
from calendar import c
import random

def check_composite(n, a, d, s):
	"""
		Theory: https://cp-algorithms.com/algebra/primality_tests.html#miller-rabin-primality-test
		check if n is composite
		n-1 = 2^s * d
		n is probable prime if  (a^d == 1 mod n) or (a^ (d*2^r) == -1 mod n) for all r in [0, s-1]
	"""
	x = pow(a, d, n)
	if x == 1 or x == n - 1:
		return False
	for r in range(1, s):
		x = (x * x) % n
		if x == n - 1:
			return False
	return True

def miller_rabin(n, iter = 10):
	"""
		check if n is probably prime
	"""
	if n<4:
		return n==2 or n==3
	s=0
	d=n-1
	while d&1==0:
		d>>=1
		s+=1
	
	for i in range(iter):
		a=random.randint(2,n-2)
		if check_composite(n, a, d, s):
			return False
	return True


def prime_gen(k):
	"""
		prime number in range [2^k , 2^(k+1) )
	"""
	while True:
		p = random.randint(2**k, 2**(k+1)-1)
		if miller_rabin(p):
			return p

