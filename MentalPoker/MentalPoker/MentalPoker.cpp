#include <iostream>
using namespace std;

int modPow(int a, int b, int mod)// ������� a^b(mod mod)
{
	int res = 1;
	for (int i = b; i > 0; i--)
	{
		res = res * a;
		if (res > mod)
		{
			res = fmod(res,mod);
		}
	}
	return res;
}

int SimpleRand()//��������� ���������� �������� �����
{
	int random;
	while(true)
	{
		random=rand()%4905+2;
		bool istrue=true;
		for(int i=2;i<(int)sqrt(random);i++)
			if (fmod(random,1)==0)
				{
					istrue=false;
					break;
				}
		if(istrue)
			break;
	}
	return random;
}

double gcd(double x, double y)//�������� ��������
{
	return y ? gcd(y, fmod(x,y)) : x;
}

int GenSecret(int n)
{
	int s;
	while(true)
	{
		s = rand()%(n-1)+1;
		if(gcd(n,s) == 1)
			break;
	}
	return s;
}

int Encrypt(int card, int key, int p)
{
	return modPow(card,key,p);
}
int Decrypt(int card, int key, int p)
{
	return modPow(card,key,p);
}

int Degree(int key, int p)
{
	p = p-1;
	int num = 1;
	while(true)
	{
		num = num + p;
		if(num%key == 0)
			return num/key;
	}
}

int main()
{
	setlocale(LC_ALL, "russian");
	int p, A, B, _A, _B, RandCard,
		card[52], Acard[52], Bcard[5], ABcard[10], BAcard[10],
		checkCard[10], memory[52], BAcheckCard[10], _ABAmixcard[5];
	p = SimpleRand();
	p=103;
	A=GenSecret(p);
	cout<<"p="<<p<<endl;
	cout<<"���� �����: "<<A<<endl;
	while(true)//��������� ����� ��� ����, ����� �� ������ � ������
	{
	B=GenSecret(p);
	if (B != A)
		break;
	}
	B=B+1;
	cout<<"���� ����: "<<B<<endl;
	_A = Degree(A,p);//����� ��� ������������
	_B = Degree(B,p);
	
	for (int i = 0 ; i < 52 ; i++)//���������� ���� � ���������� �����
	{
		card[i]=i+1;
		memory[i]=0;
		Acard[i]=Encrypt(card[i],A,p);
		if(i<10)
		{
			checkCard[i]=0;
			BAcheckCard[i]=0;
		}
	}
	cout<<"������ ����:\n";
	for(int i = 1 ; i < 53 ; i++)
	{
		cout<<card[i-1]<<" ";
		if (i%13 == 0)
			cout<<endl;
	}
	cout<<"������ ������������� ������ ����:\n";
	for(int i = 1 ; i < 53 ; i++)
	{
		cout<<Acard[i-1]<<" ";
		if (i%13 == 0)
			cout<<endl;
	}
	int Amixcard[52];
	
	for(int i = 0 ; i < 53 ; i++)//������������� ������������� ������ �����
	{
		int check = 0;
		while(true)
		{
			check=0;
			RandCard = rand()%53+1;
			for(int j = 0 ; j < 52 ; j++)
				if(RandCard != memory[j])
					check++;
			if(check == 52 )
				break;
		}
		memory[i]=RandCard;
		Amixcard[i] = Acard[RandCard-1];
	}
	cout<<"������ ������������ ������������� ������ ����:\n";
	for(int i = 1 ; i < 53 ; i++)
	{
		cout<<Amixcard[i-1]<<" ";
		if (i%13 == 0)
			cout<<endl;
	}

	for(int i = 0 ; i < 5 ; i++)//����� 5�� ��������� ���� ����� � ���������� �����
	{
		int check = 0;
		while(true)
		{
			RandCard = rand()%53+1;
			for(int j = 0 ; j < 5 ; j++)
				if(RandCard != checkCard[j])
					check++;
			if(check == 5 )
				break;
		}
		checkCard[i]=RandCard;
		BAcard[i] = Encrypt(Amixcard[RandCard],B,p);
	}
	cout<<"��� ������ � ���������� 5 ����:"<<endl;
	for(int i = 0 ; i < 5 ; i++)
		cout<<checkCard[i]+1<<"-�� "<<Amixcard[checkCard[i]]<<" : "<<BAcard[i]<<endl;
	int BAmixcard[10];
	for(int i = 0 ; i < 5 ; i++)//������������� 5�� ���� ������������� �����
	{
		int check = 0;
		while(true)
		{
			check = 0;
			RandCard = rand()%5+1;
			for(int j = 0 ; j < 5 ; j++)
				if(RandCard != BAcheckCard[j])
					check++;
			if(check == 5 )
				break;
		}
		BAcheckCard[i] = RandCard;
		BAmixcard[i] = BAcard[RandCard-1];
	}
	cout<<"��� ��������� �����:"<<endl;
	for(int i = 0 ; i < 5 ; i++)
		cout<<BAmixcard[i]<<" ";
	cout<<endl;
	cout<<"����� �������������� ����� ����:\n";
	for(int i = 0 ; i < 5 ; i ++)//����� �������������� ������������ ����� ����
	{
		_ABAmixcard[i] = Decrypt(BAmixcard[i],_A,p);
		cout<<_ABAmixcard<<" ";
	}
	cout<<endl<<"����� ����:\n";
	for(int i = 0 ; i < 5 ; i++)//��� ������������� ����� ���������� �����
	{
		Bcard[i]=Decrypt(_ABAmixcard[i],_B,p);
		cout<<Bcard[i];
	}
	cout<<endl;
	for(int i = 5 ; i < 10 ; i++)//����� ������ 5�� ��������� ���� �����
	{
		int check = 0;
		while(true)
		{
			check = 0;
			RandCard = rand()%53+1;
			for(int j = 0 ; j < 10 ; j++)
				if(RandCard != checkCard[j])
					check++;
			if(check == 10 )
				break;
		}
		checkCard[i]=RandCard;
		BAcard[i] = Acard[RandCard];
	}
	cout<<"��� ������ ������ 5 ����:"<<endl;
	for(int i = 5 ; i < 10 ; i++)
		cout<<checkCard[i]+1<<"-�� : "<<BAcard[i]<<endl;
	cout<<"����� �����:\n";
	for(int i = 5 ; i < 10 ; i++)//����� �������������� 5 ����
		cout<<Decrypt(BAcard[i],_A,p)<<" ";
	cout<<endl;
	system("pause");
	return 0;
}
