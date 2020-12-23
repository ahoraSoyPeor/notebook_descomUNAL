mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> rnd(0, INT_MAX);

typedef long long T;
struct node {
  node *left, *right;
  int prior, sz;
  T value, lazy_sum, sum;
  node() {
    left = right = NULL;
    prior = rnd(rng);
    sz = 1;
    value = lazy_sum = sum = 0;
  }
};

int cnt(node* t)  { return !t ? 0 : t->sz; }
int sum(node* t)  { return !t ? 0 : t->sum; }

void propagate(node* t) {
  if(t->lazy_sum) {
    if(t->left) t->left->lazy_sum += t->lazy_sum;
    if(t->right) t->right->lazy_sum += t->lazy_sum;
    t->sum += cnt(t) * t->lazy_sum;
    t->value += t->lazy_sum;
    t->lazy_sum = 0;
  }
}

void update(node *t) {
  t->sz = cnt(t->left) + cnt(t->right) + 1;
  t->value = sum(t->left) + sum(t->right) + t->value;
}

pair<node*, node*> split(node* t, int left_count) {
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

node* merge(node *s, node *t) {
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
}