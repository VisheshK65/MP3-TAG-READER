/*
Name          : VISHESH K
Date          : 20-10-2022
Documentation : MP3 TAG READER
Sample Input  :
1] a] ./a.out 
   b] ./a.out --help
2] View Option
   a] ./a.out -v sample.mp3
   b] ./a.out -v sample.txt
3] Edit Option
   a] ./a.out -e -t Dynamite sample.mp3
   b] ./a.out -e -a Arijit Singh sample.txt
Sample Output :
1] 
a]
-----------------------------------------------------

ERROR : ./a.out : INVALID ARGUMENTS
USAGE :
To view please pass like : ./a.out -v mp3filename
To edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename
TO get help pass like : ./a.out --help
-----------------------------------------------------

b] 
----------------------------------------------------

USAGE :
To view please pass like : ./a.out -v mp3filename
To edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename
----------------------------------------------------

2] 
a]
!! Provided a wrong input file !!
Please provide a .mp3 file
Example : sample.mp3
b]
-------------------------SELECTED VIEW DETAILS-------------------------


-----------------------------------------------------------------------
                 MP3 TAG READER AND EDITOR FOR IDV3
-----------------------------------------------------------------------
TITLE          :        Sunny Sunny - Yo Yo Honey Singh - [SongsPk.CC]
ARTIST         :        Yo Yo Honey Singh - [SongsPk.CC]
ALBUM          :        Yaariyan
YEAR           :        2013
CONTENT        :        Bollywood Music - [SongsPk.CC]
COMMENT        :        eng
-----------------------------------------------------------------------

3]
a]
!! Provided a wrong input file !!
Please provide a .mp3 file
Example : sample.mp3

b]
!! Successfully edited the data !!
-------------------------SELECTED VIEW DETAILS-------------------------


-----------------------------------------------------------------------
                 MP3 TAG READER AND EDITOR FOR IDV3
-----------------------------------------------------------------------
TITLE          :        Dynamite
ARTIST         :        Yo Yo Honey Singh - [SongsPk.CC]
ALBUM          :        Yaariyan
YEAR           :        2013
CONTENT        :        Bollywood Music - [SongsPk.CC]
COMMENT        :        eng
-----------------------------------------------------------------------


*/

#include <stdio.h>
#include <string.h>
#include "info.h"
#include "view.h"
#include "edit.h"

int main(int argc, char *argv[])
{
	ViewInfo info;                            //Create a variable of type ViewInfo structure present in view.h
	EditInfo e_info;                          //Create a variable of type EditInfo structure present in edit.h 
	if(argc < 2)                              //If the no of command line arguements is < 2 then print the error message 
	{
		printf("-----------------------------------------------------\n");
		printf("\n");
		printf("ERROR : ./a.out : INVALID ARGUMENTS\n");
		printf("USAGE :\n");
		printf("To view please pass like : ./a.out -v mp3filename\n");
		printf("To edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
		printf("TO get help pass like : ./a.out --help\n");
		printf("-----------------------------------------------------\n");
	}
	else
	{
		if(check_operation(argv) == m_help)   //if the operation to be performed is help then run the below loop           
		{
			printf("----------------------------------------------------\n");
			printf("\n");
			printf("USAGE :\n");
			printf("To view please pass like : ./a.out -v mp3filename\n");
			printf("To edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
			printf("----------------------------------------------------\n");
		}
		else if(check_operation(argv) == m_view) 		//if the operation to be performed is view then run the below loop
		{
            if(read_validate(argv, &info) == m_success) //read and validate all the command line argument inputs
			{
				if(open_file(&info) == m_success) 	//run the function to open all the required files and print error message if file doesn't open
				{
					if(validate_IDversion(&info) == m_success) //validate 1st 3 bytes. If file is ID3 version then run the below loop
					{
						printf("-------------------------SELECTED VIEW DETAILS-------------------------\n");
						puts("\n");
						printf("-----------------------------------------------------------------------\n");
						printf("                 MP3 TAG READER AND EDITOR FOR IDV3                    \n");
						printf("-----------------------------------------------------------------------\n");
			            int run = 6;                		  //run the loop 6 times, to get the details of all the tags   
			            fseek(info.fptr_input,10,SEEK_SET);   //make the pointer point to 10th byte
                        while(run != 0)
						{
							info.tag_name = find_tag(&info);  //get the tag_id enum value  
							info.tag_size = find_size(&info); //get the size of the content which the tag represents 
							fseek(info.fptr_input,3,SEEK_CUR);//skip the 3 flag data  
						    if(tag_data(info.tag_name, info.tag_size, info.fptr_input) == m_success) //call the function print the data 
							{
						    	run--;                        //reduce the count variable 
							}
							else
								return m_failure;
						}
						printf("-----------------------------------------------------------------------\n");
						return m_success;
					}
					else
						return m_failure;
				}
				else
					return m_failure;
			}
			else
				return m_failure;

            return m_success;
		}
		else if(check_operation(argv) == m_edit)             	//if -e is selected then run the edit loop
		{
            if(read_validate_edit(argv, &e_info) == m_success) 	//validate the required files 
			{
              if(open_edit_file(&e_info) == m_success)       	//open all the required files and if not present then print the error message 
			  {
			  	 char buffer[4];
			  	 fseek(e_info.fptr_input,0,SEEK_SET);           //set the file pointer to 0th byte 
			  	 fread(buffer, 1, 3, e_info.fptr_input);        //read 3 bytes 0th byte and store it in the buffer 
			  	 buffer[3] = '\0';
			  	 if(strcmp(buffer,"ID3") == 0)                  //compare the buffer stored value with ID3, if same then run below loop 
				 {
				 	  fwrite(buffer, 1, 3, e_info.temp_file);   //write the data into the temp file 
				 	  copy_data(&e_info, 7);                    //write 7 bytes into temp file  
                      e_info.tag_name = findtag(argv);          //find the tag enum value 
                      if(e_info.tag_name != e_unsupport)     
					  {
                        find_tag_name(&e_info);                 //store the tag name in the tag variable 
                        int run = 6;
                        while(run != 0)                         //run the loop for 6 times 
						{
							if(compare_tag(&e_info) == m_success) /*compare function to compare if the current tag obatined matches with the one
																	provided by the user*/
							{
                                copy_updated_data(&e_info, 4, e_info.tag); //copy the tag in the temp file 
								e_info.old_tag_size = old_size(&e_info);   //find the old size stroed associated with that tag 
                                e_info.tag_size = strlen(argv[3]);         //find the length of the data that is to be appended in the temp file  
                                e_info.tag_size += 1;
                                copy_updated_data_num(&e_info,4, e_info.tag_size); //copy the updated num value in the temp file 
                                copy_data(&e_info, 3);                     //copy flag data in temp file        
                                updated_data(&e_info, argv);               //store the updated data to a char pointer 
                                e_info.tag_size -= 1;           
                                copy_updated_data(&e_info, e_info.tag_size, e_info.tag_content); //store the updated data in the temp file 
								fseek(e_info.fptr_input, (e_info.old_tag_size -1), SEEK_CUR); 
							}
							else
							{
								fseek(e_info.fptr_input, -4, SEEK_CUR);    //set the pointer to 4 bytes backward to read the data  
								copy_data(&e_info, 4);                     //copy the tag name 
								e_info.tag_size = find_len(&e_info);       //find the length associated with the tag 
								copy_data(&e_info, 3);                     //skip the flag bytes 
								copy_data(&e_info, e_info.tag_size - 1);   //copy the tag content to the temp file 
							}
							run--;                 
						}					
						printf("!! Successfully edited the data !!\n");
						char ch;
						while(fread(&ch,1,1,e_info.fptr_input) > 0)         //run the loop to copy the remaining data to temp file 
						{
							fwrite(&ch,1,1,e_info.temp_file);
						}
                        fclose(e_info.fptr_input);

                        e_info.fptr_input = fopen(e_info.file_name,"w+");   /*close the original mp3 file and open again in w+ mode to add the
                        													  updated content*/
                        char ch1;
                        fseek(e_info.temp_file, 0, SEEK_SET);
                        while(fread(&ch1, 1, 1, e_info.temp_file) > 0)      //run the loop to copy the conten from temp to original mp3 file    
						{
							fwrite(&ch1, 1, 1, e_info.fptr_input);
						}
                        return m_success;
					  }
					  else
					  {
					  	  printf("!!  Enter a valid tag option : -t/-a/-A/-y/-c/-g !!\n");
					  	  return m_failure;
					  }
				 }
				 else
				  	  return m_failure;
			  }
			  else
			  	  return m_failure;
			}
			else
				return m_failure;
		  
		  return m_success; 
		}
		else
		{
			printf("!!  ERROR : Enter a valid operation command : --help / -v / -e  !!\n"); //print the message if wrong operation is selected 
			return m_success;
		}
	}

	return 0;
}

OperationType check_operation(char *argv[])  //function to find which operation is been selected by the user 
{
	if(strcmp(argv[1],"--help") == 0)
	{
		return m_help;
	}
	else if(strcmp(argv[1],"-v") == 0)
	{
		return m_view;
	}
	else if(strcmp(argv[1],"-e") == 0)
	{
		return m_edit;
	}
	else
	{
		return m_unsupport;
	}
}
