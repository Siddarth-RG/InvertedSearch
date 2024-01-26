#include<stdio.h>
#include"inverted.h"

/* Function Definition to DISPLAY DATABASE */
int display_database (HT *hash)
{
    int flag = 0;
    M_NODE *mtemp; 
    S_NODE *stemp;
    
    printf("[INDEX]\t  [word] %12s %14s %13s\n", "filecount", "filename", "wordcount");
    for(int i=0; i<27; i++)								//Loop to Traverse through the HASH TABLE
    {
	if( hash[i].link != NULL)							//Checking the index position in table is NULL OR NOT
	{
	    mtemp = hash[i].link;							//Update mtemp 		
	    
	    while(mtemp)								//Loop to Traverse through MAIN NODE
	    {
		printf("[%-2d]%12s %12d ", i, mtemp -> word, mtemp -> file_count); 	//Printing the details
		stemp = mtemp -> slink;							//Update stemp		
		
		while(stemp)								//Loop to Traverse through SUB NODE
		{
		    printf("%14s %13d ", stemp -> file_name, stemp -> word_count);	//Printing the details
		    stemp = stemp -> link;						//Moving to next sub node
		}
		puts("");
		mtemp = mtemp -> mlink;							//Moving to next main node
	    }
	    flag = 1;
	}
    }
    if( flag == 0 )
	return FAILURE;
    else
	return SUCCESS;
}

