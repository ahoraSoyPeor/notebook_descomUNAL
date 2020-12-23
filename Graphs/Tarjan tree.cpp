/// Complexity: O(|N|)
/// Tested: https://tinyurl.com/y9g2ljv9, https://tinyurl.com/y87q3j93
struct tarjan_tree {
  int n;
  vector<vector<int>> g, comps;
  vector<pii> bridge;
  vector<int> id, art;
  tarjan_tree(int n) : n(n), g(n+1), id(n+1), art(n+1) {}
  void add_edge(vector<vector<int>> &g, int u, int v) { /// nodes from [1, n]
    g[u].push_back(v);
    g[v].push_back(u);
  }
  void add_edge(int u, int v) { add_edge(g, u, v); }
  void tarjan(bool with_bridge) {
    vector<int> dfn(n+1), low(n+1);
    stack<int> st;
    comps.clear();
    function<void(int, int, int&)> dfs = [&](int u, int p, int &t) {
      dfn[u] = low[u] = ++t;
      st.push(u);
      int cntp = 0;
      for(int v : g[u]) {
        cntp += v == p;
        if(!dfn[v])	{
          dfs(v, u, t);
          low[u] = min(low[u], low[v]);
          if(with_bridge && low[v] > dfn[u]) {
            bridge.push_back({min(u,v), max(u,v)});
            comps.push_back({});
            for(int w = -1; w != v; )
              comps.back().push_back(w = st.top()), st.pop();
          }
          if(!with_bridge && low[v] >= dfn[u]) {
            art[u] = (dfn[u] > 1 || dfn[v] > 2);
            comps.push_back({u});
            for(int w = -1; w != v; )
              comps.back().push_back(w = st.top()), st.pop();
          }
        }
        else if(v != p || cntp > 1) low[u] = min(low[u], dfn[v]);
      }
      if(p == -1 && ( with_bridge || g[u].size() == 0 )) {
        comps.push_back({});
        for(int w = -1; w != u; )
          comps.back().push_back(w = st.top()), st.pop();
      }
    };
    for(int u = 1, t; u <= n; ++u)
      if(!dfn[u]) dfs(u, -1, t = 0);
  }
  vector<vector<int>> build_block_cut_tree() {
    tarjan(false);
    int t = 0;
    for(int u = 1; u <= n; ++u)
      if(art[u]) id[u] = t++;
    vector<vector<int>> tree(t+comps.size());
    for(int i = 0; i < comps.size(); ++i)
      for(int u : comps[i]) {
        if(!art[u]) id[u] = i+t;
        else add_edge(tree, i+t, id[u]);
      }
    return tree;
  }
  vector<vector<int>> build_bridge_tree() {
    tarjan(true);
    vector<vector<int>> tree(comps.size());
    for(int i = 0; i < comps.size(); ++i)
      for(int u : comps[i]) id[u] = i;
    for(auto &b : bridge)
      add_edge(tree, id[b.first], id[b.second]);
    return tree;
  }
};
