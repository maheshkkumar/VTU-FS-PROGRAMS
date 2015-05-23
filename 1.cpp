
/*

1. 	Write a C++ program to read series of names, one per line, from standard input and write these names spelled in reverse order
	to the standard output using I/O redirection and pipes. Repeat the exercise using an input file specified by the user instead 
	of the standard input and using an output file specified by the user instead of the standard output.

*/



#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class student{              // student class
public:
	char name[20];
}rec[25];

fstream f1, f2;
char fname1[25], fname2[25];	
	

int main(void){
	char name[25];
	int choice, n, i, j, len=0;

	cout<<"1. Console I/O \n2. File I/O \n";
	cout<<"Enter your choice:\n";
	cin>>choice;

	switch(choice){

			case 1:
					cout<<"Enter the number of students: \n";
					cin>>n;
					strcpy(fname1, "st.txt");
					f1.open(fname1, ios::out);
					for(i=1; i<=n; i++){
						cout<<"Enter "<< i <<" student name: \n";
						cin>>rec[i].name;
						strcpy(name, rec[i].name);
						f1<<name<<"\n";
						len = strlen(name);
						cout<<"Reversed Name is : ";
						for(j=len-1; j>=0; j--){
							cout<<name[j];
						}
						cout<<"\n";
					}
					f1.close();
					break;
			case 2:
					cout<<"Enter the file name, from which you want to read the names:\n";
					cin>>fname1;
					cout<<"Enter the file name, from which you want to write the reversed names.\n";
					cin>>fname2;

					f1.open(fname1, ios::in);
					f2.open(fname2, ios::out);

					if(!f1 || !f2){
						cout<<"Unable to open the file.\n";
						break;
					}

					while(1){
						f1.getline(name, 25);
						if(f1.fail()){
							break;
						}

						len = strlen(name);
						for(j=len-1; j>=0; j--){
							f2<<name[j];
							cout<<name[j];
						}
						f2<<"\n";
						cout<<"\n";
					}
					f1.close();
					f2.close();
					break;

			default: cout<<"Invalid Entry";
	}

}