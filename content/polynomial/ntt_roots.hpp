/// include modnum

template<class T> struct ntt_root { const uint32_t root; };

template<> struct ntt_root<modnum<998244353>> {
	const uint32_t root = 3;
};
