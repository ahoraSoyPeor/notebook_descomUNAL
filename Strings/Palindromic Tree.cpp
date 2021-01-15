/// Complexity: O(|N|*log(|alphabet|))
/// Tested: https://tinyurl.com/yxm8onrs
struct palindromic_tree {
  struct node{
    int len, link;
    map <char,int> next;
  };
  vector <node> pt;
  int last, it;
  string s;
  palindromic_tree (string str = "") {
    pt.reserve ( s.size()+2 );
    s = '#', it = 1, last = 1; //# isn't used in string
    add_node (), add_node();
    pt[1].len = -1, pt[0].link = 1;
    for ( char &c: str ) add_letter ( c );
  }
  int add_node () {
    pt.push_back({});
    return pt.size()-1;
  }
  int get_link ( int v ) {
    while ( s[it-pt[v].len-2] != s[it-1] ) v = pt[v].link;
    return v;
  }
  void add_letter ( char c ) {
    s += c, ++it;
    last = get_link ( last );
    if ( !pt[last].next.count (c) ) {
      int curr = add_node ();
      pt[curr].len = pt[last].len+2;
      pt[curr].link = pt[get_link(pt[last].link)].next[c];
      pt[last].next[c] = curr;
    }
    last = pt[last].next[c];
  }
  node& operator[](int i) { return pt[i]; }
  int size() { return pt.size(); }
};
