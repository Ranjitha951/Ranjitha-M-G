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
#include <stdio.h>
#include "file.h"

void saveContactsToFile(struct AddressBook *addressBook)
{
	FILE* fp = fopen("addressbook.csv", "w");  // Use "w" to overwrite file
    if(fp == NULL)
    {
        printf("Cannot open file for writing\n");
        return;
    }

    fprintf(fp, "%d\n", addressBook->contactCount); // write number of contacts
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    fclose(fp);
}
void loadContactsFromFile(struct AddressBook *addressBook)
{
    FILE* fp = fopen("addressbook.csv", "r");  
    if(fp == NULL)
    {
        printf("File not found, starting with empty address book.\n");
        addressBook->contactCount = 0;
        return;
    }

    char line[200];

    // Read number of contacts
    if(fgets(line, sizeof(line), fp) != NULL)
        sscanf(line, "%d", &addressBook->contactCount);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(fgets(line, sizeof(line), fp) != NULL)
        {
            sscanf(line, "%49[^,],%19[^,],%49[^\n]",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
        }
    }

    fclose(fp);
}



