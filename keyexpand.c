#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "utilities.h"
#include "tablecheck.h"

unsigned int rCon(int i)
{
	unsigned int answer = 2;

	int j=0;
	for(j=0; j<i-1-1; j++)
	{
		answer = xtime((unsigned char)answer);
	}

	if(i==1)
		answer = 1;

	return answer << 24;
}

void keyExpansion(unsigned char key[16], unsigned int w[44], unsigned char S[16][16])
{
	int i=0;
	for (i=0; i < 4; i++) //construct 32-bit words from 4 chars
	{
		w[i] = word(key[4*i], key[4*i+1], key[4*i+2], key[4*i+3]);
	}

	unsigned int temp = 0;

	for (i=4; i<44; i++)
	{
		temp = w[i-1];
		if (i % 4 == 0)
		{
			//add confusion and diffusion
			temp = subWord(rotWord(temp), S) ^ rCon(i/4);
		}
		w[i] = w[i-4] ^ temp;
	}
}

void expandKey(char* key, char* tablefileName)
{
	//check if length of hexstring is 32
	if(strlen(key) != 32)
	{
		fprintf(stderr, "key is not represented by a hexstring of length 32.\n");
		return;
	}
	else
	{
		int k=0;
		for(k=0; k<32; k++) //check if key contains valid hex symbols
		{
			if(key[k] < 48 || (key[k] > 57 && key[k] < 97) || key[k] > 102)
			{
				fprintf(stderr, "key is not in hexstring format.\n");
				return;
			}
		}
	}

	//check if tablefile is valid
	int isValid = checkTable(tablefileName);
	if(isValid == 1)
		return;

	//tablefile is okay, fetch values
	unsigned char S[16][16];
	unsigned int P, INVP;
	unsigned char keyBytes[16];

	fetchFromTable(tablefileName, S, &P, &INVP);
	fetchKey(key, keyBytes);

	/*int i=0, j=0;
	for(i=0; i<16; i++)
	{
		for(j=0; j<16; j++)
			printf("%02x ", S[i][j]);
		printf("\n");
	}
	printf("P = %0x \nINVP = %0x\n", P, INVP);*/

	//Key expansion algorithm

	//printf("rotWord(%08x) ==> %08x\n", 19172163, rotWord(19172163));
	//printf("subByte(%02x) ==> %02x\n", 255, subByte(255, S));
	//printf("subWord(%08x) ==> %08x\n", 1385816574, subWord(1385816574, S));
	//printf("word() ==> %08x\n", word(255, 157, 99, 230));
	/*int i=1;
	for(i=1; i<11; i++)
		printf("rCon(%d) ==> %08x\n", i, rCon(i));*/

	int i=0;

	//initialize w[]
	unsigned int w[44];
	for(i=0; i<44; i++)
		w[i] = 0;

	keyExpansion(keyBytes, w, S);

	//print results
	for(i=0; i<44; i++)
	{
		printf("w[%2d]: %08x\n", i, w[i]);
	}
}
