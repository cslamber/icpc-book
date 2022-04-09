template<uint BITS = 31> struct dinic {
	struct edge { uint to, rev; ull c, oc; ull flow() { return oc > c ? oc - c : 0; };
	vector<uint> lvl, ptr, q;
	vector<vector<edge>> adj;
	Dinic(uint n) : lvl(n), ptr(n), q(n), adj(n) {}
	void add_edge(uint a, uint b, ull c, ull rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a])-1, rcap, rcap});
	}
	ull dfs(uint v, uint t, ull f) {
		if (v == t || !f) return f;
		for (uint& i = ptr[v]; i < sz(adj[v]); i++) {
			edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ull p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ull calc(uint s, uint t) {
		ull flow = 0; q[0] = s;
		repr(L,0,BITS) do {
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (edge e : adj[v])
					if (!lvl[e.to] && e.c >> L)
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ull p = dfs(s, t, ULLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool left_of_mincut(uint a) { return lvl[a] != 0; }
};
