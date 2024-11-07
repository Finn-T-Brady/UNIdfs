#include <iostream>
#include <stdexcept>

class Maze{
	private:
		char* Mdata;
		char* CMdata;
		int x,y;
	public:
		Maze(int width,int height, char* maze):Mdata{maze},x{width},y{height}{
			bool c=Mdata[(y-2)*x+1]=='0' && Mdata[x+x-2]=='0';
			if(!c)throw std::invalid_argument("Maze data malformed:either entry or exit points blocked");

			CMdata=(char*)calloc(x*y,sizeof(char));

			//Convolution of data into Cdata
			for(int a=1;a<y-1;a++){
				for(int b=1;b<x-1;b++){
					char& C = CMdata[x*a+b];
					for(int aa=a-1;aa<a+2;aa++){
						for(int bb=b-1;bb<b+2;bb++){
							C+=Mdata[aa*x+bb]&1;
						}
					}
				}
			}
			//Convolution end

		}
		int MixPrint(){
			for(int a=0;a<y;a++){
				for(int b=0;b<x;b++){
					if(Mdata[x*a+b]=='1')std::cout<<'X';
					else std::cout<<(int)CMdata[x*a+b];
				}
				std::cout<<'\n';
			}
			return 0;
		}
		char& data(int a,int b){
			return Mdata[b*x+a];
		}
		char& data(point a){
			return Mdata[a.y*x+a.x];
		}
		char& Cdata(int a,int b){
			return CMdata[b*x+a];
		}
		char& Cdata(point a){
			return CMdata[a.y*x+a.x];
		}
};
