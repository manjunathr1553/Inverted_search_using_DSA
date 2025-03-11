#include"invert.h" // Include header file

int save_database(h_table *hash_table,char *file_name) {
        char *extn = strstr(file_name, ".txt"); // Check if file has .txt extension
        FILE *fptr;
        char ch;
        if(extn == NULL) { // Validate file extension
            printf(" ** ERROR: %s is not a valid txt file! **❌\n", file_name);
            return FAILURE;
        }
        if(strcmp(extn, ".txt")) { // Ensure correct file extension
            printf("** ERROR: %s is not a valid txt file! **❌\n", file_name);
            return FAILURE;
        }

        fptr=fopen(file_name,"w"); // Open file in write mode
        if (fptr == NULL) { // Check if file opened successfully
            printf("******** Error opening log file! ***********❌\n");
            return FAILURE;
        }
        for (int i = 0; i < 27; i++) // Loop through all indices
        {
        if (hash_table[i].word_link != NULL) // Check if words exist at index
        {
            
            main_node *temp = hash_table[i].word_link; // Get the first word node

            while (temp != NULL) // Traverse word nodes
            {
                fprintf(fptr,"#%d;", i); // Write index
                fprintf(fptr,"%s;%d;", temp->word_name, temp->file_count); // Write word and file count

                // Print all sub-nodes (file occurrences)
                sub_node *sub_temp = temp->sub_link;
                while (sub_temp != NULL) // Traverse sub-nodes
                {
                    fprintf(fptr,"%s;%d;", sub_temp->file_name, sub_temp->word_count); // Write file name and word count
                    sub_temp = sub_temp->sub_file; // Move to next sub-node
                }

                temp = temp->nextword; // Move to next word node
                fprintf(fptr,"%s","#\n"); // Add separator
            }
        }
    }
    fclose(fptr); // Close file
    return SUCCESS; // Return success
}
