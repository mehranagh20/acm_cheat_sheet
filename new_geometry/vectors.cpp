// 1D OBJECTS: VECTORS
// Vectors are represented with two members: The x and y magnitude of the vector. implementation: dd(x, y)
// The magnitude of the vector can be scaled if needed.

// converts 2 points to vector a->b
dd toVec(dd a, dd b) { return dd(b.first - a.first, b.second - a.second); }

// nonnegative s = [<1 (shorter).. 1 (same).. >1 (longer)]
dd scale(dd v, double s) { return dd(v.first * s, v.second * s); }

// translate(move) p according to v
dd translate(dd p, dd v) { return dd(p.first + v.first , p.second + v.second); }

// dot product
double dot(dd a, dd b) { return (a.first * b.first + a.second * b.second); }

// norm of vector
double norm_sq(dd v) { return v.first * v.first + v.second * v.second; }

// uses: toVec, dot, norm_sq, translate, scale -> vectors AND dist -> points
// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (by reference)
double distToLine(dd p, dd a, dd b, dd &c) {
    // formula: c = a + u * ab
    dd ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u)); // translate a to c
    return dist(p, c); // Euclidean distance between p and c
}

// uses: toVec, dot, norm_sq, translate, scale, distToLine -> vectors AND dist -> points
// returns the distance from p to the line segment ab defined by
// two points a and b (still OK if a == b)
// the closest point is stored in the 4th parameter (by reference)
double distToLineSegment(dd p, dd a, dd b, dd &c) {
    dd ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0) { // closer to a
        c = dd(a.first, a.second);
        return dist(p, a); // Euclidean distance between p and a
    }
    if (u > 1.0){ // closer to b
        c = dd(b.first, b.second);
        return dist(p, b); // Euclidean distance between p and b
    }
    return distToLine(p, a, b, c); // run distToLine as above
}

// uses: pointSlopeToLine, areIntersect, areParallel -> lines
// returns just the closest point from p to the line l
// the closest point is stored in the 3rd parameter (by reference)
void closestPoint(ddd l, dd p, dd &ans) {
    ddd perpendicular; // perpendicular to l and pass through p
    if (fabs(l.first.second) < eps) { // special case 1: vertical line
        ans.first = -(l.second); ans.second = p.second; return;
    }
    if (fabs(l.first.first) < eps) { // special case 2: horizontal line
        ans.first = p.first; ans.second = -(l.second); return;
    }
    
    pointSlopeToLine(p, 1 / l.first.first, perpendicular); // normal line
    // intersect line l with this perpendicular line
    // the intersection point is the closest point
    areIntersect(l, perpendicular, ans);
}

// uses: pointSlopeToLine, areIntersect, areParallel, toVec, translate -> vectors
// returns the reflection of point p on the line l
// the reflection point is stored in the 3rd parameter (by reference)
void reflectionPoint(ddd l, dd p, dd &ans) {
    dd b;
    closestPoint(l, p, b); // similar to distToLine
    dd v = toVec(p, b); // create a vector
    ans = translate(translate(p, v), v); // translate p twice
}

// uses toVec, norm_sq -> vectors AND radToDeg -> points
// NOTE!: returns angle aob in DEG
double angle(dd a, dd o, dd b) {
    dd oa = toVec(o, a), ob = toVec(o, b);
    double ans =  acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
    return radToDeg(ans);
}

// cross product
double cross(dd a, dd b) { return a.first * b.second - a.second * b.first; }

double cross(dd O, dd A, dd B) {
    return (A.first - O.first) * (B.second - O.second) -
            (A.second - O.second) * (B.first - O.first);
}

// uses: cross, toVec -> vectors
// returns true if point r is on the left side of line pq
// The left turn test is more famously known as the CCW (Counter Clockwise) Test.
bool ccw(dd p, dd q, dd r) { return cross(toVec(p, q), toVec(p, r)) > eps; }

// uses: corss, toVec -> vectors
// returns true if point r is on the same line as the line pq
bool collinear(dd p, dd q, dd r) { return fabs(cross(toVec(p, q), toVec(p, r))) < eps; }
