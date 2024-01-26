#ifndef INVERTED_H
#define INVERTED_H

#define SUCCESS 1
#define FAILURE 0

/* Structure to store the file names */
typedef struct node
{
    char file_name[30];
    struct node *link;
}Flist;

/* Structure for sub node */
typedef struct sub_node
{
    int word_count;
    char file_name[30];
    struct sub_node *link;
}S_NODE;

/* Structure of main node */
typedef struct main_node
{
    int file_count;
    char word[30];
    struct main_node *mlink;
    struct sub_node *slink;
}M_NODE;

/* Structure for hash table */
typedef struct hash
{
    int index;
    struct main_node *link;
}HT;

/* Function prototype for creating an HASH TABLE */
void create_hashtable(HT *);

/* Function prototype for READ AND VALIDATE the ARGUMENTS */
int read_and_validate(char *[]);

/* Function prototype to insert file in linked list */
int insert_at_last(char *);

/* Function prototype to check whether the file is EMPTY OR NOT */
int check_empty(char *file);

/* Function prototype for creating database */
int create_database(HT *, Flist *);

/* Function prototype for creating MAIN AND SUB NODES */
M_NODE * creat_main_node(char *);
S_NODE * creat_sub_node(char *);

/* Function prototype to display database */
int display_database(HT *);

/* Function prototype to search database */
int search_database(HT *, char *);

/* Function prototype to save database */
void save_database(HT *, char *);

/* Function prototype to update database */
int update_database(HT *, char *);


#endif
