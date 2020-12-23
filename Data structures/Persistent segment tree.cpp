/// Complexity: O(|N|*log|N|)
/// Tested: Not yet
struct node {
  node *left, *right;
  int v;
  node() : left(this), right(this), v(0) {}
  node(node *left, node *right, int v) :
    left(left), right(right), v(v) {}
  node* update(int l, int r, int x, int value) {
    if (l == r) return new node(nullptr, nullptr, v + value);
    int m = (l + r) / 2;
    if (x <= m)
      return new node(left->update(l, m, x, value), right, v + value);
    return new node(left, right->update(m + 1, r, x, value), v + value);
  }
};
