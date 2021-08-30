/// Complexity: O(|N|*log|N|)
/// Tested: https://tinyurl.com/jrdea8

struct info { int val; };
info merge(info &a, info &b) {
  return {a.val + b.val};
}
info NEUTRAL = {0};
struct segtree { // for point update and range queries, supports left to right merge
  int n; /// 0-indexed
  vector<info> t;
  segtree(int n, vector<int> &v) : n(n), t(2*n) {
    for(int i = 0; i < n; i++) t[i+n] = {v[i]};
    for(int i = n-1; i > 0; --i) t[i] = merge(t[i<<1], t[i<<1|1]);
  } 
  info query(int l, int r) {
    info ans_l = NEUTRAL, ans_r = NEUTRAL;
    for(l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
      if(l&1) ans_l = merge(ans_l, t[l++]);
      if(r&1) ans_r = merge(t[--r], ans_r);
    }
    return merge(ans_l, ans_r);
  }
  void modify(int p, int x) {
    for(t[p += n] = {x}; p >>= 1; ) t[p] = merge(t[p<<1], t[p<<1|1]);
  }
};