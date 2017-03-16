// 2D Objects: Circles
// Circle centered at coordinate (a, b) in a 2D Euclidean space with radius
// r is the set (x−a)^2 + (y−b)^2 = r^2.

// test point p relation to circle with c as center and r radius
// returns 0 -> inside, 1 -> border, 2 -> outside
int insideCircle(dd p, dd c, int r) {
    double dx = p.first - c.first, dy = p.second - c.second;
    double Euc = dx * dx + dy * dy, rSq = r * r;
    return rSq - Euc > eps ? 0 : (fabs(rSq - Euc) < eps ? 1 : 2);
}

double arcLen(double r, double theta){ return (theta / 360.0) * (2 * pi * r); }

// uses: degToRad -> points
// Chord of a circle is defined as a line segment whose endpoints lie on the circle
double chordLen(double r, double theta){ return 2 * r * sin(degToRad(theta) / 2); }

// Sector of a circle is defined as a region of the circle enclosed
// by two radius and an arc lying between the two radius.
double sectorArea(double r, double theta){ return (theta / 360.0) * (pi * r * r); }

// uses: degToRad -> points AND sectorArea -> circles
// Segment of a circle is defined as a region of the circle enclosed
// by a chord and an arc lying between the chord’s endpoints
double segmentArea(double r, double theta){
    return sectorArea(r, theta) - (r * r * sin(degToRad(theta)) / 2);
}

// to get the other center, reverse p1 and p2
// Determines the location of the centers (c1 and c2) of the two possible circles
// Given 2 points on the circle (p1 and p2) and radius r of the corresponding circle
bool circle2PtsRad(dd p1, dd p2, double r, dd &c) {
    double d2 = pow((p1.first - p2.first), 2) +  pow((p1.second - p2.second), 2);
    double det = r * r / d2 - 0.25;
    if (det < 0.0) return false;
    
    double h = sqrt(det);
    c.first = (p1.first + p2.first) * 0.5 + (p1.second - p2.second) * h;
    c.second = (p1.second + p2.second) * 0.5 + (p2.first - p1.first) * h;
    return true;
}
