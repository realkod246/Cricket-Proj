#ifndef SPLAYTREE_H
#define SPLAYTREE_H
#include "Node.h"


class SplayTree
{
        private:
                Node *root;
    
                    // Utility functions
                Node* RightRotate(Node*);
                Node* LeftRotate(Node*);
                Node* Splay(int, Node*);
		Node* deleteNode(Node*, int);        // Recursive counterpart of delete
                Node* insertHelper(Node*, int, string, string, int, string, int);
                string inOrderHelper(Node*);
                string preOrderHelper(Node*);
                string postOrderHelper(Node*);
                //void insertNodeHelper(Node **, int );
                string displayNodesHelper( Node * ) const;
    
    
            public:
                SplayTree(){ root = 0; };
		void purge() {root = NULL;}
    
		void remove(int rankNo)  { root = deleteNode(root, rankNo); }
                Node* getRoot(){return root;}
                void insert(int, string, string, int, string, int);
                string inOrder(){ return inOrderHelper(root);}
                string preOrder(){ return preOrderHelper(root);}
                string postOrder(){ return postOrderHelper(root);}
                void insertNode( int );
                string displayNodes();
};



//=================================================================================
//          The NEW RightRotate function
//=================================================================================

Node* SplayTree::RightRotate(Node* ptr)
{
	Node* leftchild = ptr->left;
	if (leftchild != NULL)
	{
		ptr->left = leftchild->right;
		leftchild->right = ptr;
	}
	return leftchild;
}


//=================================================================================
//          The NEW LeftRotate function
//=================================================================================

Node* SplayTree::LeftRotate(Node* ptr)
{
	Node* rightchild = ptr->right;
	if (rightchild != NULL)
	{//Inheritance & Composition
		ptr->right = rightchild->left;
		rightchild->left = ptr;
	}
	return rightchild;
}


//=================================================================================
//          The NEW Splay function
//=================================================================================

Node* SplayTree::Splay(int key, Node* root)
{
	  // Base cases: root is NULL or key is present at root
	if (root == NULL || root->getRank() == key)
		return root;
	  
	// Key lies in left subtree
	if (root->getRank() > key)
	{
		// Key is not in tree, we are done
		if (root->left == NULL)
			return root;
		  
		// Zig-Zig (Left Left)
		if (root->left->getRank() > key)
		{
			// First recursively bring the key as root of left-left
			root->left->left = Splay(key, root->left->left);
			  
			// Do first rotation for root, second rotation is done after else
			root = RightRotate(root);
		}
		else if (root->left->getRank() < key) // Zig-Zag (Left Right)
		{
			// First recursively bring the key as root of left-right
			root->left->right = Splay(key, root->left->right);
			      
			// Do first rotation for root->left
			if (root->left->right != NULL)
			root->left = LeftRotate(root->left);
		}
		  
		// Do second rotation for root
		return (root->left == NULL)? root: RightRotate(root);
	}
	else // Key lies in right subtree
	{
		// Key is not in tree, we are done
		if (root->right == NULL) return root;
		  
		// Zig-Zag (Right Left)
		if (root->right->getRank() > key)
		{
			// Bring the key as root of right-left
			root->right->left = Splay(key, root->right->left);
			  
			// Do first rotation for root->right
			if (root->right->left != NULL)
			      root->right = RightRotate(root->right);
		}
		else if (root->right->getRank() < key)// Zag-Zag (Right Right)
		{
			// Bring the key as root of right-right and do first rotation
			root->right->right = Splay(key, root->right->right);
			root = LeftRotate(root);
		}
		  
		// Do second rotation for root
		return (root->right == NULL)? root: LeftRotate(root);
	}
}


Node*  SplayTree::deleteNode(Node* ptr, int rankNo)
{
	Node* successor;
	
	if ( ptr == NULL)           // Not found!
	{
		return NULL;
	}
	else
	    if ( rankNo > ptr->getRank() )                // Search in Right subtree
		ptr->right = deleteNode(ptr->right, rankNo);
	    else if( rankNo < ptr->getRank() )            // Search in Left subtree
		ptr->left = deleteNode(ptr->left, rankNo);
	
	    else   //Node to to be deleted is found
		{
			if ( ptr->right != NULL)
			{  // delete its inorder succesor
				successor = ptr->right;
				while ( successor->left != NULL)
					successor = successor->left;
			    
				// Copy data from successor into ptr
				ptr->copyData( successor );
			    
				// Find successor now and delete it
				ptr->right = deleteNode( ptr->right, ptr->getRank() );
			}
			else
				return (ptr->left);
		}
	return(ptr);
}


Node* SplayTree::insertHelper(Node* root, int rankNo, string player, string team,
			   int totRuns, string oppTeam, int yr)
{
	Node* newnode = new Node(rankNo, player, team, totRuns, oppTeam, yr);
      
	if(root == NULL)
		return newnode;
      
	Node* parent_temp = new Node();
	Node* temp = root;
      
	if(rankNo == temp->getRank())      // No duplication
		return root;
	  
	while(temp != NULL)
	{
		parent_temp = temp;
	      
		if(rankNo < temp->getRank())
			temp = temp->left;
		else if(rankNo > temp->getRank())
			temp = temp->right;
		else
                         return root;
	}
      
	if(rankNo <= parent_temp->getRank())
		parent_temp->left = newnode;
	else
		parent_temp->right = newnode;
      
	root = Splay(rankNo, root);
	return (root);
}


void SplayTree::insert(int rankNo, string player, string team, int totRuns, string oppTeam, int yr)
{
	root = insertHelper(root, rankNo, player, team, totRuns, oppTeam, yr);
}


string SplayTree::inOrderHelper(Node* ptr)
{
	string str = "";
		  
	if ( ptr != NULL )
	{
		str.append( inOrderHelper(ptr->left) );
	      
		
		str.append( ptr->getRecord());
		str.append("\t [");
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


string SplayTree::preOrderHelper(Node* ptr)
{
	string str = "";
		  
	if ( ptr != NULL )
	{
		str.append( ptr->getRecord());
		str.append("\t [");
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


string SplayTree::postOrderHelper(Node* ptr)
{
	string str = "";
		  
	if ( ptr != NULL )
	{
		str.append( postOrderHelper(ptr->left) );
		str.append( postOrderHelper(ptr->right) );
	      
		
		str.append( ptr->getRecord());
		str.append("\t [");
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

#endif