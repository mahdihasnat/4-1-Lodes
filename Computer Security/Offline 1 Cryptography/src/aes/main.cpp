#include "aes.cpp"

int main()
{
	AES_init();
	AES a = AES("Thats my Kung Fu",16);
	char c[17] = "Two One Nine Two";
	char * x = a.encrypt(c,16);
	DBG(x);
	char * y = a.decrypt(x,16);
	DBG(y);
	
}	