#include <stdio.h>
#include <stdlib.h>
#include "const.h"

void version(){
	printf("version: %0.2f\n",VERSION);
	exit(0);
}

void help(){
	printf("Usage: genpass [options]\n");
	printf("  --user, -u: 	gen password for user (level=20)\n");
	printf("  --admin, -a: 	gen password for admin (level=10000)\n");
	printf("  --upper, -b: 	exclude upper case in gen passwrod\n");
	printf("  --lower, -s: 	exclude lower case in gen passwrod\n");
	printf("  --digits, -n: 	exclude the digits in gen passwrod\n");
	printf("  --spec-char, -c: includ special chars in gen passwrod\n");
	printf("  --out, -o <file>: output file\n");
	printf("  --exclude, -e <chars>: exclude chars\n");
	printf("  --length, -l <length>: cpecific length password\n");
	printf("  --rand-len, -r <min>-<max>: defferent length password\n");
	printf("  --rand-param, -p: 	random options\n");
	printf("  --count, -i <count>: specific count gen password\n");
	printf("  --level, -w <level>: specific level gen passwod\n");
	printf("  --help, -h: 	print this help page and exit\n");
	printf("  --verison, -v: 	print version program and exit\n");
	exit(0);
}
