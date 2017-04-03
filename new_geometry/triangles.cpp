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

// uses: triangleArea, rInCircle -> triangles
// returns true if triangle with sides a, b, c has incircle
// overload: hasInCircle(dist(a, b), dist(b, c), dist(c, a)) if a, b, c are coordinates
bool hasInCircle(double a, double b, double c){
    return fabs(rInCircle(a, b, c)) >= eps;
}

// returns center of inCircle. NOTE: incircle existance maybe needs to be checked
dd inCircle(dd p1, dd p2, dd p3) {
    dd ctr;
    double a = dist(p2, p3), b = dist(p1, p3), c = dist(p1, p2);
    ctr.first = (a * p1.first + b * p2.first + c * p3.first) / (a + b + c);
    ctr.second = (a * p1.second + b * p2.second + c * p3.second) / (a + b + c);
    return ctr;
}

// uses: triangleArea -> triangles
// returns radius of Circumcircle of triangle with 3 sides: a, b, c
// overload: rCircumCircle(dist(a, b), dist(b, c), dist(c, a)) if a, b, c are coordinates
double rCircumCircle(double a, double b, double c) {
    return a * b * c / (4.0 * triangleArea(a, b, c));
}

// uses: triangleArea, rCircumCircle -> triangles
// returns true if triangle with sides a, b, c has circumCircle
// overload: hasInCircumCircle(dist(a, b), dist(b, c), dist(c, a)) if a, b, c are coordinates
bool hasInCircumCircle(double a, double b, double c){
    return fabs(rCircumCircle(a, b, c)) >= eps;
}

// returns center of circumCircle. NOTE: circumCircle existance maybe needs to be checked
dd circumCircle(dd p1, dd p2, dd p3){
    double x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;
    double x3 = p3.first, y3 = p3.second;
    
    double a1 = 2 * (x2 - x1), b1 = 2 * (y2 - y1), c1 = x2 * x2 + y2 * y2 - x1 * x1 - y1 * y1;
    double a2 = 2 * (x3 - x1), b2 = 2 * (y3 - y1), c2 = x3 * x3 + y3 * y3 - x1 * x1 - y1 * y1;
    double d = a1 * b2 - b1 * a2;
    
    dd ctr;
    ctr.first = (c1 * b2 - b1 * c2) / d;
    ctr.second = (a1 * c2 - c1 * a2) / d;
    return ctr;
}

// Cosine Formula
// uses: radToDeg -> points
// returns angle between sides in DEG: a, b in triangle with 3rd side c
double CosineFormula(double a, double b, double c){
    double theta = acos(((a * a) + (b * b) - (c * c)) / (2 * a * b));
    return radToDeg(theta);
}
