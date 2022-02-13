tcT struct registry {
	map<T, int> fwd; vector<T> bck;
	registry() {}
	template<class It> registry(It start, It end) { for (; start != end; ++start) (*this)(*start); }
	int operator()(const T& t) { bck.push()}
	const T& operator[](size_t ind) const { return bck[ind]; }
};
