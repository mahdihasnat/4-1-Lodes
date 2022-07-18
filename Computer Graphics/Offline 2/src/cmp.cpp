#include<bits/stdc++.h>
using namespace std;

int
main(int argc,char * argv[]){

	string z[2] = {string(argv[1]),string(argv[2])};

	ifstream f[2]={ifstream(z[0]),ifstream(z[1])};
	int diff = 0;
	int total_line = 0;
	while(1){

		string l[2];
		if(f[0].eof()) break;
		getline(f[0],l[0]);
		getline(f[1],l[1]);

		total_line++;

		stringstream ss[2];
		ss[0]<<l[0];
		ss[1]<<l[1];

		int tot[2]={0,0};
		string s;
		while(ss[0]>>s)
			tot[0]++;
		while(ss[1]>>s)
			tot[1]++;
		diff = max(diff,abs(tot[0]-tot[1]));
		// cout<<tot[0]<<" "<<tot[1]<<endl;
	}
	cout<<"Difference: "<<diff<<endl;
	cout<<"Total lines: "<<total_line<<endl;
	

}