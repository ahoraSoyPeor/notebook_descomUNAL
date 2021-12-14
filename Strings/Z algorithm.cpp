/// Complexity: O(|N|)
/// Tested: https://tinyurl.com/yc3rjh4p
vector<int> z_algorithm (string &s) {
  int n = s.size();
  vector<int> z(n);
  int l = 0, r = 0;
  for(int i = 1; i < n; ++i) {
    z[i] = max(0, min(z[i-l], r-i+1));
    while (i+z[i] < n && s[z[i]] == s[i+z[i]])
      l = i, r = i+z[i], ++z[i];
  }
  return z;
}
