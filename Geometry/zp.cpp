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

struct pt
{
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
      if( x != q.x ) return x < q.x;
      return y < q.y;
    }
};

inline lf norm2 ( pt p ) { return p.x * p.x + p.y * p.y; }
inline lf dis2 ( pt p, pt q ) { return norm2(p-q); }

inline lf norm ( pt p ) { return hypotl ( p.x, p.y ); }
inline lf dis( pt p, pt q ) { return norm( p - q ); }

inline lf dot( pt p, pt q ) { return p.x * q.x + p.y * p.y; }
inline lf cross( pt p, pt q ) { return p.x * q.y - q.x * p.y ; }

inline lf orient( pt a, pt b, pt c ) { return cross( b - a, c - a ); };

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

enum {OUT,IN,ON};

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
