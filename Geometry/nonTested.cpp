 
lf part(pt a, pt b, T r) {
  lf l = abs(a-b);
  pt p = (b-a)/l;
  lf c = dot(a, p), d = 4.0 * (c*c - dot(a, a) + r*r);
  if (d < eps) return angle(a, b) * r * r * 0.5;
  d = sqrt(d) * 0.5;
  lf s = -c - d, t = -c + d;
  if (s < 0.0) s = 0.0; else if (s > l) s = l;
  if (t < 0.0) t = 0.0; else if (t > l) t = l;
  pt u = a + p*s, v = a + p*t;
  return (cross(u, v) + (angle(a, u) + angle(v, b)) * r * r) * 0.5;
}
lf inter_cp(circle c, polygon p) {
  lf ans = 0;
  int n = p.p.size();
  for (int i = 0; i < n; i++) {
    ans += part(p[i]-c.c, p[(i+1)%4]-c.c, c.r);
  }
  return abs(ans);
}
struct circle{
    point center; double r;
    bool contain(point &p) { return abs(center - p) < r + eps;}
};
T cross(point a, point b) { return a.x*b.y - a.y*b.x; }
point rot90ccw(point p) { return {-p.y, p.x}; }
point get(point a, point b, point c) {
  b = b-a, c = c-a;
  //assert(cross(b,c) != 0); /// no circumcircle if A,B,C aligned
  point cen = a + rot90ccw(b*norm(c) - c*norm(b))/cross(b,c)/2;
  return cen;
}

circle min_circle(vector<point> &cloud, int a, int b){
    point center = (cloud[a] + cloud[b]) / double(2.);
    double rat = abs(center - cloud[a]);
    circle C = {center, rat};
    for (int i = 0; i < b; ++i){
        point x = cloud[i];
        if (C.contain(x)) continue;
        center = get( cloud[a], cloud[b], cloud[i] );
        rat = abs(center - cloud[a]);
        C = {center, rat};
    }
    return C;
}

circle min_circle(vector<point> &cloud, int a){
    point center = (cloud[a] + cloud[0]) / double(2.);
    double rat = abs(center - cloud[a]);
    circle C = {center, rat};
    for (int i = 0; i < a; ++i){
        point x = cloud[i];
        if (C.contain(x)) continue;
        C = min_circle(cloud, a, i);
    }
    return C;
}
circle min_circle(vector<point> cloud){
    // random_shuffle(cloud.begin(), cloud.end());
    int n = (int)cloud.size();
    for (int i = 1; i < n; ++i){
        int u = rand() % i;
        swap(cloud[u], cloud[i]);
    }
    point center = (cloud[0] + cloud[1]) / double(2.);
    double rat = abs(center - cloud[0]);
    circle C = {center, rat};
    for (int i = 2; i < n; ++i){
        point x = cloud[i];
        if (C.contain(x)) continue;
        C = min_circle(cloud, i);
    }
    return C;
}