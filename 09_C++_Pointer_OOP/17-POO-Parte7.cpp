/*

POO - Parte 7 (Controle de Acesso)

*/


#include <iostream>
using namespace std;
 
class Data 
{
	int vDia;
	int vMes; 
	int vAno; 
 
public:

	void setDate(int dia, int mes, int ano)
	{
		vDia = dia;
		vMes = mes;
		vAno = ano;
	}
 
	void print()
	{
		cout << vDia << '/' << vMes << '/' << vAno;
	}
 
	void copyFrom(const Data d)
	{
		vDia = d.vDia;
		vMes = d.vMes;
		vAno = d.vAno;
	}
};
 
int main()
{
	Data data1;

	data1.setDate(14, 10, 2021); 
	
	Data data2;

	data2.copyFrom(data1);
	
    data2.print();
	
    cout << '\n';
 
	return 0;
}
