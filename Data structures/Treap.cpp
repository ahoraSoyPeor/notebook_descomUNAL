/// Complexity: O(|N|*log|N|)
/// Tested: Not yet
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> dis64(0, 1ll<<60);
template <typename T> 
class treap {
private:
	struct item;
	typedef struct item * pitem;
	pitem root = NULL;
	struct item {
		ll prior; int cnt, rev;
		T key, add, fsum;
		pitem l, r;
		item(T x, ll p) {
			add = 0*x; key = fsum = x;
			cnt = 1; rev = 0;
			l = r = NULL; prior = p;
		}
	};
	int cnt(pitem it) { return it ? it->cnt : 0;	}
	void upd_cnt(pitem it) {
		if(it) it->cnt = cnt(it->l) + cnt(it->r) + 1;
	}
	void upd_sum(pitem it) {
		if(it) {
			it->fsum = it->key;
			if(it->l) it->fsum += it->l->fsum;
			if(it->r) it->fsum += it->r->fsum;
		}
	}
	void update(pitem t, T add, int rev) {
		if(!t) return;
		t->add = t->add + add;
		t->rev = t->rev ^ rev;
		t->key = t->key + add;
		t->fsum = t->fsum + cnt(t) * add;
	}
	void push(pitem t) {
	 	if(!t || (t->add == 0*T() && t->rev == 0)) return;
		update(t->l, t->add, t->rev);
		update(t->r, t->add, t->rev);
		if(t->rev) swap(t->l,t->r);
		t->add = 0*T(); t->rev = 0;
	}
	void merge(pitem & t, pitem l, pitem r) {
		push(l); push(r);
		if(!l || !r) t = l ? l : r;
		else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
		else merge(r->l, l, r->l), t = r;
		upd_cnt(t); upd_sum(t);
	}
	void split(pitem t, pitem & l, pitem & r, int index) { // split index = how many elements
		if(!t) return void(l = r = 0);
		push(t);
		if(index <= cnt(t->l)) split(t->l, l, t->l, index), r = t;
		else split(t->r, t->r, r, index - 1 - cnt(t->l)), l = t;
		upd_cnt(t); upd_sum(t);
	}
	void insert(pitem & t, pitem it, int index) { // insert at position
		push(t);
		if(!t) t = it;
		else if(it->prior > t->prior) split(t, it->l, it->r, index), t = it;
		else if(index <= cnt(t->l)) insert(t->l, it, index);
		else insert(t->r, it, index-cnt(t->l)-1);
		upd_cnt(t);	upd_sum(t);
	}
	void erase(pitem & t, int index) {
		push(t);
		if(cnt(t->l) == index) merge(t, t->l, t->r);
		else if(index < cnt(t->l)) erase(t->l, index);
		else erase(t->r, index - cnt(t->l) - 1);
		upd_cnt(t);	upd_sum(t);
	}
	T get(pitem t, int index) {
		push(t);
		if(index < cnt(t->l)) return get(t->l, index);
		else if(index > cnt(t->l)) return get(t->r, index - cnt(t->l) - 1);
		return t->key;
	}  
  T query_sum (pitem &t, int l, int r) {
		pitem l1, r1;
		split (t, l1, r1, r + 1);
		pitem l2, r2;
		split (l1, l2, r2, l);
		T ret = r2->fsum;
		pitem t2;
		merge (t2, l2, r2);
		merge (t, t2, r1);
		return ret;
	}
public:
	int size() { return cnt(root); }
	void insert(int pos, T x) {
		if(pos > size()) return;
		pitem it = new item(x, dis64(rng64));
		insert(root, it, pos);
	}
	void erase(int pos) {
		if(pos >= size()) return;
		erase(root, pos);
	}
  T sum(int left, int right) {
    return query_sum(root, left, right);
	}
	T operator[](int index) { return get(root, index); }
};
