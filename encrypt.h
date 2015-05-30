/*
 * encrypt.h
 *
 *  Created on: Apr 5, 2015
 *      Author: ashton
 */

#ifndef ENCRYPT_H_
#define ENCRYPT_H_

void printState(int, unsigned char[4][4], char*);
void performEncrypt(char*, char*, char*);
void AES_encrypt(unsigned char[16], unsigned char[16], unsigned int[44], unsigned char[16][16], unsigned int);

#endif /* ENCRYPT_H_ */
