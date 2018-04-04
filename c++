#include<iostream>
using namespace std;
int main()
{
	char *a = new char(100);
	char *b = new char(100);
	cin >> a >> b;
	int strl_a = strlen(a);
	int strl_b = strlen(b);
	int cont = 0;
	while (cont < strl_a - 1 - strl_b)
	{
		char *a_cmp = new char(strl_b);
		for (int i = 0; i < strl_b; i++)
		{
			a_cmp[i] = a[i + cont];
		}
		if (a_cmp == b)
		{
			for (int i = 0; i < cont - 1; i++)
				cout << a[i];
			delete  a_cmp, b, a;
			return 0;
		}
		cont++;
		delete a_cmp;
	}
	cout << "Not found";
	delete b, a;
	return 0;
}
