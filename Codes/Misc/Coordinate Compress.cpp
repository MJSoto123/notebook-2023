// quita el 64 si solo necesitas enteros
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<int> d = a;
sort(d.begin(), d.end());
d.resize(unique(d.begin(), d.end()) - d.begin());
for (int i = 0; i < n; ++i) {
  a[i] = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
}
//original value of a[i] can be obtained through d[a[i]]