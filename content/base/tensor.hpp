template<class T, size_t d> struct tensor {
	using ind = array<size_t, d>;
	vector<T> data;
	ind dims;
	tensor(ind dims, T e = T())
		: data(accumulate(all(dims), (size_t)1, multiplies<size_t>()), e)
		, dims(dims) {}
	
	size_t ix(ind ind) const {
		size_t j = 0; rep(i,0,d) j = j*dims[i] + ind[i];
		return j;
	}

	const T& operator[](ind i) const { return data[ix(i)]; }
	T& operator[](ind i) { return data[ix(i)]; }
};