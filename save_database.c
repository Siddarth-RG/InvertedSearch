#include<stdio.h>
#include"inverted.h"

/* Function Definition to SAVE DATABASE */
void save_database (HT *hash, char *file)
{
    FILE *fptr = fopen(file, "w+"); 				//Open the backup file in read mode
    M_NODE *mtemp;						//Declaring temporary pointers 
    S_NODE *stemp;
    
    for(int i=0; i<27; i++)					//Loop to traverse through the HASH TABLE
    {
	if( hash[i].link != NULL)				//Checking the index position in hash table is EMPTY OR NOT
	{
	    mtemp = hash[i].link; 
	    while(mtemp)					//Loop to Traverse through MAIN NODES
	    {
		fprintf(fptr,"#%d; \n", i);			//Prints the main node information to file using fprintf
		fprintf(fptr,"%s; %d; ", mtemp -> word, mtemp -> file_count);
		stemp = mtemp -> slink;		
		while(stemp)					//Loop to Traverse through SUB NODES
		{
		    fprintf(fptr,"%s; %d; ", stemp -> file_name, stemp -> word_count);
		    stemp = stemp -> link;			//Moving to next sub node
		}
		fprintf(fptr,"# \n");
		mtemp = mtemp -> mlink;				//Moving to next main node
	    }
	}
    }
    printf("\nINFO : DATABASE stored in %s SUCCESSFULLY\n", file);
}

