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
};


#endif