#include <stdio.h>
#include <stdlib.h>

/* 	Jesus Garcia
	Project 1 - Images - 9/15/16
	CS430 - Prof. Palmer
	"Code should be able to read or write P3 or P6 ppm files."	*/
	
int errCheck(char str[], int args, int inputnum);

int main(int args, char *argv[]){
	
	char str[3];
	int errCode;
	int inputnum = *argv[1] - '0';
	
	/* opening file for reading */
    FILE *fh = fopen("output_3.ppm" , "r");
	
	// Code taken from Tutorialspoint.com C function library, reads a line from ppm file
	if( fgets (str, 3, fh) != NULL ) 
	{
      /* writing content to stdout */
      puts(str);
	}
	
	errCode = errCheck(str, args, inputnum);
	
	if(errCode > 0){
		return errCode;
	}
	
	printf("Hello World");
	return(0);
}

int errCheck(char str[], int args, int inputnum){
	
	// Check to see if there are 3 input arguments on launch
	if (args != 4) {
		fprintf(stderr, "Program requires: 'P# <inputname>.ppm <outputname>.ppm'");
		return(1);
	  }
	  
	// Check to see if the accepted P-type ppms are being asked for.
	if((inputnum != 3) && (inputnum != 6)){
		fprintf(stderr, "This program only works with P3 and P6 type ppm files.");
		return(2);
	}
	
	// Check to see if the ppm file actually is P3 or P6
	if((str[1] != '3') && (str[1] != '6')){
		fprintf(stderr, "PPM file is not P3 or P6.");
		return(3);
	}
	return(0);
}