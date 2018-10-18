#ifndef RBTreeREE_H
#define RBTreeREE_H

#include "Node.h"

class RBTree
{
	private:
		Node* root;
    
		// Utility functions
		void    rotateLeft( Node* );
		void    rotateRight(Node* );
		void    fixUp(Node* );
		string  inOrderHelper(Node* );
		string  preOrderHelper(Node* );
		string  postOrderHelper(Node* );
		void    deleteNode(Node* );
		Node* findNode(int );
		Node* getMinimum(Node *);
		Node* getSuccessor(Node *);
    
	public:
		// Constructor function
		RBTree(){ root = NULL;}
		
		void purge() {root = NULL;}
	
		// Mutator functions
		void insert(int, string, string, int, string, int );
		void remove(int);
	
		// Accessor functions
		Node* getRoot(){ return root;}
		string inOrder();
		string preOrder();
		string postOrder();
		string showLevels();
};


void RBTree::rotateLeft( Node* ptr )
{
	Node* rightChild = ptr->right;
	ptr->right = rightChild->left;
	  
	if (rightChild->left != NULL)
		rightChild->left->parent = ptr;
	  
	rightChild->parent = ptr->parent;
	  
	if (ptr == root)
		root = rightChild;
	else
	{
		  if( ptr == ptr->parent->left)
			ptr->parent->left = rightChild;
		  else
			ptr->parent->right = rightChild;
	}
      
	rightChild->left = ptr;
	ptr->parent = rightChild;
}


void RBTree::rotateRight(Node* ptr)
{
	Node* leftChild = ptr->left;
	ptr->left = leftChild->right;
	  
	if (leftChild->right != NULL)
		leftChild->right->parent = ptr;
	  
	leftChild->parent = ptr->parent;
	  
	if (ptr == root)
		root = leftChild;
	else
	      {
		  if( ptr == ptr->parent->right)
			ptr->parent->right = leftChild;
		  else
			ptr->parent->left = leftChild;
	      }
	      
	leftChild->right = ptr;
	ptr->parent = leftChild;
}


Node* RBTree::findNode(int rankNo)
{
	Node* ptr = root;

	while ( ptr != NULL )
        {
		if  (ptr->getRank() == rankNo)        // Found it!
		{
			  return ptr;
		}
	      
		if (rankNo < ptr->getRank() )
			ptr = ptr->left;
		else 
			ptr = ptr->right;
	}
      
	return NULL;            // Tree is empty OR did not find it
}


void RBTree::insert(int rankNo, string player, string team, int totRuns, string oppTeam, int yr)
{
	Node* newnode = new Node(rankNo, player, team, totRuns, oppTeam, yr);      // Create the new node
	 
	if (root == NULL)                   // Tree is empty - newnode is first node
	{
		newnode->setColor("BLACK");
		root = newnode;
		return;
	}
	else                                // Tree is NOT empty
	{
		Node* ancestor = NULL;
		Node* current = root;
		while (current != NULL)
		{
			ancestor = current;
			  
			if ( newnode->getRank() < current->getRank() )
				current = current->left;
			else
				current = current->right;
		}
	      
		newnode->parent = ancestor;
		  
		if ( newnode->getRank() < ancestor->getRank() )
			ancestor->left = newnode;
		else
			ancestor->right= newnode;
	      
		fixUp(newnode);
	}
}


void RBTree::fixUp( Node *ptr )
{
	Node *ptrsUncle = NULL;
      
	while ( ptr != root && ptr->parent->getColor() == "RED" )
	{
		if ( ptr->parent == ptr->parent->parent->left )
		{       // ptr's parent is a LEFT child
			ptrsUncle = ptr->parent->parent->right;
			  
			if (  ptrsUncle != NULL && ptrsUncle->getColor() == "RED" )
			{
				  ptr->parent->setColor("BLACK");
				  ptrsUncle->setColor("BLACK");
				  ptr->parent->parent->setColor("RED");
				  ptr = ptr->parent->parent;
			}
			else
			{
				if ( ptr == ptr->parent->right )
				{
					ptr = ptr->parent;
					rotateLeft( ptr );
				}	  
				ptr->parent->setColor("BLACK");
				ptr->parent->parent->setColor("RED");
				rotateRight( ptr->parent->parent );
			}
		}
		else            // ptr's parent is a RIGHT child
		{
			ptrsUncle = ptr->parent->parent->left;
			  
			if ( ptrsUncle != NULL && ptrsUncle->getColor() == "RED" )
			{
				ptr->parent->setColor("BLACK");
				ptrsUncle->setColor("BLACK");
				ptr->parent->parent->setColor("RED");
				ptr = ptr->parent->parent;
			}
			else
			{
				if ( ptr == ptr->parent->left )
				{
					ptr = ptr->parent;
					rotateRight( ptr );
				}
				ptr->parent->setColor("BLACK");
				ptr->parent->parent->setColor("RED");
				rotateLeft( ptr->parent->parent );
			}
		}
	}  
	root->setColor("BLACK");
	  
	ptrsUncle = NULL;
}


void RBTree::remove(int val)
{
	  Node* markedNode = findNode(val);
	  deleteNode(markedNode);
}


void RBTree::deleteNode(Node* node2Zap)
{
	if (node2Zap == NULL)    //If node being deleted is NULL then do nothing.
		return;
	else
	{
		Node *successor, *successorChild;
		successor = node2Zap;
	      
		if (node2Zap->left == NULL || node2Zap->right == NULL)
			  //If either of the children is NULL
			successor = node2Zap;
		else                    // node2Zap has 2 children
			successor = getSuccessor(node2Zap);
	      
		if (successor->left == NULL)
			successorChild = successor->right;
		else
			successorChild = successor->right;
		  
		if (successorChild != NULL)
			successorChild->parent = successor->parent;
		  
		if (successor->parent == NULL)
			root = successorChild;
		else if (successor == successor->parent->left)
			  successor->parent->left = successorChild;
		      else
			  successor->parent->right = successorChild;
		  
		if (successor != node2Zap)
			node2Zap->setRank(successor->getRank());

		// Finally... If color is black call fixup otherwise no fixup required
		if (successor->getColor() == "BLACK" && successorChild != NULL)
			  fixUp(successorChild);
	}
}


Node* RBTree::getSuccessor(Node* ptr)
{
	if (ptr->right == NULL)
		return ptr->left;
	else
		return(getMinimum(ptr->right));
}


Node* RBTree::getMinimum(Node *ptr)
{
	while(ptr->left != NULL)
		ptr = ptr->left;
    
	return ptr;
}


string RBTree::inOrderHelper(Node* ptr)
{
	string str = "";

	if ( ptr != NULL )
        {
		str.append( inOrderHelper(ptr->left) );
	      
		str.append( ptr->getRecord() );
		str.append( "  ");
	      
		str.append("\t \t [");
		if (ptr->getColor() == "RED")
			 str.append("RED, ");  
		else
			str.append("BLACK, ");  
		//str.append("]");
		
		//str.append("\t [");
		if (ptr->getLeft() != NULL)
			str.append(to_string(ptr->getLeft()->getRank()));
		else
			str.append("NULL");
            
		str.append(", ");
            
		if (ptr->getRight() != NULL)
			str.append(to_string(ptr->getRight()->getRank()));
		else
			str.append("NULL");
            str.append("]\n");
              
		str.append( inOrderHelper(ptr->right) );
	}
	return str;
}


string RBTree::preOrderHelper(Node* ptr)
{
	string str = "";
		  
	if ( ptr != NULL )
	{
		str.append( ptr->getRecord() );
		str.append( "  ");
		 //   str.append(to_string(ptr->getLeft()->getRank()));
		str.append("\t \t[");
		if (ptr->getColor() == "RED")
			 str.append("RED, ");  
		else
			str.append("BLACK, ");  
		
		if (ptr->getLeft() != NULL)
			str.append(to_string(ptr->getLeft()->getRank()));
		else
			str.append("NULL");
            
		str.append(", ");
            
		if (ptr->getRight() != NULL)
			str.append(to_string(ptr->getRight()->getRank()));
		else
			str.append("NULL");
            str.append("]\n");

		  
		str.append( preOrderHelper(ptr->left) );
		str.append( preOrderHelper(ptr->right) );
	}
	return str;
}


string RBTree::postOrderHelper(Node* ptr)
{
	string str = "";
		  
	if ( ptr != NULL )
	{
		str.append( postOrderHelper(ptr->left) );
		str.append( postOrderHelper(ptr->right) );
	      
		str.append( ptr->getRecord() );
		str.append( "  ");
		
		str.append("\t \t[");
		if (ptr->getColor() == "RED")
			 str.append("RED, ");  
		else
			str.append("BLACK, ");  
		
		if (ptr->getLeft() != NULL)
			str.append(to_string(ptr->getLeft()->getRank()));
		else
			str.append("NULL");
            
		str.append(", ");
            
		if (ptr->getRight() != NULL)
			str.append(to_string(ptr->getRight()->getRank()));
		else
			str.append("NULL");
            str.append("]\n");
	}
	return str;
}


string RBTree::inOrder()
{
	return inOrderHelper(root);
}


string RBTree::preOrder()
{
	return preOrderHelper(root);
}


string RBTree::postOrder()
{
	return postOrderHelper(root);
}


string RBTree::showLevels()
{
	vector <Node*> listA;
	vector <Node*> listB;
      
	string str = "";
	  
	listA.resize(0);
	listB.resize(0);
	  
	if (root == NULL)
	{
		str.append("Tree is Empty...\n");
		return str;
	}
	else
		listA.push_back(root);

      
	while (!listA.empty())
	{
		//Display the contents of listA
		for (int x = 0; x < listA.size(); x++)
		{
			str.append( to_string(listA[x]->getRank()) );
			str.append("{");
			str.append( listA[x]->getColor());
			str.append("} \t");
		}
		str.append("\n");
	      
		//Transfer contents of listA to listB
		listB = listA;
	      
		// Now purge listA and copy listB's children into listA
		listA.resize(0);

		for (int x = 0; x < listB.size(); x++)
		{
			if (listB[x]->left != NULL)
				listA.push_back(listB[x]->left);
			if (listB[x]->right != NULL)
				listA.push_back(listB[x]->right);
		}
	}
        return str;
}

#endif /* defined(RBTreeREE_H) */