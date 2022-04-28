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

int main ( int argc, char *argv[] )
{
    char* filename = argv[1];
    FILE* inputFile = fopen(filename, "r");

    printf("Super block information:\n");

    int block_size = getvalue(2, 8, inputFile, SEEK_SET);
    printf("Block size: %i\n", block_size);

    int block_count = getvalue(4, 0, inputFile, SEEK_CUR);
    printf("Block count: %i\n", block_count);

    int FAT_starts = getvalue(4, 0, inputFile, SEEK_CUR);
    printf("FAT starts: %i\n", FAT_starts);

    int FAT_blocks = getvalue(4, 0, inputFile, SEEK_CUR);
    printf("Fat blocks: %i\n", FAT_blocks);

    int RDIR_starts = getvalue(4, 0, inputFile, SEEK_CUR);
    printf("Root directory start: %i\n", RDIR_starts);

    int RDIR_blocks = getvalue(4, 0, inputFile, SEEK_CUR);
    printf("Root directory blocks: %i\n\n", RDIR_blocks);

    printf("FAT information:\n");

    //set the position indicator of inputFile to the start of the FAT table
    fseek(inputFile, block_size*FAT_starts, SEEK_SET);

    int x = 0;
    int free_count = 0;
    int reserved_count = 0;
    int allocated_count = 0;

    //look at each FAT table entry, and note its status.
    for (int i = 0; i < block_count; i++){
        x = getvalue(4, 0, inputFile, SEEK_CUR);
        if (x==0){
            free_count++;
        }
        else if (x==1){
            reserved_count++;
        }
        else{
            allocated_count++;
        }
    }

    printf("Free Blocks: %i\n", free_count);
    printf("Reserved Blocks: %i\n", reserved_count);
    printf("Allocated Blocks: %i\n", allocated_count);
    
    fclose(inputFile);
	return 0;
}