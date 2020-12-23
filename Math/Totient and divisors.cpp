vector<int> count_divisors_sieve() {
  bitset<mx> is_prime; is_prime.set();
  vector<int> cnt(mx, 1);
  is_prime[0] = is_prime[1] = 0;
  for(int i = 2; i < mx; i++) {
    if(!is_prime[i]) continue;
    cnt[i]++;
    for(int j = i+i; j < mx; j += i) {
      int n = j, c = 1;
      while( n%i == 0 ) n /= i, c++;
      cnt[j] *= c;
      is_prime[j] = 0;
    }
  }
  return cnt;
}
vector<int> euler_phi_sieve() {
  bitset<mx> is_prime; is_prime.set();
  vector<int> phi(mx);
  iota(phi.begin(), phi.end(), 0);
  is_prime[0] = is_prime[1] = 0;
  for(int i = 2; i < mx; i++) {
    if(!is_prime[i]) continue;
    for(int j = i; j < mx; j += i) {
      phi[j] -= phi[j]/i;
      is_prime[j] = 0;
    }
  }
  return phi;
}
ll euler_phi(ll n) {
  ll ans = n;
  for(ll i = 2; i * i <= n; ++i) {
    if(n % i == 0) {
      ans -= ans / i;
      while(n % i == 0) n /= i;
    }
  }
  if(n > 1) ans -= ans / n;
  return ans;
}
