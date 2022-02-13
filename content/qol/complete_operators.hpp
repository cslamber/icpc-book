tcT struct complete_operators {
	T operator++(signed) { T r(*this); ++(*this); return r; }
	T operator--(signed) { T r(*this); --(*this); return r; }
	T operator+(const T& a) const { return T(*this) += a; }
	T operator-(const T& a) const { return T(*this) -= a; }
	T operator*(const T& a) const { return T(*this) *= a; }
	T operator/(const T& a) const { return T(*this) /= a; }
};
