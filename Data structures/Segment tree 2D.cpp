/// Complexity: |log(|N|^2) per operation
/// Tested: https://tinyurl.com/ado2fybw
struct info {
  ll val;
};
info merge(info a, info b) {
  return {a.val > b.val ? a.val : b.val};
}
info NEUTRAL = {LLONG_MIN};
struct segtree_2d {
  int n, m;
  vector<vector<info>> t;
  segtree_2d(int n, int m) : n(n), m(m), t(2*n+1, vector<info>(2*m+1, NEUTRAL)) {} /// 0-indexed
  info get(int x1, int y1, int x2, int y2) {
    info ans = NEUTRAL;
    for(x1 += n, x2 += n+1; x1 < x2; x1 >>= 1, x2 >>= 1) {
      if(x1&1) ans = merge(ans, get_helper(x1++, y1, y2));
      if(x2&1) ans = merge(ans, get_helper(--x2, y1, y2));
    }
    return ans;
  }
  info get_helper(int node, int y1, int y2) {
    info ans = NEUTRAL;
    for(y1 += m, y2 += m+1; y1 < y2; y1 >>= 1, y2 >>= 1) {
      if(y1&1) ans = merge(ans, t[node][y1++]);
      if(y2&1) ans = merge(ans, t[node][--y2]);
    }
    return ans;
  }
  void update(int x, int y, info val) {
    update_helper(x += n, y, val);
    for(; x > 1; x >>= 1) update_helper(x>>1, y, val);
  }
  void update_helper(int node, int y, info val) {
    t[node][y += m] = val;
    for(; y > 1; y >>= 1) t[node][y>>1] = merge(t[node][y], t[node][y^1]); /// associative
  }
};