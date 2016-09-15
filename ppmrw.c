#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 	Jesus Garcia
	Project 1 - Images - 9/15/16
	CS430 - Prof. Palmer
	"Code should be able to read or write P3 or P6 ppm files."
	Your program (ppmrw) should have this usage pattern to convert a P3 or P6 image to P3	
		ppmrw 3 <input.pmm> <output.pmm> or ppmrw 6 <input.pmm> <output.pmm>
	Your program (ppmrw) should have this usage pattern to convert a P3 or P6 image to P6 */
	

int errCheck(int args, char *argv[]);
void writePPM(char outputName[]);


int main(int args, char *argv[]){
	
	// Run the error checks
	int errCode;
	if((errCode = errCheck(args, argv)) > 0){ return errCode; }
	
	char str[3];
	
	/* opening file for reading */
    FILE* fh = fopen(argv[2] , "r");
	fgets(str, 3, fh); // Read a line from file
	
	writePPM(argv[3]);
	printf("Program run successfully.");
	fclose(fh);
	return(0);
	
}

int errCheck(int args, char *argv[]){
	
	// Initial check to see if there are 3 input arguments on launch
	if (args != 4) {
		fprintf(stderr, "Error: Program requires usage: '# <inputname>.ppm <outputname>.ppm'");
		return(1);
	}
	
	// Check the file extension of input and output files
	char *extIn;
	char *extOut;
	if(strrchr(argv[2],'.') != NULL){
		extIn = strrchr(argv[2],'.');
	}
	if(strrchr(argv[3],'.') != NULL){
		extOut = strrchr(argv[3],'.');
	}
	
	// Check to see if the inputfile is in .ppm format
	if(strcmp(extIn, ".ppm") != 0){
		printf("Error: Input file not a PPM");
		return(2);
	}
	
	// Check to see if the inputfile is in .ppm format
	if(strcmp(extOut, ".ppm") != 0){
		printf("Error: Output file not a PPM");
		return(3);
	}
	
	// Check to see if the accepted P-type ppms are being asked for.
	int inputnum = *argv[1] - '0';
	if((inputnum != 3) && (inputnum != 6)){
		fprintf(stderr, "Error: This program only works with P3 and P6 type ppm files.");
		return(4);
	}
	
	char str[5];
	
	FILE* fh = fopen(argv[2] , "r");
	fgets(str, 3, fh); // Read a line from file
	fclose(fh);
	
	// Check to see if the ppm file actually is P3 or P6
	if((str[1] != '3') && (str[1] != '6')){
		fprintf(stderr, "Error: PPM file is not P3 or P6.");
		return(5);
	}
	
	return(0);
	
}

void writePPM(char outputName[]){
	FILE* fh2 = fopen(outputName, "w");
	
	unsigned char size = 4;
	unsigned char colordepth = 255;
	fprintf(fh2, "P3\n# CREATOR: Jesus Garcia\n");
	fprintf(fh2, "%d %d\n%d", size, size, colordepth);

	fprintf(fh2, "\n255 255 255   0 0 0   0 0 255   255 0 255 \n");
	fprintf(fh2, "255 0 0   0 255 127   0 255 0   0 0 0 \n");
	fprintf(fh2, "0 255 0   0 0 0   0 255 127   255 0 0 \n");
	fprintf(fh2, "255 0 255   0 0 255   0 0 0   255 255 255");
	fclose(fh2);
}