template<class T, size_t d> struct tensor {
	using ind = array<size_t, d>;
	vector<T> data; ind dim;
	tensor(ind dim, T e = T())
		dim(dim), data(accumulate(all(dim), (size_t)1, multiplies<size_t>()), e) {}
	size_t ix(ind ind) const {
		size_t j = 0; rep(i,0,d) j = j*dim[i] + ind[i]; return j; }
	const T& operator[](ind i) const { return data[ix(i)]; }
	T& operator[](ind i) { return data[ix(i)]; }
	template<class...Ts> inline const T& operator()(Ts...ts) const { return (*this)[ind{(size_t)ts...}]; }
	template<class...Ts> inline T& operator()(Ts...ts) { return (*this)[ind{(size_t)ts...}]; }
};
