#include <fstream>
#include <iostream>
#include <conio.h>
using namespace std;

struct tax_payment {
	int    num;  // идентификационный номер компании
	char   name[10]; // название компании
	double sum;  // сумма налоговых платежей
}; 

int main(int argc, char *argv[])
{
	std::ofstream out(argv[1], std::ios::binary);
	if (!out) throw "Error";
	int n = atoi(argv[2]);
	tax_payment s;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter num: ";
		cin >> s.num;
		cin.get();
		cout << "Enter name: ";
		cin >> s.name;
		cout << "Enter sum: ";
		cin >> s.sum;
		out.write((char*)&s, sizeof(tax_payment));
	}
	out.close();
	return 0;

}
