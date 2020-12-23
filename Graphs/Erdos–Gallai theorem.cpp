/// Complexity: O(|N|*log|N|)
/// Tested: https://tinyurl.com/yb5v9bau
/// Theorem: it gives a necessary and sufficient condition for a finite sequence
///          of natural numbers to be the degree sequence of a simple graph
bool erdos(vector<int> &d) {
  ll sum = 0;
  for(int i = 0; i < d.size(); ++i) sum += d[i];
  if(sum & 1) return false;
  sort(d.rbegin(), d.rend());
  ll l = 0, r = 0;
  for(int k = 1, i = d.size() - 1; k <= d.size(); ++k) {
    l += d[k-1];
    if(k > i) r -= d[++i];
    while (i >= k && d[i] < k+1) r += d[i--];
    if(l > 1ll*k*(k-1) + 1ll*k*(i-k+1) + r)
      return false;
  }
  return true;
}
