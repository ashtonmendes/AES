#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "utilities.h"

int checkTable(char* tablefileName)
{
	FILE *tableFile = fopen(tablefileName, "rb");

	//Check if file exists
	if(tableFile == NULL)
	{
		fprintf(stderr, "Unable to open tablefile.\n");
		return 1;
	}

	char line[600];
	char *keyword;
	int linesRead = 0;
	unsigned int P = 0;
	unsigned int INVP = 0;
	while(fgets(line, 600, tableFile) != NULL) //Read 1 line at a time
	{
		linesRead++;

		//Check whether too many lines present
		if(linesRead > 3)
		{
			fprintf(stderr, "%s contains too many lines.\n", tablefileName);
			return 1;
		}

		//Get table name
		keyword = strtok(line, "=");

		//Check whether valid keyword
		if(strcmp(keyword, "S") != 0 &&
		   strcmp(keyword, "P") != 0 &&
		   strcmp(keyword, "INVP") != 0 )
		{
			fprintf(stderr, "%s contains invalid keywords. Valid keywords are S, P and INVP.\n", tablefileName);
			return 1;
		}

		//Get values
		char *value;
		value = strtok(NULL, "=");

		//printf("key = %s value = %d \n", keyword, strlen(value));

		//Check each table separately
		if(strcmp(keyword, "S") == 0)
		{
			if(strlen(value) > 513) //S should contain only 256 hex numbers, i.e 512 (+1 newline) characters
			{
				fprintf(stderr, "Length of hexstring for S is too long ( more than 256 ).\n");
				return 1;
			}
			if(strlen(value) < 513)
			{
				fprintf(stderr, "Length of hexstring for S is too short ( less than 256 ).\n");
				return 1;
			}

			//This table contains a random permutation of the values from 00 through ff, inclusive.
			//Check whether proper permutation.
			int temp[256];
			int j=0;
			for(j=0; j<256; j++)
				temp[j] = 0;
			for(j=0; j<=510; j+=2)
			{
				//check whether hexstring is valid
				char next[3] = {value[j], value[j+1], '\0'};
				if( ((next[0] >= '0' && next[0] <='9') ||  (next[0] >= 'a' && next[0] <= 'f')) &&
					((next[1] >= '0' && next[1] <='9') ||  (next[1] >= 'a' && next[1] <= 'f'))	)
				{
					temp[convertHexToInt(next)] += 1;
				}
				else
				{
					fprintf(stderr, "Hexstring for S contains invalid characters: '%c%c'\n", value[j], value[j+1]);
					return 1;
				}
			}
			for(j=0; j<256; j++)
				if(temp[j]==0)
				{
					fprintf(stderr, "S does not contain %02x, hence it is not a proper permutation.\n", j);
					return 1;
				}
		}

		if(strcmp(keyword, "P") == 0 || strcmp(keyword, "INVP") == 0)
		{
			//P: This table contains a hexstring of length 8 which corresponds to 4 byte of binary values. Each byte is a coefficient of the a(x) polynomial in the MixColumns()
			//transformation. The first two hex digits correspond to the coefficient for x3, the next two hex digits correspond to the coefficient for x2, etc.

			//INVP: This table contains a hexstring of length 8 which corresponds to 4 byte of binary values. Each byte is a coefficient of the a-1(x) polynomial in the
			//InvMixColumns() transformation. The first two hex digits correspond to the coefficient for x3, the next two hex digits correspond to the coefficient for x2, etc.

			if(strlen(value) > 9)
			{
				fprintf(stderr, "Length of hexstring for %s is too long ( more than 8 ).\n", keyword);
				return 1;
			}
			if(strlen(value) < 9)
			{
				fprintf(stderr, "Length of hexstring for %s is too short ( less than 8 ).\n", keyword);
				return 1;
			}

			//check for invalid characters.
			int j=0;
			for(j=0; j<8; j++)
			{
				if((value[j] >= '0' && value[j] <='9') ||  (value[j] >= 'a' && value[j] <= 'f'))
				{}
				else
				{
					fprintf(stderr, "Hexstring for %s contains invalid character: '%c'\n", keyword, value[j]);
					return 1;
				}
			}

			value[8] = '\0'; //eliminate \n at the end so that convertHexToInt() will work properly

			//P (or INVP) is valid
			if(strcmp(keyword, "P") == 0)
				P = convertHexToInt(value);
			else
				INVP = convertHexToInt(value);
		}
	}

	//check whether all tables read
	if(linesRead < 3)
	{
		fprintf(stderr, "%s contains too few lines.\n", tablefileName);
		return 1;
	}

	//Check whether CIRCLEX of P and INVP is 01
	if(circleX(P, INVP) != 1)
	{
		fprintf(stderr, "%08x CIRCLEX %08x != 01. That is, P and INVP are not multiplicative inverses of each other. %08x\n", P, INVP, circleX(P, INVP));
		return 1;
	}

	//tablefile is okay.
	return 0;
}
