/*
	6. Write a C++ program to implement index on secondary key, the name, for a file of student objects. Implement add ( ), search ( ), delete ( ) using the secondary index.	
*/
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class student{
	public:
		char name[10];
		char usn[10];
		char age[5];
		char sem[5];
		char branch[5];

//		retrieve_data();
//		delete();

}rec[10];

int no;
char st_no[5];

int retrieve_data(){
	fstream f1;
	int i;
	char index[5];
	char name[10];
	char usn[10];
	char age[5];
	char sem[5];
	char branch[5];

	f1.open("record.txt", ios::in);

	for(i=0; i<no; i++){
		f1.getline(index, 5, '|');
		f1.getline(name, 10, '|');
		f1.getline(usn, 10, '|');
		f1.getline(age, 5, '|');
		f1.getline(branch, 5, '\n');

		if(strcmp(st_no, index) == 0){
			cout<<name<<"\t"<<usn<<"\t"<<age<<"\t"<<branch<<"\n";
		}
	}
	f1.close();
}

int delete_data(char usn_no[]){
	int flag;
	fstream f1, f2;
	int i;
	char index[5];
	char name[10];
	char usn[10];
	char age[5];
	char sem[5];
	char branch[5];
	char ind[10][10];

	f1.open("record.txt", ios::in);
	flag = 0;
	for(i=0; i<no; i++){
		f1.getline(index, 5, '|');
		f1.getline(name, 10, '|');
		f1.getline(usn, 10, '|');
		f1.getline(sem, 5, '|');
		f1.getline(branch, 5, '|');

		strcpy(ind[i], index);
		strcpy(rec[i].name, name);
		strcpy(rec[i].usn, usn);
		strcpy(rec[i].sem, sem);
		strcpy(rec[i].branch, branch);

		if(strcmp(ind[i], usn_no) == 0){
			flag = i;
		}
	}
	if(flag == (no-1)){
		no--;
		cout<<"Deleted\n";
	}

	for(i=flag; i<no; i++){
		rec[i] = rec[i+1];
	}
	no--;

	f1.close();

	f1.open("index.txt", ios::out);
	f2.open("record.txt", ios::out);

	for(i=0; i<no; i++){
		f1<<rec[i].usn<<"|"<<i<<"\n";
		f2<<i<<"|"<<rec[i].name<<"|"<<rec[i].usn<<"|"<<rec[i].sem<<"|"<<rec[i].branch<<"\n";
	}
	f1.close();
	f2.close();
}


int main(void){
	int choice;
	char name[10];
	char usn[10];
	char age[5];
	char sem[5];
	char branch[5];
	char rt_usn[10];
	char st_usn[10];
	int flag;
	fstream f1, f2;
	for(;;){
		cout<<"Enter your choice:\n";
		cin>>choice;

		switch(choice){
			case 1: 
				int i;
				f1.open("index.txt", ios::out);
				f2.open("record.txt", ios::out);
				cout<<"Enter the number of students:\n";
				cin>>no;
				for(i=0; i<no; i++){
					cout<<"\nEnter usn,name,sem,dept :";
					cin>>rec[i].usn>>rec[i].name>>rec[i].sem>>rec[i].branch;

					f1<<rec[i].usn<<"|"<<i<<"\n";
					f2<<i<<"|"<<rec[i].name<<"|"<<rec[i].usn<<"|"<<rec[i].sem<<"|"<<rec[i].branch<<"\n";
				}
				f1.close();
				f2.close();
				break;

			case 2:
				flag = 0;
				cout<<no;
				f1.open("index.txt", ios::in);
				cout<<"Enter the usn number:\n";
				cin>>st_usn;
				//cout<<st_usn;
				for(i=0; i<no; i++){
					f1.getline(rt_usn, 10, '|');
					f1.getline(st_no, 5, '\n');
					if(strcmp(rt_usn, st_usn) == 0){
						cout<<"record found\n";
						retrieve_data();
						flag = 1;
					}
				}
				if(flag!=1){
					cout<<"Not found\n";
				}
				f1.close();
				break;
			case 3:
				f1.open("index.txt", ios::in);
				cout<<"Enter the usn:\n";
				cin>>st_usn;
				flag = 0;
				for(i=0; i<no; i++){
					f1.getline(rt_usn, 10, '|');
					f1.getline(st_no, 5, '\n');

					if(strcmp(rt_usn, st_usn) == 0){
						delete_data(rt_usn);
						flag = 1;
					}
				}
				if(flag!=1){
						cout<<"Not found";
				}
				f1.close();
				break;
				case 4: 
					f2.open("record.txt", ios::in);
					for(i=0; i<no; i++){
						cout<<rec[i].name<<"\t"<<rec[i].usn<<"\t"<<rec[i].sem<<"\t"<<rec[i].branch<<"\n";
					}
					f2.close();
					break;
			default: exit(0);
		}
	}
}