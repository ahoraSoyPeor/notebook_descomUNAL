namespace decomposition {
  int cnt[N], depth[N], f[N]; // if depth != 0 means was removed from the tree while decomposing
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
  // depth of all tree's centroid is 1 and father is 0 (you can set up this when call this)
  int decompose (int u, int d = 1) {
    int centroid = get_centroid(u, dfs(u) >> 1);
    depth[centroid] = d; // remove this node from component
    /// add here magic function to count properties on paths
    for (int v : g[centroid])
      if (!depth[v])
        f[decompose(v, d + 1)] = centroid;
    return centroid;
  }
  int lca (int u, int v) { // lca on centroid tree
    for (; u != v; u = f[u])
      if (depth[v] > depth[u])
        swap(u, v);
    return u;
  }
}
