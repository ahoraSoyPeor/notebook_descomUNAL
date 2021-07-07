/// Complexity: O(|N|*log(|N|))
/// Tested: https://tinyurl.com/problem-L
typedef ll T;
const T is_query = -(1LL<<62);
struct line {
	T m, b;
	mutable multiset<line>::iterator it, end;
	bool operator < (const line &rhs) const {
		if(rhs.b != is_query) return m < rhs.m;
		auto s = next(it);
		if(s == end) return 0;
		return b - s->b < (long double)(s->m - m) * rhs.m;
	}
};
struct CHT : public multiset<line> {
	bool bad(iterator y) {
		auto z = next(y);
		if(y == begin()) {
			if(z == end()) return false;
			return y->m == z->m && y->b <= z->b;
		}
		auto x = prev(y);
		if(z == end()) return y->m == x->m && y->b == x->b;
		return (long double)(x->b - y->b)*(z->m - y->m) >= (long double)(y->b - z->b)*(y->m - x->m);
	}
	void add(T m, T b) {
		auto y = insert({m, b});
		y->it = y; y->end = end();
		if(bad(y)) { erase(y); return; }
		while(next(y) != end() && bad(next(y))) erase(next(y));
		while(y != begin() && bad(prev(y)))erase(prev(y));
	}
	T eval(T x) { /// for maximum
		auto l = *lower_bound({x, is_query});
		return l.m*x+l.b;
	}
};
// for minimum, you must change (b, m) to (-b, -m)