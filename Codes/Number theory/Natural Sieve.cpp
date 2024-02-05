const int N = 100000000 + 5;
bitset<N> composite;

void natural(int n){
    // (WARNING) Todos los pares son primos
    for(int i = 3; i * i <= n; i += 2) {
		if(not composite[i]) {
			for(int j = i * i; j <= n; j += i) composite[j] = true;
		}
	}
}