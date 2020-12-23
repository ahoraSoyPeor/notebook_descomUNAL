/// Complexity: O(|N|)
/// Tested: Not yet
void add(int u, int v, int w) { ng[u].push_back({v, w}); }
void binarize(int u, int p = -1) {
  int last = u, f = 0;
  for(auto x : g[u]) {
    int v = x.first, w = x.second, node = ng.size();
    if(v == p) continue;
    if(f++) {
      ng.push_back({});
      add(last, node, 0);
      add(node, v, w);
      last = node;
    } else add(u, v, w);
    binarize(v, u);
  }
}
