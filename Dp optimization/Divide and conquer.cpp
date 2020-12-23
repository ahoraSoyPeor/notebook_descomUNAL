/// Complexity: O(|N|*|K|*log|N|))
/// ******* Theory *******
/// dp[k][i]=min(dp[k−1][j]+C[i][j]), j < i
/// opt[k][i] ≤ opt[k][i+1]. 
/// A sufficient (but not necessary) condition for above is
/// C[a][c] + C[b][d] ≤ C[a][d] + C[b][c] where a < b < c < d.
void go(int k, int l, int r, int opl, int opr) {
  if(l > r) return;
  int mid = (l + r) / 2, op = -1;
  ll &best = dp[mid][k];
  best = INF;
  for(int i = min(opr, mid); i >= opl; i--) {
    ll cur = dp[i][k-1] + cost(i+1, mid);
    if(best > cur) {
      best = cur;
      op = i;
    }
  }
  go(k, l, mid-1, opl, op);
  go(k, mid+1, r, op, opr);
}
