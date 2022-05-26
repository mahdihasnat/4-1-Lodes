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
					assert(0);
				}
			}
			delete []ciphertext;
			delete []decrypted;
		}
	}
}
void print_hex(string s)
{
	for(char c: s)
		cout<<hex<<setw(2)<<setfill('0')<<(c&0xFF);
	
}

void simulation()
{
	char padding = '\0';

	int bytes = 128/8;

	string key;
	cout<<"Enter key:";
	getline(cin,key);

	if(key.size() < bytes)
	{
		cout<<"Padding key with "<<16-key.size()<<" zeros\n";
		key.resize(bytes,padding);
	}
	else if(key.size() > bytes)
	{
		cout<<"Removing "<<key.size()-16<<" characters from key\n";
		key.resize(bytes);
	}
	cout<<"Key [ASCII]: "<<key<<endl;

	cout<<"Key [HEX]: ";
	print_hex(key);
	cout<<endl;

	cout<<"Key size: "<< dec<<key.size()<<endl;
	

	auto start = chrono::high_resolution_clock::now();
	AES aes(key.c_str(),key.size());
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	
	cout<<"Time taken in  Expand Key : "<< setprecision(15)<<fixed <<duration.count()/1e9<<" s\n";
	NL;

	while(1) 
	{
		string plain;
		cout<<"Enter plaintext:";
		getline(cin,plain);
		if(plain.size() % bytes)
		{
			cout<<"Padding plaintext with "<<dec<<bytes-plain.size()%bytes<<" zeros\n";
			plain.resize(plain.size()+bytes-plain.size()%bytes,padding);
		}

		cout<<"Plaintext [ASCII]: ";
		for(int i=0;i<plain.size();i+=bytes)
			cout<<plain.substr(i,bytes)<<" ";
		cout<<endl;

		cout<<"Plaintext [HEX]: ";
		for(int i=0;i<plain.size();i+=bytes)
		{
			print_hex(plain.substr(i,bytes));
			cout<<" ";
		}
		cout<<endl;

		cout<<"Plaintext size: "<< dec<<plain.size()<<endl;

		vector<char *> ciphertexts;

		start = chrono::high_resolution_clock::now();
		for(int i=0;i<plain.size();i+=bytes)
		{
			ciphertexts.push_back( aes.encrypt(plain.substr(i,bytes).c_str(),bytes));
		}
		end = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

		cout<<"Ciphertext[ASCII]: ";
		for(auto i:ciphertexts)
		{
			for(int j=0;j<bytes;j++)
			{
				cout<<i[j]<<"";
			}
			cout<<" ";
		}
		cout<<"\n";

		cout<<"Ciphertext[HEX]: ";
		for(auto i:ciphertexts)
		{
			for(int j=0;j<bytes;j++)
			{
				cout<<hex<<setw(2)<<setfill('0')<<(i[j]&0xFF);
			}
			cout<<" ";
		}
		cout<<"\n";
		cout<<"Time taken in Encrypt : "<< setprecision(15)<<fixed <<duration.count()/1e9<<" s\n";
		NL;

		vector<char *> decrypted;

		start = chrono::high_resolution_clock::now();
		for(auto i: ciphertexts)
		{
			decrypted.push_back(aes.decrypt(i,bytes));
		}
		end = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

		cout<<"Decrypted[ASCII]: ";
		for(auto i:decrypted)
		{
			for(int j=0;j<bytes;j++)
			{
				cout<<i[j]<<"";
			}
			// cout<<" ";
		}
		cout<<"\n";
		cout<<"Decrypted[HEX]: ";
		for(auto i:decrypted)
		{
			for(int j=0;j<bytes;j++)
			{
				cout<<hex<< setw(2) << setfill('0')<<((int)i[j]&0xFF)<<"";
			}
			cout<<" ";
		}
		cout<<"\n";
		cout<<"Time taken in Decrypt : "<< setprecision(15)<<fixed <<duration.count()/1e9<<" s\n";
		NL;

		for(auto i: ciphertexts)
		{
			delete []i;
		}
		for(auto i: decrypted)
		{
			delete []i;
		}
	}
	
}

int main()
{
	AES_init();
	test();
	simulation();
	// AES a = AES("Thats my Kung Fu",16);
	// char c[17] = "Two One Nine Two";
	// char * x = a.encrypt(c,16);
	// DBG(x);
	// char * y = a.decrypt(x,16);
	// DBG(y);

	AES a = AES("Thats my Kung Fu",16);
	char c[17] = "Two One Nine Two";
	char * x = a.encrypt(c,16);
	DBG(x);
	char * y = a.decrypt(x,16);
	DBG(y);
	
}	