struct FFT {
  int mod, root, root_1, root_pw;
  void fft(vector<int> & a, bool invert) {
      int n = a.size();
      for (int i = 1, j = 0; i < n; ++i) {
          int bit = n >> 1;
          for (; j & bit; bit >>= 1)
              j ^= bit;
          j ^= bit;
          if (i < j) swap(a[i], a[j]);
      }
      for (int len = 2; len <= n; len <<= 1) {
          int wlen = invert ? root_1 : root;
          for (int i = len; i < root_pw; i <<= 1)
              wlen = 1LL * wlen * wlen % mod;
          for (int i = 0; i < n; i += len) {
              int w = 1;
              for (int j = 0; j < len / 2; ++j) {
                  int u = a[i+j], v = 1LL * a[i+j+len/2] * w % mod;
                  a[i+j] = u + v < mod ? u + v : u + v - mod;
                  a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                  w = 1LL * w * wlen % mod;
              }
          }
      }
      if (invert) {
          int n_1 = pw(n, mod-2, mod);
          for (int & x : a)
              x = 1LL * x * n_1 % mod;
      }
  }
  vector<int> multiply(vector<int> const& a, vector<int> const& b) {
      vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
      int n = 1;
      while (n < a.size() + b.size()) 
          n <<= 1;
      fa.resize(n);
      fb.resize(n);
      fft(fa, false);
      fft(fb, false);
      for (int i = 0; i < n; i++)
          fa[i] = 1LL * fa[i] * fb[i] % mod;    
      fft(fa, true);
      return fa;
  }
};
FFT A = { 998244353, 15311432, 469870224, 1<<23 };