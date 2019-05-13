#include <windows.h>
#include <fstream>
#include <conio.h>
#include <iostream>
#pragma warning(disable : 4996)
using namespace std;
struct tax_payment {
	int    num;  // идентификационный номер компании
	char   name[10]; // название компании
	double sum;  // сумма налоговых платежей
};
int main()
{
	char lpszCommandLine[100]; 
	strcpy(lpszCommandLine, "Creator.exe ");
	char nameIn[30];
	int number;
	char numberOfRecords[5];
	cout << "Enter name: ";
	cin >> nameIn;
	cout << "Enter number of records: ";
	cin >> number;
	itoa(number, numberOfRecords, 10);
	strcat(lpszCommandLine, nameIn);
	strcat(lpszCommandLine, " ");
	strcat(lpszCommandLine, numberOfRecords);
	STARTUPINFO si;
	PROCESS_INFORMATION piCreator;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	// создаем новый консольный процесс
	CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCreator);
	// закрываем дескрипторы этого процесса
	WaitForSingleObject(piCreator.hProcess, INFINITE);
	ifstream in(nameIn, ios::binary);
	int i = 0;	
	if (!in) throw "Error.";
	in.seekg(0, std::ios::end);
	int numOfStud = (int)(in.tellg() / sizeof(tax_payment));
	in.seekg(0, std::ios::beg);
	tax_payment tmp;
	while (i < numOfStud)
	{
		in.read((char*)&tmp, sizeof(tax_payment));
		cout << tmp.num << ' ' << tmp.name << ' ' << tmp.sum << endl;
		i++;
	}
	in.close();
	char nameOut[30];
	int num;
	char numb[5];
	char signTmp;
	char sign[2];
	cout << "Enter name of report: ";
	cin >> nameOut;
	cout << "Enter number of payments: ";
	cin >> num;
	cin.get();
	cout << "Enter sign: ";
	cin.get(signTmp);
	sign[0] = signTmp;
	sign[1] = '\n';
	itoa(num, numb, 10);
	strcpy(lpszCommandLine, "Reporter.exe ");
	strcat(lpszCommandLine, nameIn);
	strcat(lpszCommandLine, " ");
	strcat(lpszCommandLine, nameOut);
	strcat(lpszCommandLine, " ");
	strcat(lpszCommandLine, numb);
	strcat(lpszCommandLine, " ");
	strcat(lpszCommandLine, sign);

	PROCESS_INFORMATION piReporter;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	// создаем новый консольный процесс
	CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piReporter);
	// закрываем дескрипторы этого процесса
	WaitForSingleObject(piReporter.hProcess, INFINITE);
	CloseHandle(piCreator.hThread);
	CloseHandle(piCreator.hProcess);
	CloseHandle(piReporter.hThread);
	CloseHandle(piReporter.hProcess);

	system("pause");
	return 0;
}