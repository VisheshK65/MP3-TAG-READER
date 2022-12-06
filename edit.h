#ifndef EDIT_H
#define EDIT_H

#include<stdio.h>
#include "info.h"

/*store the all the required variable and the file pointers and integer value in a structure */
typedef struct _EditInfo
{
	char *file_name;
	FILE *fptr_input;

	char *temp_file_name;
	FILE *temp_file;

	TagReaderEdit tag_name;
	int tag_size;
	char *tag_content;
	char *tag;

	char new_tag[5];

	int old_tag_size;

	char *da_tit2;
	char *da_tpe1;
	char *da_talb;
	char *da_tyer;
	char *da_tcon;
	char *da_tcom;

}EditInfo;               

//function to validate all the required files 
Status read_validate_edit(char *argv[], EditInfo *e_info);
//function to open all the required files 
Status open_edit_file(EditInfo *e_info);
//function to find the old tag size 
int old_size(EditInfo *e_info);
//function to copy the data from original file to temp file 
void copy_data(EditInfo *e_info, int size);
//function to find the enum value of the corresponding tag 
void find_tag_name(EditInfo *e_info);
//function to update the user entered data in temp file 
void updated_data(EditInfo *e_info, char *argv[]);
//function to find the tag 
TagReaderEdit findtag(char *argv[]);
//function to compare the enum tag value with the tag read from the original file to be compared so that updated value can added in that tag space 
Status compare_tag(EditInfo *e_info);
//function to find the length of the tag 
int find_len(EditInfo *e_info);
//function to copy the updated data to temp file 
void copy_updated_data(EditInfo *e_info, int size, char *data);
//function to copy the updated data number in the temp file 
void copy_updated_data_num(EditInfo *e_info, int size, int len);

#endif
