#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "utilities.h"

void computeModprod(char* poly1, char* poly2)
{
	//check if length of hexstring is 8
	if(strlen(poly1) != 8 || strlen(poly2) != 8)
	{
		fprintf(stderr, "Either poly1 or poly2 or both are not represented by a hexstring of length 8.\n");
		return;
	}
	else
	{
		int k=0;
		for(k=0; k<8; k++) //check if poly1 contains valid hex symbols
		{
			if(poly1[k] < 48 || (poly1[k] > 57 && poly1[k] < 97) || poly1[k] > 102)
			{
				fprintf(stderr, "poly1 is not in hexstring format.\n");
				return;
			}
		}

		for(k=0; k<8; k++) //check if poly2 contains valid hex symbols
		{
			if(poly2[k] < 48 || (poly2[k] > 57 && poly2[k] < 97) || poly2[k] > 102)
			{
				fprintf(stderr, "poly2 is not in hexstring format.\n");
				return;
			}
		}
	}

	//convert hexstring to int
	unsigned int a = convertHexToInt(poly1);
	unsigned int b = convertHexToInt(poly2);

	unsigned result = circleX(a, b);

	//print results
	unsigned char d3 = (result & (255<<24)) >> 24;
	unsigned char d2 = (result & (255<<16)) >> 16;
	unsigned char d1 = (result & (255<<8)) >> 8;
	unsigned char d0 = (result & 255);
	printf("{%c%c}{%c%c}{%c%c}{%c%c} CIRCLEX {%c%c}{%c%c}{%c%c}{%c%c} = {%02x}{%02x}{%02x}{%02x}\n", poly1[0], poly1[1], poly1[2], poly1[3], poly1[4], poly1[5], poly1[6], poly1[7], poly2[0], poly2[1], poly2[2], poly2[3], poly2[4], poly2[5], poly2[6], poly2[7], d3, d2, d1, d0);
}
