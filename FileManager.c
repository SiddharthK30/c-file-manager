#include <stdio.h>
#include <string.h>

//instantiate global variables filename, new filename, and file data
char filename[60];
char newFilename[60];
char fileData[1000];

//check if file exists and return boolean
int checkFilename(char *filename, int type) {

    //instantiate result
    int result = 0;
    
    //try to open file
    FILE *file = fopen(filename, "r");

    //check that filename is not restricted
    if (strcmp("temp.txt", filename) == 0 || strcmp("change_log.txt", filename) == 0 || strcmp("FileManager.c", filename) == 0) {
        //display error since filename is restricted
        printf("%s cannot be accessed or modified\n", filename);

    //check filename to prevent overwriting existing file
    } else if (type == 1 && file != NULL) {
        //display error since file already exists
        printf("%s already exists\n", filename);

    //check filename to confirm that file exists
    } else if (type == 2 && file == NULL) {
        //display error since file does not exist
        printf("%s does not exist\n", filename);

    //if file exists then return true
    } else {
        result = 1;
    }

    //close file
    fclose(file);

    //return true or false
    return result;
}

//update changelog with latest operation
void updateChangelog (int type, char *filename, char *newFilename, char *text, int num) {
    
    //open changelog file to append latest update
    FILE *file = fopen("change_log.txt", "a");

    //instantiate line
    char line[500] = "";
    
    switch (type) {

        //create file
        case 1:
            //generate line
            sprintf(line, "Created %s\n", filename);
            //append line
            fprintf(file, line);
            break;

        //copy file
        case 2:
            //generate line
            sprintf(line, "Copied %s to %s", filename, newFilename);
            //append line
            fprintf(file, line);
            break;

        //delete file
        case 3:
            //generate line
            sprintf(line, "Deleted %s\n", filename);
            //append line
            fprintf(file, line);
            break;

        //show file
        case 4:
            //generate line
            sprintf(line, "Showed %s\n", filename);
            //append line
            fprintf(file, line);
            break;

        //rename file
        case 5:
            //generate line
            sprintf(line, "Renamed %s to %s\n", filename, newFilename);
            //append line
            fprintf(file, line);
            break;

        //append line
        case 6:
            //generate line
            sprintf(line, "Appended %s to %s\n", text, filename);
            //append line
            fprintf(file, line);
            break;

        //delete line
        case 7:
            //generate line
            sprintf(line, "Deleted line number %d from %s\n", num, filename);
            //append line
            fprintf(file, line);
            break;

        //insert line
        case 8:
            //generate line
            sprintf(line, "Inserted \"%s\" at line number %d into %s\n", text, num, filename);
            //append line
            fprintf(file, line);
            break;

        //show line
        case 9:
            //generate line
            sprintf(line, "Showed line number %d from %s\n", num, filename);
            //append line
            fprintf(file, line);
            break;

        //show changelog
        case 10:
            //generate line
            sprintf(line, "Showed changelog\n");
            //append line
            fprintf(file, line);
            break;
        
        //show number of lines
        case 11:
            //generate line
            sprintf(line, "Showed number of lines in %s\n", filename);
            //append line
            fprintf(file, line);
            break;

        //find line
        case 12:
            //generate line
            sprintf(line, "Searched for \"%s\" in %s\n", text, filename);
            //append line
            fprintf(file, line);
            break;
    }

    //close file
    fclose(file);
}

//create new file
void createFile() {
    printf("create file\n");
    //get filename userinput
    printf("Enter the name of the file: ");
    fgets(filename, sizeof(filename), stdin);
    printf("\n");
    
    //remove new line character from filename by setting it to null terminator
    filename[strcspn(filename, "\n")] = 0;

    //check filename to prevent overwriting existing file
    if (checkFilename(filename, 1) == 1) {
        //create and close file
        FILE *file = fopen(filename, "w");
        fclose(file);

        //update changelog
        updateChangelog(1, filename, "", "", 0);
    }
}

//copy existing file to new file
void copyFile() {
    printf("copy file\n");
    //get filename userinput
    printf("Enter the name of the file to copy: ");
    fgets(filename, sizeof(filename), stdin);
    printf("\n");
    
    //remove new line character from filename by setting it to null terminator
    filename[strcspn(filename, "\n")] = 0;

    //check filename to confirm that file exists
    if (checkFilename(filename, 2) == 1) {
        //get new filename userinput
        printf("Enter the name of the file to copy to: ");
        fgets(newFilename, sizeof(newFilename), stdin);
        printf("\n");

        //remove new line character from filename by setting it to null terminator
        newFilename[strcspn(newFilename, "\n")] = 0;

        //check filename to prevent overwriting existing file
        if (checkFilename(newFilename, 1) == 1) {
            //open old file
            FILE *file = fopen(filename, "r");

            //create new file
            FILE *newFile = fopen(newFilename, "a");

            //loop through each line in file
            while (fgets(fileData, sizeof(fileData), file)) {
                //append each line to new file
                fprintf(newFile, fileData);
                printf("DATA: %s", fileData);
            }

            //close files
            fclose(file);
            fclose(newFile);

            //display success message
            printf("%s copied to %s", filename, newFilename);

            //update changelog
            updateChangelog(2, filename, newFilename, "", 0);        
        }
    }
}

//delete file
void deleteFile() {
    printf("delete file\n");
    //get filename userinput
    printf("Enter the name of the file: ");
    fgets(filename, sizeof(filename), stdin);
    printf("\n");
    
    //remove new line character from filename by setting it to null terminator
    filename[strcspn(filename, "\n")] = 0;

    //check that filename is not restricted
    if (checkFilename(filename, 0) == 1) {
        //check if file succesfully deletes
        if (remove(filename) == 0) {
            //display success message
            printf("%s successfully deleted\n", filename);
            
            //update changelog
            updateChangelog(3, filename, "", "", 0);
            
        } else {
            //display error message
            printf("There was an error with deleting the %s\n", filename);
        }                       
    }
}

//display file contents
void showFile() {
    printf("show file\n");
    //get filename userinput
    printf("Enter the name of the file: ");
    fgets(filename, sizeof(filename), stdin);
    printf("\n");
    
    //remove new line character from filename by setting it to null terminator
    filename[strcspn(filename, "\n")] = 0;

    //check filename to confirm that file exists
    if (checkFilename(filename, 2) == 1) {
        //open file
        FILE *file = fopen(filename, "r");

        //loop through each line in file
        while (fgets(fileData, sizeof(fileData), file)) {
            //display each line in file
            printf("%s", fileData);
        }

        printf("\n");

        //close file
        fclose(file);

        //display success message
        printf("Successfully showed %s\n", filename);

        //update changelog
        updateChangelog(4, filename, "", "", 0);
    }
}

//rename file
void renameFile() {
    printf("delete file\n");
    //get filename userinput
    printf("Enter the name of the file: ");
    fgets(filename, sizeof(filename), stdin);
    printf("\n");
    
    //remove new line character from filename by setting it to null terminator
    filename[strcspn(filename, "\n")] = 0;

    //check filename to confirm that file exists
    if (checkFilename(filename, 2) == 1) {

        //get new filename userinput
        printf("Enter the name of the file to copy to: ");
        fgets(newFilename, sizeof(newFilename), stdin);
        printf("\n");

        //check filename to prevent overwriting existing file
        if (checkFilename(newFilename, 1) == 1) {
            //check if file succesfully deletes
            if (rename(filename, newFilename) == 0) {
                //display success message
                printf("%s renamed to %s\n", filename, newFilename);
                
                //update changelog
                updateChangelog(5, filename, newFilename, "", 0);
                
            } else {
                //display error message
                printf("There was an error with renaming %s to %s\n", filename, newFilename);
            }
        }
    }
}

//append line to file
void appendLine() {
    printf("append line\n");
    //get filename userinput
    printf("Enter the name of the file: ");
    fgets(filename, sizeof(filename), stdin);
    printf("\n");
    
    //remove new line character from filename by setting it to null terminator
    filename[strcspn(filename, "\n")] = 0;

    //check filename to confirm that file exists
    if (checkFilename(filename, 2) == 1) {
        //open file to append
        FILE *file = fopen(filename, "a");

        //instantiate text
        char text[100];
        
        //get text userinput
        printf("Enter text to append to the file: ");
        fgets(text, sizeof(text), stdin);
        printf("\n");

        //append text to the file
        fprintf(file, text);

        //close file
        fclose(file);

        //remove new line character from text by setting it to null terminator
        filename[strcspn(filename, "\n")] = 0;

        //display success message
        printf("Successfully appended line\n");

        //update changelog
        updateChangelog(6, filename, "", text, 0);
    }
}

//delete line from file
void deleteLine() {
    printf("delete line\n");
    //get filename userinput
    printf("Enter the name of the file: ");
    fgets(filename, sizeof(filename), stdin);
    
    //remove new line character from filename by setting it to null terminator
    filename[strcspn(filename, "\n")] = 0;

    //check filename to confirm that file exists
    if (checkFilename(filename, 2) == 1) {
        //open file
        FILE *file = fopen(filename, "r");

        //instantiate length
        int length = 0;

        //loop through each line in file to find number of lines
        while (fgets(fileData, sizeof(fileData), file)) {
            //increment length
            length++;
        }

        printf("\n");

        //get line number
        int num;
        printf("Enter the line number to delete: ");
        scanf("%d", &num);
        printf("\n");

        //clear temporary file
        FILE *tempFile = fopen("temp.txt", "w");

        //open temporary file to copy file to
        tempFile = fopen("temp.txt", "a");

        //open file
        file = fopen(filename, "r");

        //loop through each line in file
        while (fgets(fileData, sizeof(fileData), file)) {
            //append each line to temporary file
            fprintf(tempFile, fileData);
        }

        //initialise line number
        int lineNum = 1;

        //close temporary file in order for the updated version to be accessed
        fclose(tempFile);
        
        //open temporary file
        tempFile = fopen("temp.txt", "r");

        //clear file and open file to append
        file = fopen(filename, "w");
        file = fopen(filename, "a");
        
        //loop through each line in temporary file
        while (fgets(fileData, sizeof(fileData), tempFile)) {
            //check that current line number and line to remove are not equal
            if (lineNum != num) {
                //append each line from temporary file to file
                fprintf(file, fileData);

                //update changelog
                updateChangelog(7, filename, "", "", num);
            }
            //increment current line number
            lineNum++;
        }

        //close files
        fclose(file);
        fclose(tempFile);
    }
}

//insert line into file
void insertLine() {
    printf("insert line\n");
    //get filename userinput
    printf("Enter the name of the file: ");
    fgets(filename, sizeof(filename), stdin);
    
    //remove new line character from filename by setting it to null terminator
    filename[strcspn(filename, "\n")] = 0;

    //check filename to confirm that file exists
    if (checkFilename(filename, 2) == 1) {
        //open file
        FILE *file = fopen(filename, "r");

        //instantiate text and length
        char text[100];
        int length = 0;

        //get text userinput
        printf("Enter text to insert into the file: ");
        fgets(text, sizeof(text), stdin);

        //loop through each line in file to find number of lines
        while (fgets(fileData, sizeof(fileData), file)) {
            //increment length
            length++;
        }

        printf("\n");

        //get line number
        int num;
        printf("Enter the line number to insert text at: ");
        scanf("%d", &num);

        //check if line number is less than 1 or greater than the 1 more than the number of lines in the file
        if (num < 1 || num > length + 1) {
            //line number outside valid range
            printf("Invalid line number\n");
            //close file
            fclose(file);
            return;
        }

        //clear temporary file
        FILE *tempFile = fopen("temp.txt", "w");

        //open temporary file to copy file to
        tempFile = fopen("temp.txt", "a");

        //open file
        file = fopen(filename, "r");

        //loop through each line in file
        while (fgets(fileData, sizeof(fileData), file)) {
            //append each line to temporary file
            fprintf(tempFile, fileData);
        }

        //initialise line number
        int lineNum = 1;

        //close temporary file in order for the updated version to be accessed and open temporary file
        fclose(tempFile);
        tempFile = fopen("temp.txt", "r");

        //clear file and open file to append
        file = fopen(filename, "w");
        file = fopen(filename, "a");
        
        //special case where length = 0 and num = 1
        if (length == 0 && num == 1) {
            fprintf(file, text);
        } else {                         
            //loop through each line in temporary file
            while (fgets(fileData, sizeof(fileData), tempFile)) {
                //append each line from temporary to file
                fprintf(file, fileData);
                //increment current line number
                lineNum++;
                //check that current line number and line to insert text at are equal
                if (lineNum == num) {
                    //append text to the file
                    fprintf(file, text);
                }
            }
        }

        //close files
        fclose(file);
        fclose(tempFile);

        //update changelog
        updateChangelog(8, filename, "", "", num);
    }
}

//show specified line in file
void showLine() {
    printf("show line\n");
    //get filename userinput
    printf("Enter the name of the file: ");
    fgets(filename, sizeof(filename), stdin);
    
    //remove new line character from filename by setting it to null terminator
    filename[strcspn(filename, "\n")] = 0;

    //check filename to confirm that file exists
    if (checkFilename(filename, 2) == 1) {
        //open file
        FILE *file = fopen(filename, "r");

        //instantiate length
        int length = 0;

        //loop through each line in file to find number of lines
        while (fgets(fileData, sizeof(fileData), file)) {
            //increment length
            length++;
        }

        printf("\n");

        //get line number
        int num;
        printf("Enter the line number to show: ");
        scanf("%d", &num);
        printf("\n");

        //check if line number is less than 1 or greater than the 1 more than the number of lines in the file
        if (num < 1 || num > length + 1) {
            //line number outside valid range
            printf("Invalid line number\n");
            //close file
            fclose(file);
            return;
        }

        //open file
        file = fopen(filename, "r");

        //initialise line number
        int lineNum = 1;

        //loop through each line in file
        while (fgets(fileData, sizeof(fileData), file)) {
            //check that current line number and line to show are equal
            if (lineNum == num) {
                //display line
                printf("Text at line %d: %s\n", num, fileData);
                
                //update changelog
                updateChangelog(9, filename, "", "", num + 1);
                
                break;
            }
            //increment current line number
            lineNum++;
        }

        //close file
        fclose(file);
    }
}

//display changelog contents
void showChangelog() {
    printf("show changelog\n");
    //update changelog
    updateChangelog(10, "", "", "", 0);

    //open file
    FILE *file = fopen("change_log.txt", "r");
    
    //loop through each line in changelog
    while (fgets(fileData, sizeof(fileData), file)) {
        //display line of changelog
        printf("%s", fileData);
    }

    //close file
    fclose(file);
}

//show number of lines
void showNoLines() {
    printf("show line\n");
    //get filename userinput
    printf("Enter the name of the file: ");
    fgets(filename, sizeof(filename), stdin);
    
    //remove new line character from filename by setting it to null terminator
    filename[strcspn(filename, "\n")] = 0;

    //check filename to confirm that file exists
    if (checkFilename(filename, 2) == 1) {
        //open file
        FILE *file = fopen(filename, "r");

        //instantiate length
        int length = 0;

        //loop through each line in file to find number of lines
        while (fgets(fileData, sizeof(fileData), file)) {
            //increment length
            length++;
        }

        //display number of lines in file
        printf("\n%s has %d lines\n", filename, length);

        //close file
        fclose(file);
        
        //update changelog
        updateChangelog(11, filename, "", "", 0);
    }
}

//search each line for text
void findLine() {
    printf("search line\n");
    //get filename userinput
    printf("Enter the name of the file: ");
    fgets(filename, sizeof(filename), stdin);
    
    //remove new line character from filename by setting it to null terminator
    filename[strcspn(filename, "\n")] = 0;

    //check filename to confirm that file exists
    if (checkFilename(filename, 2) == 1) {
        //open file
        FILE *file = fopen(filename, "r");

        //instantiate text and length
        char text[100];
        int length = 0;

        //get text userinput
        printf("Enter text to search for: ");
        fgets(text, sizeof(text), stdin);

        //remove new line character from text by setting it to null terminator
        text[strcspn(text, "\n")] = 0;
        
        //loop through each line in file to search each line
        while (fgets(fileData, sizeof(fileData), file)) {
            if (strstr(fileData, text) != NULL) {
                //display success message
                printf("%s found in line %d\n\n", text, length + 1);

                //close file
                fclose(file);
                
                //update changelog
                updateChangelog(12, filename, "", text, 0);

                return;
            }
            //increment length
            length++;
        }

        //display error message
        printf("%s not found in %s\n", text, filename);

        //close file
        fclose(file);
    }
}

//main
int main() {

    //instantiate choice
    int choice;

    //force while loop
    int run = 1;

    //while loop until user enters 4 to exit the program
    while (run != 0) {
        //display options
        printf("\n");
        printf("1. File operations\n");
        printf("2. Line operations\n");
        printf("3. General operations\n");
        printf("4. Quit\n\n");
        printf("Enter a valid integer to choose an operation: ");

        //get choice userinput
        if (scanf("%d", &choice) != 1) {
            //remove invalid characters from input buffer until new line character is reached
            while (getchar() != '\n');
        }
        printf("\n");

        //compare choice to userinput
        switch (choice) {
            //file operations
            case 1:
                //display file operations
                printf("File operations\n");
                printf("1. Create new file\n");
                printf("2. Copy file to new file\n");
                printf("3. Delete file\n");
                printf("4. Show file contents\n");
                printf("5. Rename file\n");
                printf("6. Go back\n\n");

                //get choice userinput
                printf("Enter a valid integer to choose an operation: ");
                if (scanf("%d", &choice) != 1) {
                    //reset choice and remove invalid characters from input buffer until new line character is reached
                    choice = 0;
                    while (getchar() != '\n');
                
                } else {
                    //remove new line character from input buffer
                    getchar();
                }
                printf("\n");

                switch (choice) {
                    //create file
                    case 1:
                        createFile();
                        break;
                    
                    //copy file
                    case 2:
                        copyFile();
                        break;
                        
                    //delete file
                    case 3:
                        deleteFile();
                        break;

                    //show file
                    case 4:
                        showFile();
                        break;

                    //rename file
                    case 5:
                        renameFile();
                        break;

                    //go back
                    case 6:
                        printf("Going back\n");
                        break;

                    //if choice is not 1 - 6
                    default:                
                        //display invalid choice
                        printf("Invalid choice\n");
                }

                //reset choice
                choice = 0;
                break;

            //line operations
            case 2:
                //display line operations
                printf("Line operations\n");
                printf("1. Append line to file\n");
                printf("2. Delete line from file\n");
                printf("3. Insert line into file\n");
                printf("4. Show line from file\n");
                printf("5. Go back\n\n");

                //get choice userinput
                printf("Enter a valid integer to choose an operation: ");
                if (scanf("%d", &choice) != 1) {
                    //reset choice and remove invalid characters from input buffer until new line character is reached
                    choice = 0;
                    while (getchar() != '\n');
                
                } else {
                    //remove new line character from input buffer
                    getchar();
                }
                printf("\n");

                switch (choice) {
                    //append line
                    case 1:
                        appendLine();
                        break;

                    //delete line
                    case 2:
                        deleteLine();
                        break;

                    //insert line
                    case 3:
                        insertLine();
                        break;

                    //show line
                    case 4:
                        showLine();
                        break;

                    //go back
                    case 5:
                        printf("Going back\n");
                        break;

                    //if choice is not 1 - 5
                    default:
                        //display invalid choice
                        printf("Invalid choice\n");
                }

                //reset choice
                choice = 0;
                break;

            //general operations
            case 3:
                //display general operations
                printf("General operations\n");
                printf("1. Show changelog\n");
                printf("2. Show number of lines in file\n");
                printf("3. Find line that contains text\n");
                printf("4. Go back\n\n");

                //get choice userinput
                printf("Enter a valid integer to choose an operation: ");
                if (scanf("%d", &choice) != 1) {
                    //reset choice and remove invalid characters from input buffer until new line character is reached
                    choice = 0;
                    while (getchar() != '\n');
                
                } else {
                    //remove new line character from input buffer
                    getchar();
                }
                printf("\n");

                switch(choice) {

                    //show changelog
                    case 1:
                        showChangelog();
                        break;
                    
                    //show number of lines
                    case 2:
                        showNoLines();
                        break;

                    //find line
                    case 3:
                        findLine();
                        break;

                    //go back
                    case 4:
                        printf("Going back\n");
                        break;

                    //if choice is not 1 - 4
                    default:
                        //display invalid choice
                        printf("Invalid choice\n");

                }

                //reset choice
                choice = 0;
                break;

            //quit
            case 4:
                //exit while loop
                run = 0;
                break;

            //if choice is not 1 - 4
            default:
                //display invalid choice
                printf("Invalid choice\n");
        }
    }

    return 0;
}