#include<stdio.h>
#include<stdlib.h>
#include<string.h>

unsigned char xtime(unsigned char b)
{
	if((b & (1<<7)) == 0) //leftmost bit is 0
		return b<<1;
	else
		return (b<<1)^(27); // 27 = {1B} = (0001 1011)
}

unsigned char bigDot(unsigned char x, unsigned char y)
{
	unsigned char v[8], answer = 0;

	//initialize 1st entry in v[]
	v[0] = x;

	int i=1;
	for(i=1; i<8; i++) //calculate all other entries in v[]
	{
		v[i] = xtime(v[i-1]);
	}

	//mask
	unsigned char mask = 1;

	//add all terms that are required based on bits in y.
	for(i=0; i<8; i++)
	{
		if((y & mask) == mask) //current bit is 1 in y
		{
			answer = answer ^ v[i];
		}

		mask = mask << 1;//move mask to next bit
	}

	return answer;
}

unsigned int circleX(unsigned int a, unsigned int b)
{
	int answer = 0;
	unsigned char d0 = 0, d1 = 0, d2 = 0, d3 = 0;
	int mask = 255<<24; //1st 8 bits in int
	unsigned char a3 = (a & mask) >> 24;
	unsigned char b3 = (b & mask) >> 24;
	mask = mask >> 8; //2nd set of 8 bits from left.
	unsigned char a2 = (a & mask) >> 16;
	unsigned char b2 = (b & mask) >> 16;
	mask = mask >> 8; //3rd set of 8 bits from left.
	unsigned char a1 = (a & mask) >> 8;
	unsigned char b1 = (b & mask) >> 8;
	mask = mask >> 8; //rightmost 8 bits.
	unsigned char a0 = (a & mask);
	unsigned char b0 = (b & mask);

	//calculate result
	d0 = bigDot(a0, b0) ^ bigDot(a3, b1) ^ bigDot(a2, b2) ^ bigDot(a1, b3);
	d1 = bigDot(a1, b0) ^ bigDot(a0, b1) ^ bigDot(a3, b2) ^ bigDot(a2, b3);
	d2 = bigDot(a2, b0) ^ bigDot(a1, b1) ^ bigDot(a0, b2) ^ bigDot(a3, b3);
	d3 = bigDot(a3, b0) ^ bigDot(a2, b1) ^ bigDot(a1, b2) ^ bigDot(a0, b3);

	//combine results into single 32-bit int
	answer = (d3 << 24) | (d2 << 16) | (d1 << 8) | d0;

	/*printf("a = %08x b = %08x\n", a, b);
	printf("a => {%02x}{%02x}{%02x}{%02x}\n", a3,a2,a1,a0);
	printf("b => {%02x}{%02x}{%02x}{%02x}\n", b3,b2,b1,b0);
	printf("d => {%02x}{%02x}{%02x}{%02x}\n", d3,d2,d1,d0);
	printf("answer => %08x\n", answer);*/

	return answer;
}

unsigned int convertHexToInt(char* hex)
{
	unsigned int answer = 0, value = 0, shiftBy = 0;

	int i=0;
	for(i=strlen(hex)-1; i>=0; i--)
	{
		switch(hex[i])
		{
			case '0':
				value = 0;
				break;

			case '1':
				value = 1;
				break;

			case '2':
				value = 2;
				break;

			case '3':
				value = 3;
				break;

			case '4':
				value = 4;
				break;

			case '5':
				value = 5;
				break;

			case '6':
				value = 6;
				break;

			case '7':
				value = 7;
				break;

			case '8':
				value = 8;
				break;

			case '9':
				value = 9;
				break;

			case 'a':
				value = 10;
				break;

			case 'b':
				value = 11;
				break;

			case 'c':
				value = 12;
				break;

			case 'd':
				value = 13;
				break;

			case 'e':
				value = 14;
				break;

			case 'f':
				value = 15;
				break;
		}

		answer = answer ^ (value<<shiftBy);

		shiftBy += 4;
	}

	//printf("HexToInt: {%s} => %d\n", hex, answer);

	return answer;
}

unsigned long long convertHexToLong(char* hex)
{
	unsigned long long answer = 0, value = 0, shiftBy = 0;

	int i=0;
	for(i=strlen(hex)-1; i>=0; i--)
	{
		switch(hex[i])
		{
			case '0':
				value = 0;
				break;

			case '1':
				value = 1;
				break;

			case '2':
				value = 2;
				break;

			case '3':
				value = 3;
				break;

			case '4':
				value = 4;
				break;

			case '5':
				value = 5;
				break;

			case '6':
				value = 6;
				break;

			case '7':
				value = 7;
				break;

			case '8':
				value = 8;
				break;

			case '9':
				value = 9;
				break;

			case 'a':
				value = 10;
				break;

			case 'b':
				value = 11;
				break;

			case 'c':
				value = 12;
				break;

			case 'd':
				value = 13;
				break;

			case 'e':
				value = 14;
				break;

			case 'f':
				value = 15;
				break;
		}

		answer = answer ^ (value<<shiftBy);

		shiftBy += 4;
	}

	//printf("HexToInt: {%s} => %d\n", hex, answer);

	return answer;
}

int findDeg(unsigned long long poly) //finds the degree of a polynomial
{
	int degree = 0;

	unsigned long long mask = (unsigned long long)255 << ((sizeof(unsigned long long)-1)*8);

	while((poly & mask) == 0 && (mask != 0))
	{
		mask = mask >> 8;
	}

	if(mask == 0)
		return 0;

	while(mask != 0)
	{
		degree = degree + 1;
		mask = mask >> 8;
	}

	return degree-1;
}

unsigned char inverseBitCoeff(unsigned char byte) //brute force method to find inverse of polynomial with bit coefficients
{
	if(byte == 0)
		return 0;

	int i=0;
	for(i=0; i<256; i++)
		if(circleX(byte, (unsigned char)i) == 1)
			return i;

	return 0; //control will never reach this statement.
}

void longHandDiv(unsigned long long b, unsigned long long a, unsigned long long* quo, unsigned long long* rem, int isLastStep) // b divided by a = quotient: quo and remainder: rem
{
	//find degrees of the polynomials
	int deg_a = findDeg(a);
	int deg_b = findDeg(b);

	/*printf("deg(a) = %d\n", deg_a);
	printf("deg(b) = %d\n", deg_b);*/

	unsigned long long dividend = b;

	//initialize the masks
	unsigned long long mask_a = (unsigned long long)255 << (deg_a*8);
	unsigned long long mask_dividend = (unsigned long long)255 << (deg_b*8);

	unsigned char firstByte_a = ((mask_a) & a) >> (deg_a*8);
	unsigned char nxtByte_dividend = 0;
	unsigned char tempQuo = 0;
	unsigned long long temp = 0;

	int i=0;
	for(i=0; i<deg_b-deg_a+1; i++)
	{
		nxtByte_dividend = ((mask_dividend) & dividend) >> ((deg_b - i)*8); //find the next byte in b, form the left.

		/*printf("byte a = %02x\n", firstByte_a);
		printf("byte b = %02x\n", nxtByte_dividend);
		printf("inverse(a) = %02x\n", inverseBitCoeff(firstByte_a));
		printf("bigDot(inv(a), nxtByte_b) = %02x\n", bigDot(inverseBitCoeff(firstByte_a), nxtByte_dividend));*/

		if(isLastStep == 1 && i==deg_b-deg_a) //we want remainder to be {01}
		{
			tempQuo = (bigDot(inverseBitCoeff(firstByte_a), nxtByte_dividend^1));
		}
		else
		{
			tempQuo = (bigDot(inverseBitCoeff(firstByte_a), nxtByte_dividend));
		}

		*quo = ((*quo) << 8) | tempQuo; //store quotient in 'quo'

		temp = (unsigned long long)(circleX(tempQuo, (unsigned int)a)) << ((deg_b - deg_a - i)*8);

		dividend = dividend ^ temp;

		mask_dividend = mask_dividend >> 8;

		/*printf("quo = %02x\n", tempQuo);
		printf("temp = %010llx\n", temp);
		printf("dividend = %010llx\n", dividend);*/
	}

	*rem = dividend;

	//printf("%llx / %llx = quo: %llx rem: %llx\n", b, a, *quo, *rem);
}

void prettyPrint(unsigned long long data)
{
	unsigned int mask = 255 << (3*8);

	int i=3;
	for(i=3; i>=0; i--)
	{
		printf("{");
		printf("%02x", (unsigned int)((data&mask)>>(i*8)));
		printf("}");
		mask = mask >> 8;
	}
}

void fetchFromTable(char* tablefileName, unsigned char S[16][16], unsigned int* P, unsigned int* INVP)
{
	FILE *tableFile = fopen(tablefileName, "rb");

	char line[600];
	char *keyword;

	while(fgets(line, 600, tableFile) != NULL) //Read 1 line at a time
	{
		//Get table name
		keyword = strtok(line, "=");

		//Get values
		char *value;
		value = strtok(NULL, "=");

		if(strcmp(keyword, "S") == 0)
		{
			int j=0;
			for(j=0; j<=510; j+=2)
			{
				char next[3] = {value[j], value[j+1], '\0'};
				S[j/32][(j%32)/2] = convertHexToInt(next);
			}
		}

		if(strcmp(keyword, "P") == 0 || strcmp(keyword, "INVP") == 0)
		{
			value[8] = '\0'; //eliminate \n at the end so that convertHexToInt() will work properly

			//P (or INVP) is valid
			if(strcmp(keyword, "P") == 0)
				*P = convertHexToInt(value);
			else
				*INVP = convertHexToInt(value);
		}
	}
}

unsigned char subByte(unsigned char byte, unsigned char S[16][16])
{
	unsigned char answer = 0;

	//separate the 1st 4 and last 4 bits
	unsigned char first4Bits = (byte & 240) >> 4;
	unsigned char last4Bits = (byte & 15);

	answer = S[first4Bits][last4Bits];

	return answer;
}

unsigned int subWord(unsigned int word, unsigned char S[16][16])
{
	unsigned int answer = 0;

	int i=0;
	unsigned char byte = 0;
	unsigned int mask = (unsigned int)255 << 24;

	for(i=0; i<4; i++) //process a byte at a time
	{
		byte = (word & mask) >> ((3-i)*8); //get 1 byte from word
		byte = subByte(byte, S); //find substitution for that byte

		answer = answer << 8; //add substituted byte to answer
		answer = (answer | byte);

		mask = mask >> 8; //shift mask to next 8 bits
	}

	return answer;
}

unsigned int rotWord(unsigned int word)
{
	unsigned int rotated = word;

	unsigned int mask = (unsigned int)255 << 24;

	unsigned char firstByte = (rotated & mask) >> 24;

	rotated = (rotated << 8) | firstByte;

	return rotated;
}

unsigned int word(unsigned char a0, unsigned char a1, unsigned char a2, unsigned char a3)
{
	unsigned int answer = 0;

	//keep on ORing 8 bits at a time
	answer = answer | a0;
	answer = (answer<<8) | a1;
	answer = (answer<<8) | a2;
	answer = (answer<<8) | a3;

	return answer;
}

void fetchKey(char* key, unsigned char keyBytes[16])
{
	int i=0;
	for(i=0; i<=30; i+=2)
	{
		char next[3] = {key[i], key[i+1], '\0'};
		keyBytes[i/2] = convertHexToInt(next);
	}
}

void addRoundKey(unsigned char state[4][4], unsigned int w0, unsigned int w1, unsigned int w2, unsigned int w3)
{
	int row=0, col = 0;
	unsigned int mask = (unsigned int)255 << 24; //to get 1st 8 bits in word
	unsigned char temp = 0;
	unsigned int w = 0;

	for(col=0; col<4; col++)
	{
		switch(col) //select which word to EXOR this column with
		{
			case 0:
				w = w0;
				break;
			case 1:
				w = w1;
				break;
			case 2:
				w = w2;
				break;
			case 3:
				w = w3;
				break;
		}

		mask = (unsigned int)255 << 24; //reinitialize mask

		for(row=0; row<4; row++)
		{
			temp = (w & mask) >> ((3-row)*8);

			state[row][col] = state[row][col] ^ temp;

			mask = mask >> 8; //move mask to next 8 bits
		}
	}
}

void subBytes(unsigned char state[4][4], unsigned char S[16][16])
{
	int row = 0, col = 0;
	for(row=0; row<4; row++)
		for(col=0; col<4; col++)
			state[row][col] = subByte(state[row][col], S);
}

void shiftRows(unsigned char state[4][4])
{
	int row = 1, col = 0, numOfShifts = 0;
	unsigned char temp = 0;

	for(row=1; row<4; row++) //0th row need not be shifted
	{
		for(numOfShifts=0; numOfShifts<row; numOfShifts++) //multiple number of circular shifts depending on row number
		{
			temp = state[row][0];
			for(col=0; col<3; col++)
			{
				state[row][col] = state[row][col+1];
			}
			state[row][col] = temp;
		}
	}
}

void mixColumns(unsigned char state[4][4], unsigned int P)
{
	unsigned int s = 0, mask = (unsigned int)255 << 24;
	int col = 0, row = 3;

	for(col=0; col<4; col++)
	{
		mask = (unsigned int)255 << 24;

		s = word(state[3][col], state[2][col], state[1][col], state[0][col]); //construct a 32 bit word from one column in the state array.
		s = circleX(P, s);

		//now separate 8 bits and put them back into the column
		for(row=3; row>=0; row--)
		{
			state[row][col] = (s & mask) >> (row*8);
			mask = mask >> 8;
		}
	}
}

void printState(int roundNum, unsigned char state[4][4], char* stage, int numOfSpaces)
{
	int i=0;
	printf("round[%2d].%s", roundNum, stage);
	for(i=0; i<numOfSpaces; i++) //4 spaces for encrypt, 3 spaces for decrypt
		printf(" ");
	for(i=0; i<16; i++) printf("%02x", state[i%4][i/4]);
	printf("\n");
}

void invShiftRows(unsigned char state[4][4])
{
	int row = 1, col = 0, numOfShifts = 0;
	unsigned char temp = 0;

	for(row=1; row<4; row++) //0th row need not be shifted
	{
		for(numOfShifts=0; numOfShifts<row; numOfShifts++) //multiple number of circular shifts depending on row number
		{
			temp = state[row][3];
			for(col=3; col>=1; col--)
			{
				state[row][col] = state[row][col-1];
			}
			state[row][col] = temp;
		}
	}
}

unsigned char invSubByte(unsigned char byte, unsigned char S[16][16])
{
	unsigned char answer = 0;

	//find the byte in the S-box
	int row=0, col=0;
	int isFound = 0;
	for(row=0; row<16; row++)
	{
		for(col=0; col<16; col++)
		{
			if(S[row][col]==byte)
			{
				isFound = 1;
				break;
			}
		}

		if(isFound==1)
			break;
	}

	answer = (answer | row); //OR with row and shift bits to left, by 4
	answer = answer << 4;
	answer = (answer | col); //OR with col

	return answer;
}

void invSubBytes(unsigned char state[4][4], unsigned char S[16][16])
{
	int row = 0, col = 0;
	for(row=0; row<4; row++)
		for(col=0; col<4; col++)
			state[row][col] = invSubByte(state[row][col], S);
}

void invMixColumns(unsigned char state[4][4], unsigned int INVP)
{
	mixColumns(state, INVP); //invMixColumns is same, except we find circleX of a inverse and state
}




















