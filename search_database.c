#include"inverted.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

/* Function Definition for SEARCH DATABASE */
int search_database(HT *hash, char *word)		
{
    int index;
    
    if( word[0] >= 'A' && word[0] <= 'Z')		//Condition to check first letter of the word is UPPER CASE OR LOWER CASE letter
	index = word[0] % 65;				//If it is a UPPER CASE, then perform modulus by 65[A]	
    
    else if( word[0] >= 'a' && word[1] <= 'z')		//To check first letter of the word LOWER CASE OR NOT	  
	index = word[0] % 97;         			//If the letter is LOWER CASE, then perform modulus by 97[a]
    else
	index = 26;					//If in case of other special characters index is 26

    if( hash[index].link != NULL )			//Checking the particular index is EMPTY OR NOT
    {
	M_NODE *mtemp = hash[index].link;		//Declare a temporary pointer to traverse through the node
	
	while(mtemp)					//Loop to Traverse through the nodes
	{
	    if( strcmp(mtemp -> word, word) == 0)	//Condition to check word is matching with database
	    {
		S_NODE *stemp = mtemp -> slink;		//Temporary sub node variable to Traverse through sub nodes
		
		while(stemp)				//Loop to traverse the sub nodes
		{   /* prints the information */
		    printf("\"%s\" word is found in \"%s\" file %d times\n", word, stemp -> file_name, stemp -> word_count);
		    stemp = stemp -> link;		//Travers to next sub node
		}
		return SUCCESS;
	    }
	    mtemp = mtemp -> mlink;			//Travers to next main node
	}
    }
    return FAILURE;
}

