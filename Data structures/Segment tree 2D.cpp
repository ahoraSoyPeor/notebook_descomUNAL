/// Complexity: log(|N|)^2 per operation
/// Tested: https://tinyurl.com/ado2fybw
struct info {
  ll val;
};
info merge(info a, info b) {
  return {a.val > b.val ? a.val : b.val};
}
info NEUTRAL = {LLONG_MIN};
struct segtree_2d {
  int n, m; /// 0-indexed
  vector<vector<info>> t;
  segtree_2d(int n, int m) : n(n), m(m), t(2*n, vector<info>(2*m, NEUTRAL)) {} 
  segtree_2d(int n, int m, vector<vector<info>> &v) : n(n), m(m), t(2*n, vector<info>(2*m, NEUTRAL)) {
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        t[i+n][j+m] = v[i][j];
    for(int i = 0; i < n; i++)
      for(int j = m-1; j; j--)
        t[i+n][j] = merge(t[i+n][j<<1], t[i+n][j<<1|1]);
    for(int i = n-1; i; i--)
      for(int j = 0; j < 2*m; j++)
        t[i][j] = merge(t[i<<1][j],t[i<<1|1][j]);
  }
  info get(int x1, int y1, int x2, int y2) {
    info ans = NEUTRAL;
    vector<int> pos(2);
    for(x1 += n, x2 += n+1; x1 < x2; x1 >>= 1, x2 >>= 1) {
      int q = 0;
      if(x1&1) pos[q++] = x1++;
      if(x2&1) pos[q++] = --x2;
      for(int i = 0; i < q; i++) {
        for(int t1 = m+y1, t2 = m+y2+1, id = pos[i]; t1 < t2; t1 >>= 1, t2 >>= 1) {
          if(t1&1) ans = merge(ans, t[id][t1++]);
          if(t2&1) ans = merge(ans, t[id][--t2]);
        }
      }
    }
    return ans;
  }
  void update(int x, int y, info v) {
    t[x+n][y+m] = v;
    for(int j = y+m; j > 1; j >>= 1)
      t[x+n][j>>1] = merge(t[x+n][j], t[x+n][j^1]);
    for(int i = x+n; i > 1; i >>= 1) 
      for(int j = y+m; j; j >>= 1)
        t[i>>1][j] = merge(t[i][j],t[i^1][j]);
  }
};