const int MOD = 1e9+7;
struct matrix {
  const int N = 2;
  int m[N][N], r, c;
  matrix(int r = N, int c = N, bool iden = false) : r(r), c(c) {
    memset(m, 0, sizeof m);
    if(iden)
      for(int i = 0; i < r; i++) m[i][i] = 1;
  }
  matrix operator * (const matrix &o) const {
    matrix ret(r, o.c);
    for(int i = 0; i < r; ++i)
      for(int j = 0; j < o.c; ++j) {
        ll &r = ret.m[i][j];
        for(int k = 0; k < c; ++k)
          r = (r + 1ll*m[i][k]*o.m[k][j]) % MOD;
      }
    return ret;
  }
};
