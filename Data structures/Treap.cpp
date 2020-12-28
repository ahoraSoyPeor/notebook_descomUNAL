/// Complexity: log(|N|) per operation
/// Tested: https://tinyurl.com/yafpy7zc

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> rnd(0, LLONG_MAX);

typedef long long T;
struct treap {
  treap *left, *right, *father;
  ll prior; 
  int sz, idx;
  T value, lazy_sum, sum;
  treap(T x) {
    left = right = father = NULL;
    prior = rnd(rng);
    sz = 1;
    value = sum = x;
    lazy_sum = 0;
  }
};

int cnt(treap* t)  { return !t ? 0 : t->sz; }
T sum(treap* t)  { return !t ? 0 : t->sum; }
T value(treap* t)  { return !t ? 0 : t->value; }

void propagate(treap* t) {
  if(t && t->lazy_sum) {
    if(t->left) t->left->lazy_sum += t->lazy_sum;
    if(t->right) t->right->lazy_sum += t->lazy_sum;
    t->sum += cnt(t) * t->lazy_sum;
    t->value += t->lazy_sum;
    t->lazy_sum = 0;
  }
}

void update(treap *t) {
  propagate(t->left);
  propagate(t->right);
  t->sz = cnt(t->left) + cnt(t->right) + 1;
  t->sum = sum(t->left) + sum(t->right) + value(t);
  if(t->left) t->left->father = t;
  if(t->right) t->right->father = t;
}

void add_value(treap *t, T v) {
  t->value += v;
  update(t);
}
void add_lazy_sum(treap *t, T v) {
  t->lazy_sum += v;
  update(t);
}

pair<treap*, treap*> split(treap* t, int left_count) {
  if(!t) return {NULL, NULL};
  propagate(t);
  if(cnt(t->left) >= left_count) {
    auto got = split(t->left, left_count);
    t->left = got.second;
    update(t);
    return {got.first, t};
  } else {
    left_count = left_count-cnt(t->left)-1;
    auto got = split(t->right, left_count);
    t->right = got.first;
    update(t);
    return {t, got.second};
  }
}

treap* merge(treap *s, treap *t) {
  if(!s) return t;
  if(!t) return s;
  propagate(s);
  propagate(t);
  if(s->prior <= t->prior) {
    s->right = merge(s->right, t);
    update(s);
    return s;
  } else {
    t->left = merge(s, t->left);
    update(t);
    return t;
  }
};

void print(treap *x) {
  if(!x) return;
  propagate(x);
  print(x->left);
  cout << value(x) << ", ";
  print(x->right);
}

int find_left_count(treap* root, treap* x) { /// x not inclusive
  if(!x) return 0;
  int ans = cnt(x->left);
  while(x != root) {
    treap *par = x->father;
    if(par->right == x) ans += cnt(par->left)+1;
    x = par;
  }
  return ans;
}

treap *root = NULL;