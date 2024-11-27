#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "contact.h"
#include "file.h"


void listContacts(AddressBook *addressBook)           // Sort contacts based on the chosen criteria
{
    if(addressBook->contactCount!=0)
    for(int j=0;j<addressBook->contactCount-1;j++)
    {
        Contact temp;
        for(int k=0;k<addressBook->contactCount-1-j;k++)
        {
            if(strcmp(addressBook->contacts[k].name,addressBook->contacts[k+1].name)>0)
            {
                temp=addressBook->contacts[k];
                addressBook->contacts[k]=addressBook->contacts[k+1];
                addressBook->contacts[k+1]=temp;
            }
        }
    }
    
       for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("Contact %d\n\n",i+1);
        printf("Name :%s\n",addressBook->contacts[i].name);
        printf("Ph no:%s\n",addressBook->contacts[i].phone);
        printf("Email:%s\n\n",addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
int check_name(char name[]) {
        for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            printf("Error: Name must not contain digits or special characters\n");
            return 0;
        }
    }
    return 1;
}

int check_phoneno(char num[],AddressBook *addressBook) {
    int i = 0;
    int length = strlen(num);

    // Check for valid length
    if (length != 10) {
        printf("Error: Phone number must be exactly 10 digits\n");
        return 0;
    }

        for (int i = 0; i < length; i++) {
         if (!isdigit(num[i])) {
            printf("Error: Phone number must contain only digits\n");
              return 0;
           }
        }
    // Check for duplicate phone numbers
      for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, num) == 0) {
            printf("Error: Duplicate phone number found\n");
            return 0;
        }
    }
    return 1;
    }

int check_email(char email[],AddressBook *addressBook) {
    int at_count = 0;
    int length = strlen(email);

    // Check if email starts with '@'
    if (email[0] == '@') 
    {
        printf("Error: Email cannot start with '@'\n");
        return 0;
    }
    for (int i = 0; i < length; i++)
    {
        if (email[i] == '@') {
            at_count++;
        }
    }
    if (at_count != 1 || strstr(email, ".com") == NULL || strcmp(email + length - 9, "gmail.com") != 0)
    {
        printf("Error: Invalid email format (must contain exactly one '@' and end with '.com')\n");
        return 0;
    }
    // Check for duplicate emails
     for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, email) == 0) {
            printf("Error: Duplicate email found\n");
            return 0;
        }
    }
    return 1;
}
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    int n;
    printf("Enter the number of contacts to add: ");
    scanf("%d", &n);
    if(n<MAX_CONTACTS)
    {
    for (int i = 0; i < n; i++) 
    {
            int name_valid = 0;
            while(!name_valid){
            printf("Enter name: ");
            scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
            name_valid = check_name(addressBook->contacts[addressBook->contactCount].name);
            if (!name_valid) {
                printf("Invalid name, please try again.\n");
                } 
            }
             
            int num_valid = 0;
            while(!num_valid){
            printf("Enter Number: ");
            scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);
            num_valid = check_phoneno(addressBook->contacts[addressBook->contactCount].phone, addressBook);
            if (!num_valid) {
                printf("Invalid number, please try again.\n");
                }
            }

            int email_valid = 0;
            while(!email_valid){
            printf("Enter Email: ");
            scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email);
            email_valid = check_email(addressBook->contacts[addressBook->contactCount].email, addressBook);
            if (!email_valid) {
                printf("Invalid email, please try again.\n");
                }
            }

        printf("\nContact %d\n", i + 1);
        printf("Name: %s\n", addressBook->contacts[addressBook->contactCount].name);
        printf("Number: %s\n", addressBook->contacts[addressBook->contactCount].phone);
        printf("Email: %s\n", addressBook->contacts[addressBook->contactCount].email);
        printf("\n");
        addressBook->contactCount++;
    }
    }
    else
        printf("Error:Enter the number less than MAX_CONTACTS");
    //saveContactsToFile(addressBook);
        
}


void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    char input[100];
    int found = 0;  // Flag to indicate if a contact was found

    printf("\nSearch By:\n");
    printf("1. Name\n");
    printf("2. Phone number\n");
    printf("3. Email ID\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) 
    {
        case 1:
            printf("Enter name to search: ");
            scanf("%[^\n]", input);
            getchar();
            
            if (check_name(input))
            {
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (strcmp(input, addressBook->contacts[i].name) == 0) 
                    {
                        printf("Contact found:\n\n");
                        printf(" Name  : %s\n", addressBook->contacts[i].name);
                        printf(" Number: %s\n", addressBook->contacts[i].phone);
                        printf(" Email : %s\n", addressBook->contacts[i].email);
                        printf("\n");
                        found = 1;
                    }
                }
                if (!found)
                printf("Contact not found\n");
            } 
            else 
                printf("Invalid name format.\n");
            break;

        case 2:
            printf("Enter phone number to search: ");
            scanf("%s", input);
            getchar();
            
            if (check_phoneno(input,addressBook)) 
            {
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (strcmp(input, addressBook->contacts[i].phone) == 0) 
                    {
                        printf("Contact found:\n\n");
                        printf(" Name  : %s\n", addressBook->contacts[i].name);
                        printf(" Number: %s\n", addressBook->contacts[i].phone);
                        printf(" Email : %s\n", addressBook->contacts[i].email);
                        printf("\n");
                        found = 1;
                    }
                }
                if (!found) printf("Contact not found\n");
            } 
            else 
                printf("Invalid phone number format.\n");
            break;

        case 3:
            printf("Enter email ID to search: ");
            scanf("%s", input);
            getchar();
            
            if (check_email(input,addressBook)) 
            {
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (strcmp(input, addressBook->contacts[i].email) == 0) 
                    {
                        printf("Contact found\n\n");
                        printf(" Name  : %s\n", addressBook->contacts[i].name);
                        printf(" Number: %s\n", addressBook->contacts[i].phone);
                        printf(" Email : %s\n", addressBook->contacts[i].email);
                        printf("\n");
                        found = 1;
                    }
                }
                if (!found) printf("Contact not found\n");
            } 
            else 
                printf("Invalid email format.\n");
            break;

        case 4:
            printf("Exiting search.\n");
            break;

        default:
            printf("Invalid choice.please try again.\n");
    }
    addressBook->contactCount++;
}


void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice;
    char input[100];
    int found = 0;  // Flag to indicate if a contact was found

    printf("\nEdit contact - Search menu :\n");
    printf("1. Name\n");
    printf("2. Phone number\n");
    printf("3. Email ID\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    int foundIndices[100];
    int foundCount = 0;

    switch (choice) 
    {
        case 1:
            printf("Enter name to search: ");
            scanf("%[^\n]", input);
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (strcmp(input, addressBook->contacts[i].name) == 0) 
                    {
                      foundIndices[foundCount++]=i;
                    }
                }
                break;

        case 2:
            printf("Enter phone number to search: ");
            scanf("%s", input);
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (strcmp(input, addressBook->contacts[i].phone) == 0) 
                    {
                         foundIndices[foundCount++]=i;
                    }
                }
                break;

        case 3:
            printf("Enter email ID to search: ");
            scanf("%s", input);            
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (strcmp(input, addressBook->contacts[i].email) == 0) 
                    {
                        foundIndices[foundCount++]=i;
                    }
                }
                break;
        case 4:
            printf("Exiting search.\n");
            break;

        default:
            printf("Invalid choice.please try again.\n");
    }
    
    if (foundCount > 0)
     {
        printf("\nFound %d contact(s):\n", foundCount);

        // Display all found contacts
        for (int i = 0; i < foundCount; i++) {
            int index = foundIndices[i];
            printf("contact %d\n",i+1);
            printf(" Name  : %s\n", addressBook->contacts[index].name);
            printf(" Number: %s\n", addressBook->contacts[index].phone);
            printf(" Email : %s\n", addressBook->contacts[index].email);
        }

        
        int selectedContact;
        printf("Select which contact to edit: ");
        scanf("%d", &selectedContact);

        if (selectedContact < 1 || selectedContact > foundCount) //checks selection in given range or not
        {
            printf("Invalid choice!\n");
            return;
        }

        int selIndex = foundIndices[selectedContact - 1];

        // Contact found, ask which field to edit
        printf("\nContact Selected: \n"); 
        printf(" Name  : %s\n", addressBook->contacts[selIndex].name);
        printf(" Number: %s\n", addressBook->contacts[selIndex].phone);
        printf(" Email : %s\n", addressBook->contacts[selIndex].email);

//edit the contact on which basis
        printf("\nWhat to edit?\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter your choice: ");
        int editChoice;
        scanf("%d", &editChoice);

        char newValue[50];
        switch (editChoice) {
            case 1:
                printf("Enter new name: ");
                scanf(" %[^\n]", newValue);
                if (check_name(newValue))
                    {
                    strcpy(addressBook->contacts[selIndex].name,newValue);//copy new value to addressbook
                    printf("Name updated successfully!\n");
                }else {
                    printf("Invalid name\n");
                }
                break;

            case 2:
                printf("Enter new phone no: ");
                scanf("%s", newValue);
                if (check_phoneno(newValue,addressBook))
                    {
                    strcpy(addressBook->contacts[selIndex].phone, newValue);//copy new phone number to addressbook
                    printf("Phone number updated successfully!\n");
                }else {
                    printf("Invalid phone\n");
                }
                break;

            case 3:
                printf("Enter new email: ");
                scanf("%s", newValue);
                if (check_email(newValue, addressBook))
                        {
                    strcpy(addressBook->contacts[selIndex].email, newValue);//copy new email to addressbook
                    printf("Email updated successfully!\n"); 
                }else {
                    printf("Invalid email\n");
                }
                break;
            default:
                printf("Invalid choice!\n");
        }
        }else{ 
        printf("No contacts found!\n");
        }
}


void deleteContact(AddressBook *addressBook){
	/* Define the logic for deletecontact */
   int choice;
    char input[50];
    int found = 0;  // Flag to indicate if a contact was found

    printf("\nDelete contact by :\n");
    printf("1. Name\n");
    printf("2. Phone number\n");
    printf("3. Email ID\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    int foundIndices[100];
    int foundCount = 0;

    switch (choice) 
    {
        case 1:
            printf("Enter name to search: ");
            scanf("%[^\n]", input);
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (strcmp(input, addressBook->contacts[i].name) == 0) 
                    {
                      foundIndices[foundCount++]=i;
                    }
                }
                break;

        case 2:
            printf("Enter phone number to search: ");
            scanf("%s", input);
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (strcmp(input, addressBook->contacts[i].phone) == 0) 
                    {
                         foundIndices[foundCount++]=i;
                    }
                }
                break;

        case 3:
            printf("Enter email ID to search: ");
            scanf("%s", input);            
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (strcmp(input, addressBook->contacts[i].email) == 0) 
                    {
                        foundIndices[foundCount++]=i;
                    }
                }
                break;
        case 4:
            printf("Exiting..\n");
            break;

        default:
            printf("Invalid choice.please try again.\n");
    }
    
    if (foundCount > 0) {
        printf("\nFound %d contact(s):\n", foundCount);

        // Display all found contacts
        for (int i = 0; i < foundCount; i++) {
            int index = foundIndices[i];
            printf("\ncontact %d\n",i+1);
            printf(" Name  : %s\n", addressBook->contacts[index].name);
            printf(" Number: %s\n", addressBook->contacts[index].phone);
            printf(" Email : %s\n", addressBook->contacts[index].email);
        }

        
        int selectedContact;
        printf("Select which contact to delete: ");
        scanf("%d", &selectedContact);

        if (selectedContact < 1 || selectedContact > foundCount) //checks selection in given range or not
        {
            printf("Invalid choice!\n");
            return;
        }

        int selIndex = foundIndices[selectedContact - 1];

        for(int i=selIndex;i<addressBook->contactCount-1;i++)
        {
            strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
            strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
            strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
        }
        addressBook->contactCount--;
        printf("Contact deleted successfully!\n");    
    }else {
        printf("No contacts found!\n");
    }
}