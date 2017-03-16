// 2D Objects: Triangles

// returns if 3 sides a, b, c can form a triangle
// overload: canFormTriangle(dist(a, b), dist(b, c), dist(c, a)) if a, b, c are coordinates
bool canFormTriangle(double a, double b, double c){
    return ((a + b > c) && (a + c > b) && (b + c > a));
}

// Heron’s Formula. For calculation of triangle area using 3 sides a, b, c
double triangleArea(double a, double b, double c){
    double s = (a + b + c) / 2;
    return (sqrt(s) * sqrt(s - a) * sqrt(s - b) * sqrt(s - c));
}

// uses: triangleArea -> triangles
// returns radius of Incircle of triangle with 3 sides: a, b, c
// overload: rInCircle(dist(a, b), dist(b, c), dist(c, a)) if a, b, c are coordinates
double rInCircle(double a, double b, double c) {
    return triangleArea(a, b, c) / (0.5 * (a + b + c));
}

// uses: inCircle -> circles AND pointsToLine, areIntersect -> lines
// uses: translate, scale, toVec -> vectors AND dist -> points
// returns true if there is an inCircle center, returns false otherwise
// if this function returns 1, ctr will be the inCircle center
// and r is the same as rInCircle
bool inCircle(dd p1, dd p2, dd p3, dd &ctr, double &r) {
    r = rInCircle(dist(p1, p2), dist(p2, p3), dist(p3, p1));
    if (fabs(r) < eps) return false; // no inCircle center
    
    ddd l1, l2; // compute these two angle bisectors
    double ratio = dist(p1, p2) / dist(p1, p3);
    dd p = translate(p2, scale(toVec(p2, p3), ratio / (1 + ratio)));
    pointsToLine(p1, p, l1);
    
    ratio = dist(p2, p1) / dist(p2, p3);
    p = translate(p1, scale(toVec(p1, p3), ratio / (1 + ratio)));
    pointsToLine(p2, p, l2);
    
    areIntersect(l1, l2, ctr); // get their intersection point
    return true;
}

// uses: triangleArea -> triangles
// returns radius of Circumcircle of triangle with 3 sides: a, b, c
// overload: rCircumCircle(dist(a, b), dist(b, c), dist(c, a)) if a, b, c are coordinates
double rCircumCircle(double a, double b, double c) {
    return a * b * c / (4.0 * triangleArea(a, b, c));
}

// Cosine Formula
// uses: radToDeg -> points
// returns angle between sides: a, b in triangle with 3rd side c
double CosineFormula(double a, double b, double c){
    double theta = acos(((a * a) + (b * b) - (c * c)) / (2 * a * b));
    return radToDeg(theta);
}
