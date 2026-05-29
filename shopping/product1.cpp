#include <iostream>
#include<cstdio>
#include<unistd.h>
#include<stdlib.h>
#include <stdio_ext.h>
using namespace std;
#include "Bank1.cpp"
#define MAX 5
int i,j;
bool flag;
class Bank;
typedef struct product
{
	string name;
	int quantity;
	float price;
}product;
class Product 
{
	product prod[MAX];
	float total=0;
	public:
	void Shopping(void)
	{
		total=0;
	}
	void AddToCart()
	{
		cout<<"enter the name of product:";
		cin>>prod[i].name;
		cout<<"enter the quantity::";
		cin>>prod[i].quantity;
		cout<<"enter the price::";
		cin>>prod[i].price;
		i++;
	}
	void ViewCart()
	{
		for(j=0;j<i;j++,cout<<endl)
			cout<<prod[j].name<<"  "<<prod[j].quantity<<"  "<<prod[j].price;
	}
	float TotalBill()
	{
		total=0;
		for(j=0;j<i;j++)
		{
			total+=(prod[j].quantity*prod[j].price);
		}
		return total;		
	} 
	bool PayBill(Bank &b)
	{
		float bill=TotalBill();
		cout<<"enter the password::";
		long p;
		cin>>p;
		if(p==b.password)
		{
			if(b.balance<bill)
			{
				cout<<"insufficient funds"<<endl;
				return false;
			}
			else
			{
				b.balance-=bill;
				cout<<"sucessfully paid the bill"<<endl;
				i=0;
				Shopping();
				return true;
			}
		}
		else
		{
			cout<<"incorrect password"<<endl;
			return false;
		}
	}          
	void Menu(Bank &b)
	{
		int choice;
		int totalAmount;
		while(1)
		{
			cout<<"1.add to cart   2.view cart  3.total bill  4.PayBill  5.exit"<<endl;
			__fpurge(stdin);
			cout<<"enter your choice::";
			cin>>choice;
			switch(choice)
			{
				case 1:if(i==MAX)
					       cout<<"cart is Full"<<endl;
				       else
					       AddToCart();
				       break;
				case 2:if(i==0)
					       cout<<"empty list"<<endl;
				       else
					       ViewCart();
				       break;
				case 3:totalAmount=TotalBill();
				       cout<<totalAmount<<endl;
				       break;
				case 4:flag=PayBill(b);
				       if(flag)
				       {
					       Shopping();
					       b.check_balance();
					       i=0;
				       }
				       break;
				case 5:exit(0);	
			}	
		}
	}
};

int main()
{
	Bank b;
	Product main;
	int choice;
	main.Menu(b);	
}
