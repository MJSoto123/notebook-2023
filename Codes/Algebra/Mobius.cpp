const int MOBSZ = 1000000 + 10;
struct Mobius {
    bool prime[MOBSZ]; 
    int mu[MOBSZ]; 
    void init() {
        for(int i = 0; i < MOBSZ; i++) prime[i] = mu[i] = 1; 
        for(int i = 2; i < MOBSZ; i++) if(prime[i]) {
            for(int j = i; j < MOBSZ; j+=i) {
                if(j > i) prime[j] = false; 
                if(j % (1LL * i * i) == 0) mu[j] = 0; 
                mu[j] = -mu[j]; 
            }
        }
    }
} mobius; 