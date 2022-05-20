#include <bits/stdc++.h>
using namespace std;
#define DBG(x) cout <<"Line "<<__LINE__<<" "<< #x << " = " << (x) << endl
#define NL cout<<"\n"

#include "aes.h"
#include "rot.cpp"
#include "sub.cpp"


uint RoundConstants[15] = {
	(uint)0,
	(uint)0x1<<24U,
	(uint)0x2<<24U,
	(uint)0x4<<24U,
	(uint)0x8<<24U,
	(uint)0x10<<24U,
	(uint)0x20<<24U,
	(uint)0x40<<24U,
	(uint)0x80<<24U,
	(uint)0x1b<<24U,
	(uint)0x36<<24U,
	(uint)0x6c<<24U,
	(uint)0xd8<<24U,
	(uint)0xab<<24U,
	(uint)0x4d<<24U
};

void extract_matrix(char * s, uint * w)
{
	while(*s)
	{
		*w = 0;
		*w |= (*s++)<<24;
		*w |= (*s++)<<16;
		*w |= (*s++)<<8;
		*w |= (*s++);
		w++;
	}
}

AES::AES(char *key)
{
	// fails if key length is not multiple of 4

	cout<<"In AES constructor\n";
	cout<<"Key: "<<key<<"\n";
	this->nk=0;
	char * curr = key;
	while( * curr)
	{
		this->nk++;
		curr++;
		assert( *(curr++) );
		assert( *(curr++) );
		assert( *(curr++) );
	}
	DBG(this->nk);

	if(this->nk != 4 and this->nk != 6 and this->nk != 8)
	{
		cout<<"Key length must be 128, 172, or 256 bits\n";
		assert(0);
	}
	
	if(nk == 4)
	{
		nr = 10;
	}
	else if(nk == 6)
	{
		nr = 12;
	}
	else if(nk == 8)
	{
		nr = 14;
	}
	else assert(0);

	this->w = new uint[this->nk*(nr + 1)];
	curr = key;
	int i=0;

	extract_matrix(key,this->w);
	i+=nk;

	for(int round = 1;round <= nr;round++)
	{
		uint g = RotWord(w[i-1]);
		// DBG(g);
		g = SubWord(g);
		// DBG(g);
		g=g^RoundConstants[round];
		// DBG(g);
		w[i] = g ^ w[i-nk];i++;
		for(int j=0;j<nk-1;j++,i++)
			w[i] = w[i-nk] ^ w[i-1];
		
		for(int j=0;j<nk;j++)
			cout<< hex<<w[i-nk+j]<<" ";
		NL;
	}


}
AES::~AES()
{
	cout<<"In AES destructor\n";
	if(this->w)
		delete [] this->w;
}

char * AES::encrypt(char *plaintext)
{
	cout<<"In AES encrypt\n";
	cout<<"Plaintext: "<<plaintext<<"\n";
	static char c[] = {'a','b','\0'};
	cout<<"C: "<<c<<"\n";


	return c;
}

extern "C"
{

AES * AES_new(char *key){return new AES(key);}

char * AES_encrypt(AES *aes, char *plaintext){
	return aes->encrypt(plaintext);
}
void AES_delete(AES *aes){
	delete aes;
}
void AES_init(){
	cout<<"In AES init\n";

}

}
