bool intersects(P p1, P p2, P p3, P p4) {
    if((p2 - p1) * (p4 - p3) == 0) { // paralelos
        if(p1.triangle(p2, p3) != 0) return false; // no colineales
        // ahora son colineales
        // bounding boxes
        for(int it = 0; it < 2; it++) {
            if(max(p1.x, p2.x) < min(p3.x, p4.x) 
                || max(p1.y, p2.y) < min(p3.y, p4.y)) return false; 
            swap(p1, p3); 
            swap(p2, p4);
        }
        return true; 
    }

    for(int it = 0; it < 2; it++) {
        ll t1 = p1.triangle(p2, p3), t2 = p1.triangle(p2, p4);
        if((t1 < 0 && t2 < 0) || (t1 > 0 && t2 > 0)) return false; 
        swap(p1, p3);
        swap(p2, p4);
    }   
    return true; 
}

bool on_boundary(P p, P p1, P p2) { // p está en el segmento p1p2 ? 
    if(p.triangle(p1, p2) != 0) return false; // no son colineales
    return min(p1.x, p2.x) <= p.x && p.x <= max(p1.x, p2.x)
        && min(p1.y, p2.y) <= p.y && p.y <= max(p1.y, p2.y);
}

ll polygon_area(const vector<P>& poly) { // dividir entre dos al final 
    int n = poly.size();
    ll ans = 0;
    for(int i = 1; i + 1 < n; i++) ans += poly[0].triangle(poly[i], poly[i + 1]);
    return abs(ans);
}

ll points_inside(const vector<P>& poly) { // teorema de pick
    int n = poly.size();
    ll on_boundary = 0; 
    for(int i = 0; i < n; i++) {
        // segmento entre p[i] y p[i + 1]; 
        P p1 = poly[i], p2 = poly[(i + 1) % n]; 
        p2 -= p1; 
        on_boundary += gcd(abs(p2.x), abs(p2.y));
    }
    // pick: Area = Inside + Boundary / 2  - 1
    //          2 * Area = 2 * Inside + Boundary - 2
    //          Inside = (2 * Area - Boundary + 2) / 2
    return (polygon_area(poly) - on_boundary + 2) / 2;
} 