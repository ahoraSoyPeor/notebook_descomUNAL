namespace linear_seq {
  int m; //a = first m terms
  vector < int > p, a;//p = recurrence, length is m 
  inline vector < int > BM(vector < int > x) { //finds shortest linear recurrence given first x terms in O(x^2)
    vector < int > ls, cur; 
    int lf, ld;
    for (int i = 0; i < (int) x.size(); ++i) {
      int t = 0;
      for (int j = 0; j < (int) cur.size(); ++j)
        t = (t + 1 LL * x[i - j - 1] * cur[j]) % mod;
      if ((t - x[i]) % mod == 0) continue;
      if (!cur.size()) { 
        cur.resize(i + 1);
        lf = i;
        ld = (t - x[i]) % mod;
        continue;
      }
      int k = 1 LL * (t - x[i]) * pw(ld, mod - 2) % mod;
      vector < int > c(i - lf - 1); 
      c.push_back(k); 
      for (int j = 0; j < (int) ls.size(); ++j) 
        c.push_back(-1 LL * ls[j] * k % mod);
      if (c.size() < cur.size()) c.resize(cur.size());
      for (int j = 0; j < (int) cur.size(); ++j)
        c[j] = (c[j] + cur[j]) % mod;
      if (i + lf + (int) ls.size() >= (int) cur.size())
        ls = cur, lf = i, ld = (t - x[i]) % mod;
      cur = c;
    }
    for (int i = 0; i < (int) cur.size(); ++i)
      cur[i] = (cur[i] % mod + mod) % mod;
    m = cur.size();
    p.resize(m), a.resize(m);
    for (int i = 0; i < m; ++i)
      p[i] = cur[i], a[i] = x[i];
    return cur;
  }
  inline vector < int > mul(vector < int > & a, vector < int > & b) { 
    vector < int > r(2 * m);
    for (int i = 0; i < m; ++i)
      if (a[i])
        for (int j = 0; j < m; ++j)
          r[i + j] = (r[i + j] + 1 LL * a[i] * b[j]) % mod;
    for (int i = 2 * m - 1; i >= m; --i)
      if (r[i])
        for (int j = m - 1; j >= 0; --j)
          r[i - j - 1] = (r[i - j - 1] + 1 LL * p[j] * r[i]) % mod;
    r.resize(m);
    return r;
  }
  inline int calc(long long k) { //O(m*m*log(k)) 
    if (m == 0) return 0;
    vector < int > bs(m), r(m);
    if (m == 1) bs[0] = p[0];
    else bs[1] = 1;
    r[0] = 1;
    while (k) {
      if (k & 1) r = mul(r, bs);
      bs = mul(bs, bs);
      k >>= 1;
    }
    int res = 0;
    for (int i = 0; i < m; ++i)
      res = (res + 1 LL * r[i] * a[i]) % mod;
    return res;
  }
}