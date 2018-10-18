#ifndef AVLTree_AVLTree_H
#define AVLTree_AVLTree_H
#include "Node.h"

class AVLTree
{
        private:
            Node* root;
            
            Node* insertHelper(Node*, int, string, string, int, string, int);
            Node* removeHelper(Node*, int);
            string inorderHelper(Node*);
            string preorderHelper(Node*);
            string postorderHelper(Node*);
            int bsheight(Node*);
            int calcBalance(Node*);
            
            Node* LeftRotate(Node* );
            Node* SpecialCaseLeftRotate(Node* );
            Node* RightRotate(Node* );
            Node* SpecialCaseRightRotate(Node* );
            
            int max(int,int);
            void resetHeight(Node*);
            
        public:
            AVLTree() { root = NULL;}
            
            Node* getRoot()        { return root;}
            void insert(int, string, string, int, string, int);
            void remove(int val)   { root = removeHelper(root, val); }
            string preOrder()      { return preorderHelper(root); }
            string postOrder()     { return postorderHelper(root); }
            string inOrder()       { return inorderHelper(root); }
            void purge()           { root = NULL; }
};


void AVLTree::insert(int rankNo, string player, string team, int totRuns, string oppTeam, int yr)
{
        root = insertHelper(root, rankNo, player, team, totRuns, oppTeam, yr);
}


void AVLTree::resetHeight(Node* ptr)
{
        int lh, rh, ht;
        lh = bsheight(ptr->left);
        rh = bsheight(ptr->right);
        ht = max(lh, rh);
        ptr->setHeight(ht + 1);
}


int AVLTree::calcBalance(Node* ptr)
{
        int leftHeight, rightHeight;
        
        if(ptr == NULL)
            return (0);
        
        if(ptr->left == NULL)
            leftHeight = 0;
        else
            leftHeight = 1 + ptr->left->getHeight();
        
        if(ptr->right == NULL)
            rightHeight = 0;
        else
            rightHeight = 1 + ptr->right->getHeight();
        
        return(leftHeight - rightHeight);
}


int AVLTree::max(int value1, int value2)
{
        return ((value1 > value2) ? value1 : value2);
}



int AVLTree::bsheight(Node* ptr)
{
        int t;
        if (ptr == NULL)
            return -1;
        else
	{
                t = ptr->getHeight();
                return t;
	}
}


Node* AVLTree::insertHelper(Node* ptr, int rankNo, string player, string team,
			   int totRuns, string oppTeam, int yr)
 {
	if (ptr == NULL)
	{
		ptr = new Node(rankNo, player, team, totRuns, oppTeam, yr);
		return ptr;
	}
	
	if (rankNo < ptr->getRank())
	{
		ptr->left = insertHelper(ptr->left, rankNo, player, team, totRuns, oppTeam, yr);
		if ((bsheight(ptr->left) - bsheight(ptr->right))==2)  // Left unbalance
		{
			if (rankNo < ptr->left->getRank())           // Regular left unbalance
			ptr = LeftRotate(ptr);
		else                                    // Special case
			ptr = SpecialCaseLeftRotate(ptr);
		}
	}
	else if (rankNo > ptr->getRank())
	{
		ptr->right = insertHelper(ptr->right, rankNo, player, team, totRuns, oppTeam, yr);
		if ((bsheight(ptr->right) - bsheight(ptr->left))==2)  // Right unbalance
		{
		    if (rankNo > ptr->right->getRank())          // Regular right unbalance
			ptr = RightRotate(ptr);
		    else                                    // Special case
			ptr = SpecialCaseRightRotate(ptr);
		}
	}
	resetHeight(ptr);
	
	return ptr;
}



Node* AVLTree::removeHelper(Node* ptr, int val )
{
	Node* successor;
	
	if ( ptr == NULL)           // Node location is empty
	{
		return NULL;
	}
	else
		if( val > ptr->getRank() )                // Search in Right sub-tree
		{
			ptr->right = removeHelper(ptr->right, val);
			if ( calcBalance(ptr) == 2)
			{
				if(calcBalance(ptr->left) >= 0)
					ptr = LeftRotate(ptr);
				else
					ptr = SpecialCaseLeftRotate(ptr);
			}
		}
		else
		if( val < ptr->getRank() )          // Search the Left sub-tree
		{
			ptr->left = removeHelper(ptr->left, val);
			if( calcBalance(ptr) == -2 )
			{
				if( calcBalance(ptr->right) <= 0)
				    ptr = RightRotate(ptr);
				else
				    ptr = SpecialCaseRightRotate(ptr);
			}
		}
		else        //Node to to be deleted is found
		{
			if ( ptr->right != NULL)
			{  //delete its inorder succesor
				successor = ptr->right;
				while ( successor->left != NULL)
					successor = successor->left;
			    
				ptr->setRank( successor->getRank() );
				ptr->right = removeHelper( ptr->right, ptr->getRank() );
				
				if(calcBalance(ptr) == 2)
				{
					if(calcBalance(ptr->left) >= 0)
						ptr = LeftRotate(ptr);
					else
						ptr = SpecialCaseLeftRotate(ptr);
				}
			}
			else
				return(ptr->left);
		    
		}
	resetHeight(ptr);
	
	return ptr;
}


string AVLTree::inorderHelper(Node* ptr)
{
	string str = "";
	int leftHeight, rightHeight;
	
	if ( ptr != NULL )
	{
		str.append( inorderHelper(ptr->left) );
		
		str.append( ptr->getRecord());
		
		if(ptr->left == NULL)
			leftHeight = 0;
		else
			leftHeight = 1 + ptr->left->getHeight();
        
		if(ptr->right == NULL)
			rightHeight = 0;
		else
			rightHeight = 1 + ptr->right->getHeight();
        
		str.append("\t [");
		if(rightHeight - leftHeight >= 0)
		{
			//str.append("-");
			str.append(to_string(rightHeight - leftHeight));//to_string(ptr->getHeight()));
		}
		else
		{
			str.append("-");
			str.append(to_string(leftHeight - rightHeight));//to_string(ptr->getHeight()));
		}
		  
		str.append(", ");
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
		
		
		str.append( inorderHelper(ptr->right) );
	}
	return str;
}


string AVLTree::preorderHelper(Node* ptr)
{
	string str = "";
	int leftHeight, rightHeight;
	
	if ( ptr != NULL )
	    {
	      
	      		//str.append( preorderHelper(ptr->left) );

		str.append( ptr->getRecord());
		if(ptr->left == NULL)
			leftHeight = 0;
		else
			leftHeight = 1 + ptr->left->getHeight();
        
		if(ptr->right == NULL)
			rightHeight = 0;
		else
			rightHeight = 1 + ptr->right->getHeight();
        
		str.append("\t [");
		if(rightHeight - leftHeight >= 0)
			str.append(to_string(rightHeight - leftHeight));
		else
		{
			str.append("-");
			str.append(to_string(leftHeight - rightHeight));
		} 
		
		str.append(", ");
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
		
		
		str.append( preorderHelper(ptr->left) );
		str.append( preorderHelper(ptr->right) );
	    }
	return str;
}


string AVLTree::postorderHelper(Node* ptr)
{
	string str = "";
	int leftHeight, rightHeight;
	
	if ( ptr != NULL )
	    {
		str.append( inorderHelper(ptr->left) );
		str.append( inorderHelper(ptr->right) );
		
		
		str.append( ptr->getRecord());
		if(ptr->left == NULL)
			leftHeight = 0;
		else
			leftHeight = 1 + ptr->left->getHeight();
        
		if(ptr->right == NULL)
			rightHeight = 0;
		else
			rightHeight = 1 + ptr->right->getHeight();
        
		str.append("\t [");
		if(rightHeight - leftHeight >= 0)
			str.append(to_string(rightHeight - leftHeight));
		else
		{
			str.append("-");
			str.append(to_string(leftHeight - rightHeight));
		}
		  
		str.append(", ");
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

Node* AVLTree:: LeftRotate(Node* ptr)
{
	Node* rightChild;
	rightChild = ptr->left;
	ptr->left = rightChild->right;
	rightChild->right = ptr;
	  
	resetHeight(ptr);
	resetHeight(rightChild);
	  
	return rightChild;
}


Node* AVLTree:: RightRotate(Node* ptr)
{
	Node* leftChild;
	leftChild = ptr->right;
	ptr->right = leftChild->left;
	leftChild->left = ptr;
	  
	resetHeight(ptr);
	resetHeight(leftChild);
	  
	return leftChild;
}


Node* AVLTree:: SpecialCaseLeftRotate(Node* ptr1)
{
	ptr1->left=RightRotate(ptr1->left);
	return LeftRotate(ptr1);
}


Node* AVLTree::SpecialCaseRightRotate(Node* ptr1)
{
	ptr1->right = LeftRotate(ptr1->right);
	return RightRotate(ptr1);
}

#endif // defined(AVLTree_AVLTree_H)