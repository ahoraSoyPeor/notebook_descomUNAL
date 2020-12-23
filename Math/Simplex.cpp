/// Complexity: O(|N|^2 * |M|) N variables, N restrictions
/// Tested: https://tinyurl.com/ybphh57p
const double EPS = 1e-6;
typedef vector<double> vec;
namespace simplex {
  vector<int> X, Y;
  vector<vec> a;
  vec b, c;
  double z;
  int n, m;
  void pivot(int x, int y) {
    swap(X[y], Y[x]);
    b[x] /= a[x][y];
    for(int i = 0; i < m; i++)
      if(i != y)
        a[x][i] /= a[x][y];
    a[x][y] = 1 / a[x][y];
    for(int i = 0; i < n; i++)
      if(i != x && abs(a[i][y]) > EPS) {
      b[i] -= a[i][y] * b[x];
      for(int j = 0; j < m; j++)
        if(j != y)
          a[i][j] -= a[i][y] * a[x][j];
      a[i][y] =- a[i][y] * a[x][y];
    }
    z += c[y] * b[x];
    for(int i = 0; i < m; i++)
      if(i != y)
        c[i] -= c[y] * a[x][i];
    c[y] =- c[y] * a[x][y];
  }
  /// A is a vector of 1 and 0. B is the limit restriction. C is the factors of O.F.
  pair<double, vec> simplex(vector<vec> &A, vec &B, vec &C) {
    a = A; b = B; c = C;
    n = b.size(); m = c.size(); z = 0.0;
    X = vector<int>(m);
    Y = vector<int>(n);
    for(int i = 0; i < m; i++) X[i] = i;
    for(int i = 0; i < n; i++) Y[i] = i + m;
    while(1) {
      int x = -1, y = -1;
      double mn = -EPS;
      for(int i = 0; i < n; i++)
        if(b[i] < mn)
          mn = b[i], x = i;
      if(x < 0) break;
      for(int i = 0; i < m; i++)
        if(a[x][i] < -EPS) { y = i; break; }
      assert(y >= 0); // no sol
      pivot(x, y);
    }
    while(1) {
      double mx = EPS;
      int x = -1,y = -1;
      for(int i = 0; i < m; i++)
        if(c[i] > mx)
          mx = c[i], y = i;
      if(y < 0) break;
      double mn = 1e200;
      for(int i = 0; i < n; i++)
        if(a[i][y] > EPS && b[i] / a[i][y] < mn)
          mn = b[i] / a[i][y], x = i;
      assert(x >= 0); // unbound
      pivot(x, y);
    }
    vec r(m);
    for(int i = 0; i < n; i++)
      if(Y[i] < m)
        r[ Y[i] ] = b[i];
    return make_pair(z, r);
  }
}
