#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "utilities.h"
#include "tablecheck.h"
#include "keyexpand.h"

void AES_decrypt(unsigned char in[16], unsigned char out[16], unsigned int w[44], unsigned char S[16][16], unsigned int INVP)
{
	unsigned char state[4][4];

	//copy contents of input into state.
	int i=0;
	for(i=0; i<16; i++)
		state[i%4][i/4] = in[i];

	addRoundKey(state, w[40], w[41], w[42], w[43]);

	//print input
	printf("round[%2d].iinput   ", 0);
	for(i=0; i<16; i++) printf("%02x", in[i]);
	printf("\n");

	//print k_sch
	printf("round[%2d].ik_sch   %08x%08x%08x%08x\n", 0, w[40], w[41], w[42], w[43]);

	//9 normal rounds
	int round = 9;
	for(round=9; round > 0; round--)
	{
		printState(10-round, state, "istart", 3);

		invShiftRows(state);

		printState(10-round, state, "is_row", 3);

		invSubBytes(state, S);

		printState(10-round, state, "is_box", 3);

		printf("round[%2d].ik_sch   %08x%08x%08x%08x\n", 10-round, w[4*round], w[4*round + 1], w[4*round + 2], w[4*round + 3]);

		addRoundKey(state, w[4*round], w[4*round + 1], w[4*round + 2], w[4*round + 3]);

		printState(10-round, state, "ik_add", 3);

		invMixColumns(state, INVP);
	}

	//10th round is special
	printState(10, state, "istart", 3);

	invShiftRows(state);

	printState(10, state, "is_row", 3);

	invSubBytes(state, S);

	printState(10, state, "is_box", 3);

	addRoundKey(state, w[0], w[1], w[2], w[3]);

	printf("round[%2d].ik_sch   %08x%08x%08x%08x\n", 10, w[0], w[1], w[2], w[3]);

	printf("round[%2d].ioutput  ", 10);
	for(i=0; i<16; i++) printf("%02x", state[i%4][i/4]);
	printf("\n");

	//copy contents of state into out.
	for(i=0; i<16; i++)
		out[i] = state[i/4][i%4];
}

void performDecrypt(char* key, char* tablefileName, char* fileName)
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

	//For this assignment, we are only supposed to decrypt the 1st 16 bytes
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

	AES_decrypt(buffer, ciphertext, w, S, INVP); //decrypt the 1st 16 bytes

	fclose(file);

	//printf("\ninvSubByte(): %02x\n", invSubByte(218, S));
}
