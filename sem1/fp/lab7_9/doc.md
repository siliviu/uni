# Enunț

Scrieți o aplicație pentru o bibliotecă.

Aplicația stochează:

- cărți: \<id>, \<titlu>, \<descriere>, \<autor>, etc
- clienți: \<id>, \<nume>, \<CNP>, etc

Creați o aplicație care permite:

- gestiunea listei de cărți și clienți.
- adaugă, șterge, modifică, lista de cărți, lista de clienți
- căutare carte, căutare clienți.
- Închiriere/returnare carte
- Rapoarte:
  - Cele mai inchiriate cărți.
  - Clienți cu cărți închiriate ordonat dupa: nume, după numărul de cărți închiriate
  - Primi 20% dintre cei mai activi clienți (nume client si numărul de cărți închiriate)

# Listă de funcționalități

| Număr | Desciere                                        |
| ----- | ----------------------------------------------- |
| F1    | Adăugare carte în listă                         |
| F2    | Modificare carte din listă                      |
| F3    | Șterge carte din listă                          |
| F4    | Adăugare client în listă                        |
| F5    | Modificare client din listă                     |
| F6    | Șterge client din listă                         |
| F7    | Caută carte din listă                           |
| F8    | Caută client din listă                          |
| F9    | Închiriază carte                                |
| F10   | Returnează carte                                |
| F11   | Raport cele mai închiriate cărți                |
| F12   | Raport clienți după numărul de cărți închiriate |
| F13   | Raport cei mai activi 20% clienți               |

# Scenarii de rulare

## F1 : Adăugare carte în listă

| User Input         | Program output          | Description                            |
| ------------------ | ----------------------- | -------------------------------------- |
| 1 <br/> 2          |                         | Accessing the option using the menu    |
|                    | Input id                | Asking user for input                  |
| 1                  |                         | User inputs book id                    |
|                    | Input title             | Asking user for input                  |
| Moby Dick          |                         | User inputs book name                  |
|                    | Input description       | Asking user for input                  |
| Book about a whale |                         | User inputs book description           |
|                    | Input author            | Asking user for input                  |
| Herman Melville    |                         | User inputs book author                |
|                    | Input copies available  | Asking user for input                  |
| 2                  |                         | User inptus number of copies available |
|                    | The book has been added | Confirms action                        |

## F2 : Modificare carte din listă

| User Input               | Program output                 | Description                                                                               |
| ------------------------ | ------------------------------ | ----------------------------------------------------------------------------------------- |
| 1 <br/> 3                |                                | Accessing the option using the menu                                                       |
|                          | Input id of the book to modify | Asking user for input                                                                     |
| 1                        |                                | User inputs book id                                                                       |
|                          | Choose what to modify          | Prompt submenu asking user for input ( 1 = Title, 2 = Desc, 3 = Author, 4 = Nr of copies) |
| 2                        |                                | User chooses to modify book description                                                   |
|                          | Input description              | Asking user for input                                                                     |
| Book about a white whale |                                | User inputs book description                                                              |
|                          | The book has been modified     | Confirms action                                                                           |

## F3 : Șterge carte din listă

| User Input | Program output                 | Description                         |
| ---------- | ------------------------------ | ----------------------------------- |
| 1 <br/> 4  |                                | Accessing the option using the menu |
|            | Input id of the book to remove | Asking user for input               |
| 1          |                                | User inputs client id               |
|            | The book has been removed      | Confirms action                     |

## F4 : Adăugare client în listă

| User Input    | Program output                        | Description                         |
| ------------- | ------------------------------------- | ----------------------------------- |
| 2 <br/> 2     |                                       | Accessing the option using the menu |
|               | Input id                              | Asking user for input               |
| 1             |                                       | User inputs client id               |
|               | Input name                            | Asking user for input               |
| John Peterson |                                       | User inputs client name             |
|               | Input uuid                            | Asking user for input               |
| 4128920       |                                       | User inputs uuid                    |
|               | The person has been added to the list | Confirms action                     |

## F5 : Modificare client din listă

| User Input        | Program output                 | Description                                                |
| ----------------- | ------------------------------ | ---------------------------------------------------------- |
| 2 <br/> 3         |                                | Accessing the option using the menu                        |
|                   | Input id of the book to modify | Asking user for input                                      |
| 1                 |                                | User inputs client id                                      |
|                   | Choose what to modify          | Prompt submenu asking user for input ( 1 = Name , 2 = UID) |
| 1                 |                                | User chooses to modify cliet name                          |
|                   | Input name                     | Asking user for input                                      |
| John Peterson Jr. |                                | User inputs client name                                    |
|                   | The client has been modified   | Confirms action                                            |

## F6 : Șterge client din listă

| User Input | Program output                   | Description                         |
| ---------- | -------------------------------- | ----------------------------------- |
| 2 <br/> 4  |                                  | Accessing the option using the menu |
|            | Input id of the client to remove | Asking user for input               |
| 1          |                                  | User inputs client id               |
|            | The client has been removed      | Confirms action                     |

## F7 : Caută carte din listă

| User Input | Program output | Description |
| ---------- | -------------- | ----------- |
| 3 | | Accessing the option using the menu |
| | Choose what to search after | Prompt submenu for selecting search criteria | 
| 1 | | User chooses to search by ID |
| | Input ID | Asking user for input |
| 12 | | User enters ID = 12 |
| | The results are : <br/> ID : 12, Title : Moby Dick ... | Program prints the search results |
| 3 | | Accessing the option using the menu |
| | Choose what to search after | Prompt submenu for selecting search criteria | 
| 2 | | User chooses to search by Title |
| | Input Title | Asking user for input |
| harry POTTER | | User enters the title |
| | The results are : <br/> ID : 3, Title : Harry Potter and the Sorcerer's Stone  ...  <br/> ID : 4, Title : Harry Potter and the Sorcerer's Stone  ... <br/> ID : 29, Title : 3. Harry Potter and the Prisoner of Azkaban ... <br/> ... | Program prints the search results |
| 3 | | Accessing the option using the menu |
| | Choose what to search after | Prompt submenu for selecting search criteria | 
| 3 | | User chooses to search by Author |
| | Input Author | Asking user for input |
|  kin | | User enters the author |
| | The results are : <br/> ID : 11, Title : The Stand, Author : Stephen King ...  <br/> ID : 214, Title : Euphoria , Author : Lily King ... <br/> ... | Program prints the search results |


## F8 : Caută client din listă

| User Input | Program output | Description |
| ---------- | -------------- | ----------- |
| 4 | | Accessing the option using the menu |
| | Choose what to search after | Prompt submenu for selecting search criteria | 
| 1 | | User chooses to search by ID |
| | Input ID | Asking user for input |
| 12 | | User enters ID = 12 |
| | The results are : <br/> ID : 12, Name: Thomas Jefferson, UID: | Program prints the search results |
| 4 | | Accessing the option using the menu |
| | Choose what to search after | Prompt submenu for selecting search criteria | 
| 2 | | User chooses to search by Name |
| | Input Name | Asking user for input |
| Thomas | | User enters name |
| | The results are : <br/> ID : 12, Name: Thomas Jefferson, UID: 100 <br/> ID : 38, Name: Thomas Edison, UID: 900<br/> ... | Program prints the search results |
| 4 | | Accessing the option using the menu |
| | Choose what to search after | Prompt submenu for selecting search criteria | 
| 3 | | User chooses to search by UID |
| | Input UID | Asking user for input |
| 900 | | User enters uid |
| | The results are : <br/> ID : 38, Name: Thomas Edison, UID: 900 | Program prints the search results |

## F9 : Închiriază carte

| User Input | Program output | Description |
| ---------- | -------------- | ----------- |
| 5 | | Accessing the option using the menu |
| | Input Client ID | Asking user for input |
| 1 | | User chooses client with ID 1 |
| | Input Book ID | Asking user for input |
| 2 | | User chooses Book with ID 2 |
| | The book has been successfully borrowed | Confirms action |
| | Event ID: 1 | Prints the Borrow Event ID |
| 1 | | User chooses client with ID 1 |
| | Input Book ID | Asking user for input |
| 2 | | User chooses Book with ID 2 |
| | No copies left to borrow | Prints error message |


## F10 : Returnează carte

| User Input | Program output | Description |
| ---------- | -------------- | ----------- |
| 6 | | Accessing the option using the menu |
| | Input Event ID | Asking user for input |
| 1 | | User chooses borrow event with ID 1 |
| | The book has been successfully returbed | Confirms action |

## F11 : Raport cele mai închiriate cărți

| User Input | Program output | Description |
| ---------- | -------------- | ----------- |
| 7 | | Accessing the option using the menu |
| | Choose report type | Prompt submenu asking for report |
| 1 |  | User chooses to see the most rented books |
| | ID : 1 ... <br/> ID : 2 ... <br/> ID : 3 ... <br/> ID : 4 ... <br/> ID : 5 ... | Prints results |


## F12 : Raport clienți după numărul de cărți închiriate

| User Input | Program output | Description |
| ---------- | -------------- | ----------- |
| 7 | | Accessing the option using the menu |
| | Choose report type | Prompt submenu asking for report |
| 2 |  | User chooses to see clients ordered by name |
| | ID : 1, Name : Arnold ... | Prints results |
| 3 | | User chooses to see clients ordered by number of borrowed books |
| | ID : 41, ..., Borrowed: 4214 <br/> ... | Prints results |

## F13 : Raport cei mai activi 20% clienți

| User Input | Program output | Description |
| ---------- | -------------- | ----------- |
| 7 | | Accessing the option using the menu |
| | Choose report type | Prompt submenu asking for report |
| 3 |  | User chooses to see the most active 20% clients |
| | ID : 41, ..., Borrowed: 4214 <br/> ... | Prints results |

# Plan de iterații

- I1: F1, F2, F3, F4, F5, F6

- I2: F7, F8, F9, F10

- I3: F11, F12, F13
