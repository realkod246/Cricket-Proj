#ifndef Queue_H
#define Queue_H

#include <cstddef>
#include<iostream>
#include "Node.h"
using namespace std;

class Queue{
	private:
		Node* head;
	
	public:
		//con
		Queue(){head = NULL;}
		
		void purge() {head = NULL;}
		
		//Mutator Function
		void enqueue(int, string, string, int, string, int);
		string dequeue();
		
		//Accessor Function
		bool isEmpty(){return (head == NULL)?true:false;}
		string displayAll();
		string getHead();
		string getTail();
		
		int size();
};

void Queue::enqueue(int rank, string name, string nationality, int score, string opponent, int year)
{

	Node* temp = new Node(rank, name, nationality, score, opponent, year);
	
	if(head == NULL){			//Queue is empty
		head = temp;
		return;
	}
	Node* cur = head;
	
	//walk down to the last node in the queue
	while(cur->getNext() != NULL)
		cur = cur ->getNext();
	
	//Last node
	cur->setNext(temp);
}

string Queue::dequeue()
{
	string str = "";
	
	if(head == NULL)		//Queue is empty
		return ("\n\tQueue is empty...\n");
	
	str.append(head->getRecord());
	Node* temp = head;
	head = head->getNext();
	delete temp;	
	
	return str;
}

string Queue::getHead()
{
	string str = "";
	
	Node* cur = head;
	if(cur == NULL)
		return ("\n\tQueue is empty...\n");
	else
		return str.append(cur->getRecord()); 
}

string Queue::getTail()
{
	string str = "";
	
	if (head == NULL)
		return ("\nThe queue is empty...");
	else
	{
		Node* cur = head;
		while (cur->getNext() != NULL)
			cur = cur->getNext();
	    
		return str.append(cur->getRecord());
	}
}

int Queue::size(){
	Node* cur = head;
	int count = 0;
	while(cur != NULL){
		cur = cur->getNext();
		count++;
	}
	return count;
}
string Queue::displayAll(){
	Node* cur = head;
	string str = "";
	
	while(cur != NULL){
		str.append(cur->getRecord());
		str.append("\n");
		cur = cur->getNext();
	}
	str.append("\n\n");
	
	return str;
}
#endif