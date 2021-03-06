//main.cpp
/*
This program contains a class called "GTree", which gives the programmer an object to use, also called "GTree", which works as a regular Tree should.
A Tree is a kind of binary tree, made up of nodes. Each node points to two (2) other nodes, and each of those point to two (2) other nodes, etc.
The program first allows the user to enter up to 100 different number inputs, then it will create a GTree (like a Tree, except I made it) and sort the numbers such that each parent is bigger than their two children. The program can handle numbers from one (1) to one-thousand (1000).

The above description is nearly exactly copied over from my previous Tree project because this project does nearly exactly the same thing. 
This time, however, you are allowed to add, remove, and search for specific numbers throughout the Tree. Also, the medium for the inputs will now be Node structs (named GNode, of course) instead of an int array, sorted using some clever math

void addToTree(GTree*, int) - Put a number into the tree in the place that it should be in.
int* addFunction() - Get the user to put in their input(s) to add to the tree, and then print out the parsed version.
int* removeFunction() - Get the user to put in their input(s) that they want removed from the tree, and then print out the parsed version.
int searchFunction() - Get the user to input the number that they want to search the tree for.
void search(GTree*, int) - Print out the amount of times that the inputted number appears in the tree with some random UI stuff added in to make the info understandable.
bool confirmInput() - Simply asks the user for a yes or no response (y/n). Purely for modularity purposes.

@author Greggory Hickman, March 2020
@version 1.0
 */

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>

#include "BattlePack.h"
#include "GTree.h"

using namespace std;

/*
void insertToken(GTree& tree, int address, int newToken);
GTree maxTreeSort(int*);
void printTree(GTree*);
*/
void addToTree(GTree*, int);
int* addFunction();
int* removeFunction();
int searchFunction();
void search(GTree*, int);
bool confirmInput();

int main() {
	
	GTree tree;
	//Define some variables and objects that we will need throughout the program
	bool quit = false;
	int* numbersToAdd; //Going to be the current number(s) to add to the tree
	
	//Greetingd, and an introduction to what a tree is in case the user doesn't know
	cout << "Welcome to Gregg\'s fabulous Tree program!" << endl <<
	"This program is a kind of number sorter which sorts the numbers given to it in a tree formation." << endl <<
	"Each number will always have a lower number branching off to the left, and a higher number branching off to the right." << endl;
	
	//The loop that the majority of the program takes place in
	while (!quit) {
		char cmdin[LEN];
	
		//Ask how the user wants to input the numbers
		cout << "Type \"add\" to add a number" << endl << 
		"Type \"remove\" to remove a number" << endl << 
		"Type \"search\" to find out how many times a number appears within the tree" << endl << 
		"Type \"print\" to print out the tree into console" << endl << 
		"Type \"exit\" to kill the program" << endl;
	
		cout << "> ";
		cin >> cmdin; cin.clear(); cin.ignore(LEN, '\n');
		
		cout << endl;
		bool haveInput = false;
		
		//Stay in this section until we have the input
		while (!haveInput) {
			//If the user typed "add"
			if (strcmp(cmdin, "add") == 0 || strcmp(cmdin, "a") == 0 || strcmp(cmdin, "A") == 0) {
				//Call the add function
				numbersToAdd = addFunction();
				//Confirm the input
				haveInput = confirmInput();
			}
			//If the user typed "remove"
			else if (strcmp(cmdin, "remove") == 0 || strcmp(cmdin, "r") == 0 || strcmp(cmdin, "R") == 0) {
				//Call the remove function
				numbersToAdd = removeFunction(); //Pretend that numbersToAdd now says numbersToRemove
				//Confirm the input
				haveInput = confirmInput();
			}
			else if (strcmp(cmdin, "search") == 0 || strcmp(cmdin, "s") == 0 || strcmp(cmdin, "S") == 0) {
				//Call the search function
				int numberToSearchFor = searchFunction();
				//Tell the user how many times that number appears in the tree
				search(&tree, numberToSearchFor);
				break;
			}
			else if (strcmp(cmdin, "print") == 0 || strcmp(cmdin, "p") == 0 || strcmp(cmdin, "P") == 0) {
				//Print the tree
				tree.printTree();
				break;
			}
			//If the user typed "exit"
			else if (strcmp(cmdin, "exit") == 0 || strcmp(cmdin, "e") == 0 || strcmp(cmdin, "E") == 0) {
				//Exit the program
				cout << "Closing program..." << endl;
				return 0;
			}
			//If the user typed an invalid command
			else {
				cout << "Command \"" << cmdin << "\" not recognized" << endl;
				break;
			}
			cout << endl;
		}
		
		//Now, update the tree
		//If the user previously told the program to add (a) number(s)
		if (strcmp(cmdin, "add") == 0 || strcmp(cmdin, "a") == 0 || strcmp(cmdin, "A") == 0) {
			//Sort each number into the tree one by one
			for (int i = 0; numbersToAdd[i] > 0; i++) {
				//Set the current pointer back to the head
				tree.resetCurrent();
				addToTree(&tree, numbersToAdd[i]);
			}
		}
		//If the user previously told the program to remove (a) number(s)
		else if (strcmp(cmdin, "remove") == 0 || strcmp(cmdin, "r") == 0 || strcmp(cmdin, "R") == 0) {
			//Sort each number into the tree one by one
			for (int i = 0; numbersToAdd[i] > 0; i++) {
				//Set the current pointer back to the head
				int* treeGuts = tree.flushTree();
				//for (int i = 0; treeGuts[i] != 0; i++) cout << treeGuts[i] << ", ";
				for (int j = 0; j < BIGLEN; j++) {
					if (treeGuts[j] == numbersToAdd[i]) {
						treeGuts[j] = -1;
					}
				}
				for (int j = 0; j < BIGLEN; j++) {
					if (treeGuts[j] != -1) {
						addToTree(&tree, treeGuts[j]);
					}
				}
				cout << endl;
			}
		}
	}
	
	return 0;
}

void search(GTree* tree, int numberToSearchFor) {
	cout << tree->numberCount(numberToSearchFor) << " instances of the number \"" << numberToSearchFor << "\" found." << endl << endl;
	return;
}

int searchFunction() {
	char* inputString = new char[BIGLEN];
	
	cout << "Reading from console..." << endl <<
	"Enter the number you would like to search for." << endl;
	
	//Read in the input from console and put it into inputString
	cout << "Search> ";
	cin.getline(inputString, BIGLEN);
	
	//Parse the char* input into an int* with each number separated
	int* numberToSearchFor = parseZTCString(inputString, 32);
	delete(inputString); //We don't need this anymore.

	//At this point, we have our number that we want to search for. We only want the first one. The rest of them must be incinerated.
	int out = numberToSearchFor[0];
	delete(numberToSearchFor); //INCINERATE ALL OF THE UNNECESSARY NUMBERS! MWAHAHAHA!!!!
	return out;
}

bool confirmInput() {
	char confirm;
	bool haveInput = false;
	
	cout << "Confirm Input? (y/n)" << endl;
	cout << "> ";
	cin >> confirm; cin.clear(); cin.ignore(LEN, '\n');
		
	if (confirm == 'y') haveInput = true;
	
	return haveInput;
}

int* addFunction() {
	char* inputString = new char[BIGLEN];
	
	cout << "Reading from console..." << endl <<
	"Enter the number you would like to add. If you have multiple, separate them with spaces." << endl;
	
	//Read in the input from console and put it into inputString
	cout << "Add> ";
	cin.getline(inputString, BIGLEN);
	
	//Parse the char* input into an int* with each number separated
	int* numbersToAdd = parseZTCString(inputString, 32);
	delete(inputString);

	//At this point, we have our input (inputString).
	cout << "Input: ";
	for (int i = 0; numbersToAdd[i] != 0; i++) {
		cout << numbersToAdd[i] << " "; //Print all int-ified inputs
	}
		cout << endl;
	
	return numbersToAdd;
}

void addToTree(GTree* tree, int newToken) {
	//If the head is undefined
	if (tree->headIsEmpty()) {
		//Set the head to be the new token
		tree->setHead(newToken);
		return;
	}
	while (true) {
		//If the new token is smaller than current's token
		if (newToken < tree->getCurrent()) {
			//If the left child is defined
			if (!(tree->leftIsEmpty())) {
				tree->moveLeft(); //Move current one spot to the left
			}
			//If the left child is not defined
			else {
				tree->setLeft(newToken); //Set the left child to be the new token
				break;
			}
		}
		//If the new token is larger than or equal to current's token
		if (newToken >= tree->getCurrent()) {
			//If the right child is defined
			if (!(tree->rightIsEmpty())) {
				tree->moveRight(); //Move current one spot to the right
			}
			//If the right child is not defined
			else {
				tree->setRight(newToken); //Set the right child to be the new token
				break;
			}
		}
	}
	return;
}

int* removeFunction() {
	char* inputString = new char[BIGLEN];
	
	cout << "Reading from console..." << endl <<
	"Enter the number you would like to remove. If you have multiple, separate them with spaces." << endl;
	
	//Read in the input from console and put it into inputString
	cout << "Remove> ";
	cin.getline(inputString, BIGLEN);

	//Parse the char* input into an int* with each number separated
	int* numbersToRemove = parseZTCString(inputString, 32);

	//At this point, we have our input (inputString).
	cout << "Input: ";
	for (int i = 0; numbersToRemove[i] != 0; i++) {
		cout << numbersToRemove[i] << " "; //Print all int-ified inputs
	}
		cout << endl;
	
	return numbersToRemove;
}


/*
void insertToken(GTree* tree, int address, int newToken) {
	//cout << "New Token: " << newToken << ", ";
	//printTree(tree);
	
	//Replace the current token at address with input[i]
	int oldToken = tree->get(address);
	tree->set(address, newToken);
	
	//Start the cycle again if necesary
	//If the old token wasn't 0 (this is here because without it, the zeroes all the way down the chain would compare themselves to each other needlessly, which would be super-mega inefficient)
	if (oldToken != 0) {
		//If either child doesn't exist yet, set the oldToken as the new child
		if (tree->getLeft(address) == 0) {
			tree->setLeft(address, oldToken);
			return;
		}
		if (tree->getRight(address) == 0) {
			tree->setRight(address, oldToken);
			return;
		}
		
		//Otherwise, start the cycle again
		insertToken(tree, (address + 1) * 2 - 1, oldToken);
	}
}

GTree maxTreeSort(int* input) {
	
	GTree tree(BIGLEN);
	//For future reference, the "boss parent" is the very first node; the one which all others lead back to
	//
	//For every token in input...
	for (int i = 0; input[i] != 0; i++) { //i is iterator for input
		for (int j = 0; j < LEN; j++) { //j is iterator for tree
			//... and go through the tree from left to right until a token of lower magnitude than the current number from input is found.
			//At which point replace the new token with the old, then recursively sort down the tree from that point.
			if (input[i] >= tree.get(j)) {
				//Sort the new token and all of its children
				insertToken(&tree, j, input[i]);
				break;
			}
		}
	}
	
	return tree;
}


*/

/*
int* parseInput(char* inputString) {
	char* current = new char[LEN];
	int* numbersToAdd = new int[LEN];
	
	//Clear pesky leftover ram from pointer arrays
	
	clearCString(current, LEN);
	for (int i = 0; i < LEN; i++) {
		numbersToAdd[i] = 0;
	}
	
	//cout << "Starting inputString: " << inputString << endl;
	//cout << "Starting current: " << current << endl;
	
	//Parse the input
	int j = 0; //Iterator for current
	int k = 0; //Iterator for numbersToAdd
	for (int i = 0; i < BIGLEN + 1; i++) {
		//If we have hit the 100 number max limit
		if (k >= LEN - 1) {
			break;
		}
		//If is number
		if (inputString[i] >= 48 && inputString[i] <= 57) {
			//Add the digit to the end of the current multi-digit number
			current[j] = inputString[i];
			j++;
		}
		//If is space
		else if (inputString[i] == 32) {
			if (j != 0) {
				//cout << "Space: " << current << endl;
				//current contains the number that we want to convert to an integer
				int next = 0;
				
				//Iterate backwards through current
				for (int l = j - 1; l >= 0; l--) {
					//Convert the char* to int one unit place at a time by adding each value * 10^place. For example, when in the hundred's place, place = 2.
					next += (current[l] - 48) * round(pow(10, j - l - 1));
				}
				//cout << "Next: " << next << endl;
				numbersToAdd[k] = next;
				j = 0;
				k++;
				
				clearCString(current, LEN);
			}
		}
		//If is null
		else if (inputString[i] == 0) {
			if (j != 0) {
				//cout << "Null: " << current << endl;
				//current contains the number that we want to convert to an integer
				int next = 0;
				
				//Iterate backwards through current
				for (int l = j - 1; l >= 0; l--) {
					//Convert the char* to int one unit place at a time by adding each value * 10^place. For example, when in the hundred's place, place = 2.
					next += (current[l] - 48) * round(pow(10, j - l - 1));
				}
				numbersToAdd[k] = next;
				break;
			}
		}
	}
	delete(current);
	
	return numbersToAdd;
}
*/



