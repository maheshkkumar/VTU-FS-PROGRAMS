#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

using namespace std;

class student{
public:
	char name[10];
	char usn[10];
	char sem[5];
	char branch[5];
}rec[10], found[10];

char st_no[5], rt_name[10];
int no;

void sort(){
	student temp;
	int i,j;
	for(i=0; i<no-1; i++){
		for(j=0; j<no-i-1; j++){
			if(strcmp(rec[j].name, rec[j+1].name)>0){
				temp = rec[j];
				rec[j] = rec[j+1];
				rec[j+1] = temp;
			}
		}
	}
}

void write(){
	fstream f1, f2;
	int i;
	f1.open("index.txt", ios::out);
	f2.open("record.txt", ios::out);
	for(i=0; i<no; i++){
		f1<<rec[i].name<<"|"<<rec[i].usn<<"|"<<i<<"\n";
		f2<<i<<"|"<<rec[i].name<<"|"<<rec[i].usn<<"|"<<rec[i].sem<<"|"<<rec[i].branch<<"\n";
	}
	f1.close();
	f2.close();
}

void retrieve(char ind[5]){
	fstream fp;
	int i;
	char name[10];
	char usn[10];
	char sem[5];
	char branch[5];
	char index[5];
	fp.open("record.txt", ios::in);
	for(i=0; i<no; i++){
		fp.getline(index, 5, '|');
		fp.getline(name, 10, '|');
		fp.getline(usn, 10, '|');
		fp.getline(sem, 5, '|');
		fp.getline(branch, 5, '\n');

		if(strcmp(index, ind) == 0){
			cout<<name<<"\t"<<usn<<"\t"<<sem<<"\t"<<branch<<"\n";
		}
	}
	fp.close();
}


void retrieve_details(){
	int i, k=0;
	fstream fp;
	char name[10];
	char usn[10];
	char sem[5];
	char branch[5];
	char index[5];
	char ind[10][10];
	char chusn[10];
	fp.open("index.txt", ios::in);
	for(i=0; i<no; i++){
		fp.getline(name, 10, '|');
		fp.getline(usn, 10, '|');
		fp.getline(index, 5, '\n');

		if(strcmp(name, rt_name) == 0){
			strcpy(found[k].name, name);
			strcpy(found[k].usn, usn);
			strcpy(ind[k], index);
			k++;
		}
	}
	fp.close();

	if(k==1){
		retrieve(ind[0]);
		return;
	}
	else{
		for(i=0; i<k; i++){
			cout<<found[i].name<<"\t"<<found[i].usn<<"\t"<<ind[i]<<"\n";
		}
		cout<<"Enter the usn:\n";
		cin>>chusn;
		for(i=0; i<k; i++){
			if(strcmp(found[i].usn, chusn) == 0){
				retrieve(ind[i]);
			}
		}
	}
	cout<<"Invalid entry:\n";
}

void delete_index(char ind[5]){
	fstream fp, f2;
	char name[10];
	char usn[10];
	char sem[5];
	char branch[5];
	char index[5];
	char id[10][10];
	int i;
	
	fp.open("record.txt", ios::in);
	for(i=0; i<no; i++){
		fp.getline(index, 5, '|');
		fp.getline(name, 10, '|');
		fp.getline(usn, 10, '|');
		fp.getline(sem, 5, '|');
		fp.getline(branch, 5, '|');

		strcpy(rec[i].name, name);
		strcpy(rec[i].usn, usn);
		strcpy(rec[i].sem, sem);
		strcpy(rec[i].branch, branch);
		strcpy(id[i], index);
	}
	int flag = -1;
	for(i=0; i<no; i++){
		if(strcmp(index, ind) == 0){	
			flag = i;	
		}	
	}
	if(flag == (no-1)){
		no--;
		cout<<"Record delete\n";
	}
	fp.close();

	for(i=flag; i<no; i++){
		rec[i]= rec[i+1];
		cout<<"Record Deleted\n";
	}
	no--;
	fp.open("index.txt", ios::out);
	f2.open("record.txt", ios::out);
	for(i=0; i<no; i++){
		fp<<rec[i].name<<"|"<<rec[i].usn<<"|"<<i<<"\n";
		f2<<rec[i].name<<"|"<<rec[i].usn<<"|"<<rec[i].sem<<"|"<<rec[i].branch<<"\n";
	}
	fp.close();
	f2.close();
	
}

void delete_data(char n[10]){
	fstream fp;
	char name[10];
	char usn[10];
	char sem[5];
	char branch[5];
	char index[5];
	char ind[10][10];
	char chusn[10];
	int i, k=0;
	fp.open("index.txt", ios::in);

	for(i=0; i<no; i++){
		fp.getline(name, 10, '|');
		fp.getline(usn, 10, '|');
		fp.getline(index, 5, '\n');

		if(strcmp(name, n) == 0){
			strcpy(found[k].name, name);
			strcpy(found[k].usn, usn);
			strcpy(ind[i], index);
			k++;
		}
	}
	if(k == 1){
		delete_index(ind[0]);
	}

	for(i=0; i<k; i++){
		cout<<found[i].name<<"\t"<<found[i].usn<<"\n";
	}

	cout<<"Enter the usn\n";
	cin>>chusn;

	for(i=0; i<k; i++){
		if(strcmp(chusn, found[i].usn) == 0){
			delete_index(ind[i]);
		}
	}
	fp.close();
}


int main(void){
	char name[10];
	char usn[10];
	char sem[5];
	char branch[5];
	char st_usn[10], rt_usn[10], st_name[10];
	fstream f1, f2;
	int flag, i;
	int choice;

	for(;;){
		cout<<"1.Write\n2.Search\n3.Delete\n";
		cout<"Enter your choice:\n";
		cin>>choice;

		switch(choice){
			case 1:
				cout<<"Enter the number of students: \n";
				cin>>no;
				for(i=0; i<no; i++){
					cout<<"Name:\n";
					cin>>rec[i].name;
					cout<<"USN:\n";
					cin>>rec[i].usn;
					cout<<"Semester:\n";
					cin>>rec[i].sem;
					cout<<"Branch:\n";
					cin>>rec[i].branch;
				}
				sort();
				write();
				break;
			case 2:
				f1.open("index.txt", ios::in);
				if(!f1){
					cout<<"Error in opening the file\n.";
				}
				cout<<"Enter the name of the student, you want to search:\n";
				cin>>st_name;
				flag = 0;
				for(i=0; i<no; i++){
					f1.getline(rt_name, 10, '|');
					f1.getline(st_usn, 10, '|');
					f1.getline(st_no, 5, '\n');

					if(strcmp(rt_name, st_name) == 0){
						retrieve_details();
						flag = 1;
					}
				}
				if(flag!=1){
					cout<<"Name not found.\n";
				}
				f1.close();
				break;
			case 3:
				f1.open("index.txt", ios::in);
				cout<<"Enter the name you want to delete:\n";
				cin>>st_name;
				flag = 0;
				for(i=0; i<no; i++){
					f1.getline(rt_name, 10, '|');
					f1.getline(st_usn, 10, '|');
					f1.getline(st_no, 5, '\n');

					if(strcmp(rt_name, st_name) == 0){
						delete_data(rt_name);
						flag = 1;
					}
					if(flag!=1){
						cout<<"Not found\n";
					}
					f1.close();
					break;
				}
			default: 
				cout<<"Invalid Entry\n";
				break;
		}
	}
}