#include"inverted.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Function Definition to create database */
int create_database(HT *hash, Flist *f_list)
{
    FILE *fptr;						//Declaring a file pointer
    char buffer[50];					//Declaring a char buffer of size 50 bytes
    int index, i;					//Declaring variables index and i
    
    while(f_list)
    {
	fptr = fopen(f_list -> file_name, "r");		//Opening the files in read mode
	while(1)					//Super loop
	{
	    fscanf(fptr, " %s", buffer);		//Reading the words from file using fscanf
	    if(feof(fptr))				//If file pointer reaches End of file
		break;

	    char ch = buffer[0];			//Declaring a char variable ch to and storing the first character in it
	    
	    if( ch >= 'A' && ch <= 'Z')			//Condition for UPPER CASE
		index = ch % 65;			//If a character is UPPER CASE perform modulus by 65
	    
	    else if( ch >= 'a' && ch <= 'z')		//Condition for LOWER CASE
		index = ch % 97;			//If a character is LOWER CASE perform modulus by 97
	    
	    else
		index = 26;				//Index for SPECIAL CHARACTERS

	    if(hash[index].link == NULL)				//Condition to check hash link is NULL OR NOT
	    {
		M_NODE *mnew = creat_main_node(buffer);			//Function call to create a main node
		hash[index].link = mnew;				//Update hash link to main

		S_NODE *snew = creat_sub_node(f_list -> file_name);	//Function call to create a sub node
		mnew -> slink = snew;					//Update main sub node link to sub node
	    }
	    else
	    {
		M_NODE *mtemp, *mprev;					//Declaring two pointers MTEMP AND MPREV
		mtemp = mprev = hash[index].link;			
		int m_flag = 0;
		while(mtemp)						//Travers through main node
		{
		    if( strcmp(mtemp -> word, buffer) == 0)		//Condition to check for same words
		    {
			int s_flag = 0;
			S_NODE *stemp, *sprev;
			stemp = sprev =  mtemp -> slink;		//Updating mtemp pointer to sub node
			
			while(stemp)							//Travers through sub node
			{
			    if( strcmp(stemp -> file_name, f_list -> file_name) == 0)	//Comparing the file name with new file name to be inserted
			    {
				stemp -> word_count += 1;				//Condition is TRUE then increment the word_count
				s_flag = 1;						//Set flag to 1
				break;
			    }
			    sprev = stemp;						//If condition is FALSE then Travers sprev and stemp
			    stemp = stemp -> link;
			}
			if( s_flag == 0)
			{
			    S_NODE *new = creat_sub_node(f_list -> file_name);		//Function call to create a SUB NODE
			    sprev -> link = new;					
			    mtemp -> file_count += 1;					//Increment the file count
			}
			m_flag = 1;							//set main flag to 1
			break;
		    }
		    mprev = mtemp;							//Traversing the pointers
		    mtemp = mtemp -> mlink;
		}
		if( m_flag == 0)
		{
		    M_NODE *mnew = creat_main_node(buffer);
		    mprev -> mlink = mnew;

		    S_NODE *snew = creat_sub_node(f_list->file_name);
		    mnew -> slink = snew;
		}
	    }
	}
	f_list = f_list -> link;
    }
    return SUCCESS;
}
/* Function Definition to CREATE MAIN NODE */
M_NODE* creat_main_node(char *word)
{
    M_NODE *new = malloc(sizeof(M_NODE)); 			//Creating a NEW NODE
    
    if(new == NULL)						//Condition to check whether NODE is CREATED OR NOT
	return FAILURE;
    
    new -> mlink = NULL;					//Update main link to NULL
    new -> file_count = 1;					//file count to 1
    strcpy(new -> word, word);					//Update word in new word part
    return new;							//return the NEW
}

/* Function Definition to CREATE SUB NODE */
S_NODE* creat_sub_node(char *name)
{
    S_NODE *new = malloc(sizeof(S_NODE));			//Creating a NEW NODE
    
    if(new == NULL)						//Condition to check NODE is CREATED OR NOT
	return FAILURE;
    
    new -> link = NULL;						//Update link part to NULL
    new -> word_count = 1;					//Set word count
    strcpy(new -> file_name, name);				//Update filename
    return new;	
}	

