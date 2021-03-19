

vector<int> Z_function(string s) {// Z array return korbe. longest common prefis for S[0...n], S[i...n]
	int n = s.size();
	vector<int> Z(n);
	Z[0] = 0;
	for (int i = 1, l = 0, r = 0; i < n; i++) {
		if (i <= r) {
			Z[i] = min(r - i + 1, Z[i - l]);
		}
		while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) {
			Z[i]++;
		}

		if (i + Z[i] - 1 > r) {
			l = i, r = i + Z[i] - 1;
		}
	}
	return Z;
}



vector<int> prefix_count(vector<int> &lps) {  // prefix er occurance count korbo
	int n = lps.size();
	//lps is the output array of prefix function
	vector<int> ans(n + 1);
	for (int i = 0; i < n; i++)
		ans[lps[i]]++;
	for (int i = n - 1; i > 0; i--)
		ans[lps[i - 1]] += ans[i];
	for (int i = 0; i <= n; i++)
		ans[i]++;
	return ans;
	// ans[i] means the number of occurance of i length prefix
	//aabcdabaaba
	// ans[2] mane 2 length er prefix kotobar occur korse
	// ei udhahorone 2 lenght er prefix hosse (aa) jeta duibar occur korse
	
}


vector<int> prefix_function(string &s) { // lps array return korbe.
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
