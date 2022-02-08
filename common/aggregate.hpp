tcT struct aggregate {
	friend bool operator==(const T& a, const T& b) { return a.tup() == b.tup(); }
	friend bool operator!=(const T& a, const T& b) { return a.tup() != b.tup(); }
	friend bool operator< (const T& a, const T& b) { return a.tup() <  b.tup(); }
	friend bool operator<=(const T& a, const T& b) { return a.tup() <= b.tup(); }
	friend bool operator> (const T& a, const T& b) { return a.tup() >  b.tup(); }
	friend bool operator>=(const T& a, const T& b) { return a.tup() >= b.tup(); }
	friend ostream& operator<<(ostream& os, const T& a) { return os << a.tup(); }
};
