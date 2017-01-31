#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "const.h"
#include "info.h"
#include "fnct.h"

char specchars[6] = "$+.:=_";

int main(int argc,char *argv[]){

	srand(time(NULL));

	struct option long_opt[] = {
		{"user",0,0,'u'},
		{"admin",0,0,'a'},
		{"upper",0,0,'b'},
		{"lower",0,0,'s'},
		{"digits",0,0,'n'},
		{"spec-char",0,0,'c'},
		{"exclude",1,0,'e'},
		{"length",1,0,'l'},
		{"rand-len",0,0,'r'},
		{"rand-param",0,0,'p'},
		{"count",1,0,'i'},
		{"out",1,0,'o'},
		{"level",1,0,'w'},
		{"version",0,0,'v'},
		{"help",0,0,'h'},
		{0,0,0,0}
	};

	FILE *Outf;
	flags FLAGS = {TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE};

	int length = 8;
	int r = 1;
	int count = 1;

	int min,max;

	short int level = 1000;

	char exclude[128] = "";
	char ch;
	char opt;
	int optid;


	//Парсинг Переданных параметров

	while(TRUE){

		if( ( opt = getopt_long(argc,argv,"uabsnce:l:r:pi:o:w:vh",long_opt,&optid)) == -1 )
			break;

		switch(opt){
			case 'u':
				FLAGS.SPECCHAR = 0;
				level = 20;
				break;
			case 'a':
				FLAGS.SPECCHAR = 0;
				length = 16;
				level = 10000;
				break;
			case 'b':
				FLAGS.CHARHIGH = FALSE;
				break;
			case 's':
				FLAGS.CHARLOWR = FALSE;
				break;
			case 'n':
				FLAGS.NUMBER = FALSE;
				break;
			case 'c':
				FLAGS.SPECCHAR = TRUE;
				break;
			case 'e':
				sprintf(exclude,"%s",optarg);
				break;
			case 'l':
				length = atoi(optarg);
				break;
			case 'r':
				FLAGS.RANDLEN = TRUE;
				char *token, *last;

				token = strtok_r(optarg,"-",&last);
				min = atoi(token);

				token = strtok_r(NULL,"-",&last);
				max = atoi(token);

				break;
			case 'p':
				FLAGS.RANDOPT = TRUE;
				break;
			case 'i':
				count = atoi(optarg);
				break;
			case 'o':
				FLAGS.FILE = TRUE;
				if(optarg != NULL)	// если был передам параметр безопасно открывает файл 
					if(!(Outf = fopen(optarg,"w"))) 
						error("open out file",0);
				break;
			case 'w':
				level = atoi(optarg);
				break;
			case 'v':
				version();
			case 'h':
				help();			
		}
	}

	/* Генерация флагов рандомно */
	if(FLAGS.RANDOPT){

		max = 32;
		min = 8;

		FLAGS.CHARHIGH = rand()%2;
		FLAGS.CHARLOWR = rand()%2;
		FLAGS.NUMBER = rand()%2;
		FLAGS.SPECCHAR = rand()%2;
		FLAGS.RANDLEN = TRUE;
		count = rand()%20;

	}

	if(!Sflags(FLAGS)) return 0;	/* Если все символ.флаги = 0 */

	if(FLAGS.RANDLEN){	/* Если длинна меньше или = 0 */
		if((max - min) <= 0) error("wrong value min and max\n",0);
	}
	//printf("Exclude chars: '%s'\n",exclude);

	if(count > 1){	/* Вывод название программы если генерируется больше одного пароля*/

		int len = length;
		if(FLAGS.RANDLEN) len = max;


		equal(len,FLAGS.FILE,Outf);
		if(FLAGS.FILE) 	fprintf(Outf," genpass ");
		else 			printf(" genpass ");
		equal(len,FLAGS.FILE,Outf);

		putcharp(FLAGS.FILE,'\n',Outf);
	}

	for(int c = 0;c < count;c++){
		
		if(FLAGS.RANDLEN) length = rand()%(max - min) + min;

		for(int i = 0;i < length;){

			r = rand()%level;

			if(r < (level/4)){	/*	Генерируются заглавные буквы	*/
				if(FLAGS.CHARHIGH){
					ch = rand()%25+65;
				}
				else continue;
			}
			else if(r < ((level/4)*2) ){	/*	Генерируются маленькие буквы	*/
				if(FLAGS.CHARLOWR){
					ch = rand()%25+97;
				}
				else continue;
			}
			else if(r <= ((level/4)*3) ){	/*	Генерируются цифры	*/
				if(FLAGS.NUMBER){
					ch = rand()%10+0x30;
				}
				else continue;
			}
			else if(r <= ((level/4)*4) ){	/*	Генерируются специальные символы	*/
				if(FLAGS.SPECCHAR){
					ch = specchars[rand()%6];
				}
				else continue;
			}
			else{
				continue;
			}
			if(check(exclude,ch))
				continue;

			putcharp(FLAGS.FILE,ch,Outf);

			i++;
		}
		putcharp(FLAGS.FILE,'\n',Outf);
	}

	if(FLAGS.FILE) 
		fclose(Outf);

	return 0;
}

/*
putcharp: Выводит символ на консоль или в файл
*/
void putcharp(short int FLAG,char ch,FILE *out){
	if(FLAG) 
		putc(ch,out);
	else 
		putchar(ch);
}

/*
check: проверяет есть ли в строке [exclude] символ [ch]
return: 1 - есть, 0 - нет
*/
int check(char *exclude,char ch){
	for(int n = 0;exclude[n] != '\0';n++)
		if(exclude[n] == ch) return 1; /* если найден символ вернуть 1 */
	return 0;
}


//Sflag: Суммирует значения объекта
int Sflags(flags object){
	short int summ = 0;
	summ += object.CHARHIGH;
	summ += object.CHARLOWR;
	summ += object.NUMBER;
	summ += object.SPECCHAR;
	return summ;
}


//error: Вывод ошибки и выход
void error(char *str,int helps){
	printf("[%serror%s]: %s\n",RED,DEFAULT,str);
	if(helps) 
		help();
	exit(1);
}


//equal: вывод '=' для загаловка программы
void equal(int len,short int FILEF,FILE *out){
	int p = 0;
	do{
		putcharp(FILEF,'=',out);
		p++;
	}while(p < (len/2)-6);
}
