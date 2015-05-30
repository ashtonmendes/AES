#ifndef UTILITIES_H_
#define UTILITIES_H_

unsigned char bigDot(unsigned char, unsigned char);
unsigned char xtime(unsigned char);
unsigned int circleX(unsigned int, unsigned int);
unsigned int convertHexToInt(char*);
unsigned long long convertHexToLong(char*);
unsigned char inverseBitCoeff(unsigned char);
void longHandDiv(unsigned long long, unsigned long long, unsigned long long*, unsigned long long*, int);
int findDeg(unsigned long long);
void prettyPrint(unsigned long long);
void fetchFromTable(char*, unsigned char[16][16], unsigned int*, unsigned int*);
unsigned char subByte(unsigned char, unsigned char[16][16]);
unsigned int subWord(unsigned int, unsigned char[16][16]);
unsigned int rotWord(unsigned int);
unsigned int word(unsigned char, unsigned char, unsigned char, unsigned char);
void fetchKey(char*, unsigned char[16]);
void addRoundKey(unsigned char[4][4], unsigned int, unsigned int, unsigned int, unsigned int);
void subBytes(unsigned char[4][4], unsigned char[16][16]);
void shiftRows(unsigned char[4][4]);
void mixColumns(unsigned char[4][4], unsigned int);
void printState(int, unsigned char[4][4], char*, int);
void invShiftRows(unsigned char[4][4]);
void invSubBytes(unsigned char[4][4], unsigned char[16][16]);
unsigned char invSubByte(unsigned char, unsigned char[16][16]);
void invMixColumns(unsigned char[4][4], unsigned int);


#endif /* UTILITIES_H_ */
