vector<array<int,3>> triangles(vector<vu> G) {
	uint n = sz(G);
	vu p(n), ip(n); iota(all(p), 0);
	sort(all(p), cmp_by(L1(sz(G[it]))));
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

ull count_squares(vector<vu> G) {
	uint n = sz(G);
	vu p(n), ip(n); iota(all(p), 0);
	sort(all(p), cmp_by(L1(sz(G[it]))));
	rep(i,0,n) ip[p[i]] = i;
	vector<vi> D(n);
	rep(i,0,n) for (int j : G[i]) if (ip[i] < ip[j]) D[ip[i]].push_back(ip[j]);
	rep(i,0,n) sort(all(D[i]));
	map<pii,ull> cnts;
	rep(i,0,n) for (int j : D[i]) {
		for (int k : D[i]) if (k > j) cnts[{j,k}]++;
		for (int k : D[j]) if (k > i) cnts[{i,k}]++;
	}
	ull total = 0;
	for (auto [k,v] : cnts) total += v * (v - 1) / 2;
	return total;
}
