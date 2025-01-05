using System;
using System.Runtime.InteropServices;

class Program{
	[System.Runtime.InteropServices.StructLayout(LayoutKind.Explicit)]
	public struct Point{
	 	[System.Runtime.InteropServices.FieldOffset(0)]
		public int x;
		[System.Runtime.InteropServices.FieldOffset(4)]
		public int y;
		[System.Runtime.InteropServices.FieldOffset(0)]
		private ulong c;
	
		public static Point operator +(Point L,Point R){
			Point N=new Point();
			N.x=L.x+R.x;
			N.y=L.y+R.y;
			return N;
		}
		public static bool operator ==(Point L,Point R){
			return L.c==R.c;
		}
		public static bool operator !=(Point L,Point R){
			return L.c!=R.c;
		}

		public Point(int a,int b){
			this.x=a;
			this.y=b;
		}
	};
	
	static Point[] dirs = new Point[8]{
		new Point(1,0),
		new Point(1,-1),
		new Point(0,-1),
		new Point(-1,-1),
		new Point(-1,0),
		new Point(-1,1),
		new Point(0,1),
		new Point(1,1)
	};

	class Path{
		public Point Pos;
		public Point lPos;
		public int dir;
		public Path? Last;
	}
	
	class Maze{
		private int x;
		private int y;
		private string Mdata;
		private int[] CMdata;
		public Maze(int width,int height,string maze){
			x = width;
			y= height;
			Mdata=maze;
			CMdata=new int[width*height];
			for(int a=1;a<x-1;a++){
				for(int b=1;b<y-1;b++){
					CMdata[a+b*x]=0;
					for(int i=-1;i<2;i++){
						for(int j=-1;j<2;j++){
							CMdata[a+x*b]+=Mdata[(a+i)+x*(b+j)]&1;
						}
					}
				}
			}
		}

		public int MixPrint(){
			for(int a=0;a<y;a++){
				for(int b=0;b<x;b++){
					if(Mdata[x*a+b]=='1')Console.Write("X");
					else Console.Write((int)CMdata[x*a+b]);
				}
				Console.Write('\n');
			}
			return 0;
		}

		public char data(Point a){
			return Mdata[a.x+x*a.y];
		}
		public int Cdata(Point a){
			return CMdata[a.x+x*a.y];
		}
	}

	public static int Main(){
		int width=12;
		int height=10;
		string MD="111111111111111111110001111100000111110001110111110110110111110111010111111111011111111011011111100000011111111111111111";
/*		111111111111
		111111110001
		111100000111
		110001110111
		110110110111
		110111010111
		111111011111
		111011011111
		100000011111
		111111111111	*/

		Maze A=new Maze(width,height,MD);
		A.MixPrint();

		Path? Tail=null;
		int dir=0;
		Point Pos = new Point(1,height-2);
		Point lPos=Pos;
		Point CheckPos;

		Point End = new Point(width-2,1);

		//dead end check
		if(A.Cdata(Pos)==8){
			Console.Write("No Path\n");
			return 1;
		}
		
		//starting dir
		CheckPos=Pos+dirs[dir];
		while(A.data(CheckPos)!='0'){
			dir=(dir+1)&7;
			CheckPos=Pos+dirs[dir];
		}

		//Enters at branch
		if(A.Cdata(Pos)<7){
			Tail=new Path();
			Tail.Last=null;
			Tail.dir=dir;
			Tail.Pos=Pos;
			Tail.lPos=lPos;
		}
		
		//main algo begins
		bool working=true;
		bool backtrack=false;
		bool newBranch=false;
		while(working){
			do{//traversal
			   	Console.Write("t");
				lPos=Pos;
				Pos=CheckPos;
				CheckPos=Pos+dirs[dir];
			}while(A.Cdata(Pos)==6 && A.data(CheckPos)!='1');
			if(Pos==End){//check if at exit
				working=false;
				continue;
			}
			if(A.Cdata(Pos)<6){//branch presence check in prior branches
				Console.Write("p");
				Path? t=Tail;
				while(t!=null){
					backtrack=backtrack || t.Pos==Pos;
					t=t.Last;
				}
			}
			if(!backtrack && A.Cdata(Pos)<6){//branching
				Console.Write("n");
				Path? t=new Path();
				dir=-1;
				t.Last=Tail;
				Tail=t;
				Tail.Pos=Pos;
				Tail.lPos=lPos;
				Tail.dir=dir;
				newBranch=true;
			}
			backtrack=backtrack || A.Cdata(Pos)==7;//backtrack if dead-end is reached
			do{
				if(backtrack){//returning to last branch
					Console.Write("b");
					Pos=Tail.Pos;
					lPos=Tail.lPos;
					dir=Tail.dir;
				}
				int lDir=dir;
				do{//finding available path
					Console.Write("r");
					dir=(dir+1)%8;
					CheckPos=Pos+dirs[dir];
				}while(CheckPos==lPos || A.data(CheckPos)!='0');
				if(backtrack||newBranch)Tail.dir=dir;//updating Tail if needed
				backtrack=backtrack && lDir>=dir;//check if all paths tried
				if(backtrack){//cull node.
					Console.Write("c");
					Tail=Tail.Last;
					if(Tail==null){//all branches exausted. No path found.
						working=false;
						backtrack=false;
					}
				}
				newBranch=false;
			}while(backtrack);
		}
		return 0;
	}
}