/*
 * decrypt.h
 *
 *  Created on: Apr 5, 2015
 *      Author: ashton
 */

#ifndef DECRYPT_H_
#define DECRYPT_H_

void performDecrypt(char*, char*, char*);
void AES_decrypt(unsigned char[16], unsigned char[16], unsigned int[44], unsigned char[16][16], unsigned int);

#endif /* DECRYPT_H_ */
