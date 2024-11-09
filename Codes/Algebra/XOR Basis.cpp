
struct XorBasis {
    int K; 
    vi basis; 
    XorBasis(int K_) : K(K_) { basis.assign(K, 0); }
    int reduce(int x) {
        for(int i = K - 1; i >= 0; i--) {
            if(x & (1 << i)) x ^= basis[i]; 
        }
        return x; 
    }

    bool add(int x) {
        x = reduce(x);
        if(x != 0) {
            for(int i = K - 1; i >= 0; i--) {
                if( x & (1 << i)) {
                    basis[i] = x; 
                    return true; 
                }
            }
        }
        return false; 
    }

    bool check(int x) { return reduce(x) == 0; }
};
