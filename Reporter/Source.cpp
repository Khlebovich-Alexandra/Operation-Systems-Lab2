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
	std::ifstream in(argv[1], ios::binary);
	std::ofstream out(argv[2]);
	if (!out) throw "Error";
	if (!in) throw "Error.";
	int number = atoi(argv[3]);
	cout << number;
	char sign = argv[4][0];
	int i = 0;
	in.seekg(0, std::ios::end);
	int numOfStud = (int)(in.tellg() / sizeof(tax_payment));
	in.seekg(0, std::ios::beg);
	tax_payment tmp;
	out << "File report " << argv[1] << endl;
	out << "List of companies whose tax payments " << argv[4][0] << " " << number << endl;
	while (i < numOfStud)
	{
		in.read((char*)&tmp, sizeof(tax_payment));
		if (sign == '>')
		{
			if (tmp.sum > number)
			{
				out << tmp.num << ' ' << tmp.name << ' ' << tmp.sum << endl;
			}
		}
		else
		{
			if (tmp.sum < number)
			{
				out << tmp.num << ' ' << tmp.name << ' ' << tmp.sum << endl;
			}
		}
		i++;
	}

	out.close();
	system("pause");
	return 0;
}
