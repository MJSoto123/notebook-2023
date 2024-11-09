vector<P> convex_hull(vector<P> points) {
    int n = points.size();
    sort(points.begin(), points.end(), [](P p1, P p2){
        return make_pair(p1.x, p1.y) < make_pair(p2.x, p2.y);
    });
    vector<P> hull; 
    for(int rep = 0; rep < 2; rep++) { // la primera halla el hull superior
        int S = hull.size();
        for(int i = 0; i < n; i++) {
            while((int)hull.size() >= S + 2) {
                P A = hull.end()[-2]; 
                P B = hull.end()[-1]; 
                // el <= incluye puntos colineales 
                if(A.triangle(B, points[i]) <= 0) break; 
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }
        hull.pop_back(); // derecha e izquierda se repiten 
        reverse(points.begin(), points.end());
    }
    return hull; 
}