#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include "info.h"

/*Structure to hold all the variables used during the view operation*/
typedef struct _ViewInfo
{
  //Input File Details
  char *file_name;
  FILE *fptr_input;
  
  //Variables used in View Option
  TagReader tag_name;
  int tag_size;
  char *tag_content;
}ViewInfo;

//function to read and validate all the required files 
Status read_validate(char *argv[], ViewInfo *info);
//function to open all the required files 
Status open_file(ViewInfo *info);
//function to validate the ID version
Status validate_IDversion(ViewInfo *info);
//function to read the tag data and store it in the tag content char pointer 
Status tag_data(TagReader tag_name, int tag_size, FILE* fptr_input);
//function to return the enum value of the tag label found during the read operation
TagReader find_tag (ViewInfo *info);
//function to find the size of the data which the tag content is pointing to 
int find_size(ViewInfo *info);

#endif


