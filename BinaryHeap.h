#ifndef BINHEAP_H
#define BINHEAP_H
#include "Node.h"

class BinaryHeap
{
        private:
                vector <Node> heap;

        
        public:
                BinaryHeap(){heap.resize(1);}
                void purge() {heap.resize(0);}
    
                void addMaxHeap(int, string, string, int, string, int);               // Add to MaxHeap
                void addMinHeap(int, string, string, int, string, int);               // Add to MinHeap
                void maxHeapify(unsigned int);      // Heapify MaxHeap
                void minHeapify(unsigned int);      // Heapify MinHeap
                void deleteMaxHeapVal(int);         // Delete element from MaxHeap
                void deleteMinHeapVal(int);         // Delete element from MinHeap
                void removeMin(int);
		void removeMaxRoot();
                void removeMinRoot();
                string displayHeap();
                string sortMaxHeap();
                string sortMinHeap();
};


//===================================================================================
// Add new element to MaxHeap
//===================================================================================
void BinaryHeap::addMaxHeap(int rankNo, string player, string team, int totRuns, string oppTeam, int yr)
{
	Node *temp = new Node(rankNo, player, team, totRuns, oppTeam, yr);
	heap.push_back(*temp);
	maxHeapify(heap.size() - 1);
}


//===================================================================================
// Add new element to MinHeap
//===================================================================================
void BinaryHeap::addMinHeap(int rankNo, string player, string team, int totRuns, string oppTeam, int yr)
{
	Node *temp = new Node(rankNo, player, team, totRuns, oppTeam, yr);
	heap.push_back(*temp);
	minHeapify(heap.size() - 1);
}


//===================================================================================
// Recursive heapify function for a MaxHeap
//===================================================================================
void BinaryHeap::maxHeapify(unsigned int index)
{
	unsigned int left, right, maxx;
	left = 2*index;
	right = 2*index + 1;
      
	// Base case
	if (index == 0)
		return;
      
	// Check the children, if they exist and pick the larger for swapping
	if (left < heap.size() && heap[left].getRank() > heap[index].getRank())
		maxx = left;
	else
		maxx = index;
      
	if (right < heap.size() && heap[right].getRank() > heap[maxx].getRank())
		maxx = right;
      
	if (maxx != index)
	{
		  Node temp = heap[maxx];
		  heap[maxx] = heap[index];
		  heap[index] = temp;
		  maxHeapify(maxx);
	}
      
	// Now check the parent, if it exists
	maxHeapify(index/2);
}



//===================================================================================
// Recursive heapify function for a MinHeap
//===================================================================================
void BinaryHeap::minHeapify(unsigned int index)
{
	unsigned int left, right, minn;
	left = 2*index;
	right = 2*index + 1;
      
	// Base case
	if (index == 0)
		return;
      
	// Check the children, if they exist and pick the larger for swapping
	if (left < heap.size() && heap[left].getRank() < heap[index].getRank())
		minn = left;
	else
		minn = index;
      
	if (right < heap.size() && heap[right].getRank() < heap[minn].getRank())
		minn = right;
      
	if (minn != index)
	{
		  Node temp = heap[minn];
		  heap[minn] = heap[index];
		  heap[index] = temp;
		  minHeapify(minn);
	}
      
	// Now check the parent, if it exists
	minHeapify(index/2);
}


void BinaryHeap::deleteMinHeapVal(int rankNo)
{
	int x = 0;
        
	while ( x <= heap.size() )
	{
		if ( rankNo == heap[x].getRank() )
		{
			heap[x] = heap[ (heap.size() - 1) ];
			  
			heap.pop_back();
			  
			minHeapify(x);              // parent
			minHeapify((2 * x) +1);     // left child
			minHeapify((2 * x) +2 );    // right child
			break;      //No need to search further
		}
		x++;
	}
}


void BinaryHeap::deleteMaxHeapVal(int value)
{        
	int x = 0;
	  
	while ( x <= heap.size() )
	{
		if ( value == heap[x].getRank() )
		{
			heap[x] = heap[ (heap.size() - 1) ];
			  
			heap.pop_back();
			  
			maxHeapify(x);              // parent
			maxHeapify((2 * x) +1);     // left child
			maxHeapify((2 * x) +2 );    // right child
			break;      //No need to search further
		}
		x++;
	}
}   
    
    
void BinaryHeap::removeMaxRoot()
{
	if (heap.size() < 2)
		return;
	else
	{
		heap[1] = heap[heap.size() - 1];
		heap.resize(heap.size() - 1);
		maxHeapify(1);
	}
}
    
    
void BinaryHeap::removeMinRoot()
{
	if (heap.size() < 2)
		return;
	else
	{
		heap[1] = heap[heap.size() - 1];
		heap.resize(heap.size() - 1);
		minHeapify(1);
	}
    
}
 
 
string BinaryHeap::sortMaxHeap()
{
	string str ="";
	  
	while (heap.size() > 1)
	{
		str.append(heap[1].getRecord());
		str.append(" \n");
		removeMaxRoot();
	}
	str.append("\n");
	return str;
}

    
string BinaryHeap::sortMinHeap()
{
	string str ="";
	  
	while (heap.size() > 1)
	{
		str.append(heap[1].getRecord());
		str.append("\n");
		removeMinRoot();
	}
	str.append("\n");
	return str;
}


string BinaryHeap::displayHeap()
{
	string str = "";
	for (int x = 1; x < heap.size(); x++)
	{
		str.append(heap[x].getRecord());
		str.append(" \n");
	}
	str.append("\n");
	return str;
}
#endif