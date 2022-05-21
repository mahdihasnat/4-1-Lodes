#include <bits/stdc++.h>
using namespace std;
#define DBG(x) cout <<"Line "<< dec<< __LINE__<<" "<< #x << " = " << hex<< (x) << endl
#define NL cout<<"\n"

#include "aes.h"
#include "rot.cpp"
#include "sub.cpp"
#include "gf.cpp"

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

void get_matrix(const char * s, uint * w,int len)
{
	while(len>0)
	{
		*w = 0;
		*w |= ((*s++)&0xFF)<<24;
		*w |= ((*s++)&0xFF)<<16;
		*w |= ((*s++)&0xFF)<<8;
		*w |= ((*s++)&0xFF);
		w++;
		len-=4;
	}
}

void set_matrix(char *s,uint *w,int len)
{
	while(len>0)
	{
		*s++ = (*w)>>24;
		*s++ = ((*w)>>16)&0xff;
		*s++ = ((*w)>>8)&0xff;
		*s++ = (*w)&0xff;
		w++;
		len-=4;
	}
}

AES::AES(const char *key,int len)
{
	// fails if key length is not multiple of 4

	// cout<<"In AES constructor\n";
	
	
	this->nk=len/4;
	
	const char * curr = key;
	
	// DBG(this->nk);

	if(len%4 != 0 or (this->nk != 4 and this->nk != 6 and this->nk != 8))
	{
		cout<<"Key length must be 128, 172, or 256 bits\n";
		assert(0);
	}
	
	this->nr = this->nk + 6;

	this->w = new uint[this->nk*(nr + 1)];
	curr = key;
	int i=0;
	get_matrix(key,this->w,len);
	i+=this->nk;

	for(int round = 1;round <= nr;round++)
	{
		uint g = RotWord(w[i-1]);

		g = SubWord(g);
		
		g=g^RoundConstants[round];

		w[i] = g ^ w[i-nk];i++;
		for(int j=0;j<nk-1;j++,i++)
			w[i] = w[i-nk] ^ w[i-1];
	}


}
AES::~AES()
{
	// cout<<"In AES destructor\n";
	if(this->w)
		delete [] this->w;
}

char * AES::encrypt(const char *plaintext,int len)
{
	// cout<<"In AES encrypt: ";
	
	// for(int i=0;i<len;i++)
	// 	cout<<hex<<(plaintext[i]&0xff)<<" ";
	// cout<<endl;
	
	int nb = len/4;
	if(len % 4 != 0 or nb != nk)
	{
		cout<<"Plaintext length must be equal tolength of key\n";
		assert(0);
	}

#define DBG_STATE(x) cout<<"Line "<<dec<<__LINE__<<" "<< #x << " = " << hex << (x[0])<<" "<<(x[1])<<" "<<(x[2])<<" "<<(x[3])<<endl

	uint * state = new uint[nb];

	get_matrix(plaintext,state,len);
	
	// initial task
	add_round_key(state,this->w,nb);
	
	uint * curr_w = this->w+nb;

	for(int i=1;i<nr;i++){
		sub_bytes(state,nb);
		shift_row(state,nb);
		mix_column(state,nb);
		add_round_key(state,curr_w,nb);
		curr_w+=nb;
	}

	// last round
	sub_bytes(state,nb);
	shift_row(state,nb);
	add_round_key(state,curr_w,nb);
	

	// static char ciphertext[257];
	char * ciphertext = new char [len+1];
	ciphertext[len]=0;

	set_matrix(ciphertext,state,len);

	delete []state;

	return ciphertext;
}

char * AES::decrypt(const char *ciphertext,int len) {
	// cout<<"In AES decrypt: ";
	
	// for(int i=0;i<len;i++)
	// 	cout<<hex<<(ciphertext[i]&0xff)<<" ";
	// cout<<endl;

	int nb = len/4;
	if(len % 4 != 0 or nb != nk)
	{
		cout<<"Ciphertext length must be equal to length of key\n";
		assert(0);
	}

	uint * state = new uint[nb];
	get_matrix(ciphertext,state,len);

	uint * curr_w = this->w + nb*(nr);
	add_round_key(state,curr_w,nb);
	curr_w-=nb;

	for(int i=1;i<nr;i++)
	{
		inv_shift_row(state,nb);
		inv_sub_bytes(state,nb);
		add_round_key(state,curr_w,nb);
		inv_mix_column(state,nb);
		
		curr_w-=nb;
	}
	
	// last round
	inv_shift_row(state,nb);
	inv_sub_bytes(state,nb);
	add_round_key(state,curr_w,nb);

	// static char plaintext[257];
	char * plaintext = new char [len+1];
	plaintext[len]=0;

	set_matrix(plaintext,state,len);

	delete []state;
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

void AES::inv_sub_bytes(uint *state,uint col) {
	while(col--){
		*state = Inv_SubWord(*state);
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

void AES::inv_shift_row(uint *state,uint col) {
	// right shifting 1 row by 1
	uint tmp = state[col-1];
	for(int i=col-1;i>0;i--)
		state[i] = (state[i]&0xFF00FFFF) | (state[i-1]&0x00FF0000);
	state[0] = (state[0]&0xFF00FFFF) | (tmp&0x00FF0000);

	// right shifting 2 row by 2
	tmp = state[col-1];
	uint tmp2 = state[col-2];
	for(int i=col-1;i>1;i--)
		state[i] = (state[i]&0xFFFF00FF)|(state[i-2]&0x0000FF00);
	state[1] = (state[1]&0xFFFF00FF)|(tmp&0x0000FF00);
	state[0] = (state[0]&0xFFFF00FF)|(tmp2&0x0000FF00);

	// right shifting 3 row by 3
	tmp = state[col-1];
	tmp2 = state[col-2];
	uint tmp3 = state[col-3];
	for(int i=col-1;i>2;i--)
		state[i] = (state[i]&0xFFFFFF00)|(state[i-3]&0x000000FF);
	state[2] = (state[2]&0xFFFFFF00)|(tmp&0x000000FF);
	state[1] = (state[1]&0xFFFFFF00)|(tmp2&0x000000FF);
	state[0] = (state[0]&0xFFFFFF00)|(tmp3&0x000000FF);

}

void AES::mix_column(uint *state,uint col) {
	static uint Mixer [4][4] ={
		{0x02,0x03,0x01,0x01},
		{0x01,0x02,0x03,0x01},
		{0x01,0x01,0x02,0x03},
		{0x03,0x01,0x01,0x02},
	};
	Gf_matrix_mult(Mixer,state,col);
}
void AES::inv_mix_column(uint *state,uint col) {
	static uint Inv_Mixer [4][4] ={
		{0x0E,0x0B,0x0D,0x09},
		{0x09,0x0E,0x0B,0x0D},
		{0x0D,0x09,0x0E,0x0B},
		{0x0B,0x0D,0x09,0x0E},
	};
	Gf_matrix_mult(Inv_Mixer,state,col);
}

extern "C"
{

AES * AES_new(char *key,int len){return new AES(key,len);}

char * AES_encrypt(AES *aes, char *plaintext,int len){
	return aes->encrypt(plaintext,len);
}
char * AES_decrypt(AES *aes, char *ciphertext,int len){
	return aes->decrypt(ciphertext,len);
}

void AES_delete(AES *aes){
	delete aes;
}
void AES_init(){
	cout<<"In AES init\n";
	Gf_init();
}

}
