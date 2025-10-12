/* Name : Ranjitha M G
 Register Number : 
Date : 10/10/2025
Description : AddressBook project 
  The Address Book Management System is a simple console-based application designed to store and manage contact information efficiently. Users can perform key operations such as:
Create Contact: Add new contacts with Name, Phone Number, and Email.
Search Contact: Find contacts using Name or Phone Number.
Edit Contact: Update existing contact details.
Delete Contact: Remove unwanted contacts.
List All Contacts: Display all saved contacts in an organized manner.
File Storage: All contact data is stored in a file, ensuring information is saved and can be loaded across sessions.*/
#include "contact.h"
int main() 
{
    int choice;

    struct AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do 
    {
	printf("\nAddress Book Menu:\n");
	printf("1. Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) 
	{
	    case 1:
		createContact(&addressBook);
		break;
	    case 2:
		searchContact(&addressBook);
		break;
	    case 3:
		editContact(&addressBook);
		break;
	    case 4:
		deleteContact(&addressBook);
		break;
	    case 5:
		listContacts(&addressBook);
		break;
	    case 6:
		printf("Saving and Exiting...\n");
	saveContactsToFile(&addressBook);
		break;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 6);

    return 0;
}
