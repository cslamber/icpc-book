tcT struct flist{
struct elem{T hd;shared_ptr<elem>tl;};
using sp=shared_ptr<elem>;
sp v;flist(){}flist(T hd,flist tl):v(new elem{hd,tl.v}){}
flist operator>>(T hd)const{return flist(hd,*this);}
v<T> to_v()const{v<T> r;for(sp c=v;c;c=c->tl)r.Pb(c->hd);return r;}
};
