struct point{
	union{
		struct{char x,y;};
		const unsigned short c=0;
	};
};

struct Path{
	point pos,lPos;
	char dir;
	Path* Last;
};
