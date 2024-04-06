/// Complexity: O(|N|^2)
vector<lf> X, F;
lf f(lf x) {
  lf answer = 0;
  for(int i = 0; i < (int)X.size(); i++) {
    lf prod = F[i];
    for(int j = 0; j < (int)X.size(); j++) {
      if(i == j) continue;
      prod = mul(prod, divide(sub(x, X[j]), sub(X[i], X[j])));
    }
    answer = add(answer, prod);
  }
  return answer;
}
//given y=f(x) for x [0,degree]
vector< int > interpolation( vector< int > &y ) {
  int n = (int) y.size();
  vector< int > u = y, ans( n ), sum( n );
  ans[0] = u[0], sum[0] = 1;
  for( int i = 1; i < n; ++i ) {
    int inv = modpow( i, mod - 2 );
    for( int j = n - 1; j >= i; --j )
      u[j] = 1LL * (u[j] - u[j - 1] + mod) * inv % mod;
    for( int j = i; j > 0; --j ) {
      sum[j] = (sum[j - 1] - 1LL * (i - 1) * sum[j] % mod + mod) % mod;
      ans[j] = (ans[j] + 1LL * sum[j] * u[i]) % mod;
    }
    sum[0] = 1LL * (i - 1) * (mod - sum[0]) % mod;
    ans[0] = (ans[0] + 1LL * sum[0] * u[i]) % mod;
  }
  return ans;
}
 