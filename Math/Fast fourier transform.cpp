
///this fft got AC in a problem and the previous implementation got WA
typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vl conv(const vl& a, const vl& b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	rep(i,0,sz(b)) in[i].imag(b[i]);
	fft(in);
	trav(x, in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
    vector<ll> resp(sz(res));
	rep(i,0,sz(res)) resp[i] = round(imag(out[i]) / (4.0 * n));
	return resp;
}
/// Complexity: O(|N|*log(|N|))
/// Tested: https://tinyurl.com/y8g2q66b
namespace fft {
  typedef long long ll;
  const double PI = acos(-1.0);
  vector<int> rev;
  struct pt {
    double r, i;
    pt(double r = 0.0, double i = 0.0) : r(r), i(i) {}
    pt operator + (const pt & b) { return pt(r + b.r, i + b.i); }
    pt operator - (const pt & b) { return pt(r - b.r, i - b.i); }
    pt operator * (const pt & b) { return pt(r * b.r - i * b.i, r * b.i + i * b.r); }
  };
  void fft(vector<pt> &y, int on) {
    int n = y.size();
    for(int i = 1; i < n; i++) if(i < rev[i]) swap(y[i], y[rev[i]]);
    for(int m = 2; m <= n; m <<= 1) {
      pt wm(cos(-on * 2 * PI / m), sin(-on * 2 * PI / m));
      for(int k = 0; k < n; k += m) {
        pt w(1, 0);
        for(int j = 0; j < m / 2; j++) {
          pt u = y[k + j];
          pt t = w * y[k + j + m / 2];
          y[k + j] = u + t;
          y[k + j + m / 2] = u - t;
          w = w * wm;
        }
      }
    }
    if(on == -1)
      for(int i = 0; i < n; i++) y[i].r /= n;
  }
  vector<ll> mul(vector<ll> &a, vector<ll> &b) {
    int n = 1, la = a.size(), lb = b.size(), t;
    for(n = 1, t = 0; n <= (la+lb+1); n <<= 1, t++); t = 1<<(t-1);
    vector<pt> x1(n), x2(n);
    rev.assign(n, 0);
    for(int i = 0; i < n; i++) rev[i] = rev[i >> 1] >> 1 |(i & 1 ? t : 0);
    for(int i = 0; i < la; i++) x1[i] = pt(a[i], 0);
    for(int i = 0; i < lb; i++) x2[i] = pt(b[i], 0);
    fft(x1, 1); fft(x2, 1);
    for(int i = 0; i < n; i++) x1[i] = x1[i] * x2[i];
    fft(x1, -1);
    vector<ll> sol(n);
    for(int i = 0; i < n; i++) sol[i] = x1[i].r + 0.5;
    return sol;
  }
}
