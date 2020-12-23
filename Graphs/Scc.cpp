/// Complexity: O(|N|)
/// Tested: https://tinyurl.com/y8ujj3ws
int scc(int n) {
  vector<int> dfn(n+1), low(n+1), in_stack(n+1);
  stack<int> st;
  int tag = 0;
  function<void(int, int&)> dfs = [&](int u, int &t) {
    dfn[u] = low[u] = ++t;
    st.push(u);
    in_stack[u] = true;
    for(auto &v : g[u]) {
      if(!dfn[v]) {
        dfs(v, t);
        low[u] = min(low[u], low[v]);
      } else if(in_stack[v])
        low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
      int v;
      do {
        v = st.top(); st.pop();
//        id[v] = tag;
        in_stack[v] = false;
      } while (v != u);
      tag++;
    }
  };
  for(int u = 1, t; u <= n; ++u) {
    if(!dfn[u]) dfs(u, t = 0);
  }
  return tag;
}
