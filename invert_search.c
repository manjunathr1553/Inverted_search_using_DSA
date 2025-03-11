#include "invert.h" // Include header file

void display(h_table *hash_table)
{
    for (int i = 0; i < 27; i++) // Loop through all indices
    {
        if (hash_table[i].word_link != NULL) // Check if words exist at index
        {
            printf("\nIndex [%d]:\n", i);
            main_node *temp = hash_table[i].word_link;

            while (temp != NULL) // Traverse main nodes
            {
                printf("Word: %s (File Count: %d)\n", temp->word_name, temp->file_count);

                sub_node *sub_temp = temp->sub_link; // Pointer to sub-nodes
                while (sub_temp != NULL) // Traverse sub-nodes
                {
                    printf("  - Found in: %s (Word Count: %d)🔍\n", sub_temp->file_name, sub_temp->word_count);
                    sub_temp = sub_temp->sub_file; // Move to next sub-node
                }

                temp = temp->nextword; // Move to next main node
            }
        }
    }
}

int search_word(h_table *hash_table, char *word)
{
    int index;
    if (word[0] >= 'A' && word[0] <= 'Z') // Check for uppercase letters
    {
        index = word[0] - 'A'; // Convert to index
    } 
    else if (word[0] >= 'a' && word[0] <= 'z') // Check for lowercase letters
    {
        index = word[0] - 'a'; // Convert to index
    }
    else // If not a letter, assign to last index
    {
        index = 26;
    }

    if (hash_table[index].word_link != NULL) // Check if words exist at index
    {
        main_node *temp = hash_table[index].word_link;
        while (temp != NULL) // Traverse main nodes
        {
            if (strcmp(temp->word_name, word) == 0) // Compare word
            {
                printf("\n\n>>> Word found in Index [%d]✅:\n", index);
                printf("Word '%s' is present in %d Files \n", temp->word_name, temp->file_count);
                sub_node *sub_temp = temp->sub_link;
                while (sub_temp != NULL) // Traverse sub-nodes
                {
                    printf("  - In %s File Found %d Times\n", sub_temp->file_name, sub_temp->word_count);
                    sub_temp = sub_temp->sub_file; // Move to next sub-node
                }
                return SUCCESS;
            }
            temp = temp->nextword; // Move to next main node
        }  
    }
     // Word not found in table
    return FAILURE;
}
