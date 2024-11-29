#include <iostream>
#include <stdexcept>
#include "pgm.h"


#define MAXLENGTH 100
#define MAXVALUE  255


Img read_pgm(std::string& fileName){
    FILE *filePointer;   
    char line[MAXLENGTH]; /* for character input from file */
    int maximumValue = 0; /* max value from header */
    int binary;           /* flag to indicate if file is binary (P5) or ascii (P2)*/
    long i,j;             /* (i,j) for loops */
    int test,temp;        /* for detecting EOF(test) and temp storage */

    /* Open the file, return an error if necessary. */
    if((filePointer = fopen(fileName.c_str(),"r")) == NULL){
        fclose (filePointer);
        throw std::invalid_argument("ERROR: cannot open file");
    }

    /* Check the file signature ("Magic Numbers" P2 and P5); skip comments
        and blank lines (CR with no spaces before it).*/
    fgets(line,MAXLENGTH,filePointer);
    while(line[0]=='#' || line[0]=='\n') 
        fgets(line,MAXLENGTH,filePointer);

    if(line[0]=='P' && (line[1]=='2')) {
        binary = 0;
    }else if(line[0]=='P' && (line[1]=='5')) {
        binary = 1;
    }else{
        fclose(filePointer);
        throw std::invalid_argument("ERROR: incorrect file format.");
    } 

    /* Input the width, height and maximum value, skip comments and blank
    * lines. */
    fgets(line,MAXLENGTH,filePointer);
    while(line[0]=='#' || line[0]=='\n') 
        fgets (line,MAXLENGTH,filePointer);

    int rows, cols;
    sscanf(line,"%d %d", &cols, &rows);

    fgets(line,MAXLENGTH,filePointer);
    while(line[0]=='#' || line[0]=='\n') 
        fgets(line,MAXLENGTH,filePointer);
    sscanf(line,"%d",&maximumValue);

    if(cols<1 || rows<1 || maximumValue<0 || maximumValue>MAXVALUE){
        fclose (filePointer);
        throw std::invalid_argument(
            "ERROR: invalid file specifications (cols/rows/max value)"
        );
    }

    Img image (rows, std::vector<unsigned char> (cols, 0));

    /* Read in the data for binary (P5) or ascii (P2) PGM formats   */
    if (binary) {
        for (i = 0; i < rows; i++) {
            fread((void *)&(image[i][0]),
            sizeof(unsigned char),cols,filePointer); 
            if (feof(filePointer))
                break;
        }
    }else{
        for(i= 0; i < rows; i++){
            for (j =0; j < cols; j++){ 
                test = fscanf (filePointer,"%d",&temp);
                if(test == EOF)
                    break;
                image[i][j] = (unsigned char)temp;
            }
            if(test == EOF)
                break;
        }
    }

    /* close the file and return 1 indicating success */
    fclose (filePointer);
    return image;
}

void print(Img&& img){
    int rows = img.size();
    if(rows == 0)
        return;
    int cols = img[0].size();
    if(cols == 0)
        return;
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j)
            std::cout << static_cast<int>(img[i][j]) << " ";
        std::cout << std::endl;
    }
}
