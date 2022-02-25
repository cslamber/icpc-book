/// INCLUDE complete_operators

template<class T, size_t n>
struct smallmatrix {
	using M = smallmatrix;
	T a[n][n];
	M(T diag = 0) { rep(i,0,n) rep(j,0,n) a[i][j] = i == j ? diag : 0; }
	M&operator+=(const M& ot) { rep(i,0,n) rep(j,0,n) a[i][j] += ot.a[i][j]; }
	M&operator-=(const M& ot) { rep(i,0,n) rep(j,0,n) a[i][j] -= ot.a[i][j]; }
	M&operator*=(T x) { rep(i,0,n) rep(j,0,n) a[i][j] *= x; }
	M&operator/=(T x) { rep(i,0,n) rep(j,0,n) a[i][j] /= x; }
	binop(M,*,T) binop(M,/,T)
	M operator*(const M& ot) {
		M r;
		rep(i,0,n) rep(j,0,n) rep(k,0,n) r.a[i][k] += a[i][j] * ot.a[j][k];
		return r;
	}
};
