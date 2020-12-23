/// Complexity: |N|*log(|N|)
/// Tested: https://tinyurl.com/y9fz8vdt
int dfs(int u, int p = -1) {
  who[t] = u; fr[u] = t++;
  pii best = {0, -1};
  int sz = 1;
  for(auto v : g[u])
    if(v != p) {
      int cur_sz = dfs(v, u);
      sz += cur_sz;
      best = max(best, {cur_sz, v});
    }
  to[u] = t-1;
  big[u] = best.second;
  return sz;
}
void add(int u, int x) { /// x == 1 add, x == -1 delete
  cnt[u] += x;
}
void go(int u, int p = -1, bool keep = true) {
  for(auto v : g[u])
    if(v != p && v != big[u])
      go(v, u, 0);
  if(big[u] != -1) go(big[u], u, 1);
  /// add all small
  for(auto v : g[u])
    if(v != p && v != big[u])
      for(int i = fr[v]; i <= to[v]; i++)
        add(who[i], 1);
  add(u, 1);
  ans[u] = get(u);
  if(!keep)
    for(int i = fr[u]; i <= to[u]; i++)
      add(who[i], -1);
}
void solve(int root) {
  t = 0;
  dfs(root);
  go(root);
}
