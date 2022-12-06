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
#include "edit.h"


Status read_validate_edit(char *argv[], EditInfo *e_info) //function to validate the files provided by the user 
{
	if(strcmp(strstr(argv[4],"."),".mp3") == 0)
	{
		e_info -> file_name = argv[4];
		return m_success;
	}
	else
	{
		printf("!! Provided a wrong input file !!\nPlease provide a .mp3 file\nExample : sample.mp3\n");
		return m_failure;
	}
}

Status open_edit_file(EditInfo *e_info)                      //function to open all the required files 
{
	e_info -> fptr_input = fopen(e_info -> file_name, "r+"); //open the original mp3 file in read mode 
	if(e_info -> fptr_input == NULL)
	{
		perror("fopen");
		fprintf(stderr, "\nERROR: Unable to open the file %s\n", e_info-> file_name); //if failed to open then print the error message 
		return m_failure;
	}
	
	e_info->temp_file_name = "temp.mp3";                   
	e_info->temp_file = fopen(e_info->temp_file_name,"w+"); //open the temporary file  
	if(e_info->temp_file == NULL)                  
	{
		perror("fopen");                                    //print the error message 
		fprintf(stderr, "\nERROR: Unable to open the temporary file %s\n", e_info->file_name);
		return m_failure;
	}
  return m_success;
}

void copy_data(EditInfo *e_info, int size)                 //function to copy the data from original to temp file 
{
	char buffer[size];
	fread(buffer, 1, size, e_info->fptr_input);
	fwrite(buffer, 1 , size, e_info->temp_file);
}

TagReaderEdit findtag(char *argv[])                       //function the return the corresponding enum value based on the option selected by user   
{
	if(strcmp(argv[2],"-t") == 0)
		return e_tit2;
	else if(strcmp(argv[2],"-a") == 0)
		return e_tpe1;
	else if(strcmp(argv[2],"-A") == 0)
		return e_talb;
	else if(strcmp(argv[2],"-y") == 0)
		return e_tyer;
	else if(strcmp(argv[2],"-c") == 0)
		return e_tcon;
	else if(strcmp(argv[2],"-g") == 0)
		return e_tcom;
	else
		return e_unsupport;                               //if the selected option is wrong then return e_unsupport 
}

void find_tag_name(EditInfo *e_info)                      //function to find the tag name 
{
	switch(e_info->tag_name)                      //based on the enum value stored in the e_info->tag_name then store the equivalent label in tag 
	{
		case e_tit2 : e_info->tag = "TIT2";
					  break;
		case e_tpe1 : e_info->tag = "TPE1";
					  break;
		case e_talb : e_info->tag = "TALB";
					  break;
		case e_tyer : e_info->tag = "TYER";
					  break;
		case e_tcon : e_info->tag = "TCON";
					  break;
		case e_tcom : e_info->tag = "COMM";
					  break;
	}
}

int old_size(EditInfo *e_info)                    //function to find the old size stored in the respective tag 
{
	char buffer[4];
	fread(buffer, 1, 4, e_info->fptr_input);
	int size = 0, run = 3, mul = 1;
	while(run != -1)
	{
      size += ((int)(buffer[run] & 0x0F) * mul);
      mul *= 16;
      size += ((int)(buffer[run] >> 4) *  mul);
      mul *=16;
      run--;
	}
    return size;	
}
void updated_data(EditInfo *e_info, char *argv[]) 	//function to store the content of the tag in the e_info->tag_content
{
	switch(e_info->tag_name)
	{
		case e_tit2 : e_info->tag_content = argv[3];
					  break;
		case e_tpe1 : e_info->tag_content = argv[3];
					  break;
		case e_talb : e_info->tag_content = argv[3];
					  break;
		case e_tyer : e_info->tag_content = argv[3];
					  break;
		case e_tcon : e_info->tag_content = argv[3];
					  break;
		case e_tcom : e_info->tag_content = argv[3];
					  break;
	}
}
					  
void copy_updated_data(EditInfo *e_info, int size, char *data) //function to copy the updated content in the temp_file 
{
	char buffer[size + 1];
	strcpy(buffer, data);
	fwrite(buffer, 1, size, e_info->temp_file);
}

void copy_updated_data_num(EditInfo *e_info, int size, int len) /*function to print the updated number which is the length of the new data to be 
																  add*/
{
	char buffer[4];
	buffer[0] = (len >> 24) & 0xFF;
	buffer[1] = (len >> 16) & 0xFF;
	buffer[2] = (len >> 8) & 0xFF;
	buffer[3] = len & 0xFF;
	fwrite(buffer, 1, size, e_info->temp_file);
}

Status compare_tag(EditInfo *e_info)                   //function to compare the current tag in original mp3 file with the user entered tag  
{
	char buffer[5];
	fread(buffer, 1, 4, e_info->fptr_input);
	buffer[4] = '\0';
	if(strcmp(buffer, e_info->tag) == 0)
		return m_success;
	else
	{
		strcpy(e_info->new_tag, buffer);
		return m_failure;
	}
}

int find_len(EditInfo *e_info)                        //function to find the length of the remaining tag data apart from the one to be updated  
{
	char buffer[4];
	fread(buffer, 1, 4, e_info->fptr_input);
	int size = 0, run = 3, mul = 1;
	while(run != -1)
	{
		size += ((int)(buffer[run] & 0x0F) * mul);
		mul *= 16;
		size += ((int)(buffer[run] >> 4) * mul);
		mul *= 16;
		run--;
	}
	fwrite(buffer, 1, 4, e_info->temp_file);
	return size;
}
