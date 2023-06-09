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

int eventsToConsume = 0;

//----------------------------------------------------------General
// WARNING: do not change this function
enum EventType GenerateEventType() { return rand() % 3; }

void CheckArguments(int argc, char **argv) {
  // check the input introduced by the user, manages argument and handles possible user errors
  int x;
  float xf;

  if (argc < 2) {
    printf("Argument is missing (integer)!\n");
    return;
  } 
  else if (argc > 2) {
    printf("Too much arguments. You must pass only one (integer).\n");
    return;
  }

  x = atoi(argv[1]); // Convert argument to integer
  xf = atof(argv[1]);

  if (x != xf) { //If argument was decimal, for instance
    printf("You entered %f, but will be treated as %d\n", xf, x);
  }

  // Convert x to positive if negative
  if (x < 0) {
    printf("Argument passed was negative, will be treated as positive int\n");
    x *= -1;
  } 
  else if (x == 0) {
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
    printf("%d", booksCurrent->year);
    booksCurrent = booksCurrent->next;
    printf("\n");
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
    if (strcmp(current->author, author) == 0) {
			// if same author, place after this book
      return current;
    }
    else {
      current = current->next;
    }
  }
  return current; // the last book in the list
}

// function to simulate a sorting of books
void SimulateSortingBooks(struct Book *book) {
  // places the given book in the correct place in the list of books
  struct Book *booksCurrent = SearchBook(book->author);
  
  if (booksCurrent == NULL){ // list is empty
    booksHead = book;
    booksHead->next = NULL;
    eventsToConsume--;
    return;
  }

	// place after the book provided by SearchBook()
  book->next = booksCurrent->next;
  booksCurrent->next = book;

  eventsToConsume--;
}

// function to remove a list of books at the end of the program
void RemoveSortingBooks() {
  // frees the memory for all books in the list
  struct Book *current, *to_remove;
  int n = 0;

  printf("\tRemoving books...\n");
	if (booksHead == NULL)
	{
		printf("\t\tThe list of books is already empty\n");
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
    printf("\t\t1 books has been removed\n");
  else
    printf("\t\t%d books have been removed\n", n);
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
  
  while(i < NUMBER_STACKS) { //is repeated for each stack
    plateCurrent = Top_ofPlateStacks[i];
    printf("stack %d\n", i);
		if(plateCurrent == NULL) { //if either stack is empty
			printf("The stack of ");
			switch (i){
				case dinner_plate:
					printf("dinner plates");
					break;
				case soup_plate:
					printf("soup plates");
					break;
				case dessert_plate:
					printf("dessert plates");
					break;
			}
			printf(" is empty\n");
			i++;
			continue;
		}
    while(plateCurrent != NULL) { //prints the color of each plate from each stack
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
      plateCurrent = plateCurrent->next;
    }
    i++;
  }
}

// function to remove a given stack when its MAX_CAPACITY is reached
void RemoveStack(enum PlateType type) {
  struct Plate *temp;

  if (Top_ofPlateStacks[type] == NULL) { // stack is empty
		return;
  }
  while (Top_ofPlateStacks[type] != NULL) {
		// remove the top plate until the stack is empty
    temp = Top_ofPlateStacks[type]->next;
  	free(Top_ofPlateStacks[type]);
  	Top_ofPlateStacks[type] = temp;
  }
  
  CurrentState[type] = 0;
}

// put given plate at the top of the given stack
void PushPlate(struct Plate *plate, enum PlateType type)
{
	if (Top_ofPlateStacks[type] == NULL) // stack is empty
	{
		Top_ofPlateStacks[type] = plate;
		Top_ofPlateStacks[type]->next = NULL;
    CurrentState[type] += 1;
		return;
	}
	// place the plate at the top
	plate->next = Top_ofPlateStacks[type];
	Top_ofPlateStacks[type] = plate;

  CurrentState[type] += 1;
}

// function to simulate putting a generated plate to a corresponding stack
void SimulateManagingPlate(struct Plate *plate) {
  int plateType = plate->type;

  PushPlate(plate, plateType); // first place the plate
  if (CurrentState[plateType] == MAX_CAPACITY) {
		// then remove the stack if reached max_capacity
    RemoveStack(plateType);
  }

  eventsToConsume--;
}

// function to clean all stacks before the end of the program
void CleanPlateStacks() {
  int n = 0;

  printf("\tCleaning all stacks of plates...\n");

	// remove all stacks
  for (int i = 0; i < NUMBER_STACKS; i++) {
    n += CurrentState[i];
    RemoveStack(i);
  }
  
  if (n == 1)
    printf("\t\t1 plate has been removed\n");
  else
    printf("\t\t%d plates have been removed\n", n);
  
}

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
void PrintShopping() {
  struct Shopping * current = queueFirst; 
  while (current != NULL) 
  {   
    printf("ID: %d, number of things to buy: %d\n", current->robot_id, current->numberThingsToBuy);
    current = current->next; 
  } 
	printf ("\n");
}

// function to add a robot to a shopping queue
void AddToQueue(struct Shopping *shopping) {

	if (queueFirst == NULL) // queue empty
	{
		queueFirst = shopping;
		queueFirst->next = NULL;
		queueLast = queueFirst;
		return;
	}

	// add robot to the end
	queueLast->next = shopping;
	queueLast = shopping;
	queueLast->next = NULL;
}

// function to remove a robot from the queue and serve it
// it may return the number of things to buy to simulate the time
int Dequeue() {
  struct Shopping *temp;
  int thingsToBuy;
	if (queueFirst == NULL) { // queue empty
		return 0;
  }
  
	if (queueFirst->next == NULL) // only 1 robot in the queue
	{
    thingsToBuy = queueFirst->numberThingsToBuy;
		free(queueFirst);
		queueFirst = NULL;
		queueLast = NULL;
		return thingsToBuy;
	}

  thingsToBuy = queueFirst->numberThingsToBuy;
	// remove first robot in the queue
	temp = queueFirst->next;
	free(queueFirst);
	queueFirst = temp;
  return thingsToBuy;
}

// function to simulate the time the robot is in the queue
void UpdateShopping() {
  if (eventsToConsume <= 0){
    eventsToConsume = Dequeue();
  }
}

// function to simulate a robot going for shopping
void SimulateGoForShopping(struct Shopping *shopping) {
  AddToQueue(shopping);
  UpdateShopping();

  eventsToConsume--;
}

// function to clean shopping queue before the end of the program
void CleanShoppingQueue() {
  int n = 0;
  printf("\tCleaning shopping queue...\n");
  
  while (queueFirst != NULL) {
    n++;
    Dequeue();
  }
  if (n == 1)
    printf("\t\t1 robot has been removed\n");
  else
    printf("\t\t%d robots have been removed\n", n);
  
}

//----------------------------------------------------------main
// This is the main loop of the program.
// It generates and consumes events.
void SimulationLoop() {
  // declare and initialize necessary variables
  int i;
  enum EventType currentEvent;
  struct Book *currentBook;
  struct Plate *currentPlate;
  struct Shopping *currentShopping;

  InitStacks();
  
  for (i = 0; i < EventNumbers; i++) {
    // generate event type
    currentEvent = GenerateEventType();
    switch (currentEvent) { // depending on the generated event type:
			case book: // event type 0:
				currentBook = GenerateBook(); // generate book
				SimulateSortingBooks(currentBook); // Simulate sorting books
				break;
			case plate: // event type 1:
				currentPlate = GeneratePlate(); // generate plate
				SimulateManagingPlate(currentPlate); // Simulate managing plate
				break;
			case shopping: // event type 2:
				currentShopping = GenerateShopping(); // generate shopping
				SimulateGoForShopping(currentShopping); // Simulate shopping
				break;
    }
  }

  // CLEANING THE SIMULATION
  printf("STATISTICS WHEN CLEANING THE SIMULATION:\n");
  RemoveSortingBooks();
  CleanPlateStacks();
  CleanShoppingQueue();
}

int main(int argc, char **argv) {
  printf("Starting... \n");
  CheckArguments(argc, argv);

  if (EventNumbers == -1)
    return 1;

  SimulationLoop();
  return 0;
}