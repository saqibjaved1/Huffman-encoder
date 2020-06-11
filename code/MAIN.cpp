
#include "functions.h"

/////////////// MAIN FUNCTION /////////////////
int main()
{
	SetWindow(120,70);												//seting console window size through built in function
	int cont;
	system("color 2f");
	welcome();
	//////////////// Main work ///////////////////////

	Tree_node *arr[256];	
	for(int i=0;i<256;i++)											//Array of 256 characters as there are 256 characters 
	{
		arr[i]=new Tree_node;
		arr[i]->a=char(i);
		arr[i]->frequency=0;										//initializing every
		arr[i]->code="";
		arr[i]->left=NULL;
		arr[i]->right=NULL;
	}
	//////////////////////// MENU ///////////////////////////////////
	while(1)
	{
		Priority_queue q;											//making priority queue to store char from file
		string choice;
		system("color 4F");
		mainmenu();
		cin>>choice;												//requiring option from user
		if(choice=="1")
		{
			system("color 3f");
			discription();
		}
		else if(choice=="2")
		{
			system("color 3");
			system("cls");
			cout<<"\n\nENCODING....\n\n";
			cin.ignore();
			string filename;
			string str;
			ifstream infile;
			///////////// Opening file for reading and counting frequency of each character /////////////
			cout<< "Enter the name of the file which you want to encode... "<<endl;
			getline(cin,filename);
			string filename1=filename;
			filename+=".txt";
			infile.open(filename.c_str());
			if(!infile)											//if file doesn't exist with that name
			{	
				cout<<"Text file is not opened due to some reason or File doesn't exist with this name.. Sorry.. \n"<<endl;
				system("pause");
				system("cls");
				continue;
			}
			else
			{
				while(getline(infile,str))						//reading frequencies of all the characters
				{
					for(int i=0;i<str.length();i++)
					{
						for(int r=0;r<255;r++)
						{
							if(arr[r]->a==str[i])
							{
								arr[r]->frequency++;			//incrementing frequency of character that is present in file.
							}
						}
					}
					arr[10]->frequency++;					//incrementing frequency of enter...
				}
				infile.close();
				ofstream d("F://"+filename1+"1.txt");
				q.saveFile(arr,d);
				for(int i=0;i<256;i++)                        //enqueing into priority queue
				{
					if(arr[i]->frequency!=0)
					{
						q.enqueue(arr[i]);					//enqueing in increasing order of frequencies.
					}
				}
				cout<< "\n\tFollowing characters occured with the respective frequencies.. "<<endl<<endl;
				q.display();

				Tree_node *root=q.build_tree();				//making max heap tree according to frequencies of characters.		

				encoding(root,"");							//function for assigning codes to characters in tree.

				store_codes(root,arr);						//function for assigning codes to characters in array.

				getch();
				system("cls");
				cout<< "\n\tThe codes generated are :"<<endl<<endl;
				cout<<"\t\tCHARACTER\t\tCODE\n\n";
				inorder_traverse(root);						//for showing codes of all characters present in file using huffman (max heap) tree.
				getch();
				system("cls");
				/////Encoding/////
				string key;
				ofstream outfile;
				ifstream infile2;
				outfile.open(filename1 +" encoded.txt",ios::app,ios::trunc);		//saving encoded file which will have zero's and 1
				infile2.open(filename.c_str());
				if(!infile2||!outfile)
				{
					cout<<"Cannot open the file.. "<<endl;							//if file cant be created
				}
				else
				{
					while(getline(infile2,key))										//picking line by line from file to be compressed
					{
						for(int i=0;i<key.length();i++)						
						{
							for(int r=0;r<256;r++)
							{
								if(arr[r]->a==key[i])
								{
									outfile<<arr[r]->code;							//writting code for every character in encoded file.
								}
							}
						}
						outfile<<arr[10]->code;										//after every line "enter" to move to next line in storing file
					}
				}

				outfile.close();
				infile2.close();

				cout<<"The encoded file with 0's and 1's is being saved.\n\n "<<endl<<endl;
				getch();
				//////Compressing////////

				string binary;
				ifstream infile3;
				infile3.open(filename1 +" encoded.txt");						//opening encoded file to be further compressed.
				if(!infile3)
				{
					cout<<"file not opened.."<<endl;
				}
				else
				{
					getline(infile3,binary);
					compress(binary,filename1 + " compressed.txt");				//compressing function which will decrease the size of the file.
				}

				cout<<"The encoded file has been compressed as '"<<filename1<<" compressed.txt'. . "<<endl<<endl;		//finally file compressed.
				getch();
				system("cls");
			}
		}
		else if (choice=="3")													//DECODING
		{
			system("color 80");
			system("cls");
			cout<<"\n\nDECODING....\n\n";
			cin.ignore();
			string filename1;
			cout<<"Enter filename you want to Decompress and write it without the word 'compressed': \n";
			getline(cin,filename1);
			Priority_queue decoder;
			ifstream is("F://"+filename1+"1.txt");
			if(!is)																//if file doesn't exist.
			{
				cout<<"\nText file is not opened due to some reason or File doesn't exist with this name.. Sorry.. \n";
				system("pause");
				system("cls");
				continue;
			}
			else
			{
				decoder.readTextFile(is);									//reading from saved file to make tree
				Tree_node *p=decoder.build_tree();							//making tree using saved file
				encoding(p,"");												//making codes for the newly made tree .

				////////Decompressing////////
				string s=decompress(filename1+" compressed.txt");			//opening compressed file and making zero's and one from it to decode file.
				ofstream outfil;
				outfil.open(filename1+" decompressed.txt");
				outfil<<s;
				outfil.close();

				cout<<"\nThe compressed file is ready for decompression. . "<<endl<<endl;
				system("pause");
				//////Decoding////////
				string decoded;
				ifstream infil;
				infil.open(filename1+" decompressed.txt");			//opening decompressed which have zeros and 1 to decode into original file.
				ofstream outfil2;
				fflush(stdin);
				cout<<"\nEnter name of the decoded file you want to save with: \n";
				getline(cin,decoded);
				outfil2.open(decoded+".txt");				
				decode(infil,outfil2,p);							//decoding exact file which was compressed and saving it.
				cout<<"The decompressed file is being decoded which is exact replica of original text file and saved as \""<<decoded<<"\". . "<<endl<<endl;
				getch();
				system("cls");
			}
		}
		else if(choice=="4")										//to exit.
		{
			cout<<"\n\t\t\tBye Bye ..!!\n\t\t\tHave a nice day :)";

			/////// Deleting array of structures(tree_nodes) /////////////
			for(int i=0;i<256;i++)			
			{
				delete arr[i];
			}
			cout<<"\n\t\t\t";
			system("pause");
			return 0;
		}
		else                                                       //if wrong option entered.
		{
			cout<<"\n\t\t\tEnter correct option..!!\n\t\t\t";
			system("pause");
			system("cls");
		}
	}
}
