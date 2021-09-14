// Basic half-plane struct.
struct Halfplane { 

    // 'p' is a passing point of the line and 'pq' is the direction vector of the line.
    Point p, pq; 
    long double angle;

    Halfplane() {}
    Halfplane(const Point& a, const Point& b) : p(a), pq(b - a) {
        angle = atan2l(pq.y, pq.x);    
    }

    // Check if point 'r' is outside this half-plane. 
    // Every half-plane allows the region to the LEFT of its line.
    bool out(const Point& r) { 
        return cross(pq, r - p) < -eps; 
    }

    // Comparator for sorting. 
    // If the angle of both half-planes is equal, the leftmost one should go first.
    bool operator < (const Halfplane& e) const { 
        if (fabsl(angle - e.angle) < eps) return cross(pq, e.p - p) < 0;
        return angle < e.angle;
    } 

    // We use equal comparator for std::unique to easily remove parallel half-planes.
    bool operator == (const Halfplane& e) const { 
        return fabsl(angle - e.angle) < eps; 
    }

    // Intersection point of the lines of two half-planes. It is assumed they're never parallel.
    friend Point inter(const Halfplane& s, const Halfplane& t) {
        long double alpha = cross((t.p - s.p), t.pq) / cross(s.pq, t.pq);
        return s.p + (s.pq * alpha);
    }
};


// Actual algorithm
vector<Point> hp_intersect(vector<Halfplane>& H) { 

    Point box[4] = {  // Bounding box in CCW order
        Point(inf, inf), 
        Point(-inf, inf), 
        Point(-inf, -inf), 
        Point(inf, -inf) 
    };

    for(int i = 0; i<4; i++) { // Add bounding box half-planes.
        Halfplane aux(box[i], box[(i+1) % 4]);
        H.push_back(aux);
    }

    // Sort and remove duplicates
    sort(H.begin(), H.end());
    H.erase(unique(H.begin(), H.end()), H.end());

    deque<Halfplane> dq;
    int len = 0;
    for(int i = 0; i < int(H.size()); i++) {

        // Remove from the back of the deque while last half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
            dq.pop_back();
            --len;
        }

        // Remove from the front of the deque while first half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front();
            --len;
        }

        // Add new half-plane
        dq.push_back(H[i]);
        ++len;
    }

    // Final cleanup: Check half-planes at the front against the back and vice-versa
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

    // Reconstruct the convex polygon from the remaining half-planes.
    vector<Point> ret(len);
    for(int i = 0; i+1 < len; i++) {
        ret[i] = inter(dq[i], dq[i+1]);
    }
    ret.back() = inter(dq[len-1], dq[0]);
    return ret;
}

enum {IN,OUT,ON};

int point_in_polygon( vector< pt > &pol, pt &p )
{
  int wn = 0;
  for( int i = 0, n = pol.size(); i < n; ++ i )
  {
    long long c = orient( p, pol[i], pol[(i+1)%n] );
    if( c == 0 && dot( pol[i] - p, pol[(i+1)%n] - p ) <= 0 ) return ON; 
    if( c > 0 && pol[i].y <= p.y && pol[(i+1)%n].y > p.y ) ++ wn;
    if( c < 0 && pol[(i+1)%n].y <= p.y && pol[i].y > p.y ) --wn;
  }
  return wn ? IN : OUT;
}

bool insideConvexPol( vector < pt > &pol, pt &p ){
    int low = 1, high = pol.size() - 1;
    while( high - low > 1 ){
        int mid = ( high + low ) / 2;
        if( orient( pol[0], pol[mid], p ) >= 0 ) low = mid;
        else high = mid;
    }
    if( orient( pol[0], pol[low], p ) < 0 ) return false;
    if( orient( pol[low], pol[high], p ) < 0 ) return false;
    if( orient( pol[high], pol[0], p ) < 0 ) return false;
    return true;    
}

lf areaOfIntersectionOfTwoCircles( lf r1, lf r2, lf d )
{
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



