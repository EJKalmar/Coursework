#include "Constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

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
    
    FILE* inputFile;

    if (!(inputFile = fopen(file1, "r"))){
        printf("Copy failed: '%s' not found in current directory.\n", file1);
        return 0;
    };

    int block_size = getvalue(2, 8, inputFile, SEEK_SET);
    int FAT_starts = getvalue(4, 4, inputFile, SEEK_CUR);
    int FAT_blocks = getvalue(4, 0, inputFile, SEEK_CUR);
    int RDIR_starts = getvalue(4, 0, inputFile, SEEK_CUR);
    int RDIR_blocks = getvalue(4, 0, inputFile, SEEK_CUR);

    fseek(inputFile, block_size*RDIR_starts, SEEK_SET);

    char filename[31];
    int num_blocks;
    int found = 0;
    //make sure the file is not already in our system
    for(int i = 0; i < RDIR_blocks*block_size/DIRECTORY_ENTRY_SIZE; i++){
        int status = getvalue(1, 0, inputFile, SEEK_CUR);
        if(status == 3 || 2){
            getstring(filename, 31, 26, inputFile, SEEK_CUR);
            if (strcmp(filename, file2) != 0){
                fseek(inputFile, 6, SEEK_CUR);
            }
            else{
                found = 1;
                break;
            }
        }
        else if (status == 0){
            break;
        } 
    }

    if (found != 0){
        //printf("Copy failed. File '%s' was not found on %s.\n", file2, file1);
        printf("Error: '%s' already exists in the system.\n", file2);
        fclose(inputFile);
        return 0;
    }

    FILE* file = fopen(file2, "r");
    //find file size to determine how many blocks we will need
    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    num_blocks = (int) file_size / block_size;
    //determine which blocks we will use (the first ones that are free)
    int blocks[num_blocks];
    fseek(inputFile, FAT_starts*block_size, SEEK_SET);
    int blocknum = 0;
    int status;
    for(int i = 0; i < (int)FAT_blocks*block_size/4; i++){
        status = getvalue(4, 0, inputFile, SEEK_CUR);
        if (status == 0 || status == 2 || status == 4){
            blocks[blocknum] = i;
            blocknum++;
        }
        if (blocknum >= num_blocks){
            break;
        }
    }
    
    if(blocknum != num_blocks){
        printf("Not enough space on system.\n");
        return 0;
    }

    //find a free directory entry
    int dir_entry_num;
    fseek(inputFile, RDIR_starts*block_size, SEEK_SET);
    for(int i = 0; i < RDIR_blocks*block_size/DIRECTORY_ENTRY_SIZE; i++){
        status = getvalue(1, 0, inputFile, SEEK_CUR);
        if (status == DIRECTORY_ENTRY_FREE){
            dir_entry_num = i;
            break;
        }
        else if (i == RDIR_blocks*block_size/DIRECTORY_ENTRY_SIZE-1){
            printf("No space to write to system.\n");
            return 0;
        }
    }

    fclose(inputFile);

    //get the current date & time
    time_t t = time(NULL);
    struct tm date = *localtime(&t);
    date.tm_year += 1900;
    date.tm_mon += 1;    

    FILE* sys = fopen(file1, "r+");
    
    //create a directory entry
    fseek(sys, RDIR_starts*block_size + dir_entry_num*DIRECTORY_ENTRY_SIZE, SEEK_SET);
    status = DIRECTORY_ENTRY_FILE;
    fwrite(&status, 1, 1, sys);
    int tmp;
    tmp = htonl(blocks[0]);
    fwrite(&tmp, 4, 1, sys);
    tmp = htonl(num_blocks);
    fwrite(&tmp, 4, 1, sys);
    tmp = htonl(file_size);
    fwrite(&tmp, 4, 1, sys);
    tmp = htons(date.tm_year);
    fwrite(&tmp, 2, 1, sys);
    fwrite(&date.tm_mon, 1, 1, sys);
    fwrite(&date.tm_mday, 1, 1, sys);
    fwrite(&date.tm_hour, 1, 1, sys);
    fwrite(&date.tm_min, 1, 1, sys);
    fwrite(&date.tm_sec, 1, 1, sys);
    fwrite(&tmp, 2, 1, sys);
    fwrite(&date.tm_mon, 1, 1, sys);
    fwrite(&date.tm_mday, 1, 1, sys);
    fwrite(&date.tm_hour, 1, 1, sys);
    fwrite(&date.tm_min, 1, 1, sys);
    fwrite(&date.tm_sec, 1, 1, sys);
    fwrite(file2, strlen(file2), 1, sys);

    void* temp = malloc(block_size);
    fseek(file, 0, SEEK_SET);

    for(int i = 0; i < num_blocks; i++){
        //fill in FAT table entry to next block
        fseek(sys, FAT_starts*block_size + blocks[i]*FAT_ENTRY_SIZE, SEEK_SET);
        if (i == num_blocks - 1){
            status = FAT_EOF;
            fwrite(&status, FAT_ENTRY_SIZE, 1, sys);
        }
        else{
            tmp = htonl(blocks[i+1]);
            fwrite(&tmp, FAT_ENTRY_SIZE, 1, sys);
        }
        //fill block in with data
        fread(temp, block_size, 1, file);
        fseek(sys, blocks[i]*block_size, SEEK_SET);
        fwrite(temp, block_size, 1, sys);
    }

    printf("Finished copying file to system.\n");
    fclose(sys);
    fclose(file);
	return 0;
}