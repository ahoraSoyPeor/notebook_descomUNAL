/// Complexity: O(|N|*log(|N|))
/// Tested: https://tinyurl.com/y8wdubdw
const int alpha = 400; 
struct suffix_array { // s MUST not have 0 value
  vector<int> sa, pos, lcp;
  suffix_array(string s) {
    s.push_back('$'); // always add something less to input, so it stays in pos 0
    int n = s.size(), mx = max(alpha, n)+2;
    vector<int> a(n), a1(n), c(n+1), c1(n+1), head(mx), cnt(mx);
    pos = lcp = a;
    for(int i = 0; i < n; i++) c[i] = s[i], a[i] = i, cnt[ c[i] ]++;
    for(int i = 0; i < mx-1; i++) head[i+1] = head[i] + cnt[i];
    for(int k = 0; k < n; k = max(1, k<<1)) {
      for(int i = 0; i < n; i++) {
        int j = (a[i] - k + n) % n;
        a1[ head[ c[j] ]++ ] = j;
      }
      swap(a1, a);
      for(int i = 0, x = a[0], y, col = 0; i < n; i++, x = a[i], y = a[i-1]) {
        c1[x] = (i && c[x] == c[y] && c[x+k] == c[y+k]) ? col : ++col;
        if(!i || c1[x] != c1[y]) head[col] = i;
      }
      swap(c1, c);
      if(c[ a[n-1] ] == n) break;
    }
    swap(sa, a);
    for(int i = 0; i < n; i++) pos[ sa[i] ] = i;
    for(int i = 0, k = 0, j; i < n; lcp[ pos[i++] ] = k) { /// lcp[i, i+1]
      if(pos[i] == n-1) continue;
      for(k = max(0, k-1), j = sa[ pos[i]+1 ]; s[i+k] == s[j+k]; k++);
    }
  }
  int& operator[] ( int i ){ return sa[i]; }
};
