/// Complexity: O(|N|*log|N|)
/// Tested: https://tinyurl.com/y739tcsj
struct rmq {
  vector<vector<int>> table;
  rmq(vector<int> &v) : table(20, vector<int>(v.size())) {
    int n = v.size();
    for (int i = 0; i < n; i++) table[0][i] = v[i];
    for (int j = 1; (1<<j) <= n; j++)
      for (int i = 0; i + (1<<j-1) < n; i++)
        table[j][i] = min(table[j-1][i], table[j-1][i + (1<<j-1)]);
  }
  int query(int a, int b) {
    int j = 31 - __builtin_clz(b-a+1);
    return min(table[j][a], table[j][b-(1<<j)+1]);
  }
};
