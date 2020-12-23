/// Complexity: |N|*log(|N|)
/// Tested: Not yet.
/// finds a suitable x that meets: x is congruent to a_i mod n_i
/** Works for non-coprime moduli.
 Returns {-1,-1} if solution does not exist or input is invalid.
 Otherwise, returns {x,L}, where x is the solution unique to mod L = LCM of mods
*/
pair<int, int> chinese_remainder_theorem( vector<int> A, vector<int> M ) {
  int n = A.size(), a1 = A[0], m1 = M[0];
  for(int i = 1; i < n; i++) {
    int a2 = A[i], m2 = M[i];
    int g = __gcd(m1, m2);
    if( a1 % g != a2 % g ) return {-1,-1};
    int p, q;
    eea(m1/g, m2/g, &p, &q);
    int mod = m1 / g * m2;
    q %= mod; p %= mod;
    int x = ((1ll*(a1%mod)*(m2/g))%mod*q + (1ll*(a2%mod)*(m1/g))%mod*p) % mod; // if WA there is overflow
    a1 = x;
    if (a1 < 0) a1 += mod;
    m1 = mod;
  }
  return {a1, m1};
}
