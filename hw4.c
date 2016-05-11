#include <stdio.h>
#include <stdlib.h>

void stageOne(char*, char*); 
void stageTwo(char*);
void stageThree(char*, char*);

int main(int argc, char ** argv)
{
	FILE * fp; 
	char buffer[48];

	fp = fopen(argv[1], "r");

	/*Error Check File*/
	if(fp == NULL)
	{
		printf("File could not be opened!\n");
		return 1; 
	}

	/*Read file into Buffer*/
	fread(buffer, 48, 1, fp);
	fclose(fp);

	/*Prints out Original Numbers*/
	int i;
	printf("Here is your original numbers!\n");
	for(i = 0; i < 48; ++i)
	{
		printf("%02x ", buffer[i]);
		if(i == 47)
			printf("\n");
	}
	
	/*Implements Stage One*/
	for(i = 0; i < 48; i +=4)
	{
		stageOne(&buffer[i], &buffer[i+3]);
	}
	

	/*Prints results from Stage One*/
	printf("\nHere is the results from Stage One!\n");
	for(i = 0; i < 48; ++i)
	{
		printf("%02x ", buffer[i]);
		if(i == 47)
			printf("\n");
	}
	
	/*Implements Stage Two*/
	for(i = 0; i < 48; ++i)
	{
		stageTwo(&buffer[i]);
	}

	/*Prints results from Stage Two*/
	printf("\nHere is the results from Stage two!\n");
	for(i = 0; i < 48; ++i)
	{
		printf("%02x ", buffer[i]);
		if(i == 47)
			printf("\n");
	}


	/*Implements Stage Three*/
	for(i = 0; i < 48; i +=4)
	{
		stageThree(&buffer[i], &buffer[i+3]);
	}

	/*Prints results from Stage Three*/
	printf("\nHere is the results from Stage Three!\n");
	for(i = 0; i < 48; ++i)
	{
		printf("%02x ", buffer[i]);
		if(i == 47)
			printf("\n");
	}


	/*Prints the buffer as a String*/
	printf("\nThe Message is: %s\n", buffer);
	


	return 0;  
}

/*Swaps bytes c0 and c3*/
void stageOne(char* c0, char* c3)
{
	char temp = *c0; 
	*c0 = *c3;
	*c3 = temp;
	return; 
}

/*Swaps bits b5 with b3, and bit b4 with b2*/ 
void stageTwo(char* byte)
{
	/*Shifts bits i want to work with all the way over*/
	char XOR_temp = ((*byte >> 5) ^ (*byte >> 3)) & ((1U << 1) -1);
	/*XORs new mask over the original number*/
	*byte = *byte ^ ((XOR_temp <<5) | (XOR_temp <<3));

	char XOR_temp2 = ((*byte >> 4) ^ (*byte >> 2)) & ((1U << 1) -1);
	*byte = *byte ^ ((XOR_temp2 <<4) | (XOR_temp2 <<2));
 
	return; 
}	

/*XOR bytes c0 and c3 with "a"*/
void stageThree(char* c0, char* c3)
{
	*c0 = *c0 ^ 97; /*97 ascii of "a"*/
	*c3 = *c3 ^ 97;
	return; 
}
