# Address Book Project Documentation
# Description:
This Address Book project is a C program that allows users to manage their contacts efficiently. It provides functionality to create, search, edit, delete, and list contacts. The program features robust input validation and persists data by saving contacts to a CSV file.

# Key features:
Contact management with name, phone, and email fields
Comprehensive input validation for all fields
Case-insensitive search functionality
Data persistence through file I/O operations
User-friendly menu interface



# FILE STRUCTURE
contact.h       - Header file with data structures and function declarations
contact.c       - Implementation of contact management functions
file.h          - Header for file operations
file.c          - Implementation of file I/O functions
main.c          - Main program with menu interface
populate.h      - Header for dummy data population
populate.c      - Dummy contact data for testing
contacts.csv    - Data file storing contacts in CSV format


# Sample Input/Output 
# Sample Input 1: Creating a Contact
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 1
Enter name: ranjitha m g
Enter phone number: 9122567089
Enter email: ranjithamg@gmail.com

# sample output 1: Listing Contacts
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 5

::LISTED CONTACTS ARE::
-------------------------------------------
Name : ra
Phone : 1223314455
Email : rt@gmail.com
---------------------------------------------
Name : ranjitha
Phone : 8150024455
Email : ran@gmail.com
---------------------------------------------
Name : dee
Phone : 1133557799
Email : de@1.com
---------------------------------------------

# Sample Input 2: Searching Contacts
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 2
Search Menu:
1. Search by Name
2. Search by phone
3. Search by Email
Enter your opt to search:1
Enter name to search: ranjitha
contact found:
-----------------------------------------
Name  : ranjitha
Phone : 8150024455
Email : ran@gmail.com
contact found:
-----------------------------------------
Name  : ranjitha
Phone : 9107766442
Email : ranjitha@gmail.com

# Sample Input 3: Editing a Contact
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 3
Search contact to edit:
1. Search by Name
2. Search by Mobile
3. Search by Email
Enter your option: 2
Enter mobile number to search: 8150024455
1 ranjitha|8150024455| ran@gmail.com

Selected Contact: ranjitha | 8150024455 | ran@gmail.com

::Which field do you want to edit?::
1. Name
2. Phone
3. Email
Enter your choice: 3
Enter new email: rat@gmail.com
Email updated successfully!

# Sample Input 4: Deleting a Contact
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 4
:::Delete Contact Menu:::
1. Search by Name
2. Search by Mobile
3. Search by Email
Enter your option: 1
Enter name to delete: ranjitha
1) ranjitha | 8150024455 | rat@gmail.com
2) ranjitha | 9107766442 | ranjitha@gmail.com
Multiple contacts found. Enter the index number to delete (1-2): 2

Deleting Contact: ranjitha | 9107766442 | ranjitha@gmail.com
Contact deleted successfully!
# Sample Input 5: Exiting the Program
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 6
Saving and Exiting...





