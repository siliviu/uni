#include <bits/stdc++.h>

using namespace std;

int main() {
	auto Solve1 = [&] {
		int n, m;
		cin >> n >> m;
		vector<vector<int>> G(n + 1, vector<int>(n + 1)), seen(n + 1, vector<int>(n + 1));
		while (m--) {
			int x, y;
			cin >> x >> y;
			G[x].emplace_back(y);
		}
		auto dfs = [&](auto& self, vector<int>& seen, int node) -> void {
			for (auto x : G[node])
				if (!seen[x]) {
					seen[x] = 1;
					self(self, seen, x);
				}
		};
		for (int i = 1; i <= n; ++i) {
			dfs(dfs, seen[i], i);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j)
				cout << seen[i][j] << ' ';
			cout << '\n';
		}
	};
	auto Solve2 = [&] {
		int n;
		ifstream ccin("graf.txt");
		ccin >> n;
		vector<vector<int>> G(n + 1);
		int x, y;
		while (ccin >> x >> y)
			G[x].emplace_back(y);
		ccin.close();
		int s;
		cin >> s;
		vector<int> d(n + 1);
		queue<int> Q;
		d[s] = 1;
		Q.emplace(s);
		while (!Q.empty()) {
			int node = Q.front();
			Q.pop();
			for (auto x : G[node])
				if (!d[x]) {
					d[x] = d[node] + 1;
					Q.emplace(x);
				}
		}
		for (int i = 1; i <= n; ++i)
			cout << i << ' ' << d[i] - 1 << '\n';
	};
	auto Solve3 = [&] {
		vector<pair<int, int>> dd = { {-1,0},{0,1},{0,-1},{1,0} };
		vector<string> v;
		//ifstream cin("labirint_1.txt");
		ifstream cin("labirint_2.txt");
		string s;
		while (getline(cin, s))
			v.emplace_back(s)/*, cerr << s << '\n'*/;
		int n = v.size(), m = v[0].size();
		pair<int, int> start, finish;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				if (v[i][j] == 'S')
					start = { i,j };
				else if (v[i][j] == 'F')
					finish = { i,j };
		vector<vector<pair<int, int>>> p(n, vector<pair<int, int>>(m));
		queue<pair<int, int>> Q;
		Q.emplace(start);
		p[start.first][start.second] = { -1,-1 };
		while (!Q.empty()) {
			auto [y, x] = Q.front();
			Q.pop();
			for (int i = 0; i < 4; ++i) {
				int yy = y + dd[i].first, xx = x + dd[i].second;
				if (yy >= 0 && xx >= 0 && yy < n && xx < m && (v[yy][xx] == ' ' || v[yy][xx] == 'F') && p[yy][xx] == make_pair(0, 0)) {
					p[yy][xx] = { y,x };
					Q.emplace(yy, xx);
				}
			}
		}
		//cerr << p[finish.first][finish.second].first << ' ' << p[finish.first][finish.second].second << '\n';
		for (auto [y, x] = finish; y != -1;) {
			//cerr << y << ' ' << x << '\n';
			v[y][x] = '*';
			auto [yy, xx] = p[y][x];
			y = yy, x = xx;
		}
		v[start.first][start.second] = 'S';
		v[finish.first][finish.second] = 'F';
		for (int i = 0; i < n; ++i)
			cout << v[i] << '\n';


	};
	auto Solve4 = [&] {
		int n, m;
		cin >> n >> m;
		vector<vector<int>> G(n + 1);
		while (m--) {
			int x, y;
			cin >> x >> y;
			G[x].emplace_back(y);
		}
		int s;
		cin >> s;
		vector<int> d(n + 1);
		queue<int> Q;
		d[s] = 1;
		Q.emplace(s);
		while (!Q.empty()) {
			int node = Q.front();
			Q.pop();
			for (auto x : G[node])
				if (!d[x]) {
					d[x] = d[node] + 1;
					Q.emplace(x);
				}
		}
		for (int i = 1; i <= n; ++i)
			if (d[i])
				cout << i << ' ' << d[i] - 1 << '\n';
	};
	auto Solve5 = [&] {
		int n, m;
		cin >> n >> m;
		vector<vector<int>> G(n + 1, vector<int>(n + 1));
		vector<int> seen(n + 1);
		while (m--) {
			int x, y;
			cin >> x >> y;
			G[x].emplace_back(y);
		}
		auto dfs = [&](auto& self, int node) -> void {
			seen[node] = 1;
			for (auto x : G[node])
				if (!seen[x])
					self(self, x);
		};
		int s;
		cin >> s;
		dfs(dfs, s);
		for (int i = 1; i <= n; ++i)
			if (seen[i])
				cout << i << ' ';
	};
	Solve3();
}