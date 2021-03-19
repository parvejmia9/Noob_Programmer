

vector<int> prefix_function(string &s) { // lps array
	
	/// HERE s IS THE PATTERN NOT THE MAIN STRING///
	
	int n = s.size();
	vector<int> lps(n);
	lps[0] = 0;
	for (int i = 1; i < n; i++) {
		int l = lps[i - 1];
		while (l > 0 && s[i] != s[l]) {
			l = lps[l - 1];
		}
		if (s[i] == s[l]) l++;
		lps[i] = l;
	}
	return lps;
}


vector<int> kmp(string &s, string &p) {// it will return the indicex the strating of asubtring where the pattern found
	p += '#';
	vector<int> lps = prefix_function(p);
	vector<int> ans;
	int n = s.size();
	int len = p.size() - 1;
	int prev = 0;
	for (int i = 0; i < n; i++) {
		int l = prev;
		while (l > 0 && s[i] != p[l]) {
			l = lps[l - 1];
		}
		if (s[i] == p[l]) l++;
		if (l == len) {
			ans.push_back((i - len + 1));
		}
		prev = l;
	}
	return ans;
}
