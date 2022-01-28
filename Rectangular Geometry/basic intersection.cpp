class rect {
public:
	ll x1, y1, x2, y2;
	void init(ll a, ll b, ll c , ll d) {
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
	ll area() {
		return abs(x1 - x2) * abs(y1 - y2);
	}
};
ll intersect(rect A, rect B) {
	ll x = max((min(A.x2, B.x2) - max(A.x1, B.x1)), 0LL);
	ll y = max((min(A.y2, B.y2) - max(A.y1, B.y1)), 0LL);
	return (x * y);
}
rect intersect_rect(rect A, rect B) {
	rect tm;
	tm.init(-2, -2, -2, -2);
	if (intersect(A, B) == 0) {
		return tm;
	}
	ll x1 = max(A.x1, B.x1);
	ll x2 = min(A.x2, B.x2);
	ll y1 = max(A.y1, B.y1);
	ll y2 = min(A.y2, B.y2);
	tm.init(x1, y1, x2, y2);
	return tm;
}
