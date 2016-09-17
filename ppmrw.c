#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 	Jesus Garcia
	Project 1 - pictures - 9/15/16
	CS430 - Prof. Palmer
	"Code should be able to read or write P3 or P6 ppm files."
	Your program (ppmrw) should have this usage pattern to convert a P3 or P6 picture to P3	
		ppmrw 3 <input.pmm> <output.pmm> or ppmrw 6 <input.pmm> <output.pmm>
	Your program (ppmrw) should have this usage pattern to convert a P3 or P6 picture to P6

*/
	
typedef struct pixData{
	unsigned char r,g,b;
} pixData;

typedef struct pixMap{
	unsigned char width, height;
	pixData *pixel;
} pixMap;

int errCheck(int args, char *argv[]);
void writePPM(const char outputName[]);
static pixMap *getP6PPM(const char *filename);
void createp6PPM(const char *filename, pixMap *picture);

int main(int args, char *argv[]){
	
	// Run the error checks
	errCheck(args, argv);
	
	int inputnum = *argv[1] - '0';
	if(inputnum == 3){
		writePPM(argv[3]);
	}else if(inputnum == 6){
		createp6PPM(argv[3], getP6PPM(argv[2]));
	}
	printf("Program run successfully.");
	return(0);
	
}



int errCheck(int args, char *argv[]){
	
	// Initial check to see if there are 3 input arguments on launch
	if (args != 4) {
		fprintf(stderr, "Error: Program requires usage: '# <inputname>.ppm <outputname>.ppm'");
		exit(1);
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
		exit(2);
	}
	
	// Check to see if the inputfile is in .ppm format
	if(strcmp(extOut, ".ppm") != 0){
		printf("Error: Output file not a PPM");
		exit(3);
	}
	
	// Check to see if the accepted P-type ppms are being asked for.
	int inputnum = *argv[1] - '0';
	if((inputnum != 3) && (inputnum != 6)){
		fprintf(stderr, "Error: This program only works with P3 and P6 type ppm files.");
		exit(4);
	}
	
	char str[5];
	FILE* fh = fopen(argv[2] , "r");
	fgets(str, 3, fh); // Read a line from file
	fclose(fh);
	
	// Check to see if the ppm file actually is P3 or P6
	if((str[1] != '3') && (str[1] != '6')){
		fprintf(stderr, "Error: PPM file is not P3 or P6.");
		exit(5);
	}
	return(0);
}

void writePPM(const char outputName[]){
	FILE* fh2 = fopen(outputName, "w");
	
	unsigned char size = 8;
	unsigned char colordepth = 255;
	fprintf(fh2, "P3\n# CREATOR: Jesus Garcia\n");
	fprintf(fh2, "%d %d\n%d", size, size, colordepth);

	fprintf(fh2, "\n255 255 255   0 0 0   0 0 255   255 0 255 \n");
	fprintf(fh2, "255 0 0   0 255 127   0 255 0   0 0 0 \n");
	fprintf(fh2, "0 255 0   0 0 0   0 255 127   255 0 0 \n");
	fprintf(fh2, "255 0 255   0 0 255   0 0 0   255 255 255");
	fclose(fh2);
}

static unsigned char *getP3PPM(const char *filename){
	
}

static pixMap *getP6PPM(const char *filename)
{
		
	char buffer[8];					// buffer of size 8
	pixMap *picture; 				// Struct creation, contains a 'width', 'height', 'pixData'
	FILE *inFile;					// File handler
	int c, rgb_comp_color;			// c is to be used for comment checking, rgb_c_c
	inFile = fopen(filename, "rb");	// Open PPM file for reading
	
	/* This code must run in this order as the ppm file must follow
		A specific pattern of reads and writes */

	if (!fgets(buffer, sizeof(buffer), inFile)){	// Loads picture format into buffer[] array
		fprintf(stderr, "Unable to allocate memory\n", filename);
		exit(6);
	}
    
    picture = (pixMap* )malloc(sizeof(pixMap));	// Allocate memory from picture
    if (picture == NULL) {								// If picture is allowed no memory
         fprintf(stderr, "Unable to allocate memory\n");
         exit(7);
    }

    // This code block will skip past a comment line
    c = getc(inFile);					// Usage of c int
    while (c == '#') { 					// Check for comments
		while (getc(inFile) != '\n') ;	// This while loop stops when a newline is found
		c = getc(inFile);				// Read the comment line
    }
    ungetc(c, inFile);	// Clear the c variable
	
    // Load picture size
    if (fscanf(inFile, "%d %d", &picture->width, &picture->height) != 2) {	// Stores the width and height of pic
         fprintf(stderr, "Error: File has invalid width and/or height.\n");
         exit(8);
    }
    // Load RGB color depth
    if (fscanf(inFile, "%d", &rgb_comp_color) != 1) { // Reads the single line where max color depth is
         fprintf(stderr, "Error: Invalid rgb component\n");
         exit(9);
    }
    // ENSURES ONLY FUNCTIONS FOR 8bit RGB ppms
    if (rgb_comp_color!= 255) {	// 255 = 8 bits of all 1's or '1111 1111'
         fprintf(stderr, "Error: RGB component must be 8 bit RGB\n", filename);
         exit(10);
    }
    while (fgetc(inFile) != '\n') ; // Clear whitespaces
    (*picture).pixel = (pixData*)malloc((*picture).width * (*picture).height * sizeof(pixData)); // Allocate sufficient memory for the pixMap pixel data
    if (!picture) {	// Check if picture is not NULL
         fprintf(stderr, "Error: Memory Allocation failed.\n");
         exit(11);
    }
    //read pixel data from file
    if (fread((*picture).pixel, 3 * (*picture).width, (*picture).height, inFile) != (*picture).height) {	// Check if stored data is same length as original pictures height
         fprintf(stderr, "Error: Data corruption.\n", filename);
         exit(12); 
    }

	// Close off the input file
    fclose(inFile);
    return picture;	// Return the pixMap data
}

void createp6PPM(const char *filename, pixMap *picture)
{
	// Create/open file to output p6 file to
    FILE *outFile;
    outFile = fopen(filename, "wb");

    //write the header file
		fprintf(outFile, "P6\n");										// PPM format (P6)
		fprintf(outFile, "# An auto comment line\n");					// Comment line
		fprintf(outFile, "%d %d\n",(*picture).width,(*picture).height);	// Dimensions of ppm file
		fprintf(outFile, "%d\n", 255);									// 8 bit RGB color depth

	// Binary pixel/pixmap data
	fwrite((*picture).pixel, 3 * (*picture).width, (*picture).height, outFile);
    fclose(outFile); // Close off output file
}