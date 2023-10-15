struct seg {
    pt p, q;
    int id;
    lf get_y(double x) const {
        if (fabsl (p.x - q.x) < EPS) return p.y;
        return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
    }
};
bool operator<(const seg& a, const seg& b) {
    lf x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
    return a.get_y(x) < b.get_y(x) - EPS;
}
//Use where[id] = s.insert(nxt, a[id]) & s.erase(where[id]);
set<seg> s;
vector<set<seg>::iterator> where;
