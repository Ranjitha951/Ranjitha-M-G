#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(struct AddressBook *addressBook) 
{
	printf("::LISTED CONTACTS ARE::\n");
	printf("-------------------------------------------\n");
	for(int i = 0;i < addressBook->contactCount;i++)
	{
		printf("Name : %s\n", addressBook->contacts[i].name);
		printf("Phone : %s\n", addressBook->contacts[i].phone);
		printf("Email : %s\n", addressBook->contacts[i].email);
		printf("---------------------------------------------\n");
	}
    /* Define the logic for print the contacts */
}

void initialize(struct AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);

   // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
void saveAndExit(struct AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
// phone validation
int ValidPhone(const char phone[], struct AddressBook *addressBook) 
{
    int i;
    if (strlen(phone) != 10) // must be 10 digits
	    return 0;  
    for (i = 0; i < 10; i++) // loop upto 10 characters 
    {
        if (!(phone[i] >= '0' && phone[i] <= '9')) // check all characters are digits
	       	return 0;
    }
    // check duplicate phone
    
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
	       	return 0;
    }
    return 1; // valid phone
}
// email validation
int ValidEmail(const char email[], struct AddressBook *addressBook)
{
	int i;
	int len = strlen(email); // email length
	if(len < 7)
		return 0;
	if(strcmp(email + len - 4, ".com") != 0) // end with .com
		return 0;
	char *at = strchr(email, '@'); // find @ symbol
	if(at == NULL)
		return 0;
	int at_index = at - email; // find positon of @
	if(at_index < 1)
		return 0;
	if((len - 4 ) - (at_index + 1) < 1)
		return 0;
	for(i = 0;i < len;i++)
	{
		if(email[i] >= 'A' && email[i] <= 'Z') // uppercase are not allowed 
			return 0;
	}
	// check duplicate email
	for(i = 0;i < addressBook->contactCount;i++)
	{
		if(strcmp(addressBook->contacts[i].email, email) == 0)
		{
			return 0;
		}
	}
	return 1; // valid email
		
				
}
void createContact(struct AddressBook *addressBook)
{

    char name[50], phone[20], email[50];
    int flag;

    printf("Enter name: ");
    scanf(" %[^\n]", name);
    do 
    {
        flag = 1;
        printf("Enter phone number: ");
        scanf("%s", phone);
      	// check phone validity
	if (!ValidPhone(phone, addressBook))
	{
            flag = 0; 
        }
    }
    while (!flag);
    do
    {
	    flag = 1;

    
        printf("Enter email: ");
        scanf("%s", email);
	if (!ValidEmail(email, addressBook)) // check email validity
            flag = 0;
    }
    while (!flag);

    //store contact   
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);
     addressBook->contactCount++;
        /* Define the logic for create */
}


void searchContact(struct AddressBook *addressBook) 
{
    int opt, i, found;
    char name[50], phone[20], email[50];

    printf("\nSearch Menu:\n"); // search menu
    printf("1. Search by Name\n");
    printf("2. Search by phone\n");
    printf("3. Search by Email\n");
    printf("Enter your opt to search: ");
    scanf("%d", &opt);

    switch (opt)
    {
    case 1: 
        printf("Enter name to search: "); // search by name
        scanf(" %[^\n]", name);
        found = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, name) == 0) // compare names
            {
		printf("contact found:");
                printf("\n-----------------------------------------\n");
                printf("Name  : %s\n", addressBook->contacts[i].name);
                printf("Phone : %s\n", addressBook->contacts[i].phone);
                printf("Email : %s\n", addressBook->contacts[i].email);
                found = 1;
            }
        }
	break; // stop loop once found
        if (!found)
            printf("\nContact not found.\n");
        break;

    case 2:
         
        printf("Enter phone number to search: "); // search by phone
        scanf("%s", phone);
        found = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, phone) == 0) // compare phone number
            {
		printf("contact found:");
                printf("\n------------------------------------------\n");
                printf("Name  : %s\n", addressBook->contacts[i].name);
                printf("Phone : %s\n", addressBook->contacts[i].phone);
                printf("Email : %s\n", addressBook->contacts[i].email);
                found = 1;
                
            }
        }
	break;
        if (!found)
            printf("\nContact not found.\n");
        break;

    case 3:
        printf("Enter email to search: "); // search by email
        scanf("%s", email);
        found = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, email) == 0) // compare email
            {
                printf("\nContact Found:\n");
		printf("\n------------------------------------------\n");
                printf("Name  : %s\n", addressBook->contacts[i].name);
                printf("Phone : %s\n", addressBook->contacts[i].phone);
                printf("Email : %s\n", addressBook->contacts[i].email);
                found = 1;
                
            }
        }
	break;
        if (!found)
            printf("\nContact not found.\n");
        break;

    default:
        printf("Invalid search option.\n");
    }
}

    /* Define the logic for search */


void updateName(struct AddressBook *addressBook, int index)
{
    char newName[50];
    printf("Enter new name: ");
    scanf(" %[^\n]", newName);
    strcpy(addressBook->contacts[index].name, newName); // copy new name
    printf("Name updated successfully!\n");
}

void updatePhone(struct AddressBook *addressBook, int index) 
{
    char newPhone[20];
    int valid;
    do 
    {
        valid = 1;
        printf("Enter new phone: ");
        scanf("%s", newPhone);
        if (!ValidPhone(newPhone, addressBook)) // validate phone
       	{
            printf("Invalid or duplicate phone. Try again.\n");
            valid = 0;
        }
    } 
    while (!valid); // repeat untill vaild input
    strcpy(addressBook->contacts[index].phone, newPhone); // update phone number
    printf("Phone updated successfully!\n");
}

void updateEmail(struct AddressBook *addressBook, int index)
{
    char newEmail[50];
    int valid;
    do 
    {
        valid = 1;
        printf("Enter new email: ");
        scanf("%s", newEmail);
        if (!ValidEmail(newEmail, addressBook)) // validate email
	{
            printf("Invalid or duplicate email. Try again.\n");
            valid = 0;
        }
    } 
    while (!valid); // repeat until valid
    strcpy(addressBook->contacts[index].email, newEmail); // update email
    printf("Email updated successfully!\n");
}

       void editContact(struct AddressBook *addressBook)
{
    int opt, i, count = 0;
    char name[50], phone[20], email[50];
    int foundIndexes[100];  // store indexes of found contacts

    printf("\nSearch contact to edit:\n"); // display menu
    printf("1. Search by Name\n");
    printf("2. Search by Mobile\n");
    printf("3. Search by Email\n");
    printf("Enter your option: ");
    scanf("%d", &opt);

    switch (opt)
    {
    case 1:
        printf("Enter name to search: ");
        scanf(" %[^\n]", name);
        count = 0;
        for (i = 0; i < addressBook->contactCount; i++) // loop upto contactCount
	{
            if (strcmp(addressBook->contacts[i].name, name) == 0) // match name
	    {
                printf("%d %s|%s|%s\n", count+1, addressBook->contacts[i].name,addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                foundIndexes[count] = i; // store index
                count++;
            }
        }
        break;

    case 2:
        printf("Enter mobile number to search: ");
        scanf("%s", phone);
        count = 0;
        for (i = 0; i < addressBook->contactCount; i++)
       	{
            if (strcmp(addressBook->contacts[i].phone, phone) == 0) 
	    {
                printf("%d %s|%s| %s\n", count+1, addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                foundIndexes[count] = i; // store index of matched contact
                count++;
            }
        }
        break;

    case 3:
        printf("Enter email to search: ");
        scanf("%s", email);
        count = 0;
        for (i = 0; i < addressBook->contactCount; i++)
       	{
            if (strcmp(addressBook->contacts[i].email, email) == 0) // compare phone numbers
	    {
                printf("%d %s|%s|%s\n", count+1, addressBook->contacts[i].name,addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                foundIndexes[count] = i; // store index of matched contact
                count++; 
            }
        }
        break;

    default:
        printf("Invalid option.\n");
        return;
    }

    if (count == 0) // if no matches found
    {
        printf("No contact found.\n");
        return;
    }

    // If multiple contacts found, ask which to edit
    int chosenIndex;
    if (count == 1) 
    {
        chosenIndex = foundIndexes[0];
    } 
    else 
    {
        int choice;
        printf("Multiple contacts found. Enter the index number to edit (1-%d): ", count);
        scanf("%d", &choice);
        if (choice < 1 || choice > count)// invalid input check
       	{
            printf("Invalid choice.\n");
            return;
        }
        chosenIndex = foundIndexes[choice-1];// get slected index
    }

    printf("\nSelected Contact: %s | %s | %s\n",addressBook->contacts[chosenIndex].name,addressBook->contacts[chosenIndex].phone,
        addressBook->contacts[chosenIndex].email);
    // Ask which field to edit
    int Opt;
    printf("\n::Which field do you want to edit?::\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &Opt);

    switch (Opt) 
    {
        case 1:
	       	updateName(addressBook, chosenIndex); 
		break;
        case 2:
	       	updatePhone(addressBook, chosenIndex);
	       	break;
        case 3:
	       	updateEmail(addressBook, chosenIndex); 
		break;
        default:
	       	printf("Invalid option.\n");
    }
}


    /* Define the logic for Editcontact */

 


void deleteContact(struct AddressBook *addressBook)
{
    int opt, i, count = 0;
    char name[50], phone[20], email[50];
    int foundIndexes[100]; // Store indexes of found contacts

    printf("\n:::Delete Contact Menu:::\n");// serach menu
    printf("1. Search by Name\n");
    printf("2. Search by Mobile\n");
    printf("3. Search by Email\n");
    printf("Enter your option: ");
    scanf("%d", &opt);

    switch (opt)
    {
    case 1:
        printf("Enter name to delete: ");
        scanf(" %[^\n]", name);
        count = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, name) == 0)
            {
                printf("%d) %s | %s | %s\n", count + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                foundIndexes[count] = i;
                count++;
            }
        }
        break;

    case 2:
        do
        {
            printf("Enter mobile number to delete: ");
            scanf("%s", phone);
            if (strlen(phone) != 10)
                printf("Invalid phone number!\n");
        }
       	while (strlen(phone) != 10);

        count = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, phone) == 0)
            {
                printf("%d) %s | %s | %s\n", count + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                foundIndexes[count] = i;
                count++;
            }
        }
        break;

    case 3:
        // Validate email before searching
        do
        {
            int len, valid = 1;
            printf("Enter email to delete: ");
            scanf("%s", email);
            len = strlen(email);
            if (strchr(email, '@') == NULL || strcmp(email + len - 4, ".com") != 0)
            {
                printf("Invalid email!\n");
                valid = 0;
                continue;
            }
            if (!valid)
                continue;
            else
                break;
        } 
	while (1);

        count = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, email) == 0)
            {
                printf("%d) %s | %s | %s\n", count + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                foundIndexes[count] = i;
                count++;
            }
        }
        break;

    default:
        printf("Invalid option.\n");
        return;
    }

    if (count == 0)
    {
        printf("No contact found.\n");
        return;
    }

    // If multiple contacts found, ask which to delete
    int chosenIndex;
    if (count == 1)
    {
        chosenIndex = foundIndexes[0];
    }
    else
    {
        int choice;
        printf("Multiple contacts found. Enter the index number to delete (1-%d): ", count);
        scanf("%d", &choice);
        if (choice < 1 || choice > count)
        {
            printf("Invalid choice.\n");
            return;
        }
        chosenIndex = foundIndexes[choice - 1]; // selected index
    }

    printf("\nDeleting Contact: %s | %s | %s\n",
           addressBook->contacts[chosenIndex].name,
           addressBook->contacts[chosenIndex].phone,
           addressBook->contacts[chosenIndex].email);

    // Shift contacts up
    for (i = chosenIndex; i < addressBook->contactCount - 1; i++) // shift contacts
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;// decrease total count
    printf("Contact deleted successfully!\n");
}
/* Define the logic for deletecontact */



