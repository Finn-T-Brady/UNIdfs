#include "Path.h"
#include "maze.h"
#include <iostream>

point dirs[8] = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};

int main(){

	//Standard Case
	char* MD="111111111111111111110001111100000111110001110111110110110111110111010111111111011111111011011111100000011111111111111111";
/*	111111111111
	111111110001
	111100000111
	110001110111
	110110110111
	110111010111
	111111011111
	111011011111
	100000011111
	111111111111	*/
	short width=12,height=10;


	//Simple Case
//	char* MD="11111111100101011110101111101011111010111001101111111111";
/*	11111111
 	10010101
 	11101011
 	11101011
 	11101011
 	10011011
 	11111111	*/
//	short int width=8,height=7;

	Maze A(width,height,MD);
	A.MixPrint();
	
	Path* Tail;
	Tail=nullptr;

	int dir=0;
	point Pos{1,height-2};
	point lPos=Pos;
	point CheckPos;
	
	point End{width-2,1};

	if(A.Cdata(Pos)==8){
		std::cout<<"No Path\n";
		return 1;
	}
	CheckPos=Pos+dirs[dir];
	while(A.data(CheckPos)!='0'){
		dir=(dir+1)&7;
		CheckPos=Pos+dirs[dir];
	}
	if(A.Cdata(Pos)<7){
		Tail=(Path*)malloc(sizeof(Path));
		Tail->Last=nullptr;
		Tail->dir=dir;
		Tail->Pos=Pos;
		Tail->lPos=lPos;
	}
	bool working=true;
	bool backtrack=false;
	bool newBranch=false;
	while(working){
		do{//traversal
		   	std::cout<<"t";
			lPos=Pos;
			Pos=CheckPos;
			CheckPos=Pos+dirs[dir];
		}while(A.Cdata(Pos)==6 && A.data(CheckPos)!='1');
		if(Pos==End){//check if at exit
			working=false;
			continue;
		}
		if(A.Cdata(Pos)<6){//branch presence check in prior branches
			std::cout<<"p";
			Path* t=Tail;
			while(t){
				backtrack=backtrack || t->Pos==Pos;
				t=t->Last;
			}
		}
		if(!backtrack && A.Cdata(Pos)<6){//branching
			std::cout<<"n";
			Path* t=(Path*)malloc(sizeof(Path));
			dir=-1;
			t->Last=Tail;
			Tail=t;
			Tail->Pos=Pos;
			Tail->lPos=lPos;
			Tail->dir=dir;
			newBranch=true;
		}
		backtrack=backtrack || A.Cdata(Pos)==7;//backtrack if dead-end is reached
		do{
			if(backtrack){//returning to last branch
				std::cout<<"b";
				Pos=Tail->Pos;
				lPos=Tail->lPos;
				dir=Tail->dir;
			}
			char lDir=dir;
			do{//finding available path
				std::cout<<"r";
				dir=(dir+1)&7;
				CheckPos=Pos+dirs[dir];
			}while(CheckPos==lPos || A.data(CheckPos)!='0');
			if(backtrack||newBranch)Tail->dir=dir;//updating Tail if needed
			backtrack=backtrack && lDir>=dir;//check if all paths tried
			if(backtrack){//cull node.
				std::cout<<"c";
				Path* t=Tail;
				Tail=Tail->Last;
				free(t);
				if(Tail==nullptr){//all branches exausted. No path found.
					working=false;
					backtrack=false;

				}
			}
			newBranch=false;
		}while(backtrack);
	}

	return 0;
}
