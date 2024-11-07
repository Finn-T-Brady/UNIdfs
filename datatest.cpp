#include <iostream>
#include "Path.h"
using namespace std;
int main(){
	point a,b;
	a.x=7;
	a.y=8;
	b.x=8;
	b.y=7;
	
	cout<<"A:"<<(int)a.x<<','<<(int)a.y<<':'<<a.c<<'\n';
	cout<<"B:"<<(int)b.x<<','<<(int)b.y<<':'<<b.c<<'\n';

	b.x=7;
	b.y=8;
	if(a.c==b.c)cout<<"!!!\n";
	
	
	a.x=5;
	a.y=2;
	b.x=1;
	b.y=2;
	point c = a+b;
	cout<<"A:"<<a.x<<','<<a.y<<':'<<a.c<<'\n';
	cout<<"B:"<<b.x<<','<<b.y<<':'<<b.c<<'\n';
	cout<<"A+B:"<<c.x<<','<<c.y<<':'<<c.c<<'\n';
	cout<<'\n';	
	a.x=65000;
	a.y=0;
	b.x=10000;
	b.y=0;
	c=a+b;
	cout<<"A:"<<a.x<<','<<a.y<<':'<<a.c<<'\n';
	cout<<"B:"<<b.x<<','<<b.y<<':'<<b.c<<'\n';
	cout<<"A+B:"<<c.x<<','<<c.y<<':'<<c.c<<'\n';
	cout<<'\n';

	a.c=-1;
	cout<<"A:"<<a.x<<','<<a.y<<':'<<a.c<<'\n';
	
	return 0;
}
