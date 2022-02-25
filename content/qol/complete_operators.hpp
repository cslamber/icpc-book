#define incdec(T) \
	T operator++(signed) { T r(*this); ++(*this); return r; } \
	T operator--(signed) { T r(*this); --(*this); return r; }
#define binop(T,op,O) \
	T operator op (const O& a) const { return T(*this) op = a; }
