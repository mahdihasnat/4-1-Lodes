#include "aes.cpp"

int main()
{
	AES_init();
	AES a = AES("Thats my Kung Fu");
	char c[17] = "Two One Nine Two";
	cout<<a.encrypt(c)<<"\n";
	cout<<bitset<8>( Gf_mult(0x03,0x2F))<<"\n";
}	