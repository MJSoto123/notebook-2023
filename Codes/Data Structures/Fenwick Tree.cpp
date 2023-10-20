
int lso(int n) {return (n & (-n));}

// las consultas están indexadas en 1
struct FenwickTree{
    vector<int> ft; 
    FenwickTree(int m) {ft.assign(m + 1, 0);};
    int rsq(int j) {
        int sum = 0;
        for(; j; j -= lso(j)) sum += ft[j];
        return sum;
    }
    void upd(int i, int v) {
        for(; i < ft.size(); i += lso(i)) ft[i] += v;
    }
};