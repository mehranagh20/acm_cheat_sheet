// 1D OBJECTS: LINES
// Euclidean equation ax + by + c = 0. implementation: ddd(dd(a, b), c)
// Subsequent functions in this subsection assume that this linear equation has b = 1 for
// non vertical lines and b = 0 for vertical lines unless otherwise stated.

// the answer is stored in the third parameter (pass by reference)
void pointsToLine(dd p1, dd p2, ddd &l) {
    if (fabs(p1.first - p2.first) < eps) { // vertical line is fine
        l.first.first = 1.0; l.first.second = 0.0; l.second = -p1.first;
    }
    
    else {
        l.first.first = -(p1.second - p2.second) / (p1.first - p2.first);
        l.first.second = 1.0; // IMPORTANT: we fix the value of b to 1.0
        l.second = -(l.first.first * p1.first) - p1.second;
    }
}

// convert point and gradient/slope to line
// y = mx + c --> ax + by + c = 0
void pointSlopeToLine(dd p, double m, ddd &l) {
    l.first.first = -m; l.first.second = 1;
    l.second = -((l.first.first * p.first) + (l.first.second * p.second));
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
bool areIntersect(ddd l1, ddd l2, dd &p) {
    if (areParallel(l1, l2)) return false; // no intersection
    
    // solve system of 2 linear algebraic equations with 2 unknowns
    p.first = (l2.first.second * l1.second - l1.first.second * l2.second) /
    (l2.first.first * l1.first.second - l1.first.first * l2.first.second);
    
    // special case: test for vertical line to avoid division by zero
    if (fabs(l1.first.second) > eps)
        p.second = -(l1.first.first * p.first + l1.second);
    else
        p.second = -(l2.first.first * p.first + l2.second);
    return true;
}
