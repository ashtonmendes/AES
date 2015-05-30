#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "utilities.h"

void computeInverse(char* poly)
{
	int k=0;

	if(strlen(poly)!=8)
	{
		fprintf(stderr, "bad polynomial.\n");
		return;
	}

	for(k=0; k<8; k++) //check if poly contains valid hex symbols
	{
		if(poly[k] < 48 || (poly[k] > 57 && poly[k] < 97) || poly[k] > 102)
		{
			fprintf(stderr, "poly is not in hexstring format.\n");
			return;
		}
	}

	//printf("computeInverse(): poly=%s \n", poly);

	//Table Method of the Extended Euclidean Algorithm
	unsigned long long rem[7], quo[7], x[7]; //1-based arrays
	int i=0, isSpecialCase=0;
	for(i=0; i<7; i++) //initialize the arrays
	{
		rem[i] = ~(unsigned long long)0;
		quo[i] = 0;
		x[i] = 0;
	}

	rem[1] = convertHexToLong("0100000001"); //M(x)
	rem[2] = convertHexToLong(poly);
	x[1] = 0;
	x[2] = 1;

	for(i=3; rem[i]>1; i++)
	{
		if( i==findDeg(rem[2])+3 || (i>3 && (findDeg(rem[i-2]) - findDeg(rem[i-1]) > 1)) )
			isSpecialCase = 1;
		else
			isSpecialCase = 0;

		longHandDiv(rem[i-2], rem[i-1], &quo[i], &rem[i], isSpecialCase); //if degree of 'poly' is k, terminate table method at i=k+3

		x[i] = circleX((unsigned int)quo[i], (unsigned int)x[i-1]) ^ x[i-2];

		if(rem[i] == 0) //no multiplicative inverse exists
			break;
	}

	//print results
	for(i=1; i<=6; i++)
	{
		printf("i=%d, ", i);
		printf("rem[i]=");
		prettyPrint(rem[i]);
		printf(", quo[i]=");
		prettyPrint(quo[i]);
		printf(", aux[i]=");
		prettyPrint(x[i]);
		printf("\n");

		if(rem[i] == 1)
		{
			printf("Multiplicative inverse of ");
			prettyPrint(rem[2]);
			printf(" is ");
			prettyPrint(x[i]);
			printf("\n");
			break;
		}
		else if(rem[i] == 0)
		{
			prettyPrint(rem[2]);
			printf(" does not have a multiplicative inverse.\n");
			break;
		}
	}
}
