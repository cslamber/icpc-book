tcT struct copy_ptr : unique_ptr<T> {
	using unique_ptr<T>::unique_ptr;
	copy_ptr() {}
	copy_ptr(const copy_ptr& other) { reset(new T(*other.get())); }
	copy_ptr& operator=(const copy_ptr& other) { return *this = copy_ptr(other); }
};
