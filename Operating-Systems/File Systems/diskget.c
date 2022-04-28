#include "Constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

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

//fills array with block numbers of all data for a file given its starting_block and number of blocks
int getblocks(int* array, int starting_block, int num_blocks, int FAT_starts, int block_size, FILE* f){
    int blocknum = starting_block;
    fseek(f, FAT_starts*block_size, SEEK_SET);
    for(int i = 0; i < num_blocks; i++){
        array[i] = blocknum;
        fseek(f, FAT_starts*512 + blocknum*4, SEEK_SET);
        blocknum = getvalue(4, 0, f, SEEK_CUR);
    }
    return 0;
}

int main ( int argc, char *argv[] )
{
    char* file1 = argv[1];
    char* file2 = argv[2];
    
    FILE* checkdir;
    FILE* inputFile;

    if((checkdir = fopen(file2, "r"))){
        fclose(checkdir);
        printf("Copy failed: '%s' already exists in current directory. Remove it and try again.\n", file2);
        return 0;
    }

    if (!(inputFile = fopen(file1, "r"))){
        printf("Copy failed: '%s' not found in current directory.\n", file1);
        return 0;
    };

    int block_size = getvalue(2, 8, inputFile, SEEK_SET);
    int FAT_starts = getvalue(4, 4, inputFile, SEEK_CUR);
    int RDIR_starts = getvalue(4, 4, inputFile, SEEK_CUR);
    int RDIR_blocks = getvalue(4, 0, inputFile, SEEK_CUR);

    fseek(inputFile, block_size*RDIR_starts, SEEK_SET);

    char filename[31];
    int starting_block;
    int num_blocks;
    int found = 0;

    for(int i = 0; i < RDIR_blocks*block_size/DIRECTORY_ENTRY_SIZE; i++){
        
        //determine the file type. Do not print info if file is not in use.
        int status = getvalue(1, 0, inputFile, SEEK_CUR);
        if(status == 3 || 2){
            getstring(filename, 31, 26, inputFile, SEEK_CUR);
            if (strcmp(filename, file2) != 0){
                fseek(inputFile, 6, SEEK_CUR);
            }
            else{
                found = 1;
                printf("File is in the system. ");
                break;
            } 
        } 
    }

    if (found != 1){
        printf("File not found.\n");
        fclose(inputFile);
        return 0;
    }

    starting_block = getvalue(4, -57, inputFile, SEEK_CUR);
    num_blocks = getvalue(4, 0, inputFile, SEEK_CUR);

    FILE* outputFile = fopen(file2, "w");

    int blocks[num_blocks];
    getblocks(blocks, starting_block, num_blocks, FAT_starts, block_size, inputFile);

    fseek(inputFile, starting_block * block_size, SEEK_SET);
 
    void* temp = malloc(block_size);
    for(int i = 0; i < num_blocks; i++){
        fseek(inputFile, blocks[i]*512, SEEK_SET);
        fread(temp, block_size, 1, inputFile);
        fwrite(temp, block_size, 1, outputFile);
    }

    printf("Finished copying file to current directory.\n");
    fclose(inputFile);
    fclose(outputFile);
	return 0;
}