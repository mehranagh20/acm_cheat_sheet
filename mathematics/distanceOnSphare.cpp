double getDistOnSphare (double plat , double plong ,
                        double qlat , double qlong , double radius = 6378.0){
    double pi = 3.141592653589793;
    plat *= (pi /180.0);
    plong *= (pi /180.0);
    qlat *= (pi /180.0);
    qlong *= (pi /180.0);
    long double Distance = acos( sin(plat) * sin(qlat) +
        cos(plat) * cos(qlat) * cos(plong) * cos(qlong) +
        cos(plat) * cos(qlat) * sin(plong) * sin(qlong)
       ) * 6378.0; // 6378 = R Of Earth
     return Distance;
}

double gcDistance(double pLat, double pLong,
    double qLat, double qLong, double radius) {
    pLat *= PI / 180; pLong *= PI / 180; // convert degree to radian
    qLat *= PI / 180; qLong *= PI / 180;
    return radius * acos(cos(pLat)*cos(pLong)*cos(qLat)*cos(qLong) +
    cos(pLat)*sin(pLong)*cos(qLat)*sin(qLong) + sin(pLat)*sin(qLat));
}
or
acos(cos(qlat) * cos(plat) * cos(plong - qlong) + sin(qlat) * sin(plat));
