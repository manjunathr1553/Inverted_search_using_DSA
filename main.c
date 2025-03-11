/*Documentation 
Name : Manjunath R
Date : 04/03/2025
Title: InvertedSearch
Dis :The purpose of storing an index is to optimize speed and performance in
finding relevant documents for a search query. Without an index, the search
engine would scan every document in the corpus, which would require
considerable time and computing power.
Sample input / output : >>📁 The files are: 
-> file1.txt -> file2.txt 
>>>>>> Hash table creation Successful ✅✅

Choose one option:
1. Create Database 🔃
2. Display Database 📒
3. Search Database 🔍
4. Save Database 🔃
5. Update Database 🆙
6. Exit 🔚
Enter your choice: 1

<<<<<<<<<<<<<<<<< Database created successfully >>>>>>>✅

Choose one option:
1. Create Database 🔃
2. Display Database 📒
3. Search Database 🔍
4. Save Database 🔃
5. Update Database 🆙
6. Exit 🔚
Enter your choice: 4

Enter the file name:back.txt

>>>>>> Database successfully saved to back.txt ✅*/
#include<stdio.h> 
#include <stdlib.h> 
#include"invert.h" 
#include<stdio_ext.h> // Extended I/O functions

int main(int argc, char *argv[]) {
    
    int database=0;
    if(argc < 2) { // Check if files are provided
        printf("ERROR: No files!\n");
        return 1;
    }
    filelist *filelist_head = NULL;

    if(validate_args(&filelist_head, argv) == FAILURE) { // Validate input files
        printf("ERROR: No valid files passed!\n");
        database=1;
    }
    print_list(filelist_head); // Print the list of files
    
    h_table hash_table[27]; // Hash table with 27 indices
    create_hash_table(hash_table); // Initialize hash table
    int choice;
    char savefile[20];
    int update_flag=0, create_falg=0; // Flags for database state
   
    do {
        choice = -1; // Reset choice
        printf("\nChoose one option:\n1. Create Database 🔃\n2. Display Database 📒\n3. Search Database 🔍\n4. Save Database 🔃\n5. Update Database 🆙\n6. Exit 🔚\nEnter your choice: ");
        __fpurge(stdin); // Clear input buffer
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                if(database)
                {
                    printf("No valid files are passed🥱\n");
                    break;
                }
                if(create_falg==0) // Check if database is already created
                {
                    if(create_database(hash_table,filelist_head)==SUCCESS)
                    {
                        printf("\n<<<<<<<<<<<<<<<<< Database created successfully >>>>>>>✅\n");
                        create_falg=1;
                    }
                    else if(create_database(hash_table,filelist_head)== 2)
                    {
                        printf("\n....Database created successfull through updating....🥱✅\n");
                        create_falg=1;
                    } 
                    else
                    printf("\n>>>>>>>>>>>>> Database creation unsuccessfully! ❌\n");
                }
                else{
                    printf("\n>>>>>>>> Database already created! 🥱✅\n");
                }
                break;
            case 2:
            if(create_falg==0 && update_flag == 0) // Ensure database exists before displaying
            {
                printf(">>>>>>>>>>>>> Still Database not created to Display❓ <<<<<<<<<<<\n");
                break;
            }
                display(hash_table); // Display database
                break;
            case 3:
            if(create_falg==0 && update_flag == 0) // Ensure database exists before searching
            {
                printf(">>>>>>>>>>>>> Still Database not created to search🔍❓ <<<<<<<<<<<\n");
                break;
            }
                char str[50];
                printf("Enter the data to search 🔍: ");
                scanf("%s", str);
                if(search_word(hash_table,str) == FAILURE)
                    printf("\n....Data not found....❌\n");
                break;
            case 4:
            if(create_falg==0 && update_flag == 0) // Ensure database exists before saving
            {
                printf(">>>>>>>>>>>>> Still Database not created to save ❓<<<<<<<<<<<\n");
                break;
            }
            printf("\nEnter the file name:");
            scanf("%s",savefile);
            if(save_database(hash_table,savefile)==SUCCESS)
            printf("\n>>>>>> Database successfully saved to %s ✅\n",savefile);
                break;
            case 5:
            if(create_falg==0 && update_flag == 0) // Ensure update is possible
            {
                char str2[50];
                printf("Enter the FILE name: ");
                scanf("%s", str2);
                if(update(hash_table,str2,&filelist_head)==SUCCESS)
                {
                    update_flag =1;
                    printf(">>>>>>>> Update Successfull ✅\n");
                }
                else{
                    printf("...................Updation Failed ..........🚫\n");
                }
            }
            else
            {
                printf("...................Updation Not Possible ..........🚫\n");
            }
                break;
            case 6:
                printf(">>>>>>>>>>>>>>> Thank GOD work is over🥱🥱🥱 <<<<<<<<<<<<<\n");
                break;
            default:
                printf("******* Invalid choice! ******* ❌\n");
        }
    } while(choice != 6); // Repeat until user chooses exit
    return 0;
}
