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

// Dummy contact data
static struct Contact dummyContacts[] = {
    {"John Doe", "1234567890", "john@example.com"},
    {"Alice Smith", "0987654321", "alice@example.com"},
    {"Bob Johnson", "1112223333", "bob@company.com"},
    {"Carol White", "4445556666", "carol@company.com"},
    {"David Brown", "7778889999", "david@example.com"},
    {"Eve Davis", "6665554444", "eve@example.com"},
    {"Frank Miller", "3334445555", "frank@example.com"},
    {"Grace Wilson", "2223334444", "grace@example.com"},
    {"Hannah Clark", "5556667777", "hannah@example.com"},
    {"Ian Lewis", "8889990000", "ian@example.com"}
};

void populateAddressBook(struct AddressBook* addressBook)
{
    int numDummyContacts = sizeof(dummyContacts) / sizeof(dummyContacts[0]);
    for (int i = 0; i < numDummyContacts; i++) {
        addressBook->contacts[addressBook->contactCount++] = dummyContacts[i];
    }
}
