#ifndef VALIDATE_H
#define VALIDATE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 

#define FILENAMESIZE 20  // Max filename length
#define SUCCESS 0
#define FAILURE -1
#define DATA_NOT_FOUND 1

// Structure for storing valid filenames
typedef struct validFiles 
{
    char filename[FILENAMESIZE];
    struct validFiles *link;  // Pointer to next file node
} filelist;

// Structure for storing word occurrences in a file
typedef struct sub_nodes
{
    int word_count;            // Number of times the word appears
    char file_name[FILENAMESIZE]; // Name of the file
    struct sub_nodes *sub_file; // Pointer to the next file node
} sub_node;

// Structure for storing words in the hash table
typedef struct node
{
    int file_count;         // Number of files containing this word
    char word_name[100];    // Word stored in this node
    struct node *nextword;  // Pointer to the next word node
    sub_node *sub_link;     // Pointer to sub-nodes (file occurrences)
} main_node;

// Structure for the hash table
typedef struct table
{
    int index;           // Hash index
    main_node *word_link; // Pointer to the first word node
} h_table;

// Function declarations
int validate_args(filelist **list_head, char *argv[]);  // Validate command-line arguments

int insert_at_last(filelist **head, char *data);  // Insert file name at the end of the list

void print_list(filelist *head);  // Print all file names in the list

void display(h_table *hash_table);  // Display the hash table contents

int create_database(h_table *hash_table, filelist *filelist_head); // Create the database

void create_hash_table(h_table *hash_table);  // Initialize hash table

int search_word(h_table *hash_table, char *str); // Search for a word in the hash table

int save_database(h_table *hash_table, char *file_name); // Save database to a file

int update(h_table *hash_table, char *file_name, filelist **filelist_head); // Update the database from a file

int sl_delete_element(filelist **head, char *data); // Delete a file from the list

#endif // VALIDATE_H
