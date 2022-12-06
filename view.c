/*
Name          : VISHESH K
Date          :
Documentation :
Sample Input  :
Sample Output :
*/

#include <stdio.h>
#include <string.h>
#include "info.h"
#include "view.h"

Status read_validate(char *argv[], ViewInfo *info)    //function to read and validate the required files  
{
	if(strcmp(strstr(argv[2],"."),".mp3") == 0)
	{
		info -> file_name = argv[2];
		return m_success;
	}
	else
	{
		printf("!! Provided a wrong input file !!\nPlease provide a .mp3 file\nExample : sample.mp3\n");
		return m_failure;
	}
}

Status open_file(ViewInfo *info)                   //function to open all the required files 
{
	info -> fptr_input = fopen(info -> file_name, "r+");
	if(info -> fptr_input == NULL)
	{
		perror("fopen");
		fprintf(stderr, "\nERROR: Unable to open file %s\n", info -> file_name);
		return m_failure;
	}
	else
	{
		return m_success;
	}
}

Status validate_IDversion(ViewInfo *info)      //function to validate if the version we are working with is ID3 or not 
{
	fseek(info->fptr_input,0,SEEK_SET);
	char buffer[4];
	fread(buffer,1,3,info->fptr_input);
	buffer[3] = '\0';
	if(strcmp(buffer,"ID3") == 0)
		return m_success;
	else
		return m_failure;
}

Status tag_data(TagReader tag_name, int tag_size, FILE* fptr_input) //function to read the tag data and print the output 
{
	char buffer[tag_size];
	fread(buffer, 1, tag_size-1, fptr_input);        //read the size no of bytes to buffer and print the data accordingly 
    buffer[tag_size - 1] = '\0';
	switch(tag_name)
	{
		case m_tit2: printf("TITLE          :        %s\n", buffer);
					 break;
		case m_tpe1: printf("ARTIST         :        %s\n", buffer);
					 break;
		case m_talb: printf("ALBUM          :        %s\n", buffer);
					 break;
		case m_tyer: printf("YEAR           :        %s\n", buffer);
					 break;
		case m_tcon: printf("CONTENT        :        %s\n", buffer);
					 break;
		case m_tcom: printf("COMMENT        :        %s\n", buffer);
					 break;
	}
	return m_success;
}

TagReader find_tag(ViewInfo *info)      //function to return the enum value based on the tag value which is read 
{
	char buffer[5];
	fread(buffer,1,4,info->fptr_input);
	buffer[4] = '\0';
	if(strcmp(buffer,"TIT2") == 0)
		return m_tit2;
	else if(strcmp(buffer,"TPE1") == 0)
		return m_tpe1;
	else if(strcmp(buffer,"TALB") == 0)
		return m_talb;
	else if(strcmp(buffer,"TYER") == 0)
		return m_tyer;
	else if(strcmp(buffer,"TCON") == 0)
		return m_tcon;
	else if(strcmp(buffer,"COMM") == 0)
		return m_tcom;
}

int find_size(ViewInfo *info)          //function to return the size of the tag content 
{
	char buffer[4];
	fread(buffer,1,4,info->fptr_input);
	int size = 0, run = 3, mul = 1;
	while(run != -1)                   //loop used to find the size by multiplying the bytes with 16 power index pos value  
	{
      size += ((int)(buffer[run] & 0x0F) * mul);
      mul *= 16;
      size += ((int)(buffer[run] >> 4) *  mul);
      mul *=16;
      run--;
	}
    return size;
}


