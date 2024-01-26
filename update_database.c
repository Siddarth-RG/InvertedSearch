#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"inverted.h"

/* Function Definition for UPDATE DATABASE */
int update_database(HT *hash, char *file)
{
    char buffer[50];								//Declare a char buffer of 50 bytes
    char *token;								//Declaring a char variable token
    FILE *fptr = fopen(file, "r");						//Open file in READ MODE
    fscanf(fptr, "%s", buffer);							//Reading the data of file by using fscanf
    
    if( buffer[0] != '#')							//Condition to check whether the first character # OR not
	return FAILURE;
    rewind(fptr);

    int index;									//Declare a variable index
    while(1)									//Super loop
    {
	fscanf(fptr, "%s", buffer);						//Read the data from file
	if( buffer[strlen(buffer) -1] != ';')
	    break;

	index = atoi(strtok(buffer, "#;"));					//To get the index

	fscanf(fptr, "%s", buffer);						//Extracts the word
	token = strtok(buffer, ";");						//To get the word

	if( hash[index].link == NULL)
	{
	    M_NODE *mnew = creat_main_node(token);
	    hash[index].link = mnew;

	    fscanf(fptr, "%s", buffer);						//Extracts the file count
	    int file_count = atoi(strtok(buffer, ";"));				//To get the file count
	    mnew -> file_count = file_count;

	    S_NODE *snew, *sprev;						//Declaring two pointers
	    fscanf(fptr, "%s", buffer);						//Extracts the filename
	    token = strtok(buffer, ";");					//To get the file name
	    snew = sprev = creat_sub_node(token);
	    mnew -> slink = snew;

	    fscanf(fptr,"%s",buffer);						//Extracts the word count
	    snew -> word_count = atoi(strtok(buffer, ";"));			//To get the word count

	    for(int i=1; i<file_count; i++)
	    {
		fscanf(fptr, "%s", buffer);					//Extracts the file name
		S_NODE *snew = creat_sub_node(strtok(buffer, ";"));
		fscanf(fptr, "%s", buffer);					//Extracts the word count
		snew -> word_count = atoi(strtok(buffer, ";"));			//To get the word count
		sprev -> link = snew;
		sprev = snew;
	    }
	    sprev -> link = NULL;
	}
	else
	{
	    int flag = 0;
	    M_NODE *mtemp = hash[index].link;					//Declaring two pointers and update
	    M_NODE *mprev = mtemp;
	    while(mtemp)							//Loop to Travers throughout the MAIN NODE
	    {
		if( strcmp(mtemp -> word, token) == 0)			
		{
		    int s_flag = 0;
		    fscanf(fptr, "%s", buffer); 				//Extracts the filecount
		    int f_count = atoi(strtok(buffer, ";"));			//To get the file count
		    for(int i=0; i<f_count; i++)				//Loop runs upto file count times
		    {
			S_NODE *stemp, *sprev;					//Declaring pointers
			stemp = sprev = mtemp -> slink;
			fscanf(fptr, "%s", buffer); 				//Extracts the filename
			char *fname = strtok(buffer, ";");			//To get the file name
			for(int j=0; j<mtemp -> file_count; j++)
			{
			    if( strcmp(stemp -> file_name, fname) == 0)
			    {
				fscanf(fptr, "%s", buffer); 			//To get the wordcount
				s_flag = 1;
				break;
			    }
			    sprev = stemp;
			    stemp = stemp->link;
			}
			if(s_flag == 0)
			{
			    S_NODE *new = creat_sub_node(fname);
			    sprev -> link = new;
			    fscanf(fptr, "%s", buffer); 			//Extracts the wordcount
			    new -> word_count = atoi(strtok(buffer, ";"));	//To get the word count

			    mtemp -> file_count += 1;			
			}	
		    }
		    flag = 1;
		}
		mprev = mtemp;
		mtemp = mtemp->mlink;
	    }
	    if( flag == 0)
	    { 
		M_NODE *mnew = creat_main_node(token);
		mprev->mlink = mnew;

		fscanf(fptr, "%s", buffer);                           		//Extracts the file count
		int file_count = atoi(strtok(buffer, ";"));			//To get the file count
		mnew -> file_count = file_count;

		S_NODE *snew, *sprev;
		fscanf(fptr, "%s", buffer);                           		//Extracts the filename
		token = strtok(buffer, ";");					//File name
		snew = sprev = creat_sub_node(token);
		mnew -> slink = snew;

		fscanf(fptr, "%s", buffer);                           		//Extracts the word count
		snew -> word_count = atoi(strtok(buffer, ";"));			//To get the word count

		for(int i=1; i<file_count; i++)					//Loop runs upto file count times
		{
		    fscanf(fptr, "%s", buffer);                       		//Extracting the file name
		    S_NODE *snew = creat_sub_node(strtok(buffer, ";"));
		    fscanf(fptr, "%s", buffer);                               	//Extracting the word count
		    snew -> word_count = atoi(strtok(buffer, ";"));
		    sprev -> link = snew;
		    sprev = snew;
		}
		sprev -> link = NULL;
	    }
	}
	fscanf(fptr, "%s", buffer);						//Skips the # at the end of line
	if( feof(fptr) )
	    break;
    }
    return SUCCESS;
}
