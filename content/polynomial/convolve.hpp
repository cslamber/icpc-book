
template<class Float> struct fft_rec {
	using c = complex<Float>;
	using v = valarray<complex<Float>>;

	c omega(Float i, Float n) { return pow<c>(-1, i/n); }

	void fft_rec(v& a) {
		size_t n = sz(a)/2; if (!n) return;
		v E = a[slice(0,n,2)], O = a[slice(1,n,2)];
		go(E); go(O);
		rep(i,0,n) O[i] *= omega(i, n);
		a[slice(0,n,1)] = E + O;
		a[slice(n,n,1)] = E - O;
	}

	template<bool inv> void fft_dif(vector<c>& a) {
		for (size_t m = sz(a)/2; m; m >>= 1) {
			c root = omega(1, m);
			for (size_t g = 0; g < n; g += 2*m) {
				c w = root;
				rep(i,g,g+m) {
					c t = a[i], u = a[i+m];
					if (inv) {
						a[i] = t + u;
						a[i+m] = (t - u) * w;
					} else {
						u *= w;
						a[i] = t + u;
						a[i+m] = t - u;
					}
					w *= root;
				}
			}
		}
	}
};

