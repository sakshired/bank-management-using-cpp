#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<iomanip.h>
#include<string.h>
#include<process.h>
int acc;float amt;int flag=0,pos=0;
class employee
{ char empname[30];
  int empid;
  char pass[11];
  char des[25];
  char branch[25];
  float sal;
 public:
  void getdata();
  void showdata();
  int retempid()
  {return empid;}
  char* retpass()
  {return pass;}
}e;
class account
{ char name[15],acctype[10],employed;
  int age;
  int accno;
  float balance;
 public:
 account()
 {strcpy(name,"default");
  strcpy(acctype,"default");
  employed='n';
  age=0;
  accno=11200;
  balance=0.0;
 }
 void get();
 void getno();
 void show();
 void withdraw(float amt)
 {balance-=amt;}
 void deposit(float amt)
 {balance+=amt;}
 int retaccno()
 {return accno;}
 void cbalance()
 {cout<<"\nYOUR CURRENT BALANCE IS :"<<balance;
 }
}a;
void account::getno()                        //TO GET ACCOUNT NUMBER
{
 int n;
 ifstream fin("account.dat",ios::binary);
 fin.seekg(0,ios::end);
 n=fin.tellg()/sizeof(account);
 accno+=n;
}
void account::get()
{
 cout<<"\nENTER THE FOLLOWING DETAILS\n";
 cout<<"\n Name:";
 gets(name);
 cout<<"\n Type of account:";
 gets(acctype);
 cout<<"\n Age:";
 cin>>age;
 cout<<"\n Are you employed?(y/n)";
 cin>>employed;
 cout<<"\n\n";
}
void account::show()
{
 cout<<accno<<"\t\t"<<acctype<<"\t\t"<<name<<"\t"<<age;
 cout<<"\t"<<employed<<"\t\t"<<balance<<endl;
}
void employee::getdata()
{
 cout<<"\nEnter the following details\n";
 cout<<"\n Employee ID:";
 cin>>empid;
 cout<<"\nEnter your password(10 characters):";
 gets(pass);
 cout<<"\n Name of employee:";
 gets(empname);
 cout<<"\n Designation:";
 gets(des);
 cout<<"\n Branch name:";
 gets(branch);
 cout<<"\n Salary:";
 cin>>sal;
 cout<<endl<<endl;
}
void employee::showdata()
{
 cout<<empname<<"\t"<<empid<<"\t\t"<<des<<"\t\t"<<branch<<"\t\t"<<sal<<endl;
}
void enter()                 //FUNCTION TO ENTER EMPLOYEE DETAILS
{
 ofstream fout("empf.dat",ios::binary|ios::app);
 e.getdata();
 fout.write((char*)&e,sizeof(e));
 fout.close();
}
void show()            //FUNCTION TO DISPLAY EMPLOYEE DETAILS
{
 ifstream fin("empf.dat",ios::binary);
 cout<<"\nNAME\t\tEMPLOYEE ID\tDESIGNATION\tBRANCH\t\tSALARY\n";
 while(fin.read((char*)&e,sizeof(e)))
 {e.showdata();
  cout<<"------------------------------------------------------------------------\n";
 }
 fin.close();
}
void modifyem()                //FUNCTION TO MODIFY EMPLOYEE DETAILS
{
 fstream f("empf.dat",ios::binary|ios::in|ios::out);
 int eid;
 cout<<"\nenter your employee id:";
 cin>>eid;
 while(!f.eof())
while(!f.eof())
 {
 pos=f.tellg();
 f.read((char*)&e,sizeof(e));
 if(eid==e.retempid())
 {
  e.getdata();
  f.seekp(pos,ios::beg);
  f.write((char*)&e,sizeof(e));
  cout<<"\nAccount modified";flag=1;
  break;
 }
 }
 f.close();
 if(flag==0)
 cout<<"\nAccount not found";
}
void create_acc()                 //FUNCTION TO CREATE AN ACCOUNT
{
 ofstream f("account.dat",ios::binary|ios::app);
 a.get();
 a.getno();
 f.write((char*)&a,sizeof(a));
 cout<<"\nACOUNT CREATED SUCCESSFULLY!!\n";
 cout<<"\nYOUR ACCOUNT NUMBER IS "<<a.retaccno();
 f.close();
}
void withdraw()                      //FUNCTION TO WITHDRAW MONEY
{
 fstream f("account.dat",ios::binary|ios::in|ios::out);
 cout<<"\nEnter your account number:";cin>>acc;
 cout<<"\nEnter the amount you want to withdraw:";cin>>amt;
 while(!f.eof())
 { pos=f.tellg();
   f.read((char*)&a,sizeof(a));
   if(acc==a.retaccno())
   { a.withdraw(amt);
     f.seekp(pos,ios::beg);
     f.write((char*)&a,sizeof(a));
     flag=1;
     cout<<"\nMONEY WITHDRAWN SUCCESSFULLY";
     break;
   }
 }
 f.close();
 if(flag==0)
 cout<<"\nACCOUNT DOESNOT EXIST";
}
void deposit()                            //FUNCTION TO DEPOSIT MONEY
{
 fstream f("account.dat",ios::binary|ios::in|ios::out);
 cout<<"\nEnter your account number:";
 cin>>acc;
 cout<<"\nEnter the money you want to deposited:";
 cin>>amt;
 while(!f.eof())
 {pos=f.tellg();
  f.read((char*)&a,sizeof(a));
  if(acc==a.retaccno())
  {a.deposit(amt);
   f.seekp(pos,ios::beg);
   f.write((char*)&a,sizeof(a));
   flag=1;
   cout<<"\nMONEY DEPOSITED SUCCESSFULLY";
   break;
  }
 }
 if(flag==0)
 cout<<"\nACCOUNT DOESNOT EXIST";
 f.close();
}
void show_account()             //FUNCTION TO DISPLAY ALL ACCOUNT DETAILS
{
 ifstream fin("account.dat",ios::binary);
 cout<<"\nAccount no.\tAccount type\tAccount Holder";
 cout<<"\tAge\tEmployed\tBalance"<<endl;
 while(fin.read((char*)&a,sizeof(a)))
 {a.show();
  cout<<"---------------------------------------------------------------------------\n";
 }
 fin.close();
}
void check()               //FUNCTION TO CHECK CURRENT BALANCE
{
 ifstream fin("account.dat",ios::binary);
 cout<<"\nEnter your account number:";cin>>acc;
 while(fin.read((char*)&a,sizeof(a)))
 {
 if(acc==a.retaccno())
 {flag=1;
  a.cbalance();
 }
 }
 fin.close();
 if(flag==0)
 cout<<"\nAccount not found";
}
void modifyac()         //FUNCTION TO MODIFY ACCOUNT DETAILS
{
 fstream f("account.dat",ios::binary|ios::in|ios::out);
 cout<<"\nEnter your account number:";
 cin>>acc;
 while(!f.eof())
 {
 pos=f.tellg();
 f.read((char*)&a,sizeof(a));
 if(acc==a.retaccno())
 {
  a.get();
  f.seekp(pos,ios::beg);
  f.write((char*)&a,sizeof(a));
  flag=1;
  cout<<"\nACCOUNT MODIFIED";
  break;
 }
 }
 f.close();
 if(flag==0)
 cout<<"\nACCOUNT NOT FOUND";
}
int checkpass()
{
char p[11];int eid,i=0;
cout<<"\n\n\n\n\n\t\tEnter employee ID:";cin>>eid;
cout<<"\t\tEnter password:";
while(i<10)
{p[i]=getch();
cout<<"*";
i++;
}
getch();
ifstream fin("empf.dat",ios::binary);
while(fin.read((char*)&e,sizeof(e)))
{
 if(eid==e.retempid())
 {
  if(strcmp(e.retpass(),p)==0)
  flag=1;
 }
}
fin.close();
return flag;
}
void main()
{
 int ch,op,i;
 char cho;
 do
 {
 clrscr();
 cout<<setw(40)<<"ABC BANK\n";
 cout<<"---------------------------------------------------------------------------";
 cout<<endl<<endl<<endl<<endl;
 cout<<"\t\t\tWELCOME TO ABC BANK\n\n";
 cout<<"1.Employee\n";
 cout<<"2.Customer\n";
 cout<<"Enter your choice:";cin>>ch;
 clrscr();
 switch(ch)
 {case 1:cout<<"\nCHOOSE YOUR OPTION:";
	 cout<<"\n1.Enter employee details";
	 cout<<"\n2.Show employee details";
	 cout<<"\n3.Modify employee details";
	 cout<<"\n4.Show details of all bank accounts";
	 cout<<"\n5.Exit";
	 cout<<"\nOption:";cin>>op;
	 switch(op)
	 {case 1:enter();
		 break;
	  case 2:i=checkpass();
		if(i==0)
{cout<<"\nINCORRECT EMPLOYEE ID AND PASSWORD";break;}
		 cout<<endl;show();break;
	  case 3:
		 i=checkpass();
		 if(i==0)
{cout<<"\nINCORRECT EMPLOYEE ID AND PASSWORD";break;}
		 cout<<endl;modifyem();
		 break;
	  case 4:
		i=checkpass();
		if(i==0)
{cout<<"\nINCORRECT EMPLOYEE ID AND PASSWORD";break;}
		 cout<<endl;show_account();
		 break;
	  case 5:exit(0);
	 }
	 break;
  case 2:cout<<"\nCHOOSE YOUR OPTION:";
	 cout<<"\n1.Create an account";
	 cout<<"\n2.Deposit money";
	 cout<<"\n3.Withdraw money";
	 cout<<"\n4.Check balance";
	 cout<<"\n5.Modify account details";
	 cout<<"\nOption:";
	 cin>>op;
	 switch(op)
	 {case 1:create_acc();
		 break;
	  case 2:deposit();
		 break;
	  case 3:withdraw();
		 break;
	  case 4:check();
		 break;
	  case 5:modifyac();
		 break;
	 }
	 break;
 default:cout<<"\nINVALID CHOICE!!";
}
 cout<<"\nGO BACK TO MAIN PAGE?(y/n)";
 cin>>cho;
}while(cho=='y');
getch();}
