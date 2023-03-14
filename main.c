/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 1

Simulator - main program
*/

#include <stdio.h>
#include <stdlib.h>

#include "project1.h" // header with all data structures

int EventNumbers = -1;

//----------------------------------------------------------General
// WARNING: do not change this function
enum EventType GenerateEventType() { return rand() % 3; }

void CheckArguments(int argc, char **argv) {
  // check the input introduced by the user
  int x;
  float xf;

  if (argc < 2) {
    printf("Argument is missing (integer)!\n");
    return;
  } else if (argc > 2) {
    printf("Too much arguments. You must pass only one (integer).\n");
    return;
  }

  x = atoi(argv[1]); // Convert argument to integer
  xf = atof(argv[1]);

  if (x != xf) {
    printf("You entered %f, but will be treated as %d\n", xf, x);
  }

  // Convert x to positive if negative
  if (x < 0) {
    printf("Argument passed was negative, will be treated as positive int\n");
    x *= -1;
  } else if (x == 0) {
    printf("You must enter an integer (over 0)\n");
    return;
  }

  EventNumbers = x;
}

//----------------------------------------------------------Books
// WARNING: do not change this function
struct Book *GenerateBook() {
  // reserve memory for a book
  struct Book *book = malloc(sizeof(struct Book));
  int bookNum = rand() % 8;
  // initialize the book's fields
  strcpy(book->author, authors[bookNum]);
  strcpy(book->title, titles[bookNum]);
  int year = rand() % 40 + 1980;
  book->year = year;
  return book;
}

// function to print a list of books
void PrintBooks() {
  struct Book *booksCurrent = booksHead;
  while (booksCurrent != NULL) {
    printf("%s=>", booksCurrent->author);
    printf("%s=>", booksCurrent->title);
    printf("%d=>", booksCurrent->year);
    booksCurrent = booksCurrent->next;
  }
  printf("\n");
}

// function to search for a book
struct Book *SearchBook(char author[20]) {
  // returns the pointer to the book where the given book must be after (it will
  // be after the book of the same author)
  if (booksHead == NULL) // list is empty
    return NULL;

  struct Book *current = booksHead;
  while (current->next != NULL) {
    if (current->author == author)
      return current;
    else
      current = current->next;
  }
  return current; // NULL; // not found
}

// function to simulate a sorting of books
void SimulateSortingBooks(struct Book *book) {}

// function to remove a list of books at the end of the program
void RemoveSortingBooks() {}

//----------------------------------------------------------Stack
// WARNING: do not change this function
struct Plate *GeneratePlate() {
  // reserve memory for a Plate
  struct Plate *plate = malloc(sizeof(struct Plate));
  // initialize the plate's fields
  enum PlateType type = rand() % 3;
  enum Colors color = rand() % 4;
  plate->type = type;
  plate->color = color;
  return plate;
}

// function to initialize all stacks of plates
void InitStacks() {}

// function to print all stacks of different plates
void PrintPlates() {}

// function to remove a given stack when its MAX_CAPACITY is reached
void RemoveStack(/*...*/) {}

// function to simulate putting a generated plate to a corresponding stack
void SimulateManagingPlate(struct Plate *plate) {}

// function to clean all stacks before the end of the program
void CleanPlateStacks() {}

//----------------------------------------------------------Shopping
// WARNING: do not change this function
struct Shopping *GenerateShopping() {
  // reserve memory for a Shopping
  struct Shopping *shopping = malloc(sizeof(struct Shopping));
  // initialize the shopping's fields
  int n = rand() % 5 + 1;
  shopping->numberThingsToBuy = n;
  nextRobotID++;
  shopping->robot_id = nextRobotID;
  return shopping;
}

// function to print a list of robots in a shopping queue
void PrintShopping() {}

// function to add a robot to a shopping queue
void AddToQueue(struct Shopping *shopping) {}

// function to remove a robot from the queue and serve it
// it may return the number of things to buy to simulate the time
int Dequeue() {}

// function to simulate the time the robot is in the queue
void UpdateShopping(/*...*/) {}

// function to simulate a robot going for shopping
void SimulateGoForShopping(struct Shopping *shopping) {}

// function to clean shopping queue before the end of the program
void CleanShoppingQueue(/*...*/) {}

//----------------------------------------------------------main
// This is the main loop of the program.
// It generates and consumes events.
void SimulationLoop(int EventNumbers) {
  // declare and initialize necessary variables

  InitStacks();

  for (int i = 0; i < EventNumbers; i++) {
    // generate event type
    // depending on the generated event type:
    // event type 0:
    // generate book
    // Simulate sorting books
    // event type 1:
    // generate plate
    // Simulate managing plate
    // event type 2:
    // generate shopping
    // Simulate shopping
    // UpdateShopping
  }
  // CLEANING THE SIMULATION
}

int main(int argc, char **argv) {
  printf("Starting... \n");
  CheckArguments(argc, argv);

  if (EventNumbers == -1)
    return 1;

  SimulationLoop(EventNumbers);
  return 0;
}