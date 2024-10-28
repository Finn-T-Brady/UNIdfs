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

	return 0;
}
