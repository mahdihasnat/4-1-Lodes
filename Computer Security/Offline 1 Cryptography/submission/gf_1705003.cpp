
// https://www.youtube.com/watch?v=FUdEpUoA4mc
// https://www.youtube.com/watch?v=3mQ3TdozIUQ


// My GF(2^8) implementation
// Given Irreducable Polynomial = x^8 + x^4 + x^3 + x + 1 , 0x11b
// 0 -> 0
// g^ 0 -> 1
// g^1 -> g
// g^2 -> g^2
// g^3 -> g^3
// g^4 -> g^4
// g^5 -> g^5
// g^6 -> g^6
// g^7 -> g^7
// g^8 -> g^8 % 0x11b

//  so , 
//          { 0 if i==  0
// gen[i] = { gen[i-1]<<1 if gen[i-1] < 0x80
// 		    { gen[i-1]<<1 ^ 0x11b if gen[i-1] >= 0x80

// multiplication of g^x * g^y = g^((x+y)%(2^8 - 1))
// division of g^x / g^y = g^((x-y)%(2^8 - 1))

// uint GF_Gen[256]; // 0th entry is invalid
// int GF_Inv[256]; // 0th entry is invalid

void Gf_init()
{
	cout<<"In GF_init\n";

	// GF_Gen[0]=1;
	// GF_Inv[1]=0;

	// for(int i=1;i<255;i++)
	// {
	// 	GF_Gen[i]=GF_Gen[i-1]<<1;
	// 	if(GF_Gen[i-1]&0x80)
	// 		GF_Gen[i]^=0x11b;
	// 	GF_Inv[GF_Gen[i]]=i;
	// 	// cout<<"GF_Gen["<<i<<"]="<<hex<<GF_Gen[i]<<"\n";
	// }
	
}

uint Gf_mult(int x,int y)
{
	uint res = 0;
	while(x)
	{
		if(x &1)
			res^=y;
		y<<=1;
		if(y&0x100)
			y^=0x11b;
		x>>=1;
	}
	return res;
}
void Gf_matrix_mult(const uint  mat1[4][4],uint *state,int col)
{
	for(int i=0;i<col;i++)
	{
		uint tmp = 0;
		
		for(int row = 0; row < 4; row++)
		{
			uint tmp2 = 0;
			tmp2 ^= Gf_mult(mat1[row][0],(state[i] & 0xFF000000)>>24);
			tmp2 ^= Gf_mult(mat1[row][1],(state[i] & 0x00FF0000)>>16);
			tmp2 ^= Gf_mult(mat1[row][2],(state[i] & 0x0000FF00)>>8);
			tmp2 ^= Gf_mult(mat1[row][3],(state[i] & 0x000000FF));
			tmp ^= tmp2<<(8*(3-row));
		}
		// DBG(tmp);
		state[i]=tmp;
	}
}