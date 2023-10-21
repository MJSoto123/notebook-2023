
const int MOD = 1e9 + 7;
// modificar los struct 
// operadores * y + 
// en node + = merge
// en operation * = merge 
// node * operation = como afecta la operacion al nodo
struct operation{
	bool swapped;
	operation() : swapped(false) {}
	operation(bool s) : swapped(s) {}

	operation operator * (const operation &rhs) const {
		operation res; 
		res.swapped = (this -> swapped) ^ rhs.swapped;
		return res;  
	}

	bool id() {
		return !swapped;
	}

	void clear() {
		swapped = false; 
	}
};  


struct node {
    int imx, imn, mx, mn; 
	node() { imx = imn = mx = mn = 0; }
    node(int imx, int imn, int mx, int mn) : imx(imx), imn(imn), mx(mx), mn(mn) { }

	node operator + (const node &rhs) const {
		node res;
		res.mx = max(this -> mx, rhs.mx);
        res.mn = min(this -> mn, rhs.mn);
        if(this -> mx >= rhs.mx) res.imx = (this -> imx);
        else res.imx = rhs.imx; 
        if(this -> mn <= rhs.mn) res.imn = (this -> imn);
        else res.imn = rhs.imn; 
		return res;
	}

	node operator * (const operation &rhs) const {
		node res; 
        if(rhs.swapped) {
            res.imx = imn; 
            res.imn = imx; 
            res.mx = MOD - mn; 
            res.mn = MOD - mx; 
        }else{
            res.imx = imx; 
            res.imn = imn; 
            res.mx = mx; 
            res.mn = mn; 
        }
        return res; 
	}
};

const int N = 4e6 + 20;
node tree[N * 4];
operation lazy[N * 4];
pii arr[N];

void build(int v, int tl, int tr) {
	lazy[v].clear();
	if(tl == tr) {
		tree[v] = node(arr[tl].second, arr[tl].second, arr[tl].first, arr[tl].first);
		return; 
	}
	int tm = (tl + tr) / 2;
	build(v * 2, tl, tm);
	build(v * 2 + 1, tm + 1, tr);
	tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

void push(int v) {
	if(lazy[v].id()) return; 
	tree[v * 2] = tree[v * 2] * lazy[v];
	tree[v * 2 + 1] = tree[v * 2 + 1] * lazy[v];
	lazy[v * 2] = lazy[v] * lazy[v * 2];
	lazy[v * 2 + 1] = lazy[v] * lazy[v * 2 + 1];
	lazy[v].clear();
}	

void update(int v, int tl, int tr, int l, int r, operation &op) {
	if(l > r) return; 
	if(l == tl && r == tr) {
		tree[v] = tree[v] * op; 
		lazy[v] = op * lazy[v]; 
		return; 
	}
	push(v);
	int tm = (tl + tr) / 2;
	update(v * 2, tl, tm, l, min(r, tm), op);
	update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, op);
	tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

node query(int v, int tl, int tr, int l, int r) {
	if(l > r) return node();
	if(l == tl && r == tr) return tree[v];
	push(v);
	int tm = (tl + tr) / 2;
	return query(v * 2, tl, tm, l, min(r, tm)) 
		+ query(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r);
}
