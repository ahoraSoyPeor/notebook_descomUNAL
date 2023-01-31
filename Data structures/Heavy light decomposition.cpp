/// Complexity: O(|N|)
/// Tested: https://tinyurl.com/ybdbmbw7(problem L)
int idx; /// top is father of the chain, up is father of a node
vector<int> len, depth, in, out, top, up;
int dfs_len( int u, int p, int d ) {
  up[u] = p;  depth[u] = d;
  int sz = 1;
  for( auto& v : g[u] ) {
    if( v == p ) continue;
    sz += dfs_len(v, u, d+1);
    if(len[ g[u][0] ] <= len[v]) swap(g[u][0], v);
  }
  return len[u] = sz;
}
void dfs_hld( int u, int p = 0 ) {
  in[u] = idx++;
  narr[ in[u] ] = val[u]; /// to initialize the segment tree
  for( auto& v : g[u] ) {
    if( v == p ) continue;
    top[v] = (v == g[u][0] ? top[u] : v);
    dfs_hld(v, u);
  }
  out[u] = idx-1;
}
void update_hld( int u, int val ) {
  update_DS(in[u], val);
}
data query_hld( int u, int v ) {
  data val = NULL_DATA;
  while( top[u] != top[v] ) {
    if( depth[ top[u] ] < depth[ top[v] ] ) swap(u, v);
    val = val+query_DS(in[ top[u] ], in[u]);
    u = up[ top[u] ];
  }
  if( depth[u] > depth[v] ) swap(u, v);
  val = val+query_DS(in[u], in[v]);
  return val;
/// when updates are on edges use:
///   val[v] is cost_edge(up[v], v), mind root's cost
///   if(depth[u] == depth[v]) return val;
///   val = val+query_DS(in[u] + 1, in[v]);
}
void build(int n, int root) {
  top = len = in = out = up = depth = vector<int>(n+1);
  idx = 1; /// DS index [1, n]
  dfs_len(root, root, 0); 
  top[root] = root; 
  dfs_hld(root, root);
  /// initialize DS
}
