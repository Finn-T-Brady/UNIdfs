#include <iostream>

class Maze{
	private:
		char** data;
		char** Cdata;
		int x,y;
	public:
		Maze(int width,int height, char** maze){

		}
		int print(){
			for(int x=0;x<y;x++){
				std::cout<<data[x]<<'\n';
			}
			return 0;
		}
};
