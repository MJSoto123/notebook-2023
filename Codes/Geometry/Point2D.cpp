
struct P{
    ll x, y; 
    P() : x(0), y(0) {}
    P(ll x_, ll y_) : x(x_), y(y_) {}
    void read() { cin >> x >> y; }


    P operator - (const P& b) const { 
        return P(x - b.x, y - b.y); 
    }
    void operator-=(const P& b) {
        x -= b.x; 
        y -= b.y; 
    }

    ll operator *(const P& b) const { 
        return 1LL * x * b.y - 1LL * y * b.x; 
    }
    // si miro a Pb, en que lado queda c
    // positivo = izquierda
    ll triangle(const P& b, const P& c) const {
        return (b - *this) * (c - *this);
    }

    friend ostream& operator<<(ostream& os, const P& p) {
        os << p.x << " " << p.y; return os; 
    }

};
