#ifndef AES_H

#define AES_H

typedef unsigned int uint;

class AES
{
public:
	AES(char *key); // key must be of  len 128, 172, 256
	char * encrypt(char *plaintext);
	~AES();
private:
	uint *w;
	int nk;
	int nr;
	void add_round_key(uint *state,uint *w,uint col);
	void sub_bytes(uint *state,uint col);
	void shift_row(uint *state,uint col);
	void mix_column(uint *state,uint col);
	
};


#endif