/// Complexity: O(|P|)
/// Tested: not yet
/// Find the multiplicative inverse of all 2<=i<p, module p
inv[1] = 1;
for(int i = 2; i < p; ++i)
	inv[i] = (p - (p / i) * inv[p % i] % p) % p;
