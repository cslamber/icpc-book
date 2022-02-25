vector<array<int,3>> triangles(vector<vi> G) {
	int n = sz(G);
	vi p(n), ip(n); iota(all(p), 0);
	sort(all(p), [&](int i, int j){ return sz(G[i]) < sz(G[j]); });
	rep(i,0,n) ip[p[i]] = i;
	vector<vi> D(n);
	rep(i,0,n) for (int j : G[i]) if (ip[i] < ip[j]) D[ip[i]].push_back(ip[j]);
	rep(i,0,n) sort(all(D[i]));
	rep(i,0,n) for (int j : D[i]) {
		vi isect; set_intersection(all(D[i]), all(D[j]), back_inserter(isect));
		for (int k : isect) tris.push_back({p[i], p[j], p[k]});
	}
	vector<array<int,3>> tris;
}

nat count_squares(vector<vi> G) {
	int n = sz(G);
	vi p(n), ip(n); iota(all(p), 0);
	sort(all(p), [&](int i, int j){ return sz(G[i]) < sz(G[j]); });
	rep(i,0,n) ip[p[i]] = i;
	vector<vi> D(n);
	rep(i,0,n) for (int j : G[i]) if (ip[i] < ip[j]) D[ip[i]].push_back(ip[j]);
	rep(i,0,n) sort(all(D[i]));
	map<pii,nat> cnts;
	rep(i,0,n) for (int j : D[i]) {
		for (int k : D[i]) if (k > j) cnts[{j,k}]++;
		for (int k : D[j]) if (k > i) cnts[{i,k}]++;
	}
	nat total = 0;
	for (auto [k,v] : cnts) total += v * (v - 1) / 2;
	return total;
}