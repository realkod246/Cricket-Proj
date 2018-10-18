#ifndef STACK_H
#define STACK_H
#include "Node.h"

class Stack
{
	  private:
		Node* head;
	  
	  public:
		// Constructor
		Stack(){head = NULL;}
		
		void purge() {head = NULL;}
	    
		//Mutator functions
		void push(int, string, string, int, string, int);
		string pop();
	    
		// accessor functions
		string getSize();
		bool isEmpty(){return (head == NULL)?true:false;}
		string displayAll();
		string getHead();
		string getTail();   
};

void Stack::push(int rank, string name, string natinality, int score, string opponent, int year)
{
	Node* temp = new Node(rank, name, natinality, score, opponent, year);//Name, Natinality, Score, Opponent, Year);

	if(head == NULL)	//List is empty
	{
		head = temp;
		return;
	}
	
	Node* cur = head;
	
	//walk down to the last node in the list
	while(cur->getNext() != NULL)
		cur = cur ->getNext();
	
	//Last node
	cur->setNext(temp);
}

string Stack::pop()
{
	string str = "";
	
	if (head == NULL)       // the stack is empty
		return ("\n\tStack is empty...\n");
        
	if(head-> getNext() == NULL){	//List has only one node 
		str.append(head->getRecord());
		delete head;
	}
	else{
		Node* prev = head;
		Node* cur = head->getNext();
		
		while(cur->getNext() != NULL){
			prev = cur;
			cur = cur->getNext();
		}
		str.append(cur->getRecord());
		prev->setNext(NULL);
		delete cur;
	}
	return str;
}

string Stack::getSize()
{
    Node* cur = head;
    int count = 0;
    while (cur != NULL)
    {
        cur = cur->getNext();
        count++;
    }
    return to_string(count);
}

string Stack::displayAll()
{
	string str = "";

	if(head == NULL)
		return ("\n\tStack is empty...\n");
  
	Node* cur = head;
	while(cur != NULL){
		str.append(cur->getRecord());
		str.append("\n");
		cur = cur->getNext();
	}
	str.append("\n\n");
	return str;
}

string Stack::getHead()
{
	string str = "";
	
	Node* cur = head;
	if (head == NULL)
		return ("\nThe stack is empty...");
	else
		return str.append( head->getRecord());
}

string Stack::getTail()
{
	string str = "";
	
	if (head == NULL)
		return ("\nThe stack is empty...");
	else
	{
		Node* cur = head;
		while (cur->getNext() != NULL)
			cur = cur->getNext();
	    
		return str.append(cur->getRecord());
	}
}
#endif /* Stack_H */