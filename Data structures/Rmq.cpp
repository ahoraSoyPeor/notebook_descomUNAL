/// Complexity: O(|N|*log|N|)
/// Tested: https://tinyurl.com/y739tcsj
struct rmq {
  vector<vector<int> > table;
  rmq(vector<int> &v) : table(v.size() + 1, vector<int>(20)) {
    int n = v.size()+1;
    for (int i = 0; i < n; i++) table[i][0] = v[i];
    for (int j = 1; (1<<j) <= n; j++)
      for (int i = 0; i + (1<<j-1) < n; i++)
        table[i][j] = max(table[i][j-1], table[i + (1<<j-1)][j-1]);
  }
  int query(int a, int b) {
    int j = 31 - __builtin_clz(b-a+1);
    return max(table[a][j], table[b-(1<<j)+1][j]);
  }
};
