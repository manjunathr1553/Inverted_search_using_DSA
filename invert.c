#include"invert.h"

int validate_args(filelist **list_head, char *argv[]) {
    int index = 1, nofiles = 1;
    // Iterate through all command-line arguments (file names)
    while(argv[index] != NULL) {
        int duplicate;
        // Check if the file has a valid .txt extension
        char *extn = strstr(argv[index], ".txt");
        FILE *fptr;
        char ch;
        filelist *temp = *list_head;
        if(extn == NULL) { // Validate extension presence
            printf("ERROR: %s is not a valid txt file!❌\n", argv[index]);
            index++;
            continue;
        }
        if(strcmp(extn, ".txt")) { // Ensure correct file extension
            printf("ERROR: %s is not a valid txt file!❌\n", argv[index]);
            index++;
            continue;
        }

        // Check if the file exists
        fptr = fopen(argv[index], "r");
        if(fptr == NULL) { // File does not exist
            printf("ERROR: %s does not exist!❌\n", argv[index]);
            index++;
            continue;
        }

        // Check if the file is empty
        if((ch = fgetc(fptr)) == EOF) { // Empty file check
            printf("ERROR: %s is an empty file!❌\n", argv[index]);
            index++;
            continue;
        }

        fclose(fptr); // Close the file after checking

        // Check if the file is already in the list
        duplicate = 0;
        while(temp != NULL) { // Iterate through the file list
            if(!strcmp(argv[index], temp->filename)) { // Compare file names
                duplicate = 1;
                break;
            }
            temp = temp -> link;
        }

        if(duplicate) { // Skip if file is already present
            printf("ERROR: %s is already given!\n", argv[index]);
            index++;
            continue;
        }

        // Add the file to the list
        nofiles = 0;
        insert_at_last(list_head, argv[index]); // Insert file into list
        index++;
    }

    // Return failure if no valid files were found
    if(nofiles)
        return FAILURE;

    return SUCCESS;
}

int insert_at_last(filelist **head, char *data) {
    // Create a new node
    filelist *new_node = malloc(sizeof(filelist));
    // Validate memory allocation
    if(new_node == NULL)
        return FAILURE;
    // Copy file name into node and initialize link
    strcpy(new_node->filename, data);
    new_node -> link = NULL;
    
    // Check if the list is empty
    if(*head == NULL) {
        *head = new_node; // Set new node as the head
        return SUCCESS;
    }
    else {
        // Traverse to the last node
        filelist *temp = *head;
        while(temp -> link != NULL) {
            temp = temp -> link;
        }
        // Append new node at the end
        temp -> link = new_node;
        return SUCCESS;
    }
}

void print_list(filelist *head) {
    // Check if the list is empty
    if (head == NULL) {
        printf("..........There are zero files to create database........0️⃣\n");
    }
    else {
        printf("\n >>📁 The files are: \n");
        // Traverse and print all file names
        while (head) {		
            printf("-> %s ", head -> filename);
            head = head -> link;
        }
    }
}
