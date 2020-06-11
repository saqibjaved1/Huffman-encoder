#include "QUEUE.H"


//////SOME GLOBAL FUNCTIONS////


///////////////// welcome screen function /////////////////////
void welcome ()
{
	string A="\n\n";
	A+="\n\n\n\n\n";
	A+="\n\t\t\t==========================================\n\t\t\t";
	A+="*   * *   * ***** ***** *   * ***** *    * \n\t\t\t";
	A+="*   * *   * *     *     ** ** *   * * *  * \n\t\t\t"; 
	A+="***** *   * ***** ***** * * * ***** *  * * \n\t\t\t"; 
	A+="*   * *   * *     *     *   * *   * *   ** \n\t\t\t"; 
	A+="*   * ***** *     *     *   * *   * *    * \n\t\t\t"; 
	A+="==========================================\n\t\t\t"; 

	A+="\n\t\t\t==============================================================\n\t\t\t";
	A+="***** ***** *   * ***** ***** ***** ***** ***** * OOOOO *    * \n\t\t\t";
	A+="*     *   * ** ** *   * *   * *     *     *     * O   O **   * \n\t\t\t";
	A+="*     *   * ** ** *   * *   * *     *     *     * O   O **   * \n\t\t\t";
	A+="*     *   * * * * ***** ***** ***** ***** ***** * O   O * *  * \n\t\t\t";
	A+="*     *   * *   * *     * *   *         *     * * O   O *   ** \n\t\t\t";
	A+="***** ***** *   * *     *   * ***** ***** ***** * OOOOO *    * \n\t\t\t";
	A+="==============================================================\n";
	A+="\n\n\n\t\t\tCREDITS :\n";
	A+="\t\t\tSaqib Javed \n\t\t\t";
	for(int i=0;i<A.length();i++)			//used for printing after some time
	{
		A.at(i);				
		Sleep(30);
		cout<<A[i];
	}
	getch();
	system("cls");
}
void mainmenu()								//function for main menu
{
	cout<<"\n\n\n\n\n\n\n\n\t\t\t==============================================\n\t\t\t";
	cout<<"*   *   *   * *   *    *   * ***** **  * *   *  \n\t\t\t";
	cout<<"** **  * *  * **  *    ** ** *     **  * *   *      \n\t\t\t";
	cout<<"* * * ***** * * * *    * * * ***** * * * *   * \n\t\t\t";
	cout<<"*   * *   * * *  **    *   * *     *  ** *   *     \n\t\t\t";
	cout<<"*   * *   * * *   *    *   * ***** *   * *****    \n\t\t\t";
	cout<<"==============================================\n\n\n\t\t\t";
	string A="Enter \n\n\t\t\t>> 1- to Read Huffman Algorithm Description.\n\t\t\t";
	A+=">> 2- to Encode a File. \n\t\t\t>> 3- to Decode a File.\n\t\t\t>> 4- to Exit.\n\t\t\t";
	for(int i=0;i<A.length();i++)						//used for printing after some time
	{
		A.at(i);
		Sleep(30);
		cout<<A[i];
	}
}

//////////////////Inorder traversal////////////////////
void inorder_traverse(Tree_node * head)
{
	if(head!=NULL)
	{
		inorder_traverse(head->left);							//inorder traversal for showing all characters codes in the huffman tree.
		if(head->a >= 0 && head->a< 256)
		{
			if(head->a==' ')
			{
				cout<<"\t\tSpace"<<"\t\t\t"<<head->code<<"  "<<endl;
			}
			else if(head->a==char(10))
			{
				cout<<"\t\tEnter"<<"\t\t\t"<<head->code<<"  "<<endl;
			}
			else
			{
				cout<<"\t\t"<<head->a<<"\t\t\t"<<head->code<<"  "<<endl;
			}
		}
		inorder_traverse(head->right);
	}
}

///////// recursive function that assign codes to all characters //////////////
void encoding(Tree_node * root,string str)
{
	if(root->left!=NULL && root->right!=NULL)				//assigning codes if it is a left node it gives and 1 if it's right and carry on
	{														//untill a leaf node comes.
		Tree_node *l=root->left;
		string str1=str+"0";
		encoding(l,str1);									
		Tree_node *r=root->right;                
		string str2=str+"1";                
		encoding(r,str2);           
	}
	else if(root->left==NULL && root->right==NULL)
	{
		root->code=str;
	}
}

///////////// Function to compress the encoded file //////////////////////

void compress(string Data,string Fl)
{
	ofstream inp;
	inp.open(Fl.c_str(),ios::trunc,ios::binary);		//compressing the 1 and 0's from encoded file as they have greater size.
	int octets = Data.length()/8;						//making new characters so that data is compressed and new file has less size.
	inp.write((char *)&octets,sizeof(int));
	for(int i=0;i<(Data.length()/8);++i)
	{
		char c='\0';
		for(int j=0;j<8;j++)
		{
			c=c<<1;
			if (Data[(i*8)+j]=='0')
			{	
				c=c|0;
			}
			else 
			{
				c=c|1;
			}
		}
		inp.write((char *)&c,sizeof(char));
	}
	if (Data.length()%8!=0)
	{
		string remData = Data.substr(octets*8);
		for(int i=0;i<remData.length();++i)
		{
			char oc=remData[i];
			inp.write((char *)&oc,sizeof(char));
		}
	}
	inp.close();
}




//////////// recursive function that saves codes for each character in their structures //////////

void store_codes(Tree_node * root,Tree_node * arr[])
{
	if(root->left!=NULL && root->right!=NULL)					
	{
		store_codes(root->left,arr);							//using recusrion for storing codes.
		store_codes(root->right,arr);
	}
	else if(root->left==NULL && root->right==NULL)				//storing codes in array and then using it to write in files.
	{
		for(int i=0;i<256;i++)
		{
			if(arr[i]->a==root->a)
			{
				arr[i]->code=root->code;
			}
		}
	}

}



////////////// function that decodes a given encoded file /////////////////////


void decode(ifstream & infile,ofstream & outfile,Tree_node *root)
{
	char msg;						// bit read from encoded file
	Tree_node * key;				// keeping check on path in decoding tree
	for(;;)
	{
		key=root;
		while(key->left!=NULL || key->right!=NULL)
		{
			infile>>msg;				//traversing data from file which have 1 and zero's
			if(infile.eof())
			{	return;	}
			else
			{
				if(msg=='0')
				{
					key=key->left;
				}
				else if(msg=='1')
				{
					key=key->right;
				}
				else
				{
					cout<<"Wrong message bit: " <<msg<< " -- ,So ignored"<<endl;
				}
			}
		}
		outfile<<key->a;				//printing characters and making exact same file which was compressed by huffman encoding
	}
}
///////////// Function to decompress the compressed file //////////////////////

string decompress(string Fl)
{
	string Data="";
	ifstream out;
	out.open(Fl.c_str(),ios::binary);
	int x;
	out.read((char*)&x,sizeof(int));
	for(int i=0;i<x;++i)					//restoring 1 and 0's from new self made characters from compressed file
	{
		char c;
		out.read((char*)&c,sizeof( char));
		for(int j=0;j<8;++j)
		{
			char tmp=(char)128;
			if ((tmp&c)==tmp)
			{
				Data = Data + "1";
			}
			else
			{
				Data = Data + "0";
			}
			c=c<<1;
		}
	}
	char oc;
	while(out.read((char*)&oc,sizeof(char)))
	{
		Data=Data+oc;
	}
	return Data;
	out.close();
}
/////////////////Global functions //////////////////////////
void gotoxy(int x,int y)									//built in gotoxy function used to construct trees in discription on console
{    
	HANDLE console_handle;    
	COORD cursor_coord;    
	cursor_coord.X=x;    
	cursor_coord.Y=y;    
	console_handle= GetStdHandle( STD_OUTPUT_HANDLE);    
	SetConsoleCursorPosition(console_handle,cursor_coord);    
}

void discription()					//function for the whole program discription
{
	system("cls");

	cout<<"\nStep 1: Read whole text file and find frequency of occurences of all characters. "<<endl;
	cout<<"\t\t\ Characters and Frequencies "<<endl<<endl;
	cout<<"\t\t\tR"<<"-"<<"Frequency :"<<" "<<2<<endl;
	cout<<"\t\t\tA"<<"-"<<"Frequency :"<<" "<<1<<endl;
	cout<<"\t\t\tS"<<"-"<<"Frequency :"<<" "<<2<<endl<<endl;
	cout<<"Step 2: Make priority queue out of collected data."<<endl;

	///////////// Priority Quiz Grid /////////////

	for(int i=20;i<45;i++)
	{
		gotoxy(i,10); cout<<'-';
	}
	for(int i=20;i<45;i++)
	{
		gotoxy(i,13); cout<<'-';
	}


	gotoxy(10,11.5);cout<<"FRONT-->";

	gotoxy(51,11.5);cout<<"<--REAR";

	gotoxy(24.5,11);cout<<'A';
	gotoxy(24.5,12);cout<<1;
	gotoxy(32.5,11);cout<<'R';
	gotoxy(32.5,12);cout<<2;
	gotoxy(40,11);cout<<'S';
	gotoxy(40,12);cout<<2;

	////////////////// Max heap tree ////////////////////

	gotoxy(0,15);
	cout<<"Step 3: "<<"Every time dequeue 2 nodes,make new node,to its left right assign those dequeued nodes,\n\t ";
	cout<<"and then enqueue it again keeping in mind its correct place according to its sumed frequency.."<<endl;

	cout<<endl;
	gotoxy(32.5,20);cout<<5;
	gotoxy(32.5,21);cout<<char(3);

	gotoxy(30.5,22);cout<<'/';
	gotoxy(29.5,23);cout<<'/';  
	gotoxy(28,24);cout<<'/';

	gotoxy(37,25);cout<<'S';
	gotoxy(37,26);cout<<2;

	gotoxy(33.5,22);cout<<char(92);
	gotoxy(34.5,23);cout<<char(92);  
	gotoxy(35,24);cout<<char(92);


	gotoxy(26,25);cout<<3;
	gotoxy(26,26);cout<<char(3);

	gotoxy(25.5,27);cout<<'/';
	gotoxy(24.5,28);cout<<'/'; 
	gotoxy(23,29);cout<<'/';

	gotoxy(21.5,30);cout<<'A';
	gotoxy(21.5,31);cout<<1;

	gotoxy(27,27);cout<<char(92);
	gotoxy(28.5,28);cout<<char(92);  
	gotoxy(29.5,29);cout<<char(92);

	gotoxy(31.5,30);cout<<'R';
	gotoxy(31.5,31);cout<<2;

	gotoxy(0,33);
	cout<<"Step 4: "<<"Generate binary code for the characters by traversing tree, if left,\n\tassign '0' else if, assign '1' ."<<endl;

	cout<<endl;
	gotoxy(32.5,36);cout<<5;
	gotoxy(32.5,37);cout<<char(3);

	gotoxy(30.5,38);cout<<'/';
	gotoxy(29.5,39);cout<<'/';    
	gotoxy(28,40);cout<<'/';

	gotoxy(37,41);cout<<'S';
	gotoxy(37,42);cout<<2;

	gotoxy(33.5,38);cout<<char(92);
	gotoxy(34.5,39);cout<<char(92); 
	gotoxy(35,40);cout<<char(92);


	gotoxy(26,41);cout<<3;
	gotoxy(26,42);cout<<char(3);

	gotoxy(25.5,43);cout<<'/';
	gotoxy(24.5,44);cout<<'/'; 
	gotoxy(23,45);cout<<'/';

	gotoxy(21.5,46);cout<<'A';
	gotoxy(21.5,47);cout<<1;

	gotoxy(27,43);cout<<char(92);
	gotoxy(28.5,44);cout<<char(92); 
	gotoxy(29.5,45);cout<<char(92);

	gotoxy(31.5,46);cout<<'R';
	gotoxy(31.5,47);cout<<2;


	gotoxy(27.5,39); cout<<"0";
	gotoxy(36.5,39);cout<<"1";
	gotoxy(30.5,44);cout<<"1"; 
	gotoxy(22.5,44);cout<<"0"; 

	gotoxy(0,50);
	cout<<"Step 5: "<<"Finally, you have found the binary codes for each character . "<<endl<<endl;
	cout<<"\t\t\t  Codes : "<<"\n\n";
	cout<<"\t\t\t"<<"  A --- 00"<<endl;
	cout<<"\t\t\t"<<"  R --- 01"<<endl;
	cout<<"\t\t\t"<<"  S --- 1"<<endl<<endl;
	cout<<"\tIt shows us easily that originally file was occupying 40 Bits, but now 8 Bits.\n\tClearly, The file has been compressed. "<<endl;

	getch();
	system("cls");
}
////built in function used to set console window size.
bool SetWindow(int Width, int Height) 
{ 
	_COORD coord; 
	coord.X = Width; 
	coord.Y = Height; 

	_SMALL_RECT Rect; 
	Rect.Top = 0; 
	Rect.Left = 0; 
	Rect.Bottom = Height - 1; 
	Rect.Right = Width - 1; 

	// Get handle of the standard output 
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); 
	if (Handle == NULL) 
	{ 
		return FALSE; 
	} 

	// Set screen buffer size to that specified in coord 
	if(!SetConsoleScreenBufferSize(Handle, coord)) 
	{ 
		return FALSE; 
	} 

	// Set the window size to that specified in Rect 
	if(!SetConsoleWindowInfo(Handle, TRUE, &Rect)) 
	{ 
		return FALSE; 
	} 

	return TRUE; 
} 
