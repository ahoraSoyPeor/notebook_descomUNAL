/// Complexity: O(log(|N|))
/// Tested: https://tinyurl.com/y8yc52gv
bool diophantine(ll a, ll b, ll c, ll &x, ll &y, ll &g) {
  x = y = 0;
  if(a == 0 && b == 0) return c == 0;
  if(b == 0) swap(a, b), swap(x, y);
  g = eea(abs(a), abs(b), x, y);
  if(c % g) return false;
  a /= g; b /= g; c /= g;
  if(a < 0) x *= -1;
  x = (x % b) * (c % b) % b;
  if(x < 0) x += b;
  y = (c - a*x) / b;
  return true;
}
///finds the first k | x + b * k / gcd(a, b) >= val
ll greater_or_equal_than(ll a, ll b, ll x, ll val, ll g) {
  lf got = 1.0 * (val - x) * g / b;
  return b > 0 ? ceil(got) : floor(got);
}
void get_xy (ll a, ll b, ll &x, ll &y, ll k, ll g) { /// if for y, change the order to b,a y,x
  x = x + b / g * k;
  y = y - a / g * k;
}
