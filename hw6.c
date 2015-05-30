#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include "tablecheck.h"
#include "modprod.h"
#include "encrypt.h"
#include "decrypt.h"
#include "keyexpand.h"
#include "inverse.h"

void printUsage()
{
	fprintf(stderr, "Usage:\nhw6 tablecheck -t=tablefile \nhw6 modprod -p1=poly1 -p2=poly2 \nhw6 keyexpand -k=key -t=tablefile \nhw6 encrypt -k=key -t=tablefile [file] \nhw6 decrypt -k=key -t=tablefile [file] \nhw6 inverse -p=poly\n");
}

int main(int argc, char *argv[])
{
	//skip argv[0]
	argc--;
	argv++;

	if(argc <= 0) //No arguments provided
	{
		fprintf(stderr, "Please enter command line arguments.\n");
		printUsage();
		return EXIT_FAILURE;
	}

	//tablecheck
	if(strcmp(*argv, "tablecheck") == 0)
	{
		if(argc-1 < 1 || argc-1 > 1)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		char* tablefile = malloc(100*sizeof(char));

		for(argc--; argc>0; argc--)
		{
			argv++;

			if(strlen(*argv) < 4)
			{
				fprintf(stderr, "Malformed command.\n");
				printUsage();
				return EXIT_FAILURE;
			}

			//tablefile
			if(argv[0][0]=='-' && argv[0][1]=='t' && argv[0][2]=='=')
			{
				//Get tablefile from argv
				int i=0;
				for(i=3; i<strlen(*argv); i++)
				{
					tablefile[i-3] = argv[0][i];
				}
				tablefile[i-3] = '\0';
			}

			else
			{
				fprintf(stderr, "Malformed command.\n");
				printUsage();
				return EXIT_FAILURE;
			}
		}

		checkTable(tablefile);
	}

	//modprod
	else if(strcmp(*argv, "modprod") == 0)
	{
		//Get hold of arguments
		char* poly1 = malloc(100*sizeof(char));
		char* poly2 = malloc(100*sizeof(char));

		//No, less or extra parameters for modprod
		if(argc-1 < 2 || argc-1 > 2)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		for(argc--; argc>0; argc--)
		{
			argv++;

			if(strlen(*argv) < 5)
			{
				fprintf(stderr, "Malformed command.\n");
				printUsage();
				return EXIT_FAILURE;
			}

			//poly1
			if(argv[0][0]=='-' && argv[0][1]=='p' && argv[0][2]=='1' && argv[0][3]=='=')
			{
				//Get poly1 from argv
				int i=0;
				for(i=4; i<strlen(*argv); i++)
				{
					poly1[i-4] = argv[0][i];
				}
				poly1[i-4] = '\0';
			}

			//poly2
			else if(argv[0][0]=='-' && argv[0][1]=='p' && argv[0][2]=='2' && argv[0][3]=='=')
			{
				//Get poly2 from argv
				int i=0;
				for(i=4; i<strlen(*argv); i++)
				{
					poly2[i-4] = argv[0][i];
				}
				poly2[i-4] = '\0';
			}

			else
			{
				fprintf(stderr, "Malformed command.\n");
				printUsage();
				return EXIT_FAILURE;
			}
		}

		if(strlen(poly1) == 0 || strlen(poly2) == 0)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		computeModprod(poly1, poly2);

		free(poly1);
		free(poly2);
	}

	//keyexpand
	else if(strcmp(*argv, "keyexpand") == 0)
	{
		//Get hold of arguments
		char* key = malloc(100*sizeof(char));
		char* tablefileName = malloc(100*sizeof(char));

		//No, less or extra parameters for keyexpand
		if(argc-1 < 2 || argc-1 > 2)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		for(argc--; argc>0; argc--)
		{
			argv++;

			if(strlen(*argv) < 4)
			{
				fprintf(stderr, "Malformed command.\n");
				printUsage();
				return EXIT_FAILURE;
			}

			//key
			if(argv[0][0]=='-' && argv[0][1]=='k' && argv[0][2]=='=')
			{
				//Get key from argv
				int i=0;
				for(i=3; i<strlen(*argv); i++)
				{
					key[i-3] = argv[0][i];
				}
				key[i-3] = '\0';
			}

			//tablefile
			else if(argv[0][0]=='-' && argv[0][1]=='t' && argv[0][2]=='=')
			{
				//Get tablefile from argv
				int i=0;
				for(i=3; i<strlen(*argv); i++)
				{
					tablefileName[i-3] = argv[0][i];
				}
				tablefileName[i-3] = '\0';
			}

			else
			{
				fprintf(stderr, "Malformed command.\n");
				printUsage();
				return EXIT_FAILURE;
			}
		}

		if(strlen(key) == 0 || strlen(tablefileName) == 0)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		expandKey(key, tablefileName);

		free(key);
		free(tablefileName);
	}

	//Encrypt - Decrypt
	else if(strcmp(*argv, "encrypt") == 0 || strcmp(*argv, "decrypt") == 0)
	{
		char command[10]="";
		if(strcmp(*argv, "encrypt") == 0)strcpy(command, "encrypt");
		if(strcmp(*argv, "decrypt") == 0)strcpy(command, "decrypt");

		//Get hold of arguments
		char* key = malloc(100*sizeof(char));
		char* tableFileName = malloc(100*sizeof(char));
		char* file = malloc(100*sizeof(char));
		*file='\0';

		//No, less or extra parameters
		if(argc-1 < 2 || argc-1 > 3)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		for(argc--; argc>0; argc--)
		{
			argv++;

			//Commanldine option encountered
			if(argv[0][0] == '-')
			{
				if(strlen(*argv) < 4)
				{
					fprintf(stderr, "Malformed command.\n");
					printUsage();
					return EXIT_FAILURE;
				}

				//key
				if(argv[0][0]=='-' && argv[0][1]=='k' && argv[0][2]=='=')
				{
					//Get key from argv
					int i=0;
					for(i=3; i<strlen(*argv); i++)
					{
						key[i-3] = argv[0][i];
					}
					key[i-3] = '\0';
				}
				else if(argv[0][0]=='-' && argv[0][1]=='t' && argv[0][2]=='=')
				{
					//Get tableFileName from argv
					int i=0;
					for(i=3; i<strlen(*argv); i++)
					{
						tableFileName[i-3] = argv[0][i];
					}
					tableFileName[i-3] = '\0';
				}
				else
				{
					fprintf(stderr, "Malformed command.\n");
					printUsage();
					return EXIT_FAILURE;
				}
			}

			//file
			else if(strlen(*argv) > 0)
			{
				//Get file from argv
				int i=0;
				for(i=0; i<strlen(*argv); i++)
				{
					file[i] = argv[0][i];
				}
				file[i] = '\0';
			}
		}

		//Check for errors
		if(strlen(key)==0 || strlen(tableFileName)==0)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}
		else
		{
			if(strcmp(command, "encrypt")==0 || strcmp(command, "decrypt")==0)
			{
				//CHECK FORMAT OF KEY

				/*if(strlen(key)!=16)
				{
					fprintf(stderr, "Key should be 8-bytes long, in hexstring format.\n");
					printUsage();
					return EXIT_FAILURE;
				}
				else if(strlen(key)==16)
				{
					int k=0;
					for(k=0; k<16; k++)
					{
						if(key[k] < 48 || (key[k] > 57 && key[k] < 97) || key[k] > 102)
						{
							fprintf(stderr, "Key is not in hexstring format.\n");
							printUsage();
							return EXIT_FAILURE;
						}
					}
				}*/
			}
		}

		if(strlen(key) == 0 || strlen(tableFileName) == 0)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		if(strcmp(command, "encrypt") == 0) performEncrypt(key, tableFileName, file);
		if(strcmp(command, "decrypt") == 0) performDecrypt(key, tableFileName, file);

		free(key);
		free(tableFileName);
		free(file);
	}

	//inverse
	else if(strcmp(*argv, "inverse") == 0)
	{
		if(argc-1 < 1 || argc-1 > 1)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		char* poly = malloc(100*sizeof(char));

		for(argc--; argc>0; argc--)
		{
			argv++;

			if(strlen(*argv) < 4)
			{
				fprintf(stderr, "Malformed command.\n");
				printUsage();
				return EXIT_FAILURE;
			}

			//poly
			if(argv[0][0]=='-' && argv[0][1]=='p' && argv[0][2]=='=')
			{
				//Get tablefile from argv
				int i=0;
				for(i=3; i<strlen(*argv); i++)
				{
					poly[i-3] = argv[0][i];
				}
				poly[i-3] = '\0';
			}
		}

		if(strlen(poly) == 0)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		computeInverse(poly);
	}

	else
	{
		fprintf(stderr, "Malformed command.\n");
		printUsage();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
