#include<iostream>
using namespace std;
int passwordCount;
class Bank
{
	int account_no;
	string name;
	static int cnt;
	const static int password=12345;
	long int mobile_no;
	float balance;
	public :
	Bank()
	{
		/*	cout<<"enter the name::";
			cin>>name;
			cout<<"enter the mobile no::";
			cin>>mobile_no;
		//	cout<<"enter the amount to be added :";
		//	cin>>balance;*/
		name="venu";
		mobile_no=9885797985;
		balance=200000;
		cnt++;
		account_no=cnt;
	}
	int passwordCheck(int a)
	{
		if(a==password)
			return 1;
		else
			return 0;
	}
	void print()
	{
		cout<<"account ::"<<account_no<<endl;
		cout<<"name ::"<<name<<endl;
		cout<<"mobile no ::"<<mobile_no<<endl;
		cout<<"balance ::"<<balance<<endl;
		cout<<"------------------------------"<<endl;
	}
	void check_balance()
	{
		cout<<"current balance="<<balance<<endl;
	}
	void deposit(float a)
	{
		balance=a+balance;	
	}
	bool withdraw(float a)
	{
		if(balance<a)
			return false;
		balance=balance-a;
		return true;	
	}
	int transfer(float a,int a_c,Bank *arr)
	{
		int i;
		int flag1=0;
		if(a>balance)
			return 0;
		for(i=1;i<5;i++)
		{
			if(arr[i].account_no==a_c)
			{
				break;
			}
		}
		if(i<5)
		{
			flag1=arr[0].withdraw(a);
			arr[i].deposit(a);
		}
		else if(i==5)
			return i;
		return flag1;	
	}
	bool PayBill(int bill)
	{
		cout<<"enter the password::";
		long p;
		cin>>p;
		if(p==password)
		{
			if(balance<bill)
			{
				cout<<"insufficient funds"<<endl;
				return false;
			}
			else
			{
				balance-=bill;
				cout<<"sucessfully paid the bill"<<endl;
				return true;
			}
		}
		else
		{
			cout<<"incorrect password"<<endl;
			return false;
		}
	}
	friend class MENU;
};
int Bank :: cnt;
const int Bank :: password;
