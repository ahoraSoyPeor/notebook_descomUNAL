struct line {
  ll m, b;
  ll eval (ll x) { return m*x + b; }
};
struct cht {
  vector<line> lines;
  vector<lf> inter;
  int n;
  lf get_inter(line &a, line &b) { return lf(b.b - a.b) / (a.m - b.m); }
  inline bool ok(line &a, line &b, line &c) { 
    return lf(a.b-c.b) / (c.m-a.m) > lf(a.b-b.b) / (b.m-a.m); 
  }
  void add(line l) { 
    n = lines.size();
    if(n && lines.back().m == l.m && lines.back().b >= l.b) return;
    if(n == 1 && lines.back().m == l.m && lines.back().b < l.b) lines.pop_back(), n--;
    while(n >= 2 && !ok(lines[n-2], lines[n-1], l)) {
      n--;
      lines.pop_back(); inter.pop_back();
    }
    lines.push_back(l); n++;
    if(n >= 2) inter.push_back(get_inter(lines[n-1], lines[n-2]));
  }
  ll get_max(lf x) {
    if(lines.size() == 0) return LLONG_MIN;
    if(lines.size() == 1) return lines[0].eval(x);
    int pos = lower_bound(inter.begin(), inter.end(), x) - inter.begin();
    return lines[pos].eval(x);
  }
};
// for max: order slops non-decreasing
// for min: order slops non-descending