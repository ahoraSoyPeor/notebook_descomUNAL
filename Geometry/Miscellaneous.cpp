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
bool circumcircle_contains( triangle tr, pt D ) {//triange CCW
  pt A = tr.vert[0] - D, B = tr.vert[1] - D, C = tr.vert[2] - D;

  lf norm_a = norm2( tr.vert[0] ) - norm2( D );
  lf norm_b = norm2( tr.vert[1] ) - norm2( D );
  lf norm_c = norm2( tr.vert[2] ) - norm2( D );

  lf det1 = A.x * ( B.y * norm_c - norm_b * C.y );
  lf det2 = B.x * ( C.y * norm_a - norm_c * A.y );
  lf det3 = C.x * ( A.y * norm_b - norm_a * B.y );

  return det1 + det2 + det3 > E0;
}
lf areaOfIntersectionOfTwoCircles( lf r1, lf r2, lf d ) {
  if( d >= r1 + r2 )
    return 0.0L;
  if( d <= fabsl( r2 - r1 ) )
    return PI * ( r1 < r2 ? r1 * r1 : r2 * r2 );
  lf alpha = safeAcos( ( r1 * r1 - r2 * r2 + d * d ) / ( 2.0L * d * r1 ) );
  lf betha = safeAcos( ( r2 * r2 - r1 * r1 + d * d ) / ( 2.0L * d * r2 ) );
  lf a1 = r1 * r1 * ( alpha - sinl( alpha ) * cosl( alpha ) );
  lf a2 = r2 * r2 * ( betha - sinl( betha ) * cosl( betha ) );
  return a1 + a2;
};
bool half(pt p) { /// true if is in (0, 180]
  assert(p.x != 0 || p.y != 0); /// the argument of (0,0) is undefined
  return p.y > 0 || (p.y == 0 && p.x < 0);
}
bool half_from(pt p, pt v = {1, 0}) {
  return cross(v,p) < 0 || (cross(v,p) == 0 && dot(v,p) < 0);
}
bool polar_cmp(const pt &a, const pt &b) {
  return make_tuple(half(a), 0) < make_tuple(half(b), cross(a,b));
}
bool in_disk(pt a, pt b, pt p) {
  return dot(a-p, b-p) <= 0;
}
bool on_segment(pt a, pt b, pt p) {
  return orient(a,b,p) == 0 && in_disk(a,b,p);
}
bool proper_inter(pt a, pt b, pt c, pt d, pt &out) {
  T oa = orient(c,d,a), ob = orient(c,d,b),
    oc = orient(a,b,c), od = orient(a,b,d);
  if (oa*ob < 0 && oc*od < 0) {
    out = (a*ob - b*oa) / (ob-oa);
    return true;
  }
  return false;
}
set<pt> inter_ss(pt a, pt b, pt c, pt d) {
  pt out;
  if (proper_inter(a,b,c,d,out)) return {out};
  set<pt> s;
  if (on_segment(c,d,a)) s.insert(a);
  if (on_segment(c,d,b)) s.insert(b);
  if (on_segment(a,b,c)) s.insert(c);
  if (on_segment(a,b,d)) s.insert(d);
  return s;
}
lf pt_to_seg(pt a, pt b, pt p) {
  if(a != b) {
    line l(a,b);
    if (l.cmp_proj(a,p) && l.cmp_proj(p,b)) /// if closest to  projection
      return l.dist(p); /// output distance to line
  }
  return min(abs(p-a), abs(p-b)); /// otherwise distance to A or B
}
lf seg_to_seg(pt a, pt b, pt c, pt d) {
  pt dummy;
  if (proper_inter(a,b,c,d,dummy)) return 0;
  return min({pt_to_seg(a,b,c), pt_to_seg(a,b,d),
              pt_to_seg(c,d,a), pt_to_seg(c,d,b)});
}

enum {IN, OUT, ON};
struct polygon {
  vector<pt> p;
  polygon(int n) : p(n) {}
  pt centroid() {
    pt c{0, 0};
    lf scale = 6. * area(true);
    for(int i = 0, n = p.size(); i < n; ++i) {
      int j = (i+1 == n ? 0 : i+1);
      c = c + (p[i] + p[j]) * cross(p[i], p[j]);
    }
    return c / scale;
  }
  ll pick() {
    ll boundary = 0;
    for(int i = 0, n = p.size(); i < n; i++) {
      int j = (i+1 == n ? 0 : i+1);
      boundary += __gcd((ll)abs(p[i].x - p[j].x), (ll)abs(p[i].y - p[j].y));
    }
    return area() + 1 - boundary/2;
  }
  pt& operator[] (int i){ return p[i]; }
};
int tangents(circle c1, circle c2, bool inner, vector<pair<pt,pt>> &out) {
  if(inner) c2.r = -c2.r;
  pt d = c2.c-c1.c;
  double dr = c1.r-c2.r, d2 = norm(d), h2 = d2-dr*dr;
  if(d2 == 0 || h2 < 0) { assert(h2 != 0); return 0; }
  for(double s : {-1,1}) {
    pt v = (d*dr + rot90ccw(d)*sqrt(h2)*s)/d2;
    out.push_back({c1.c + v*c1.r, c2.c + v*c2.r});
  }
  return 1 + (h2 > 0);
}
int tangent_through_pt(pt p, circle c, pair<pt, pt> &out) {
  double d = abs(p - c.c);
	if(d < c.r) return 0;
  pt base = c.c-p;
  double w = sqrt(norm(base) - c.r*c.r);
  pt a = {w, c.r}, b = {w, -c.r};
  pt s = p + base*a/norm(base)*w;
  pt t = p + base*b/norm(base)*w;
  out = {s, t};
  return 1 + (abs(c.c-p) == c.r);
}
