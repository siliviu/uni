# Enunț

Creați o aplicație pentru gestiunea concurenților de la un concurs de programare.
Programul înregistrează scorul obținut de fiecare concurent la 10 probe diferite, fiecare probă este notat cu un scor de la 1 la 10. 
Fiecare participant este identificat printr-un număr de concurs, scorul este ținut într-o listă unde concurentul 3 are scorul pe poziția 3 în listă.
Programul trebuie sa ofere următoarele funcționalități:

1. Adaugă un scor la un participant.
    * Adaugă scor pentru un nou participant (ultimul participant)
    * Inserare scor pentru un participant.

2. Modificare scor.
    * Șterge scorul pentru un participant dat.
    * Șterge scorul pentru un interval de participanți.
    * Înlocuiește scorul de la un participant.

3. Tipărește lista de participanți.
    * Tipărește participanții care au scor mai mic decât un scor dat.
    * Tipărește participanții ordonat după scor
    * Tipărește participanții cu scor mai mare decât un scor dat, ordonat după scor.

4. Operații pe un subset de participanți.
    * Calculează media scorurilor pentru un interval dat (ex. Se da 1 și 5 se tipărește media scorurilor participanților 1,2,3,4 și 5)
    * Calculează scorul minim pentru un interval de participanți dat.
    * Tipărește participanții dintr-un interval dat care au scorul multiplu de 10.

5. Filtrare.
    * Eliminare participanți care au scorul multiplu unui număr dat. Ex. Se da numărul 10, se elimină scorul de la toți participanții care nu au scorul multiplu de 10.
    * Eliminare participanți care au scorul mai mic decât un scor dat.

6. Undo
    * Reface ultima operație (lista de scoruri revine la numerele ce existau înainte de ultima operație care a modificat lista) – **Nu folosiți funcția deepCopy**

# Listă de funcționalități

| Număr | Descriere funcție |
| - | - |
| F1 | Adăugarea scorului unui nou participant |
| F2 | Inserare scor participant |
| F3 | Șterge scorul unui participant |
| F4 | Șterge scorul unui interval de participanți |
| F5 | Schimbă scorul unui participant |
| F6 | Printează participanții cu scor mai mic decât un scor dat |
| F7 | Printează participanții ordonați după scor |
| F8 | Printează participanții cu scor mai mic decât un scor dat, ordonați după scor |
| F9 | Calculează media scorurilor pentru un interval dat |
| F10 | Calculează scorul minim pentru un interval dat |
| F11 | Tipărește participanții dintr-un interval dat cu scor multiplu de 10 |
| F12 | Filtrează participanții cu scor multiplu de un scor dat |
| F13 | Filtrează participanții cu scor mai mic decât un scor dat |
| F14 | Reface ultima operație asupra listei |

# Plan de iterații

## Prima iterație:

Vom implementa meniul programului, logica principală și documentația acestuia. Cerințele realizate vor fi 1 și 3, adică funcționalitățile F1, F2, F6, F7 și F8.

## A doua iterație:
Adăugăm funcționalități noi pentru a rezolva cerințele 2 și 5, adică funcționalitățile F3, F4, F5, F12, F13. În culise, reorganizăm codul pentru a ne fi mai ușor să adăugăm feature-uri noi.

## A treia iterație:
Rafinăm codul și implementăm cerințele rămase: 4 și 6, funcționalitățile F9, F10, F11, F14.

# Scenarii de rulare

## F1 : Adăugarea scorului unui nou participant

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 1 | | User chooses the add submenu |
| | Add submenu | Program prints the add submenu |
| 1 | | User chooses to add score of a new participant |
| | Task input dialog | Program asks user to enter the task for the score addition (1-10) |
| a | | User enters a bad input |
| | Invalid input warning. Task input dialog | Program doesn't accept the input and asks for it again |
| 1 | | User chooses task 1 |
| | Score input dialog | Program asks user to enter the score (1-10) |
| 12 | | User enters a bad input |
| | Invalid input warning. Score input dialog | Program doesn't accept the input and asks for it again |
| 4 | | User chooses 4 as score |
| | Operation successful. Participant 4 now has score ....| Confirms the operation was successful and prints the current score for the last participant |
| | Add submenu | Program prints the add submenu |

## F2 : Inserare scor participant

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 1 | | User chooses the add submenu |
| | Add submenu | Program prints the add submenu |
| 2 | | User chooses to add score of an existing participant |
| | Participant input dialog | Program asks user to enter the participant number (eg 1-3) |
| 44 | | User enters a bad input |
| | Invalid input warning. Participant input dialog | Program doesn't accept the input and asks for it again |
| 3 | | User chooses participant 3 |
| | Task input dialog | Program asks user to enter the task for the score addition (1-10) |
| 1 | | User chooses task 1 |
| | Score input dialog | Program asks user to enter the score (1-10) |
| 4 | | User chooses 4 as score |
| | Operation successful. Participant 3 now has score ... | Confirms the operation was successful if the participant didn't have a score set for the taskand prints the current score for participant 3 |
| *or* |
| | Error. Participant already has a score for that task | Program prints error message as the operation failed because the participant already had a score for that task |
| | Add submenu | Program prints the add submenu |


## F3 : Șterge scorul unui participant

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 2 | | User chooses the modify submenu |
| | Modify submenu | Program prints the modify submenu |
| 1 | | User chooses to remove the score of an existing participant |
| | Participant input dialog | Program asks user to enter the participant number (eg 1-3) |
| 3 | | User chooses participant 3 |
| | Task input dialog | Program asks user to enter the task for the score modification (1-10) |
| 1 | | User chooses task 1 |
| | Operation successful. Participant 3 now has score ... | Confirms the operation was successful if the participant had a score set for the task and prints the current score for participant 3 |
| *or* |
| | Error. Operation failed | Program prints error message as the operation failed because the participant didn't have a score for that task |
| | Add submenu | Program prints the modify submenu |

## F4 : Șterge scorul unui interval de participanți

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 2 | | User chooses the modify submenu |
| | Modify submenu | Program prints the modify submenu |
| 2 | | User chooses to remove the score of an interval of participants |
| | Participant input dialog (left endpoint) | Program asks user to enter the participant number for the left end of the interval (eg 1-3) |
| 2 | | User chooses participant 2 for the left end of the interval |
| | Participant input dialog (right endpoint) | Program asks user to enter the participant number for the right end of the interval (eg 1-3) |
| 1 | | User chooses participant 1 for the right end of the interval, 1 < 2 |
| | Invalid input warning. Participant input dialog (left endpoint) | Program doesn't accept the input as it doesn't form an interval and asks for both endpoints again | 
| 2 | | User chooses participant 2 for the left end of the interval |
| | Participant input dialog (right endpoint) | Program asks user to enter the participant number for the right end of the interval (eg 1-3) |
| 3 | | User chooses participant 3 for the right end of the interval, 3 > 2 |
| | Task input dialog | Program asks user to enter the task for the score modification (1-10) |
| 1 | | User chooses task 1 |
| | Operation successful. Participants 2-3 now have score ... | Confirms the operation was successful if the participant had a score set for the task and prints the current score for participants 2-4 |
| *or* |
| | Error. Operation failed | Program prints error message as the operation failed because one of the participants didn't have a score for that task |
| | Add submenu | Program prints the modify submenu |

## F5 : Schimbă scorul unui participant

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 2 | | User chooses the modify submenu |
| | Modify submenu | Program prints the modify submenu |
| 3 | | User chooses to modify the score of an existing participant |
| | Participant input dialog | Program asks user to enter the participant number (eg 1-3) |
| 3 | | User chooses participant 3 |
| | Task input dialog | Program asks user to enter the task for the score modification (1-10) |
| 1 | | User chooses task 1 |
| | Score input dialog | Program asks user to enter the score (1-10) |
| 4 | | User chooses 4 as score |
| | Operation successful. Participant 3 now has score ... | Confirms the operation was successful if the participant had a score set for the task and prints the current score for participant 3 |
| *or* |
| | Error. Operation failed | Program prints error message as the operation failed because the participant didn't have a score for that task |
| | Add submenu | Program prints the modify submenu |

## F6 : Printează participanții cu scor mai mic decât un scor dat

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 3 | | User chooses the print submenu |
| | Print submenu | Program prints the print submenu |
| 2 | | User chooses to print all participants with scores smaller than |
| | Task input dialog | Program asks user to enter the task for the print (0-10) |
| 1 | | User chooses task 1 |
| | Score input dialog | Program asks user to enter the score (1-10) |
| 4 | | User chooses 4 as score |
| | The list is ... | Program prints a list of participants with scores smaller than 4 for the first task |
| | Print submenu | 

## F7 : Printează participanții ordonați după scor

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 3 | | User chooses the print submenu |
| | Print submenu | Program prints the print submenu |
| 2 | | User chooses to print all participants in order of score |
| | Task input dialog | Program asks user to enter the task for the print (0-10) |
| 1 | | User chooses task 1 |
| | The list is ... | Program prints a list of participants in order of their scores for the first task |
| | Print submenu | 
| 2 | | User chooses to print all participants in order of score |
| | Task input dialog | Program asks user to enter the task for the print (0-10) |
| 0 | | User chooses 0, the sum of scores for all tasks |
| | The list is ... | Program prints a list of participants in order of their scores for all tasks |
| | Print submenu |

## F8 : Printează participanții cu scor mai mic decât un scor dat, ordonați după scor

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 3 | | User chooses the print submenu |
| | Print submenu | Program prints the print submenu |
| 3 | | User chooses to print all participants in order of score, with score smaller than |
| | Task input dialog | Program asks user to enter the task for the print (0-10) |
| 0 | | User chooses task 0, sum of scores for all tasks |
| | Score input dialog | Program asks user to enter the score (1-100) |
| 94 | | User chooses 94 as score |
| | The list is ... | Program prints a list of participants with scores smaller than 94, in order of their scores for all tasks |
| | Print submenu |


## F9 : Calculează media scorurilor pentru un interval dat

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 4 | | User chooses the operation submenu |
| | Operation submenu | Program prints the operation submenu |
| 1 | | User chooses to calculate the average of scores in an interval |
| | Participant input dialog (left endpoint) | Program asks user to enter the participant number for the left end of the interval (eg 1-3) |
| 2 | | User chooses participant 2 for the left end of the interval |
| | Participant input dialog (right endpoint) | Program asks user to enter the participant number for the right end of the interval (eg 1-3) |
| 3 | | User chooses participant 3 for the right end of the interval, 3 > 2 |
| | Task input dialog | Program asks user to enter the task for the score modification (1-10) |
| 1 | | User chooses task 1 |
| | 2.33 | Program prints average of numbers |
| | Operation submenu |


## F10 : Calculează scorul minim pentru un interval dat 

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 4 | | User chooses the operation submenu |
| | Operation submenu | Program prints the operation submenu |
| 2 | | User chooses to calculate the minimum of scores in an interval |
| | Participant input dialog (left endpoint) | Program asks user to enter the participant number for the left end of the interval (eg 1-3) |
| 2 | | User chooses participant 2 for the left end of the interval |
| | Participant input dialog (right endpoint) | Program asks user to enter the participant number for the right end of the interval (eg 1-3) |
| 3 | | User chooses participant 3 for the right end of the interval, 3 > 2 |
| | Task input dialog | Program asks user to enter the task for the score modification (1-10) |
| 1 | | User chooses task 1 |
| | 1 | Program prints minimum of numbers |
| | Operation submenu |

## F11 : Tipărește participanții dintr-un interval dat cu scor multiplu de 10

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 4 | | User chooses the operation submenu |
| | Operation submenu | Program prints the operation submenu |
| 2 | | User chooses to print participants with scores multiples of 10 in an interval |
| | Participant input dialog (left endpoint) | Program asks user to enter the participant number for the left end of the interval (eg 1-3) |
| 2 | | User chooses participant 2 for the left end of the interval |
| | Participant input dialog (right endpoint) | Program asks user to enter the participant number for the right end of the interval (eg 1-3) |
| 3 | | User chooses participant 3 for the right end of the interval, 3 > 2 |
| | Task input dialog | Program asks user to enter the task for the score modification (1-10) |
| 1 | | User chooses task 1 |
| | [1,2] | Program prints the required list |
| | Operation submenu |

## F12 : Filtrează participanții cu scor multiplu de un scor dat

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 5 | | User chooses the filter submenu |
| | Operation submenu | Program prints the filter submenu |
| 1 | | User chooses to filter out scores multiples of |
| | Task input dialog | Program asks user to enter the task for the print (0-10) |
| 1 | | User chooses task 1 |
| | Score input dialog | Program asks user to enter the score (1-10) |
| 4 | | User chooses 4 as score |
| | The list is ... | Program prints given list |
| | Print submenu |

## F13 : Filtrează participanții cu scor mai mic decât un scor dat

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 5 | | User chooses the filter submenu |
| | Operation submenu | Program prints the filter submenu |
| 2 | | User chooses to filter out scores smaller thab |
| | Task input dialog | Program asks user to enter the task for the print (0-10) |
| 1 | | User chooses task 1 |
| | Score input dialog | Program asks user to enter the score (1-10) |
| 4 | | User chooses 4 as score |
| | The list is ... | Program prints given list |
| | Print submenu |

## F14 : Reface ultima operație asupra listei

| User Input | Program output | Description |
| - | - | - |
| | Application Menu | Program prints main menu |
| 6 | | User chooses to undo the last operation |
| | Undo successful | Confirms the operation was successful if there was something to undo |
| or |
| | No more actions left to undo | Warns the user there is nothing left to undo |
| | Application submenu |


# Listă de taskuri

* F1:
    * T1 : Input task, scor
    * T2 : Creeaza lista noua cu scorul setat pentru task
    * T3 : Adauga noua lista curenta la lista cu toate starile

* F2:
    * T1 : Input participant, task, scor
    * T2 : Schimba scorul participantului la task in scor
    * T3 : Adauga noua lista curenta la lista cu toate starile

* F3:
    * T1 : Input participant, task
    * T2 : Sterge scorul partcipantului la task
    * T3 : Adauga noua lista curenta la lista cu toate starile

* F4:
    * T1 : Input interval, task
    * T2 : Sterge scorul partcipantilor din interval la task
    * T3 : Adauga noua lista curenta la lista cu toate starile

* F5:
    * T1 : Input participant, task, scor
    * T2 : Schimba scorul participantului la task in scor
    * T3 : Adauga noua lista curenta la lista cu toate starile

* F6:
    * T1 : Input task, scor
    * T2 : Obtine lista filtrata
    * T3 : Afiseaza lista

* F7:
    * T1 : Obtine lista sortata
    * T2 : Afiseaza lista

* F8:
    * T1 : Input task, scor
    * T2 : Obtine lista filtrata
    * T3 : Obtine lista sortata
    * T4 : Afiseaza lista

* F9:
    * T1 : Input interval, task
    * T2 : Obtine lista trunchiata
    * T3 : Calculeaza media listei
    * T4 : Afiseaza rezultatul 

* F10:
    * T1 : Input interval, task
    * T2 : Obtine lista trunchiata
    * T3 : Calculeaza minimul listei
    * T4 : Afiseaza rezultatul 

* F11:
    * T1 : Input interval, task
    * T2 : Obtine lista trunchiata
    * T3 : Filtreaza lista
    * T4 : Afiseaza lista

* F12:
    * T1 : Input task, scor
    * T2 : Obtine lista filtrata
    * T3 : Afiseaza lista

* F13:
    * T1 : Input task, scor
    * T2 : Obtine lista filtrata
    * T3 : Afiseaza lista

* F14:
    * T1 : Sterge ultimul element din lista cu toate starile