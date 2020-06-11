#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
#include<conio.h>
using namespace std;

#ifndef QUEUE_H
#define QUEUE_H
////structure used to store data of any character
struct Tree_node
{
	char a;												//for storing corresponding character
	int frequency;										//for storing corresponding character frequency present in file
	Tree_node * left;									//used when making tree
	Tree_node * right;
	Tree_node*next;										//used in making priority queue
	string code;										//used for storing respective code of the character
};

///////// priority queue class /////////////
class   Priority_queue
{
	Tree_node * front;
	Tree_node *rear;
public:
	////constructor initializing front and rear with NULL
	Priority_queue::Priority_queue();

	/////destructor for PRIORITY QUEUE CLASS which destructs every node if called.
	Priority_queue::~ Priority_queue();

	/////This function add nodes to PRIORITY QUEUE CLASS in arranged or ascending order of frequencies.
	void Priority_queue::enqueue(Tree_node *b);

	///////function used to dequeue a node from queue ,it helps in making a tree.it dequeues the node with least frequency 
	Tree_node *Priority_queue:: dequeue();

	////////// function  that helps to make a binary heap out of priority queue /////////// 
	Tree_node *Priority_queue:: build_tree();
	
	//////////// display function to display all nodes character and frequencies in a priority queue /////////////
	void Priority_queue::display();
	
	//////function to save array of characters with their frequencies and used for decoding
	void Priority_queue::saveFile( Tree_node* a[],ofstream &outFile );

	///function to read data from file to store into array and make queue.
	void Priority_queue::readTextFile( ifstream &inFile );
};

#endif