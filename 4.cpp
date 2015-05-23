/*
	4. Write a C++ program to write student objects with Variable – Length records using
	any suitable record structure and to read from this file a student record using RRN.
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class student{
	public:
		char name[10];
		char usn[10];
		char sem[5];
		char age[5];
		char branch[5];
}s;

fstream fp;

void write(){
	//pass
	int n,i;

	fp.open("student.txt", ios::out | ios::app);
	if(!fp){
		cout<<"Unable to open the file\n";
	}

	cout<<"Enter the number of students\n";
	cin>>n;

	for(i=0; i<n; i++){
		cout<<"Enter the name\n";
		cin>>s.name;
		cout<<"Enter the usn\n";
		cin>>s.usn;
		cout<<"Enter the sem\n";
		cin>>s.sem;
		cout<<"Enter the age\n";
		cin>>s.age;
		cout<<"Enter the branch\n";
		cin>>s.branch;

		fp<<i<<"|"<<s.name<<"|"<<s.usn<<"|"<<s.sem<<"|"<<s.age<<"|"<<s.branch<<"\n";
	}
	fp.close();
}
void display(){
	//pass
	student s;
	char rrn[5];
	int i;

	fp.open("student.txt", ios::in);
	if(!fp){
		cout<<"Unable to open \n";
	}

	while(!fp.eof()){
		fp.getline(rrn , 4, '|');
		fp.getline(s.name , 10, '|');
		fp.getline(s.usn , 10, '|');
		fp.getline(s.sem , 5, '|');
		fp.getline(s.age , 5, '|');
		fp.getline(s.branch, 5, '\n');

		cout<<rrn<<"\t"<<s.name<<"\t"<<s.usn<<"\t"<<s.sem<<"\t"<<s.age<<"\t"<<s.branch<<"\n";
	}
	fp.close();
}

void search(){
	//pass
	student std[10];
	char rrn[5];
	char rrn1[10][15];
	int i,j, flag=-1;
	fp.open("student.txt", ios::in);
	cout<<"Enter the rrn number\n";
	cin>>rrn;
	i=0;
	while(!fp.eof()){
		fp.getline(rrn1[i], 4, '|');
		fp.getline(std[i].name, 10, '|');
		fp.getline(std[i].usn, 10, '|');
		fp.getline(std[i].sem, 5, '|');
		fp.getline(std[i].age, 5, '|');
		fp.getline(std[i].branch, 5, '\n');
		i++;
	}
		i--;
		for(j=0; j<i; j++){
			if(strcmp(rrn1[j], rrn) == 0){
				flag = 1;
				cout<<"RRN found";
				cout<<"RRN\tName\tUSN\tSemester\tAge\tBranch\n";
				cout<<rrn<<"\t"<<std[j].name<<"\t"<<std[j].usn<<
		"\t"<<std[j].age<<"\t"<<std[j].sem<<"\t"<<std[j].branch<<"\n";
				break;
			}
		}
		if(flag == -1){
			cout<<"RRN not found\n";
		}
		fp.close();
	}

int main(void){
	int choice;
	do{
		cout<<"1. Write\n2.Search\n3. Display\n";
		cout<<"Enter your choice:\n";
		cin>>choice;
		switch(choice){
			case 1:
				write();
				break;
			case 2:
				search();
				break;
			case 3:
				display();
				break; 
			default:
				cout<<"Invalid Entry\n";
				break;
		}
	}while(choice>0 && choice <4);
}