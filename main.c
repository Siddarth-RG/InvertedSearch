#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"inverted.h"

int g_flag = 0, i=0;
Flist *head = NULL;
int main (int argc, char *argv[])
{
    if(argc < 2)
    {
	printf("\nPlease pass valid Arguments\nUSAGE: ./a.out file1.txt file2.txt file3.txt...\n\n");
	return FAILURE;
    }
    
    if( read_and_validate(argv) == SUCCESS)
    {
	printf("\nINFO : Read and Validation is SUCCESSFULL\n");
	int op;
	int count = 1;

	printf("\nSelect your choice among following options : \n");
	while(1)
	{
	    printf("\n1. Create DATABASE\n2. Display DATABASE\n3. Search DATABASE\n4. Update DATABASE\n5. Save DATABASE\n");
	    scanf(" %d", &op);
	    HT hash_table[27];
	    if( count == 1)
	    {
		create_hashtable(hash_table);
		count++;
	    }
	    switch(op)
	    {
		case 1:
		    {
			if(g_flag == 1)
			{
			    printf("\nINFO : The DATABASE is ALREADY CREATED\n");
			}
			else if( create_database(hash_table, head) == SUCCESS )
			{
			    g_flag = 1;
			    printf("\nINFO : DATABASE is CREATED SUCCESSFULLY\n");
			}
			else
			{
			    printf("\nERROR : Creating DATABASE is FAILURE\n");
			    return FAILURE;
			}
		    }
		    break;
		case 2:
		    {
			if( display_database(hash_table) == FAILURE )
			    puts("\nINFO : The DATABASE is EMPTY\n");
		    }
		    break;
		case 3:
		    {
			char word[30];
			printf("\nINFO : Enter the word you want to search : ");
			scanf("%s", word);
			
			if( search_database(hash_table, word) == FAILURE)
			    printf("\"%s\" word not found in DATABASE\n", word);
		    }
		    break;
		case 4:
		    {
			char name[20];
			printf("\nEnter the file name to update data : ");
			scanf(" %s", name);
			if( strstr(name, ".txt") == NULL)
			{
			    printf("\nERROR : %s is not a .txt file, Pass .txt files\n", name);
			}
			else if(check_empty(name) == -1)
			{
			    printf("\nINFO : %s doesn't exist\n", name);
			}
			else if( check_empty(name) == FAILURE)
			    printf("\nINFO : %s file is empty\n", name);
			
			else if( update_database(hash_table, name) == SUCCESS)
			{
			    printf("\n%s file updated to DATABASE SUCCESSFULLY\n", name);
			    g_flag = 1;
			}
			else
			    printf("\nERROR : %s file is not in correct pattern\nfile updation to DATABASE FAILED\n", name);

		    }
		    break;
		case 5:
		    {
			char name[20];
			printf("\nEnter the file name to save database : ");
			scanf(" %s", name);
			if( strchr(name, '.') != NULL)
			{
			    char n[20];
			    while( name[i] != '.')
			    {
				n[i] = name[i];
				i++;
			    }
			    n[i] = '\0';
			    strcpy(name, n);
			}
			strcat(name, ".txt");
			save_database(hash_table, name);
		    }
		    break;
		default:
		    {
			puts("\nINFO : Enter proper choice");
			continue;
		    }
	    }
	    while(1)
	    {
		char opt;
		printf("\nDo you want to continue ? \nEnter y/Y to continue and n/N to discontinue\n\n");
		scanf(" %c", &opt);
		
		if(opt == 'y' || opt == 'Y')
		    break;
		
		else if( opt == 'n' || opt == 'N')
		    return 0;
		
		else
		    puts("\nINFO : Enter proper key");
	    }	
	}
    }
    else
    {
	printf("\nERROR : Read and Validation FAILED\n");
	return 0;
    }
}

/* Function definition for READ AND VALIDATE ARGUMENTS */
int read_and_validate(char *argv[])
{
    int i = 1;
    int R_flag = 0;
    while(argv[i] != NULL)								//Condition to check whether argument passed or not
    {
	if( strstr(argv[i], ".txt") != NULL)						//Condition to check passed file is ".txt" file OR NOT
	{
	    if( check_empty(argv[i]) == SUCCESS)					//Function call to check for file empty
	    {
		if( insert_at_last(argv[i]) == SUCCESS)					//Function call to insert file in linked list
		{
		    printf("\nSuccessfull : Inserting file name : %s into file linked list\n", argv[i]);
		    R_flag = 1;
		}
		else
		{
		    printf("\nFailure : Inserting file name : %s into file linked list\n", argv[i]);
		}
	    }
	    else if(check_empty(argv[i]) == FAILURE )					//If the passed file is EMPTY 
	    {
		printf("\n%s file is empty\n", argv[i]);
	    }
	    else
		printf("\n%s file doesn't exist\n", argv[i]);
	}
	else
	{
	    printf("\n%s is not a .txt file", argv[i]);					//Error message if USER passes non .txt file
	}
	i++;										//Increment the value of i
    }
    if(R_flag == 1)
	return SUCCESS;
    else
	return FAILURE;
}

/* Function Definition to insert file in linked list */
int insert_at_last(char *name)
{
    Flist *new = malloc(sizeof(Flist));				//Creating a NEW NODE
    
    if(new == NULL)						//Condition to check whether the NODE is CREATED OR NOT
	return FAILURE;
    
    strcpy(new -> file_name, name);				//Updating filename to new 		
    new -> link = NULL;						//Updating new link as NULL
    
    if(head == NULL)						//Condition to check whether LIST is EMPTY OR NOT
    {
	head = new;						//Updating head with new
    }
    else
    {
	Flist *temp, *prev;					//Declaring two pointers TEMP AND PREV
	temp = prev = head;					//Initialize both the pointers with heas
	
	while(temp)						//while to go through the LIST
	{
	    if( strcmp(temp -> file_name, name) == 0)		//Comparing the file name(Checking for duplicates)
	    {
		printf("\nDuplicate file found : %s\n", name);	//If duplicate found, print this error message and return FAILURE
		return FAILURE;
	    }
	    prev = temp;					//Update prev to temp
	    temp = temp -> link;				//Travers temp
	}
	prev -> link = new;					//Updating prev link to new
    }
    return SUCCESS;
}

/* Function Definition to check whether files are EMPTY OR NOT */
int check_empty(char *file)
{
    FILE *fptr = fopen(file, "r");				//Using fptr to open the file in read mode
    
    if(fptr == NULL)						//If file does't exist it will return NULL
	return -1;

    fseek(fptr, 0, SEEK_END);					//Using fseek to set file indicator at the end
    
    if( ftell(fptr) < 1)					//If file is empty then it will return -1
    {
	fclose(fptr);						//fclose - to close the file
	return FAILURE;
    }
    fclose(fptr);
    return SUCCESS;
}

/* Function Definition to create hash table */
void create_hashtable(HT *hash)
{
    for(int i=0; i<27; i++)
    {
	hash[i].index = i;					//Updating index values 
	hash[i].link = NULL;					//Updating link to NULL
    }
}

