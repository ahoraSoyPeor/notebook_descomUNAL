namespace decomposition {
  int cnt[MAX], depth[MAX], f[MAX];
  int dfs (int u, int p = -1) {
    cnt[u] = 1;
    for (int v : g[u])
      if (!depth[v] && v != p)
        cnt[u] += dfs(v, u);
      return cnt[u];
  }
  int get_centroid (int u, int r, int p = -1) {
    for (int v : g[u])
      if (!depth[v] && v != p && cnt[v] > r)
        return get_centroid(v, r, u);
    return u;
  }
  int decompose (int u, int d = 1) {
    int centroid = get_centroid(u, dfs(u) >> 1);
    depth[centroid] = d;
    /// magic function
    for (int v : g[centroid])
      if (!depth[v])
        f[decompose(v, d + 1)] = centroid;
    return centroid;
  }
  int lca (int u, int v) {
    for (; u != v; u = f[u])
      if (depth[v] > depth[u])
        swap(u, v);
    return u;
  }
}
