#include "QUEUE.h"


////constructor initializing front and rear with NULL
Priority_queue::Priority_queue()
{
	front=NULL;
	rear=NULL;
}

/////destructor for PRIORITY QUEUE CLASS which destructs every node if called.
Priority_queue::~ Priority_queue()
{
	while(front)
	{
		Tree_node *t=front;
		front=front->next;
		delete t;
	}
}

/////This function add nodes to PRIORITY QUEUE CLASS in arranged or ascending order of frequencies.
void Priority_queue::enqueue(Tree_node *b)                         //enqueue function to add nodes in priority queue
{
	if(front==NULL&&rear==NULL)
	{
		Tree_node *c =new Tree_node;
		c->a=b->a;
		c->next=NULL;
		c->left=b->left;
		c->right=b->right;
		c->frequency=b->frequency;
		front=c;
		rear=c;
	}
	else
	{
		if(b->frequency <= front->frequency)                            //comparing frequencies
		{
			Tree_node * c=new Tree_node;
			c->a=b->a;
			c->frequency=b->frequency;
			c->next=front;
			c->left=b->left;
			c->right=b->right;
			front=c;
		}
		else if(b->frequency > rear->frequency)
		{
			Tree_node * c=new Tree_node;
			c->a=b->a;
			c->frequency=b->frequency;
			c->next=NULL;
			rear->next=c;
			c->left=b->left;
			c->right=b->right;
			rear=c;
		}

		else
		{
			Tree_node *t1;
			t1=front;
			Tree_node *t2;
			t2=NULL;
			do
			{
				t2=t1;
				t1=t1->next;
			}while(t1->frequency < b->frequency);

			if(t2!=NULL)
			{
				Tree_node *c=new Tree_node;
				c->a=b->a;
				c->frequency=b->frequency;
				c->left=b->left;
				c->right=b->right;
				c->next=t1;
				t2->next=c;
			}
		}
	}
}

///////function used to dequeue a node from queue ,it helps in making a tree.it dequeues the node with least frequency 
Tree_node *Priority_queue:: dequeue()
{
	if(front!=NULL)
	{
		Tree_node *t=new Tree_node;
		t=front;
		front=front->next;
		return t;
	}
	else if(front==NULL)
	{
		cout<<"Cannot dequeue .. No elements entered.. "<<endl;
	}
}

////////// function  that helps to make a binary heap out of priority queue /////////// 
Tree_node *Priority_queue:: build_tree()
{                                                               //this function returns the huffman or max heap tree arranged according to frequencies
	while(front!=NULL)
	{                
		Tree_node *t=new Tree_node;
		t->left=dequeue();										//dequeueing 2 nodes and making it left and right node of new node which is root. and making whole tree.
		t->right=dequeue();
		t->frequency=t->left->frequency+t->right->frequency;

		if(front!=NULL)
		{
			enqueue(t);
		}
		else 
		{
			return t;
		}
	}
}

//////////// display function to display all nodes character and frequencies in a priority queue /////////////
void Priority_queue::display()
{
	cout<<"\t\tCHARACTER\t\tFrequency\n "<<endl;
	if(front!=NULL)
	{
		Tree_node *t=front;
		do
		{
			if(t->a==' ')
			{
				cout<<"\t\tSpace"<<"\t\t\t"<<t->frequency<<"  "<<endl;
			}
			else if(t->a==char(10))
			{
				cout<<"\t\tEnter"<<"\t\t\t"<<t->frequency<<"  "<<endl;
			}
			else
			{
				cout<<"\t\t"<<t->a<<"\t\t\t"<<t->frequency<<"  "<<endl;
			}
			t=t->next;
		}while(t!=NULL);
	}
	else if(front==NULL)
	{
		cout<<"There is no node to be displayed ... "<<endl;
	}
}

//////function to save array of characters with their frequencies and used for decoding
void  Priority_queue::saveFile( Tree_node* a[],ofstream &outFile )
{
	for(int j=0;j<256;j++)					
	{
		if(a[j]->frequency != 0)							
		{
			string s;
			s.push_back(a[j]->a);
			if(a[j]->a==char(10))
				s="enter";
			if (a[j]->a==char(32))
				s="space";
			outFile << a[j]->frequency <<" "<<s<< " ";
		}
	}
}

void Priority_queue::readTextFile( ifstream &inFile )
{
	Tree_node *arr[256];
	for(int i=0;i<256;i++)							//Array of 256 characters intialized by NULL and zero frequencies and the corresponding character.
	{
		arr[i]=new Tree_node;
		arr[i]->a=char(i);
		arr[i]->frequency=0;
		arr[i]->code="";
		arr[i]->left=NULL;
		arr[i]->right=NULL;
	}
	string s;
	Tree_node *root=new Tree_node;
	while(inFile>>root->frequency>>s)				//reading frequency and character from file to store in array and then enqueue it.
	{
		if(s=="enter")
		{
			arr[10]->frequency=root->frequency;
		}
		else if(s=="space")
		{
			arr[32]->frequency=root->frequency;
		}
		else
		{
			int ch=s.at(0);
			arr[ch]->frequency=root->frequency;
		}
	}
	for(int i=0;i<256;i++)                        //enqueing into priority queue
	{
		if(arr[i]->frequency!=0)
		{
			enqueue(arr[i]);
		}
	}
}
