 
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
