#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>

#define fori(X) for (size_t i = 0; i < X; i++)
#define NAME_SIZE 128

using namespace std;

struct Employee {
	char name[NAME_SIZE];
	char surname[NAME_SIZE];
	size_t age;
};

//���������� ������ ����������
Employee* add_emp(Employee* elist, size_t& size, Employee new_emp) {
	Employee* new_elist = new Employee[size + 1];//����� ������ �� 1 ������
	for (size_t i = 0; i < size; i++)
		new_elist[i] = elist[i];
	new_elist[size] = new_emp;
	size++;
	delete[] elist;//�������� ������ ������
	return new_elist; //������� �����
}
//�������������� ����������
Employee* edit_emp(Employee* elist, Employee new_emp) {
	cout << (elist);
	return elist;
}

//�������� ����������
Employee* del_emp(Employee* elist, size_t& size, Employee* del_emp) {
	Employee* new_elist = new Employee[size -1];//����� ������ �� 1 ������
	Employee* tmp_pos = elist;
	fori(size) {
		if (tmp_pos == del_emp)
			if (i < size - 1)
				tmp_pos++;
			else
				break;
		*(new_elist+i) = *(tmp_pos++);
	}
	size--;
	delete[] elist;//�������� ������ ������
	return new_elist; //������� �����
}

Employee* search_by_surname(Employee* elist, size_t size, char* surname)
{
	fori(size)
		if (strstr(elist[i].surname, surname) != NULL)
			return elist + i;
}

void show_one_emp(Employee* elist) {
		cout << elist->name << " " << elist->surname << " "
		<< elist->age << " " << endl;
}

//����� ���������� ��� ���� �����������
void show_emp(Employee* elist, size_t& size) {
	fori(size)
		show_one_emp(elist + i);
}
