#include "const.h"

typedef struct {
	int CHARHIGH:2;
	int CHARLOWR:2;
	int NUMBER:2;
	int SPECCHAR:2;
	int RANDLEN:2;
	int RANDOPT:2;
	int FILE:2;
} flags;

void putcharp(short int FLAG,char ch,FILE *out);
void equal(int len,short int FILEF,FILE *out);
int parsopt(char *arg,char *str);
int check(char *exclude,char ch);
void error(char *str,int helps);
int Sflags(flags object);
void version();
void help();
