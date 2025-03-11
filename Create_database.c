#include"invert.h" 

void create_hash_table(h_table *hash_table)
{
    for(int i=0;i<27;i++) // Initialize all hash table entries
    {
        hash_table[i].index=i; // Assign index value
        hash_table[i].word_link=NULL; // Set word_link to NULL
    }
    printf("\n>>>>>> Hash table creation Successful ✅✅\n"); // Indicate success
}

int create_database(h_table *hash_table, filelist *filelist_head)
{
    char word[40]=" "; // Buffer to store words from files
    FILE *fptr;
    int index;
    if(filelist_head == NULL) // Check if file list is empty
    {
        return 2;
    }
    while(filelist_head != NULL) // Iterate through each file
    {
        fptr=fopen(filelist_head->filename,"r"); // Open the file for reading
        if (fptr == NULL) { // Check if file opening failed
            printf("\n>>>>>>>>>>> Error opening file: %s ❌\n", filelist_head->filename);
        }       
        while((fscanf(fptr,"%s",word)!= EOF)) // Read words from the file
        {
            // Determine index based on the first character of the word
            if(word[0] >='A' && word[0]<='Z')
            {
                index=word[0] - 'A'; // Convert uppercase letter to index
            } 
            else if(word[0] >='a' && word[0]<='z')
            {
                index=word[0] - 'a'; // Convert lowercase letter to index
            }
            else
            {
                index=26; // Assign index for non-alphabetic words
            }

            if(hash_table[index].word_link == NULL) // If no entry exists at index
            {
                main_node *new_mainnode= malloc(sizeof(main_node)); // Allocate memory for main node
                if(new_mainnode == NULL) // Check if allocation failed
                {
                    printf(".............ERROR IN NODE CREATION...........❌\n");
                    return FAILURE;
                }
                new_mainnode->file_count=1; // Initialize file count
                strcpy(new_mainnode->word_name,word); // Store word
                new_mainnode->nextword=NULL; // Initialize nextword pointer
                
                sub_node *new_sub=malloc(sizeof(sub_node)); // Allocate memory for sub node
                if(new_sub == NULL) // Check if allocation failed
                {
                    printf("................ERROR IN NODE CREATION...........❌\n");
                    return FAILURE;
                }
                new_sub->word_count=1; // Initialize word count
                strcpy(new_sub->file_name,filelist_head->filename); // Store file name
                new_sub->sub_file=NULL; // Initialize sub_file pointer
                new_mainnode->sub_link=new_sub; // Link sub-node to main node
                hash_table[index].word_link=new_mainnode; // Link main node to hash table
            }
            else if(hash_table[index].word_link != NULL) // If entry exists
            {
                main_node *temp = hash_table[index].word_link, *prev=NULL;
                int flag=0, file_present=0;
                while(temp !=NULL) // Traverse main nodes to find a match
                {
                    if(strcmp(temp->word_name,word) == 0) // If word already exists
                    {
                        flag=1;
                        break;
                    }
                    prev=temp;
                    temp = temp->nextword;
                }

                if(flag) // If word exists in the hash table
                {
                    sub_node *file_temp = temp->sub_link, *file_prev=NULL;
                    while(file_temp !=NULL) // Traverse sub nodes (file occurrences)
                    {
                        if(!strcmp(file_temp->file_name,filelist_head->filename)) // If file already exists
                        {
                            file_present=1;
                            break;
                        }
                        file_prev=file_temp;
                        file_temp=file_temp->sub_file;
                    }  
                    
                    if(file_present) // If file already exists, increment word count
                    {
                        file_temp->word_count++;
                    }
                    else // If file does not exist, create a new sub-node
                    {
                        sub_node *new_sub=malloc(sizeof(sub_node)); // Allocate memory for sub node
                        if(new_sub == NULL) // Check if allocation failed
                        {
                            printf("ERROR IN NODE CREATION\n");
                            return FAILURE;
                        }
                        new_sub->word_count=1; // Initialize word count
                        strcpy(new_sub->file_name,filelist_head->filename); // Store file name
                        new_sub->sub_file=NULL; // Initialize sub_file pointer
                        file_prev->sub_file=new_sub; // Link new sub-node
                        temp->file_count++; // Increment file count for main node
                    }
                }
                else // If word does not exist, create a new main node
                {
                    main_node *new_mainnode= malloc(sizeof(main_node)); // Allocate memory for main node
                    if(new_mainnode == NULL) // Check if allocation failed
                    {
                        printf("ERROR IN NODE CREATION\n");
                        return FAILURE;
                    }
                    new_mainnode->file_count=1; // Initialize file count
                    strcpy(new_mainnode->word_name,word); // Store word
                    new_mainnode->nextword=NULL; // Initialize nextword pointer

                    sub_node *new_sub=malloc(sizeof(sub_node)); // Allocate memory for sub node
                    if(new_sub == NULL) // Check if allocation failed
                    {
                        printf("ERROR IN NODE CREATION\n");
                        return FAILURE;
                    }
                    new_sub->word_count=1; // Initialize word count
                    strcpy(new_sub->file_name,filelist_head->filename); // Store file name
                    new_sub->sub_file=NULL; // Initialize sub_file pointer
                    new_mainnode->sub_link=new_sub; // Link sub-node to main node
                    prev->nextword=new_mainnode; // Link main node to previous node
                }
            }
        }
        filelist_head=filelist_head->link; // Move to the next file
    }
    return SUCCESS; // Return success
}
