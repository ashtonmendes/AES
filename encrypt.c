#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "utilities.h"
#include "tablecheck.h"
#include "keyexpand.h"

void AES_encrypt(unsigned char in[16], unsigned char out[16], unsigned int w[44], unsigned char S[16][16], unsigned int P)
{
	unsigned char state[4][4];

	//copy contents of input into state.
	int i=0;
	for(i=0; i<16; i++)
		state[i%4][i/4] = in[i];

	addRoundKey(state, w[0], w[1], w[2], w[3]);

	//print input
	printf("round[%2d].input    ", 0);
	for(i=0; i<16; i++) printf("%02x", in[i]);
	printf("\n");

	//print k_sch
	printf("round[%2d].k_sch    %08x%08x%08x%08x\n", 0, w[0], w[1], w[2], w[3]);

	//9 normal rounds
	int round = 1;
	for(round=1; round < 10; round++)
	{
		printState(round, state, "start", 4);

		subBytes(state, S);

		printState(round, state, "s_box", 4);

		shiftRows(state);

		printState(round, state, "s_row", 4);

		mixColumns(state, P);

		printState(round, state, "m_col", 4);

		addRoundKey(state, w[4*round], w[4*round + 1], w[4*round + 2], w[4*round + 3]);

		//print k_sch
		printf("round[%2d].k_sch    %08x%08x%08x%08x\n", round, w[4*round], w[4*round + 1], w[4*round + 2], w[4*round + 3]);
	}

	//10th round is special
	printState(round, state, "start", 4);

	subBytes(state, S);

	printState(round, state, "s_box", 4);

	shiftRows(state);

	printState(round, state, "s_row", 4);

	addRoundKey(state, w[40], w[41], w[42], w[43]);

	printf("round[%2d].k_sch    %08x%08x%08x%08x\n", round, w[40], w[41], w[42], w[43]);

	printf("round[%2d].output   ", 10);
	for(i=0; i<16; i++) printf("%02x", state[i%4][i/4]);
	printf("\n");

	//copy contents of state into out.
	for(i=0; i<16; i++)
		out[i] = state[i/4][i%4];
}

void performEncrypt(char* key, char* tablefileName, char* fileName)
{
	//printf("performEncrypt(): key = %s tablefileName = %s fileName = %s\n", key, tablefileName, fileName);

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

	//Key expansion algorithm
	unsigned int w[44];
	int i=0;
	for(i=0; i<44; i++)w[i] = 0;
	keyExpansion(keyBytes, w, S);

	//Check if inputfile is accessible
	FILE *file = fopen(fileName, "rb");
	if(strlen(fileName)!=0 && file==NULL)
	{
		fprintf(stderr, "Unable to open %s.\n", fileName);
		return;
	}
	if(strlen(fileName)==0)
		file = stdin;

	//For this assignment, we are only supposed to encrypt the 1st 16 bytes
	int bytesRead = -1;
	unsigned char buffer[16];
	unsigned char ciphertext[16];

	for(i=0; i<8; i++)
		buffer[i] = 0;

	bytesRead = fread(buffer, sizeof(char), 16, file);

	if(bytesRead < 16)
	{
		fprintf(stderr, "The input is less than 16 bytes.");
		return;
	}

	AES_encrypt(buffer, ciphertext, w, S, P); //encrypt the 1st 16 bytes

	fclose(file);

	/*unsigned char state[4][4];
	int i=0,j=0;
	for(i=0; i<16; i++)
		state[i/4][i%4] = 0;

	addRoundKey(state, 16909060, 84281096, 151653132, 219025168);
	shiftRows(state);

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
			printf("%02x ", state[i][j]);
		printf("\n");
	}*/
}
