#ifndef Node_H
#define Node_H
class Node
{
	  private:
		int     rank;
		string  name;
		string  nationality;
		int     score;
		string  opponent;
		int     year;
		int	height;
		string	color;

	    
    
        public:
		Node* left;
		Node* right;
		Node* nextPtr;
		Node* parent;

	
		    // Constructor functions
		Node(){right = left = parent = NULL; color = "RED"; height = 0;}
		Node(int, string, string, int, string, int);
	
		    //Accessor functions
		int      getRank()       { return rank; }
		string   getName()       { return name; }
		string   getNationality(){ return nationality; }
		int      getYear()       { return year; }
		int      getScore()      { return score; }
		string   getopponent()   { return opponent; }
		Node*    getLeft()       { return left; }
		Node*    getRight()      { return right; }
		int getHeight() 	 { return height;}
		
		Node* getNext()		 {return nextPtr;}
		string getColor()	 {return color;}

		string   getRecord();
		
		//Mutator functions
		void setRank(int num)           { rank = num; }
		void setName(string str)        { name = str; }
		void setnationality(string str) { nationality = str; }
		void setYear(int yr)            { year = yr; }
		void setScore(int totscore)     { score = totscore; }
		void setOpponent(string oppTeam){ opponent = oppTeam; }
		void setLeft(Node* ptr)      	{ left = ptr;}
		void setRight(Node* ptr)     	{ right = ptr;}
		void copyData(Node*);
		void setHeight(int ht)  	{height = ht;}
		void setNext(Node* ptr)		{nextPtr = ptr;}
		void setColor(string col)	{color = col;}

		
};


Node::Node(int rankNo, string player, string team, int totRuns, string oppTeam, int yr)
{
	  rank        = rankNo;
	  name        = player;
	  nationality = team;
	  score       = totRuns;
	  opponent    = oppTeam;
	  year        = yr;
	  left        = NULL;
	  right       = NULL;
	  nextPtr     = NULL;
	  height      = 0;
	  color       = "RED";
}


string Node::getRecord()
{
	  string record = to_string(rank);
	  record.append(" \t");
	  record.append(name);
	  record.append(" \t\t");
	  record.append(nationality);
	  record.append(" \t\t\t");
	  record.append(to_string(score));
	  record.append(" \t\t");
	  record.append(opponent);
	  record.append(" \t\t");
	  record.append(to_string(year));
	  
	  return record;
}


void Node::copyData(Node* ptr)
{
	  rank        = ptr->rank;
	  name        = ptr->name;
	  nationality = ptr->nationality;
	  score       = ptr->score;
	  opponent    = ptr->opponent;
	  year        = ptr->year;
}
#endif