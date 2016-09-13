#include <stdio.h>
#include <stdlib.h>

/* 	Jesus Garcia
	Project 1 - Images - 9/15/16
	CS430 - Prof. Palmer
	"Code should be able to read or write P3 or P6 ppm files."	*/

int main(int args, char *argv[]){
	if (args != 4) {
		printf("Program requires: 'P# <inputname>.ppm <outputname>.ppm'");
		return(1);
	  }
	  
	printf("Hello World");
	return(0);
}