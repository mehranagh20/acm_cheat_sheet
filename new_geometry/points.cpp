// unit conversion
double degToRad(double theta){
    return theta * pi / 180.0;
}

double radToDeg(double theta){
    return theta * 180.0 / pi;
}

// testing equality in dd points
bool areEqualPoints(dd p1, dd p2){
    return (fabs(p1.first - p2.first) < eps && fabs(p1.second - p2.second) < eps);
}


//distance of points (Euclidean distance)
double dist(dd p1, dd p2){
    // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
    return hypot(p1.first - p2.first, p1.second - p2.second);
}


// rotate p by theta degrees CCW(counter clock wise) w.r.t origin (0, 0)
dd rotate(dd p, double theta) {
    double rad = degToRad(theta);
    return dd(p.first * cos(rad) - p.second * sin(rad),
              p.first * sin(rad) + p.second * cos(rad));
}
