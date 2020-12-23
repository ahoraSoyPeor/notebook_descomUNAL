/// Complexity: O(|N|^2))
/// Tested: https://tinyurl.com/y6ofp8wb
/// ******* Theory *******
/// dp[i][j]= min(dp[i][k]+dp[k][j])+C[i][j], i<k<j
/// where opt[i][j−1] ≤ opt[i][j] ≤ opt[i+1][j]. 
/// sufficient (but not necessary) condition for above is 
/// C[a][c] + C[b][d] ≤ C[a][d] + C[b][c] and C[b][c] ≤ C[a][d] where a ≤ b ≤ c ≤ d.
for(int i = 1; i <= n; i++) {
  opt[i][i] = i;
  dp[i][i] = sum[i] - sum[i-1];
}
for(int len = 2; len <= n; len++)
  for(int l = 1; l+len-1 <= n; l++) {
    int r = l+len-1;
    dp[l][r] = oo;
    for(int i = opt[l][r-1]; i <= opt[l+1][r]; i++) {
      ll cur = dp[l][i-1] + dp[i+1][r] + sum[r] - sum[l-1];
      if(cur < dp[l][r]) {
        dp[l][r] = cur;
        opt[l][r] = i;
      }
    }
  }
