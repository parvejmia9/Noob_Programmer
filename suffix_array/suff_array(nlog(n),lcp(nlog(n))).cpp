vector<vector<int>>rnk(23);// will be used to calc lcp
int jump;
vector<int> suff_array_build(string s) {
    s += '$';
    int n = s.size();
    int mx = 256;
    vector<int> sa(n);//suffix array
    vector<int> p(n), c(n), cnt(max(n, mx));
    for (char ch : s) cnt[ch]++;
    for (int i = 1; i < mx; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    int classes = 1;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (s[p[i - 1]] != s[p[i]]) classes++;
        c[p[i]] = classes - 1;
    }
    // initialized finished
    int h = 0;
    rnk[0] = c;
    vector<int> pn(n), cn(n);
    while ((1 << h) < n) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) {
            cnt[c[pn[i]]]++;
        }
        for (int i = 1; i < classes; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            p[--cnt[c[pn[i]]]] = pn[i];
        }

        classes = 1;
        cn[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            int pos1 = (p[i] + (1 << h)) - n;
            int pos2 = (p[i - 1] + (1 << h)) - n;
            if (pos1 < 0) pos1 += n;
            if (pos2 < 0) pos2 += n;
            pair<int, int> cur = {c[p[i]], c[pos1]};
            pair<int, int> prev = {c[p[i - 1]], c[pos2]};
            if (cur != prev) classes++;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
        rnk[h + 1] = c;// to store eq classes of each transition
        h++;
    }
    jump = h;
    p.erase(p.begin());
    return p;
}
// this lcp(i.j) will return the lcp of p[i] suffix and p[j] prefix;
// i!=j
int lcp(int i, int j) {
    int ans = 0;
    for (int k = jump; k >= 0; k--) {
        if (rnk[k][i] == rnk[k][j]) {
            ans += (1 << k);
            i += (1 << k);
            j += (1 << k);
        }
    }
    return ans;
}
