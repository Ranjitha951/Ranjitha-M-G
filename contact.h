#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>

struct Contact
{
    char name[50];
    char phone[20];
    char email[50];
};

struct AddressBook
{
    struct Contact contacts[100];
    int contactCount;
};

void createContact(struct AddressBook *addressBook);
void searchContact(struct AddressBook *addressBook);
void editContact(struct AddressBook *addressBook);
void deleteContact(struct AddressBook *addressBook);
void listContacts(struct AddressBook *addressBook);
void initialize(struct AddressBook *addressBook);
void saveContactsToFile(struct AddressBook *AddressBook);

#endif
