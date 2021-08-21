/// Complexity: O(|N|*log|N|)
/// Tested: https://tinyurl.com/2h9atzz9

struct node {
  int lz, lzL, lzR, val;
  node *L, *R;
  node(int lz = 0) : lz(lz), lzL(0), lzR(0), val(0), L(0), R(0) {}
  void propagate(int l, int r) {
    if(lz) {
      if(l != r) {
        if(L) L->lz ^= 1;
        else lzL ^= 1;
        if(R) R->lz ^= 1;
        else lzR ^= 1;
      }
      val = (r-l+1) - val;
      lz = 0;
    }
  }
};
int get_val(node* root, int lz, int a, int b) {
  if(!root) return lz*(b-a+1);
  return root->val;
}
int NEUTRAL = 0;
struct implicit_segtree { 
  node* root;
  int n; // 0-indexed
  implicit_segtree(int n) : n(n), root(new node()) {}
  void update(int a, int b, int x) { update(root, a, b, 0, n-1, x); }
  void update(node* &root, int a, int b, int l, int r, int x, int lz = 0) {
    if((l > b || r < a) && !root) return; // break condition, this line optimizes memory
    if(root == nullptr) root = new node(lz);
    root->propagate(l, r);
    if(l > b || r < a) return; // break condition
    if(a <= l && r <= b) { // tag condition
      root->lz = x;
      root->propagate(l, r);
    } else {
      int m = (l+r) >> 1;
      update(root->L, a, b, l, m, x, root->lzL);
      update(root->R, a, b, m+1, r, x, root->lzR);
      root->val = get_val(root->L, root->lzL, l, m) + get_val(root->R, root->lzR, m+1, r);
    }
  }
  int query(int a, int b) { return query(root, a, b, 0, n-1); }
  int query(node* root, int a, int b, int l, int r, int lz = 0) {
    if(l > b || r < a) return NEUTRAL;
    if(root) root->propagate(l, r);
    if((a <= l && r <= b) || !root) { 
      return get_val(root, lz, l, r);
    } else {
      int m = (l+r) >> 1;
      return query(root->L, a, b, l, m, root->lzL) + query(root->R, a, b, m+1, r, root->lzR);
    }
  }
};

