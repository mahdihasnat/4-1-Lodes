#include "aes.cpp"


void test()
{
	int tot = 100;
	int tot2 = 10;
	int len = 256/8;
	int cnt1 = tot;
	while(cnt1--)
	{
		string ky;
		for(int i=0;i<len;i++)
		{
			ky.push_back(rand()%256);
		}
		AES aes(ky.c_str(),len);
		int cnt2= tot2;
		while(cnt2--)
		{
			string plaintext;
			for(int i=0;i<len;i++)
			{
				plaintext.push_back(rand()%256);
			}
			auto ciphertext = aes.encrypt(plaintext.c_str(),len);
			auto decrypted = aes.decrypt(ciphertext,len);
			for(int i=0;i<len;i++)
			{
				if(plaintext[i] != decrypted[i])
				{
					cout<<"error"<<endl;
					cout<<"plaintext:"<<plaintext<<endl;
					cout<<"ciphertext:"<<ciphertext<<endl;
					cout<<"decrypted:"<<decrypted<<endl;
					return;
				}
			}
			delete []ciphertext;
			delete []decrypted;
		}
	}
}

int main()
{
	AES_init();
	test();
	// AES a = AES("Thats my Kung Fu",16);
	// char c[17] = "Two One Nine Two";
	// char * x = a.encrypt(c,16);
	// DBG(x);
	// char * y = a.decrypt(x,16);
	// DBG(y);
	
}	