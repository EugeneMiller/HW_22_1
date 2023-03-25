/*Evgenij Melnik*/
#include <iostream>
#include <io.h>
#include "Employee.h"


#define polustroka "Hello"
#undef polustroka 
#define polustroka(s) #s
#define conc(a,b,c) #a## #b## #c
#define say_goodbye true



using namespace std;

/*������� 1. �������� �������������� ������� �����������. 
��������� ������ ������������ ���� ������,
�������������� ������ ����������, �������� ����������,
����� ���������� �� �������, ����� ���������� ���
���� �����������, ���������� ��������, ��� �������
������� ���������� �� ��������� �����. �����������
����������� ���������� ��������� ���������� � ����.
����� ���� ������ ����������� ����������� � ���� (���
������ �� ��������� � �������������, � �������� 
���������� ��������� � �� ������� ������������). ���
������ ��������� ���������� �������� ������ ����������� 
�� ���������� ������������� �����.*/

void save_data(char * filename, size_t size, Employee *elist ) {
	FILE* fp;
	if (fopen_s(&fp, filename, "wb") != 0)
		cout << "Couldn't open file " << filename << endl;
	else {
		fwrite(&size, sizeof(size_t), 1, fp);//�������� ���-�� �����������
		if (size)
			fori(size)
			fwrite(&elist[i], sizeof(Employee), 1, fp);
		fclose(fp);
	}
}



int main() {
	Employee* elist{ nullptr };//������ �����������
	FILE* fp;
	char filename[] = "1.ebd";//�������� ����
	size_t size{};//���-�� ������� � ����
	char choice{'e'};
	struct _finddata_t fileinfo;//������ � �����

	long done = _findfirst("*.ebd", &fileinfo);
	cout << fileinfo.name << " - " << fileinfo.size << endl;
	/*while (done != -1) {
		cout << fileinfo.name << " - " << fileinfo.size << endl;
		done = _findnext(done, &fileinfo);
	}*/
	//1- ������ ���� �� �����
	if (fopen_s(&fp, filename, "rb") != 0) {
		cout << "Couldn't open file " << filename << endl;
		if (fopen_s(&fp, filename, "wb") != 0) {
			cout << "Error creating file";
			return 0;
		}
		else {
			fclose(fp);
			size = 0;
		}
	}
	else {
		if (fread(&size, sizeof(size_t), 1, fp) == 0)//�������� ���������� ����������� 
			size = 0;
		else if (size) {
			elist = new Employee[size];
			fori(size) {
				if (fread(&elist[i], sizeof(Employee), 1, fp) == 0) {//�������� ���������� ����������� 
					size = i;
					cout << "Database corrupted!";
					break;
				}
			}
		}
		fclose(fp);
	}

	//���� -  ������ �� ������� �����������
	do {
		cout << " Choose action:\n 1 - New employee\n 2 - Edit employee\n "
			<< "\n 3 - Show all\n 4 - Search by surname\n e - Exit\n";
		cin >> choice;
		switch (choice) {
		case '1'://���� ����������
			Employee new_emp;
			cout << "Name:";
			cin >> new_emp.name;
			cout << "\nSurname:";
			cin >> new_emp.surname;
			cout << "\nAge:";
			cin >> new_emp.age;
			elist = add_emp(elist, size, new_emp);
			break;
		case '2':
			size_t num;
			cout << "Employee number:";
			cin >> num;
			cout << "New name:";
			cin >> new_emp.name;
			cout << "\nNew surname:";
			cin >> new_emp.surname;
			cout << "\nNew age:";
			cin >> new_emp.age;
			if (num < size)
				edit_emp(elist + num, new_emp);
			else
				cout << "No such element!"<<endl;
			break;
		case '3':
			show_emp(elist,size);
			break;
		case '4':
			char surname[NAME_SIZE];
			Employee* result;//��������� �� ����, ���� ����
			char ans;
			cout << "Enter surname:";
			cin >> surname;
			result = search_by_surname(elist, size, surname);
			show_one_emp(result);
			cout << "Delete? y|n";
			cin >> ans;
			if (ans == 'y' || ans == 'Y')
				elist = del_emp(elist, size, result);
			break;
		default:
				choice = 'e';
		}
	} while (choice != 'e');
	/*
#if say_goodbye==true
	cout << polustroka(Hello) << " world" << endl;
#elif say_goodbye==false
	cout << "Goodbye";
#endif
	cout << conc(How, Are, You);*/
	//2 - ������ ����������� � ����
	save_data(filename, size, elist);

	return 0;
}