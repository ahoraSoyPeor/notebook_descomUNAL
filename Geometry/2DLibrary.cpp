struct Halfplane { // Every half-plane allows the region to the LEFT of its line.
    
    Point p, pq; 
    long double angle;

    Halfplane() {}
    Halfplane(const Point& a, const Point& b) : p(a), pq(b - a) {
        angle = atan2l(pq.y, pq.x);    
    }
    
    bool out(const Point& r) { 
        return cross(pq, r - p) < -eps; 
    }

    bool operator < (const Halfplane& e) const { 
        if (fabsl(angle - e.angle) < eps) return cross(pq, e.p - p) < 0;
        return angle < e.angle;
    } 

    bool operator == (const Halfplane& e) const { 
        return fabsl(angle - e.angle) < eps; 
    }

    friend Point inter(const Halfplane& s, const Halfplane& t) {
        long double alpha = cross((t.p - s.p), t.pq) / cross(s.pq, t.pq);
        return s.p + (s.pq * alpha);
    }
};

vector<Point> hp_intersect(vector<Halfplane>& H) { 

    Point box[4] = {  // Bounding box in CCW order
        Point(inf, inf), 
        Point(-inf, inf), 
        Point(-inf, -inf), 
        Point(inf, -inf) 
    };

    for(int i = 0; i<4; i++) {
        Halfplane aux(box[i], box[(i+1) % 4]);
        H.push_back(aux);
    }

    sort(H.begin(), H.end());
    H.erase(unique(H.begin(), H.end()), H.end());

    deque<Halfplane> dq;
    int len = 0;
    for(int i = 0; i < int(H.size()); i++) {
        while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
            dq.pop_back();
            --len;
        }
        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front();
            --len;
        }
        dq.push_back(H[i]);
        ++len;
    }

    while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))) {
        dq.pop_back();
        --len;
    }
    while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) {
        dq.pop_front();
        --len;
    }

    // Report empty intersection if necessary
    if (len < 3) return vector<Point>();

    vector<Point> ret(len);
    for(int i = 0; i+1 < len; i++)
        ret[i] = inter(dq[i], dq[i+1]);

    ret.back() = inter(dq[len-1], dq[0]);
    return ret;
}

typedef long double lf;
const lf EPS = 1e-8L;
const lf E0 = 0.0L;//Keep = 0 for integer coordinates, otherwise = EPS
const lf INF = 9e18;

enum {OUT,IN,ON};

struct pt {
  lf x,y;
  pt(){}
  pt(lf a , lf b): x(a), y(b){}

  pt operator - (const pt &q ) const {
    return {x - q.x , y - q.y };
  }

  pt operator + (const pt &q ) const {
    return {x + q.x , y + q.y };
  }

  pt operator * (const lf &t ) const {
    return {x * t , y * t };
  }

  bool operator < ( const pt & q ) const {
    if( fabsl( x - q.x ) > E0 ) return x < q.x;
    return y < q.y;
  }

  void normalize() {
    lf norm = hypotl( x, y );
    if( fabsl( norm ) > EPS )
      x /= norm, y /= norm;
  }
};

pt rot90( pt p ) { return { -p.y, p.x }; }
pt rot( pt p, lf w ) { 
  return { cosl( w ) * p.x - sinl( w ) * p.y, sinl( w ) * p.x + cosl( w ) * p.y };
}

lf norm2 ( pt p ) { return p.x * p.x + p.y * p.y; }
lf dis2 ( pt p, pt q ) { return norm2(p-q); }

lf norm ( pt p ) { return hypotl ( p.x, p.y ); }
lf dis( pt p, pt q ) { return norm( p - q ); }

lf dot( pt p, pt q ) { return p.x * q.x + p.y * q.y; }
lf cross( pt p, pt q ) { return p.x * q.y - q.x * p.y ; }

lf orient( pt a, pt b, pt c ) { return cross( b - a, c - a ); };

struct line {
  pt nv;
  lf c;

  line( pt _nv, lf _c ) : nv( _nv ), c( _c ) {}

  line ( pt p, pt q ) {
    nv = { p.y - q.y, q.x - p.x };
    c = -dot( p, nv );
  }

  lf eval( pt p ) { return dot( nv, p ) + c; }

  lf distance2( pt p ) {
    return eval( p ) / norm2( nv ) * eval( p );
  }

  lf distance( pt p ) {
    return fabsl( eval( p ) ) / norm( nv );
  }

  pt projection( pt p ) {
    return p - nv * ( eval( p ) / norm2( nv ) );
  }
};

pt lines_intersection( line a, line b ) {
  lf d = cross( a.nv, b.nv );
  //assert( fabsl( d ) > E0 );
  lf dx = a.nv.y * b.c - a.c * b.nv.y;
  lf dy = a.c * b.nv.x - a.nv.x * b.c;
  return { dx / d, dy / d };
}

line bisector( pt a, pt b ) {
  pt nv = ( b - a ), p = ( a + b ) * 0.5L;
  lf c = -dot( nv, p );
  return line( nv, c );
}

struct Circle {
  pt center;
  lf r;

  Circle( pt p, lf rad ) : center( p ), r( rad ) {};

  Circle( pt p, pt q ) {
    center = ( p + q ) * 0.5L;
    r = dis( p, q ) * 0.5L;
  }

  Circle( pt a, pt b, pt c ) {
    line lb = bisector( a, b ), lc = bisector( a, c );
    center = lines_intersection( lb, lc );
    r = dis( a, center );
  }

  int contains( pt &p ) {
    lf det = r * r - dis2( center, p );
    if( fabsl( det ) <= E0 ) return ON;
    return ( det > E0 ? IN : OUT );
  }
};

vector< pt > circle_line_intersection( Circle c, line l ) {
  lf h2 = c.r * c.r - l.distance2( c.center );
  if( fabsl( h2 ) < EPS ) return { l.projection( c.center ) };
  if( h2 < 0.0L ) return {};
  
  pt dir = rot90( l.nv );
  pt p = l.projection( c.center );
  lf t = sqrtl( h2 / norm2( dir ) );

  return { p + dir * t, p - dir * t };
}

vector< pt > circle_circle_intersection( Circle c1, Circle c2 ) {
  pt dir = c2.center - c1.center;
  lf d2 = dis2( c1.center, c2.center );

  if( d2 <= E0 ) { 
    //assert( fabsl( c1.r - c2.r ) > E0 );
    return {};
  }
  
  lf td = 0.5L * ( d2 + c1.r * c1.r - c2.r * c2.r );
  lf h2 = c1.r * c1.r - td / d2 * td;

  pt p = c1.center + dir * ( td / d2 );
  if( fabsl( h2 ) < EPS ) return { p };
  if( h2 < 0.0L ) return {};

  pt dir_h = rot90(dir) * sqrtl( h2 / d2 );
  return { p + dir_h, p - dir_h };
}

vector< pt > convex_hull( vector< pt > v ) {
  sort( v.begin(), v.end() );//remove repeated points if needed
  const int n = v.size();
  if( n < 3 ) return v;
  vector< pt > ch( 2 * n );

  int k = 0;
  for( int i = 0; i < n; ++ i ) {
    while( k > 1 && orient( ch[k-2], ch[k-1], v[i] ) <= E0 )
      --k;
    ch[k++] = v[i];
  }

  const int t = k;
  for( int i = n - 2; i >= 0; -- i ) {
    while( k > t && orient( ch[k-2], ch[k-1], v[i] ) <= E0 )
      --k;
    ch[k++] = v[i];
  }
  ch.resize( k - 1 );
  return ch;
}

int point_in_polygon( const vector< pt > &pol, const pt &p ) {
  int wn = 0;
  for( int i = 0, n = pol.size(); i < n; ++ i ) {
    lf c = orient( p, pol[i], pol[(i+1)%n] );
    if( fabsl( c ) <= E0 && dot( pol[i] - p, pol[(i+1)%n] - p ) <= E0 ) return ON;
    if( c > 0 && pol[i].y <= p.y + E0 && pol[(i+1)%n].y - p.y > E0 ) ++wn;
    if( c < 0 && pol[(i+1)%n].y <= p.y + E0 && pol[i].y - p.y > E0 ) --wn;
  }
  return wn ? IN : OUT;
}

int point_in_convex_polygon( const vector < pt > &pol, const pt &p ) {
  int low = 1, high = pol.size() - 1;
  while( high - low > 1 ) {
    int mid = ( low + high ) / 2;
    if( orient( pol[0], pol[mid], p ) >= -E0 ) low = mid;
    else high = mid;
  }
  if( orient( pol[0], pol[low], p ) < -E0 ) return OUT;
  if( orient( pol[low], pol[high], p ) < -E0 ) return OUT;
  if( orient( pol[high], pol[0], p ) < -E0 ) return OUT;

  if( low == 1 && orient( pol[0], pol[low], p ) <= E0 ) return ON;
  if( orient( pol[low], pol[high], p ) <= E0 ) return ON;
  if( high == (int) pol.size() -1 && orient( pol[high], pol[0], p ) <= E0 ) return ON;
  return IN;
}

Circle min_circle( vector< pt > v ) {
  random_shuffle( v.begin(), v.end() );
  auto f2 = [&]( int a, int b ){
    Circle ans( v[a], v[b] );
    for( int i = 0; i < a; ++ i )
      if( ans.contains( v[i] ) == OUT )
        ans = Circle( v[i], v[a], v[b] );
    return ans;
  };

  auto f1 = [&]( int a ){
    Circle ans( v[a], 0.0L );
    for( int i = 0; i < a; ++ i )
      if( ans.contains( v[i] ) == OUT )
        ans = f2( i, a );
    return ans;
  };

  Circle ans( v[0], 0.0L );
  for( int i = 1; i < (int) v.size(); ++ i )
    if( ans.contains( v[i] ) == OUT )
      ans = f1( i );

  return ans;
}

pair < pt, pt >  closest_points ( vector< pt > v ) {
  sort( v.begin(), v.end() );
  pair< pt, pt > ans;
  lf d2 = INF;

  function< void( int, int ) > solve = [&]( int l, int r ) {
    if( l == r ) return;

    int mid = ( l + r ) / 2;
    lf x_mid = v[mid].x;
    solve( l, mid );
    solve( mid + 1, r );

    vector< pt > aux;
    int p1 = l, p2 = mid + 1;
    while ( p1 <= mid && p2 <= r ) {
      if( v[p1].y < v[p2].y ) aux.push_back( v[p1++] );
      else aux.push_back( v[p2++] );
    }
    while( p1 <= mid ) aux.push_back( v[p1++] );
    while( p2 <= r ) aux.push_back( v[p2++] );

    vector < pt > nb;
    for( int i = l; i <= r; ++ i ) {
      v[i] = aux[i-l];
      lf dx = ( x_mid - v[i].x );
      if( dx * dx < d2 )
        nb.push_back( v[i] );
    }

    for( int i = 0; i < (int) nb.size(); ++ i ) {
      for( int k = i + 1; k < (int) nb.size(); ++ k ) {
        lf dy = ( nb[k].y - nb[i].y );
        if( dy * dy > d2 ) break;
        lf nd2 = dis2( nb[i], nb[k] );
        if( nd2 < d2 ) d2 = nd2, ans = {nb[i], nb[k]};
      }
    }
  };
  solve( 0, v.size() -1 );
  return ans;
}
