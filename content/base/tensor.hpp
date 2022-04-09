template<class T, uint D> struct tensor {
	vector<T> data; array<uint, D> dim;
	tensor(array<uint, D> dim, T e = T())
		: dim(dim), data(accumulate(all(dim), 1U, multiplies<uint>())) {}

	template<uint I> struct slice {
		tensor& t; uint base;
		decltype(auto) operator[](uint i) {
			if constexpr (I+1 == D) return t.data[base*t.dim[I] + i];
			else return slice<I+1>{ t, base*t.dim[I] + i };
		}
		uint size() const { return t.dim[I]; }
	};

	operator slice<0>() { return {*this, 0}; }
	decltype(auto) operator[](uint i) { return slice<0>(*this)[i]; }
};
