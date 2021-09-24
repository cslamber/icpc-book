tcT struct Point2{
using P=Point2;T x,y;
tuple<T&,T&> tup()const{return tie(x,y);}
bool operator<(P a)const{return tup()<a.tup();}
bool operator==(P a)const{return tup()==a.tup();}
P operator+(P a)const{return{x+a.x,y+a.y};}
P operator-(P a)const{return{x-a.x,y-a.y};}
P operator*(T a)const{return{x*a,y*a};}
P operator/(T a)const{return{x/a,y/a};}
P&operator+=(P a){return*this=*this+a;}
P&operator-=(P a){return*this=*this-a;}
P&operator*=(T a){return*this=*this*a;}
P&operator/=(T a){return*this=*this/a;}
T dot(P a)const{return x*a.x+y*a.y;}
T dot(P a,P b)const{return(a-*this).dot(b-*this);}
T cross(P a)const{return x*a.y-y*a.x;}
T cross(P a,P b)const{return(a-*this).cross(b-*this);}
T dist2()const{return dot(*this);}
P perp()const{return{-y,x};}
db angle()const{return atan2(y,x);}
db dist()const{return sqrt(db(dist2()));}
};
