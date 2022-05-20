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
	
	this->nr = this->nk + 6;

	this->w = new uint[this->nk*(nr + 1)];
	curr = key;
	int i=0;
	extract_matrix(key,this->w);
	i+=this->nk;

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

	int len = strlen(plaintext);
	int nb = len/4;
	if(len % 4 != 0 or nb != nk)
	{
		cout<<"Plaintext length must be equal tolength of key\n";
		assert(0);
	}

#define DBG_STATE(x) cout<<"Line "<<__LINE__<<" "<< #x << " = " << (x[0])<<" "<<(x[1])<<" "<<(x[2])<<" "<<(x[3])<<endl

	uint * state = new uint[nb];

	extract_matrix(plaintext,state);
	DBG_STATE(state);
	DBG_STATE(this->w);
	add_round_key(state,this->w,nb);
	DBG_STATE(state);
	uint * curr_wb = this->w;
	
	int w_index = nk;

	for(int i=1;i<nr;i++){
		sub_bytes(state,nb);
		DBG_STATE(state);
		shift_row(state,nb);
		DBG_STATE(state);

		w_index+=nk;
	}

	delete state;
	return plaintext;
}

inline void AES::add_round_key(uint *state,uint *w,uint col) {
	for(int i=0;i<col;i++)
		*state++ ^= *w++;
}

void AES::sub_bytes(uint *state,uint col) {
	while(col--){
		*state = SubWord(*state);
		state++;
	}
}

void AES::shift_row(uint *state,uint col) {
	//left shifting 1 row by 1
	uint tmp = *state;
	for(int i=0;i<col-1;i++)
		state[i] = (state[i]&0xFF00FFFF) | (state[i+1]&0x00FF0000);
	state[col-1] = (state[col-1]&0xFF00FFFF) | (tmp&0x00FF0000);

	// left shifting 2 row by 2
	tmp = state[0];
	uint tmp2 = state[1];
	for(int i=0;i<col-2;i++)
		state[i] = (state[i] &0xFFFF00FF)|(state[i+2]&0x0000FF00);
	state[col-2] = (state[col-2]&0xFFFF00FF)|(tmp&0x0000FF00);
	state[col-1] = (state[col-1]&0xFFFF00FF)|(tmp2&0x0000FF00);

	//left shifting 3 row by 3
	tmp = state[0];
	tmp2 = state[1];
	uint tmp3 = state[2];
	for(int i=0;i<col-3;i++)
		state[i] = (state[i]&0xFFFFFF00)|(state[i+3]&0x000000FF);
	state[col-3] = (state[col-3]&0xFFFFFF00)|(tmp&0x000000FF);
	state[col-2] = (state[col-2]&0xFFFFFF00)|(tmp2&0x000000FF);
	state[col-1] = (state[col-1]&0xFFFFFF00)|(tmp3&0x000000FF);

}

void AES::mix_column(uint *state,uint col) {
	
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
