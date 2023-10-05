

typedef long long   type;

struct line {
  type m, b;
  type eval (type x) {
    return m * x + b;
  }
};

/// M = 4 * (number of updates) * (log R) where R is the range of the segtree
/// oo is the max abs value that the function may take

const type R = 1e9+5;
const int M = 1e7;
const type oo = 2e18;

struct li_chao {
  /// see comments for min

  int nodes;
  line lines[M];
  int lf[M], rg[M];

  void ini () {
    nodes = 0;
    memset(lf, -1, sizeof lf);
    memset(rg, -1, sizeof rg);
    lines[0] = {0, -oo}; /// change to {0, oo};
  }

  int add_line (int node, type l, type r, line nw) {
    if (node == -1) {
      lines[++nodes] = nw;
      return nodes;
    }
    type m = (l + r) >> 1;

    bool lef = nw.eval(l) > lines[node].eval(l); ///change > to <
    bool mid = nw.eval(m) > lines[node].eval(m); ///change > to <

    if (mid) swap(nw, lines[node]);
    lines[++nodes] = lines[node];
    lf[nodes] = lf[node];
    rg[nodes] = rg[node];

    int sv = nodes;
    if (r == l) return sv;
    if (lef != mid) lf[sv] = add_line(lf[node], l, m, nw);
    else rg[sv] = add_line(rg[node], m + 1, r, nw);
    return sv;
  }

  type get(int node, type l, type r, type x) {
    if (node == -1) return -oo; ///change to oo
    type m = (l + r) / 2;
    if(l == r) {
        return lines[node].eval(x);
    } else if(x < m) {
        return max(lines[node].eval(x), get(lf[node], l, m, x)); ///change max to min
    } else {
        return max(lines[node].eval(x), get(rg[node], m + 1, r, x)); ///change max to min
    }
  }
};
