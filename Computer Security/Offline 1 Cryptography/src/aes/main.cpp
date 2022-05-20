#include "aes.cpp"

int main()
{
	AES a = AES("Thats my Kung Fu");
	cout<<a.encrypt("Two One Nine Two")<<"\n";
}