const int N = 100000000 + 5;
vector<int> primes;
bitset<N> composite;

void lineal(int n){
    for(int i = 2; i <= n; i++) {
		if(not composite[i]) primes.emplace_back(i);
		for(int p : primes) {
			if(i * p > n) break;
			composite[i * p] = true;
			if(i % p == 0) break;
		}
	}
}