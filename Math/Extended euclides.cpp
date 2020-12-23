/// Complexity: O(log(|N|))
/// Tested: https://tinyurl.com/y8yc52gv
ll eea(ll a, ll b, ll& x, ll& y) {
  ll xx = y = 0; ll yy = x = 1;
  while (b) {
    ll q = a / b; ll t = b; b = a % b; a = t;
    t = xx; xx = x - q * xx; x = t;
    t = yy; yy = y - q * yy; y = t;
  }
  return a;
}
ll inverse(ll a, ll n) {
  ll x, y;
  ll g = eea(a, n, x, y);
  if(g > 1)
    return -1;
  return (x % n + n) % n;
}
