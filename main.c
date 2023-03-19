/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 1

Simulator - main program
DUBTES:
1. must books be organized alphabetically by author?
2. color of plates
3. void InitStacks() and *Top_ofPlateStacks[NUMBER_STACKS]
4. events consumed (events of the same type are consumed together or we can consume first 1 book, then 1 plate, then 1 book...?)
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
  return current; // the last book in the list
}

// function to simulate a sorting of books
void SimulateSortingBooks(struct Book *book) {
  // places the given book in the correct place in the list of books
  struct Book *booksCurrent = SearchBook(book->author);
  
  if (booksCurrent == NULL){
    booksHead = book;
    booksHead->next = NULL;
    return;
  }

  book->next = booksCurrent->next;
  booksCurrent->next = book;
  PrintBooks(); //test print book list
}

// function to remove a list of books at the end of the program
void RemoveSortingBooks() {
  // frees the memory for all books in the list
  struct Book *current, *to_remove;
  int n;

  printf("Removing books...\n");
	if (booksHead == NULL)
	{
		printf("The list of books is already empty\n");
		return;
	}

  current = booksHead;
  while (current != NULL){
    // Free the memory until reached the last book
    to_remove = current;
    current = current->next;
    free(to_remove);
    n++;
  }
  booksHead = NULL;
  if (n == 1)
    printf("\t1 books has been removed\n");
  else
    printf("\t%d books have been removed\n", n);
}

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
void InitStacks() {
  int i;
  for (i = 0; i < NUMBER_STACKS; i++) {
    Top_ofPlateStacks[i] = NULL;
    CurrentState[i] = 0;
  }
}
  
// function to print all stacks of different plates
void PrintPlates() {
  int i = 0;
  struct Plate *plateCurrent;
  enum PlateType plateType;
  enum Colors plateColor;
  
  while(i < NUMBER_STACKS) {
    plateCurrent = Top_ofPlateStacks[i];
    
    while(plateCurrent != NULL) {
      if(plateCurrent == NULL) {
        plateType = plateCurrent->type;
        printf("The stack of ");
        switch (plateType){
          case dinner_plate:
            printf("dinner plates");
            break;
          case soup_plate:
            printf("soup plate");
            break;
          case dessert_plate:
            printf("dessert plate");
            break;
        }
        printf(" is empty\n");
      }
  
      else{
        plateColor = plateCurrent->color;
        switch (plateColor){
          case white:
            printf("white");
            break;
          case green:
            printf("green");
            break;
          case yellow:
            printf("yellow");
            break;
          case beige:
            printf("beige");
            break;
        }
        printf(" plate\n");
      }
  
      plateCurrent = plateCurrent->next;
    }
    i++;
  }
}

// function to remove a given stack when its MAX_CAPACITY is reached
void RemoveStack(enum PlateType type) {
  struct Plate *temp;

  if (Top_ofPlateStacks[type] == NULL) {
		return;
  }
  while(Top_ofPlateStacks[type] != NULL) {
    temp = Top_ofPlateStacks[type]->next;
  	free(Top_ofPlateStacks[type]);
  	Top_ofPlateStacks[type] = temp;
  }
  
  CurrentState[type] = 0;
  
  PrintPlates();
}

// put given plate at the top of the given stack
void PushPlate(struct Plate *plate, enum PlateType type)
{
	if (Top_ofPlateStacks[type] == NULL)
	{
		Top_ofPlateStacks[type] = plate;
		Top_ofPlateStacks[type]->next = NULL;
    CurrentState[type] += 1;
    printf("1. Pushing plate to stack %d, now there are %d plates.\n", type, CurrentState[type]);
		return;
	}
	plate->next = Top_ofPlateStacks[type];
	Top_ofPlateStacks[type] = plate;

  CurrentState[type] += 1;
  printf("2. Pushing plate to stack %d, now there are %d plates.\n", type, CurrentState[type]);
}

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
  int i;
  enum EventType currentEvent;
  struct Book *currenBook;
  struct Plate *currenPlate;

  for (i = 0; i < EventNumbers; i++) {
    currentEvent = GenerateEventType();
    switch (currentEvent) {
    case book:
      currenBook = GenerateBook();
      break;
    case plate:
      currenPlate = GeneratePlate();
      break;
    case shopping:
			GenerateShopping();
      break;
    }
  }

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