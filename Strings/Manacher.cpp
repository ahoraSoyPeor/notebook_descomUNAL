/// Complexity: O(|N|)
/// Tested: https://tinyurl.com/y6upxbpa
///to = i - from[i];
///len = to - from[i] + 1 = i - 2 * from[i] + 1;
vector<int> manacher(string &s) {
  int n = s.size(), p = 0, pr = -1;
  vector<int> from(2*n-1);
  for(int i = 0; i < 2*n-1; ++i) {
    int r = i <= 2*pr ? min(p - from[2*p - i], pr) : i/2;
    int l = i - r;
    while(l > 0 && r < n-1 && s[l-1] == s[r+1]) --l, ++r;
    from[i] = l;
    if (r > pr) {
      pr = r;
      p = i;
    }
  }
  return from;
}
