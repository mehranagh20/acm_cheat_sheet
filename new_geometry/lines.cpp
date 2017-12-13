// 1D OBJECTS: LINES
// Euclidean equation ax + by + c = 0. implementation: ddd(dd(a, b), c)
// Subsequent functions in this subsection assume that this linear equation has b = 1 for
// non vertical lines and b = 0 for vertical lines unless otherwise stated.

// the answer is stored in the third parameter (pass by reference)
void pointsToLine(dd p1, dd p2, ddd &l) {
    double &a = l.first.first, &b = l.first.second, &c = l.second;
    double &x1 = p1.first, &y1 = p1.second, &x2 = p2.first;
    
    if (fabs(x1 - x2) < eps) // vertical line is fine
        a = 1.0, b = 0.0, c = -x1;
    
    else {
        a = -(y1 - p2.second) / (x1 - x2);
        b = 1.0; // IMPORTANT: we fix the value of b to 1.0
        c = -(a * x1) - y1;
    }
}

// convert point and gradient/slope to line. y = mx + c --> ax + by + c = 0
void pointSlopeToLine(dd p, double m, ddd &l) {
    double &a = l.first.first, &b = l.first.second, &c = l.second;
    a = -m, b = 1, c = -((a * p.first) + (b * p.second));
}

// check coefficients a & b
bool areParallel(ddd l1, ddd l2) {
    return (fabs(l1.first.first - l2.first.first) < eps) &&
    (fabs(l1.first.second-l2.first.second) < eps);
}

// uses: areParallel -> lines
// also check coefficient c. NOTE: uses areParallel!!
bool areSame(ddd l1, ddd l2) {
    return areParallel(l1 ,l2) && (fabs(l1.second - l2.second) < eps);
}

// uses: areParallel -> lines
// returns true (+ intersection point) if two lines are intersect
bool lineIntersect(ddd l1, ddd l2, dd &p) {
    double &a1 = l1.first.first, &b1 = l1.first.second, &c1 = l1.second;
    double &a2 = l2.first.first, &b2 = l2.first.second, &c2 = l2.second;
    double &x = p.first, &y = p.second;
    if (areParallel(l1, l2)) return false; // no intersection

    // solve system of 2 linear algebraic equations with 2 unknowns
    x = (b2 * c1 - b1 * c2) / (a2 * b1 - a1 * b2);

    // special case: test for vertical line to avoid division by zero
    y = -(fabs(b1) > eps ? a1 * x + c1 : a2 * x + c2);
    return true;
}

// uses: lineIntersect, pointsToLine -> lines // dist -> points
// returns true (+ intersection point) if two segments (a-b) & (m-n) are intersect
// has some terrible bugs :)
bool segIntersect(dd a, dd b, dd m, dd n, dd &p){
    ddd l1; pointsToLine(a, b, l1);
    ddd l2; pointsToLine(m, n, l2);

    if(lineIntersect(l1, l2, p))
        return (fabs(dist(a, b) - (dist(a, p) + dist(p, b))) < eps);
    return false;
}

// uses: cross
bool segIntersect(dd p1, dd p2, dd q1, dd q2){
  dd t1 = dd(q2.first - q1.first, q2.second - q1.second);
  dd t2 = dd(p2.first - p1.first, p2.second - p1.second);
  dd t3 = dd(q1.first - p1.first, q1.second - p1.second);

  double d = cross(t1, t2);
  if(!d) return p2 == q2;

  double t = cross(t2, t3) / d, s = cross(t1, t3) / d;
  return 0 <= t && t <= 1 && 0 <= s && s <= 1;
}

// line segment p-q intersect with line A-B.
dd lineIntersectSeg(dd p, dd q, dd A, dd B) {
    double px = p.first, py = p.second, qx = q.first, qy = q.second;
    double a = B.second - A.second, b = A.first - B.first;
    double c = B.first * A.second - A.first * B.second;
    double u = fabs(a * px + b * py + c);
    double v = fabs(a * qx + b * qy + c);
    return dd((px * v + qx * u) / (u + v), (py * v + qy * u) / (u + v));
}
