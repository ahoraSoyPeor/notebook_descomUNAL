/// Complexity: log(|N|)
/// Tested: https://tinyurl.com/y88y7ws7
int lower_find(int val) { /// last value < or <= to val
  int idx = 0;
  for(int i = 31-__builtin_clz(n); i >= 0; --i) {
    int nidx = idx | (1 << i);
    if(nidx <= n && bit[nidx] <= val) { /// change <= to <
      val -= bit[nidx];
      idx = nidx;
    }
  }
  return idx;
}
