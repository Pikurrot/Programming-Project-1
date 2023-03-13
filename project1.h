/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 1

project1.h
Header of all necessary data structures required by the project 1.
It also contains enumeration types and additional variables,
arrays for managing data structures and their initial values
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum EventType { book = 0, plate = 1, shopping = 2 };

//--------------------------------------------------------------------------Books
// predefined authors of books; there are 8 books
char authors[8][20] = {{"Philip Roth"},        {"Dan Brown"},
                       {"Charlotte Bronte"},   {"Stephenie Meyer"},
                       {"Katarzyna Grochola"}, {"J.K. Rowling"},
                       {"Veronica Roth"},      {"Yann Martel"}};

// predefined titles of books; there are 8 books
char titles[8][20] = {{"Nemesis"},    {"Origin"},        {"Jane Eyre"},
                      {"The host"},   {"Zielone drzwi"}, {"Harry Potter"},
                      {"Divergente"}, {"Life of Pi"}};

// a pointer to the head of the book list
struct Book *booksHead = NULL;

struct Book {
  char author[20];
  char title[20];
  int year;
  struct Book *next;
};

//--------------------------------------------------------------------------Plates

#define NUMBER_STACKS 3
#define MAX_CAPACITY 3

enum PlateType { dinner_plate = 0, soup_plate = 1, dessert_plate = 2 };
enum Colors { white = 0, green = 1, yellow = 2, beige = 3 };

// There are 3 different stacks, each one for each type of plate
// Here we create a static array to have 3 pointers to a top element of each
// stack
struct Plate *Top_ofPlateStacks[NUMBER_STACKS];

// Each stack has a current number of plates
// At the beginning each stack has 0 plates
// Here we create a static array where we will store a number of plates for each
// stack We assume here that the capacity of each stack is MAX_CAPACITY (which
// is 3)
int CurrentState[NUMBER_STACKS];

struct Plate {
  enum PlateType type;
  enum Colors color;
  struct Plate *next;
};

//--------------------------------------------------------------------------Shopping

// a pointer to the first element of the shopping list
struct Shopping *queueFirst = NULL;
// a pointer to the last element of the shopping list
struct Shopping *queueLast = NULL;

// global variable that is used for assigning a next identifier
// when a next robot is generated
int nextRobotID = -1;

struct Shopping {
  int numberThingsToBuy;
  int robot_id;
  struct Shopping *next;
};
