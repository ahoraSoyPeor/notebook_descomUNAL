struct bucket {
  int l, r, lazy;
  bucket(int l, int r) : l(l), r(r), lazy(0) {}
  void build() {
    for(int i = l; i <= r; i++) a[i] += lazy;
    for(int i = l; i <= r; i++) {} /// build DS from scratch
    lazy = 0;
  }
  void update(int L, int R, ll v) {
    if(L == l && R == r) lazy += v;
    else { /// handle by hand
      for(int i = L; i <= R; i++) a[i] += v; 
      build();
    }
  }
  int query(int L, int R) {
    int ans = INT_MIN;
    if(L == l && R == r) ans = ds.get_max(x);
    else { /// handle by hand
      for(int i = L; i <= R; i++) ans = max(ans, abs(a[i] + x) * b[i]);
    }
    return ans;
  }
};
{ /// at main(), update from a to b, len is the size of bucket
  int l = a / len, r = b / len;
  for(int i = l i <= r; i++) { /// in theory, all are complete
    int x = max(l, i*len);
    int y = min(r, (i+1)*len-1);
    bucket[i].operation(x, y);
  }
}
