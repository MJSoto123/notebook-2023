const int N = 1e6 + 100;
int trie[N][26]; // N = suma de longitudes
bool stop[N];
int ct = 0;
 
void insert(string word) {
	int node = 0;
	for(int i = 0; i < (int)word.size(); i++) {
		if(!trie[node][word[i] - 'a']) trie[node][word[i] - 'a'] = ++ct; 
		node = trie[node][word[i] - 'a'];
	}
	stop[node] = true;
}
