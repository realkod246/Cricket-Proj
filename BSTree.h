#ifndef BST_BSTree_h
#define BST_BSTree_h
#include "Node.h"

class BSTree
{
        private:
            Node* root;
    
                // Recursive counterpart of insert
            Node* insertHelper(Node*, int, string, string, int, string, int);
            Node* deleteNode(Node*, int);        // Recursive counterpart of delete
            string inOrderHelper(Node* );         // Recursive counterpart of inorder            
	    string preOrderHelper(Node* );        // Recursive counterpart of preorder
            string postOrderHelper(Node* );       // Recursive counterpart of postorder
            
        public:
            BSTree()     { root = NULL;}
            void purge() { root = NULL;}
            
            Node* getRoot()    { return root;}
            void insert(int, string, string, int, string, int);
            void remove(int rankNo)  { root = deleteNode(root, rankNo); }
            string preOrder()     { return preOrderHelper(root); }
            string postOrder()    { return postOrderHelper(root); }
            string inOrder()      { return inOrderHelper(root); }
};


Node* BSTree::insertHelper(Node* ptr, int rankNo, string player, string team,
			   int totRuns, string oppTeam, int yr)
{
	if ( ptr == NULL )              // The tree is empty - new first node!
	{
		ptr = new Node(rankNo, player, team, totRuns, oppTeam, yr);
	}
	else                            // choose which sub-tree to follow
	{
		if (rankNo >= ptr->getRank())  // insert in right subtree - Operational defn.
			ptr->right = insertHelper(ptr->right, rankNo, player, team, totRuns, oppTeam, yr);
		else
			ptr->left = insertHelper(ptr->left, rankNo, player, team, totRuns, oppTeam, yr);
	}
	return ptr;
}



void BSTree::insert(int rankNo, string player, string team, int totRuns, string oppTeam, int yr)
{
	root = insertHelper(root, rankNo, player, team, totRuns, oppTeam, yr);
}


Node*  BSTree::deleteNode(Node* ptr, int rankNo )
{
	Node* successor;
	
	if ( ptr == NULL)           // Not found
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
				ptr->right = deleteNode( ptr->right, ptr->getRank());
			}
			else
				return(ptr->left);
		}
		return(ptr);
}


string BSTree::inOrderHelper(Node* ptr)
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


string BSTree::preOrderHelper(Node* ptr)
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


string BSTree::postOrderHelper(Node* ptr)
{
	string str = "";
	
	if ( ptr != NULL )
	{
		str.append( inOrderHelper(ptr->left) );
		str.append( inOrderHelper(ptr->right) );
			
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