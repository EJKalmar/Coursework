#include "Constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

//returns integer value of a section of memory of length byte_length at location byte_offset from whence
int getvalue(int byte_length, int byte_offset, FILE* f, int whence){
    unsigned int* x = malloc(byte_length);
    fseek(f, byte_offset, whence);
    fread(x, byte_length, 1, f);
    unsigned int tmp = 0;
    if (byte_length ==1){
        tmp = *x;
    }
    else if (byte_length == 2){
        tmp = htons(*x);
    }
    else{
        tmp = htonl(*x);
    }
    x = &tmp;
    int result = *x;
    return result;
}

//fills array with string value from data of length byte_length at location byte_offset from whence
int getstring(char* array, int byte_length, int byte_offset, FILE* f, int whence){
    fseek(f, byte_offset, whence);
    for(int i=0;i<byte_length;i++){
        fread(&array[i], 1, 1, f);    
    }
    return 0;
}

//returns a date constructed from the next 7 bytes of data starting at location byte_offset from whence
//format YYYY/MM/DD HH:MM:SS
int getdate(char* array, int byte_offset, FILE* f, int whence){
    fseek(f, byte_offset, whence);
    int x;
    //year
    x = getvalue(2,0,f, SEEK_CUR);
    array[0] = (char) 48 + (x/1000) % 10;
    array[1] = (char) 48 + (x/100) % 10;
    array[2] = (char) 48 + (x/10) % 10;
    array[3] = (char) 48 + x % 10;
    //month
    x = getvalue(1, 0, f, SEEK_CUR);
    array[5] = (char) 48 + (x/10) % 10;
    array[6] = (char) 48 + x % 10;
    //day
    x = getvalue(1, 0, f, SEEK_CUR);
    array[8] = (char) 48 + (x/10) % 10;
    array[9] = (char) 48 + x % 10;
    //hour
    x = getvalue(1, 0, f, SEEK_CUR);
    array[11] = (char) 48 + (x/10) % 10;
    array[12] = (char) 48 + x % 10;
    //minute
    x = getvalue(1, 0, f, SEEK_CUR);
    array[14] = (char) 48 + (x/10) % 10;
    array[15] = (char) 48 + x % 10;
    //second
    x = getvalue(1, 0, f, SEEK_CUR);
    array[17] = (char) 48 + (x/10) % 10;
    array[18] = (char) 48 + x % 10;
    //special
    array[4] = array[7] = '/';
    array[13] = array[16] = ':';
    array[10] = ' ';
    return 0;
}
int main ( int argc, char *argv[] )
{
    char* filename = argv[1];
    FILE* inputFile = fopen(filename, "r");

    int block_size = getvalue(2, 8, inputFile, SEEK_SET);
    int RDIR_starts = getvalue(4, 12, inputFile, SEEK_CUR);
    int RDIR_blocks = getvalue(4, 0, inputFile, SEEK_CUR);

    fseek(inputFile, block_size*RDIR_starts, SEEK_SET);

    char f_type;
    int f_length;
    char f_name[31];
    char f_time_modified[19];

    for(int i = 0; i < RDIR_blocks*block_size/DIRECTORY_ENTRY_SIZE; i++){
        
        //determine the file type. Do not print info if file is not in use.
        int temp = getvalue(1, 0, inputFile, SEEK_CUR);
        if(temp != 0){
            if (temp == 3 || temp == 2){
                f_type = 'F';
            }
            else if (temp == 5 || temp == 4){
                f_type = 'D';
            }
            else{
                f_type = '_';
            }
            
            f_length = getvalue(4, 8, inputFile, SEEK_CUR);
            getdate(f_time_modified, 7, inputFile, SEEK_CUR);
            getstring(f_name, 31, 0, inputFile, SEEK_CUR);

            fseek(inputFile, 6, SEEK_CUR);

            printf("%c %10i %30s %s\n", f_type, f_length, f_name, f_time_modified);
        }
        else{
            fseek(inputFile, 63, SEEK_CUR);
        }
    }

    fclose(inputFile);
	return 0;
}