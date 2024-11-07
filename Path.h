struct point{
	union{
		struct{short x,y;};
		unsigned int c=0;
	};
};
struct Path{
	Path* Last;
	point Pos,lPos;
	char dir;
};
point operator+(const point& a,const point& b){
	point c;
//	c.c=a.c+b.c;//funny overflow risk lol
	c.x=a.x+b.x;
	c.y=a.y+b.y;
	return c;
}
inline bool operator==(const point& a, const point& b){
	return a.c==b.c;
}
inline bool operator!=(const point& a, const point& b){
	return a.c!=b.c;
}
