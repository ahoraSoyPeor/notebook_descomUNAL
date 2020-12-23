/// Complexity: O(|N|*log|N|)
/// Tested: https://tinyurl.com/y9g2ljv9, https://tinyurl.com/y87q3j93
int lca(int a, int b) {
  if(depth[a] < depth[b]) swap(a, b);
  //int ans = INT_MAX;
  for(int i = LOG2-1; i >= 0; --i)
    if(depth[ dp[a][i] ] >= depth[b]) {
      //ans = min(ans, mn[a][i]);
      a = dp[a][i];
    }
  //if (a == b) return ans;
  if(a == b) return a;
  for(int i = LOG2-1; i >= 0; --i)
    if(dp[a][i] != dp[b][i]) {
      //ans = min(ans, mn[a][i]);
      //ans = min(ans, mn[b][i]);
      a = dp[a][i],
      b = dp[b][i];
    }
  //ans = min(ans, mn[a][0]);
  //ans = min(ans, mn[b][0]);
  //return ans;
  return dp[a][0];
}
void dfs(int u, int d = 1, int p = -1) {
  depth[u] = d;
  for(auto v : g[u]) {
    //int v = x.first;
    //int w = x.second;
    if(v != p) {
      dfs(v, d + 1, u);
      dp[v][0] = u;
      //mn[v][0] = w;
    }
  }
}
void build(int n) {
  for(int i = 0; i <= n; i++) dp[i][0] = -1;
  for(int i = 0; i < n, i++) {
    if(dp[i][0] == -1) {
      dp[i][0] = i;
      //mn[i][0] = INT_MAX;
      dfs(i);
    }
  }

  for(int j = 0; j < LOG2-1; ++j)
    for(int i = 0; i <= n; ++i) { // nodes
      dp[i][j+1] = dp[ dp[i][j] ][j];
      //mn[i][j+1] = min(mn[ dp[i][j] ][j], mn[i][j]);
    }
}
