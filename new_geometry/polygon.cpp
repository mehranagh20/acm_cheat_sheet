// POLYGONS

// Implementation
// 3 points, entered in counter clockwise order, 0-based indexing
//
// vdd P;
// P.push_back(point(1, 1)); // P0
// P.push_back(point(3, 3)); // P1
// P.push_back(point(9, 1)); // P2
// P.push_back(P[0]); // important: loop back

// returns the perimeter, which is the sum of Euclidian distances
// of consecutive line segments (polygon edges)
double polygonPerimeter(const vdd &P) {
    double result = 0.0;
    for (int i = 0; i < P.size() - 1; ++i) // remember that P[0] = P[n-1]
        result += dist(P[i], P[i + 1]);
    return result;
}

// returns the area, which is half the determinant
double polygonArea(const vdd &P) {
    double result = 0.0, x1, y1, x2, y2;
    for (int i = 0; i < (int)P.size() - 1; i++) {
        x1 = P[i].first, x2 = P[i + 1].first;
        y1 = P[i].second, y2 = P[i + 1].second;
        result += (x1 * y2 - x2 * y1);
    }
    return fabs(result) / 2.0;
}

// uses: ccw, cross, toVec -> vectors
// note: ccw func must change inorder to accept collinear lines (> -eps)
// returns true if all three consecutive vertices of P form the same turns
bool isConvex(const vdd &P) {
    int sz = (int)P.size();
    if (sz <= 3) return false;
    bool isLeft = ccw(P[0], P[1], P[2]);
    
    for (int i = 1; i < sz - 1; i++) // then compare with the others
        if (ccw(P[i], P[i + 1], P[(i + 2) == sz ? 1 : i + 2]) != isLeft)
            return false; // different sign -> this polygon is concave
    return true; // this polygon is convex
}

// uses: ccw, cross, toVec, angle, norm_sq -> vectors AND radToDeg -> points
// returns true if point pt is in either convex/concave polygon P
bool inPolygon(dd pt, const vdd &P) {
    int sz = (int)P.size();
    if (sz <= 3) return false;
    
    double sum = 0; // assume the first vertex is equal to the last vertex
    for (int i = 0; i < sz - 1; i++) {
        if (ccw(pt, P[i], P[i + 1])) // left turn/ccw
            sum += degToRad(angle(P[i], pt, P[i + 1]));
        else // right turn/cw
            sum -= degToRad(angle(P[i], pt, P[i + 1]));
    }
    return fabs(fabs(sum) - 2 * pi) < eps;
}

// uses: collinear, corss, toVec -> vectors
// returns true if point pt is on convex/concave polygon P
bool onPolygon(dd pt, const vdd &P){
    int sz = (int)P.size();
    if (sz <= 3) return false;
    
    for (int i = 0; i < sz - 1; ++i)
        if(collinear(P[i], P[i + 1], pt))
            return true;
    
    return false;
}

// uses cross, toVec -> vectos AND lineIntersectSeg -> lines
// cuts polygon Q along the line formed by point a -> point b
// (note: the last point must be the same as the first point)
// to get the right cut just call the function with a, b reversed
vdd cutPolygon(dd a, dd b, const vdd &Q) {
    vdd P;
    for (int i = 0; i < (int)Q.size(); i++) {
        double left1 = cross(toVec(a, b), toVec(a, Q[i])), left2 = 0;
        if (i != (int)Q.size() - 1)
            left2 = cross(toVec(a, b), toVec(a, Q[i+1]));
        
        if (left1 > -eps) P.push_back(Q[i]); // Q[i] is on the left of ab
        if (left1 * left2 < -eps) // edge (Q[i], Q[i+1]) crosses line ab
            P.push_back(lineIntersectSeg(Q[i], Q[i+1], a, b));
    }
    if (!P.empty() && P.back() != P.front())
        P.push_back(P.front()); // make P’s first point = P’s last point
    return P;
}

// CONVEX HALL
// uses: cross -> vectors
// IMPORTANT!: the first point does not have to be replicated as the last point
vdd convexHull(vdd P){
    int n = P.size(),k = 0; vdd H(2*n);
    sort(P.begin(), P.end());
    for(int i = 0; i < n; i++){
        while(k >= 2 && cross(H[k - 2], H[k - 1] , P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    
    for(int i = n - 2, t = k + 1; i >= 0; i--){
        while(k >= t && cross(H[k - 2], H[k - 1] , P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k); return H;
}
