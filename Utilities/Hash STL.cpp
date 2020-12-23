/// Complexity: -
/// Tested: https://tinyurl.com/y8orp8t2
struct Hash {
  size_t operator()(const pii &x) const {
    return (size_t) x.first * 37U + (size_t) x.second;
  }
	size_t operator()(const vector<int> &v)const{
		size_t s = 0;
		for(auto &e : v)
			s ^= hash<int>()(e)+0x9e3779b9+(s<<6)+(s>>2);
		return s;
	}
};
unordered_map<pii, T, Hash> mp;
mp.reserve(1024); /// power of 2
mp.max_load_factor(0.25);
