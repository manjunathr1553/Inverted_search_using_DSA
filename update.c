#include "invert.h"

int update(h_table *hash_table, char *file_name, filelist **filelist_head)
{
    char *extn = strstr(file_name, ".txt"); // Check if file has .txt extension
    if(extn == NULL) { // Validate file extension
        printf(" ** ERROR: %s is not a valid txt file! **❌\n", file_name);
        return FAILURE;
    }
    if(strcmp(extn, ".txt")) { // Ensure correct file extension
        printf("** ERROR: %s is not a valid txt file! **❌\n", file_name);
        return FAILURE;
    }
    FILE *fptr = fopen(file_name, "r"); // Open the file in read mode
    if (!fptr) // Check if file opening failed
    {
        printf("Error: Unable to open file %s\n", file_name);
        return FAILURE;
    }
    char ch1 = fgetc(fptr);
    fseek(fptr, 0, SEEK_END); // Move file pointer to end
    fseek(fptr, -2, SEEK_CUR);
    char ch2 = fgetc(fptr);
    if(ch1 != '#' && ch2 != '#')
    {
        printf("Invalid database file ❌\n");
        fclose(fptr);
        return FAILURE;
    }
    long size = ftell(fptr); // Get file size
    if (size < 2) // Check if file is empty or too small
    {
        printf("Invalid database file ❌\n");
        fclose(fptr);
        return FAILURE;
    }

    rewind(fptr); // Reset file pointer to the beginning
    int index, count;
    char str[100];

    while (fscanf(fptr, "#%d;%[^;];%d;", &index, str, &count) == 3) // Read word index, word, and file count
    {
        main_node *new_mainnode = malloc(sizeof(main_node)); // Allocate memory for a new main node
        if (!new_mainnode) // Check if allocation failed
        {
            printf("ERROR: Memory allocation failed\n");
            fclose(fptr);
            return FAILURE;
        }

        new_mainnode->file_count = count; // Store file count
        strcpy(new_mainnode->word_name, str); // Store word name
        new_mainnode->nextword = NULL; // Initialize nextword pointer
        new_mainnode->sub_link = NULL; // Initialize sub_link pointer

        if (hash_table[index].word_link == NULL) // If hash table index is empty, assign new node
        {
            hash_table[index].word_link = new_mainnode;
        }
        else // If index already contains words, append new node at the end
        {
            main_node *word_temp = hash_table[index].word_link;
            while (word_temp->nextword) // Traverse to the last node
            {
                word_temp = word_temp->nextword;
            }
            word_temp->nextword = new_mainnode; // Link new main node
        }

        sub_node *temp = NULL; // Temporary pointer for sub-nodes
        while (count--) // Loop for the number of file occurrences
        {
            char filename[20];
            int word_count;
            if (fscanf(fptr, "%[^;];%d;", filename, &word_count) != 2) // Read filename and word count
            {
                printf("ERROR: Invalid database format\n");
                fclose(fptr);
                return FAILURE;
            }

            sub_node *new_sub = malloc(sizeof(sub_node)); // Allocate memory for sub-node
            if (!new_sub) // Check if allocation failed
            {
                printf("ERROR: Memory allocation failed❌\n");
                fclose(fptr);
                return FAILURE;
            }

            new_sub->word_count = word_count; // Store word count
            strcpy(new_sub->file_name, filename); // Store filename
            new_sub->sub_file = NULL; // Initialize sub_file pointer

            int status = sl_delete_element(filelist_head, filename); // Remove duplicate file entries
            if (!status)
            {
                printf(">>>> '%s' is already exist in Database no need to add in Database 🔃✅\n",filename);
            }

            if (!new_mainnode->sub_link) // If no sub-node exists, assign first sub-node
            {
                new_mainnode->sub_link = new_sub;
                temp = new_sub;
            }
            else // If sub-nodes exist, append new sub-node
            {
                temp->sub_file = new_sub;
                temp = new_sub;
            }
        }
        fseek(fptr, 2, SEEK_CUR); // Skip separator characters in file
    }

    fclose(fptr); // Close the file
    return SUCCESS; // Return success status
}

int sl_delete_element(filelist **head, char *data)
{
    if (*head == NULL) // Check if the list is empty
    {
        return FAILURE; // Return failure if list is empty
    }

    filelist *temp = *head, *prev = NULL; // Initialize pointers for traversal

    if (strcmp((*head)->filename, data) == 0) // Check if head node contains the data
    {
        *head = (*head)->link; // Move head pointer to next node
        free(temp); // Free memory of removed node
        return SUCCESS; // Return success
    }

    while (temp != NULL) // Traverse the list to find the node
    {
        if (strcmp(temp->filename, data) == 0) // Check if current node contains the data
        {
            prev->link = temp->link; // Bypass the node to be deleted
            free(temp); // Free memory of the deleted node
            return SUCCESS; // Return success
        }
        prev = temp; // Move prev pointer to current node
        temp = temp->link; // Move temp pointer to next node
    }

    return DATA_NOT_FOUND; // Return failure if data not found in list
}
