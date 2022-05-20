#include "aes.cpp"

int main()
{
	AES a = AES("Thats my Kung Fu");
	DBG(a.encrypt("Two One Nine Two"));
}