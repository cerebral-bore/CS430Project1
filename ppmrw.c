#include <stdio.h>
#include <stdlib.h>

/* 	Jesus Garcia
	Project 1 - Images - 9/15/16
	CS430 - Prof. Palmer
	"Code should be able to read or write P3 or P6 ppm files."	*/

int main(int args, char *argv[]){
	
	char str[3];
	
	/* opening file for reading */
    FILE *fh = fopen("output_3.ppm" , "r");
	
	// Code taken from Tutorialspoint.com C function library
	if( fgets (str, 3, fh) != NULL ) 
	{
      /* writing content to stdout */
      puts(str);
	}

	// Check to see if there are 3 input arguments on launch
	if (args != 4) {
		fprintf(stderr, "Program requires: 'P# <inputname>.ppm <outputname>.ppm'");
		return(1);
	  }
	  
	// Check to see if the accepted P-type ppms are being asked for.
	if((*argv[1] != '3') && (*argv[1] != '6')){
		fprintf(stderr, "This program only works with P3 and P6 type ppm files.");
		return(2);
	}
	fprintf(stderr, str);
	
	// Check to see if the ppm file actually is P3 or P6
	if((str[1] != '3') && (str[1] != '6')){
		fprintf(stderr, "PPM file is not P3 or P6.");
		return(3);
	}
	
	printf("Hello World");
	return(0);
}