#pragma GCC optimize("unroll-loops","Ofast")
#include <bits/stdc++.h>
#include <random>
#include <chrono>

using namespace std;
using pi = pair<int, int>;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
template<class T>
int rand(T x, T y) { return std::uniform_int_distribution<T>(x, y)(rng); };

int main() {
	const int INF = 0x3F3F3F3F;
	auto Solve = [&](const vector<vector<pi>>& G) {
		int N = G.size() - 1;
		vector dist(N + 1, vector(N + 1, INF));
		for (int i = 1; i <= N; ++i) {
			auto& dp = dist[i];
			dp[i] = 0;
			priority_queue<pi, vector<pi>, greater<pi>> PQ;
			PQ.emplace(0, i);
			while (!PQ.empty()) {
				auto [cost, node] = PQ.top();
				PQ.pop();
				if (dp[node] != cost)
					continue;
				for (auto [x, w] : G[node])
					if (cost + w < dp[x]) {
						dp[x] = cost + w;
						PQ.emplace(dp[x], x);
					}
			}
		}
		return dist;
	};
	auto GetSmart = [&](vector<vector<pi>> G) {
		int n = G.size() - 1;
		vector ans(n + 1, INF), dp(n + 1, INF);
		for (int i = 1; i <= n; ++i)
			G[0].emplace_back(i, 0);
		queue<int> Q;
		vector<int> inq(n + 1), buf(n + 1), depth(n + 1), subtree(n + 1), p(n + 1);
		Q.emplace(0);
		dp[0] = 0;
		inq[0] = 1;
		while (!Q.empty()) {
			int node = Q.front();
			Q.pop(), inq[node] = 0;
			for (auto [x, cost] : G[node])
				if (dp[node] + cost < dp[x]) {
					dp[x] = dp[node] + cost;
					p[x] = node;
					if (!inq[x])
						Q.emplace(x), inq[x] = 1;
				}
		}
		vector<vector<pi>> GT(n + 1);
		for (int i = 1; i <= n; ++i)
			for (auto& [x, w] : G[i])
				GT[x].emplace_back(i, w);
		vector<vector<int>> T(n + 1);
		for (int i = 1; i <= n; ++i)
			T[p[i]].emplace_back(i);
		auto dfs = [&](auto& self, int node, int col) -> void {
			subtree[node] = col;
			for (auto x : T[node]) {
				depth[x] = depth[node] + 1;
				self(self, x, col);
			}
		};
		for (auto x : T[0]) {
			depth[x] = 1;
			dfs(dfs, x, x);
		}
		//for (int i = 1; i <= n; ++i)
			//cerr << i << ' ' << p[i] << ' ' << depth[i] << ' ' << subtree[i] << '\n';
		for (int i = 1; i <= n; ++i) {
			auto dfs = [&](auto& self, int node, int mode) -> void {
				if (node != i) {
					swap(buf[node], dp[node]);
					if (mode) {
						Q.emplace(node);
						inq[node] = 1;
						for (auto [x, w] : GT[node])
							if (subtree[x] != subtree[node])
								dp[node] = min(dp[node], dp[x] + w);
					}
				}
				for (auto x : T[node])
					self(self, x, mode);
			};
			if (depth[i] == 1) {
				dfs(dfs, i, 1);
				//cerr << "SPECIAL: " << i << '\n';
				//for (int i = 1; i <= n; ++i)
					//cerr << "DBG B: " << i << ' ' << dp[i] << '\n';
				while (!Q.empty()) {
					int node = Q.front();
					Q.pop(), inq[node] = 0;
					for (auto [x, cost] : G[node])
						if (subtree[x] == subtree[node] && dp[node] + cost < dp[x]) {
							dp[x] = dp[node] + cost;
							if (!inq[x])
								Q.emplace(x), inq[x] = 1;
						}
				}
				//for (int i = 1; i <= n; ++i)
					//cerr << "DBG A: " << i << ' ' << dp[i] << '\n';
			}
			for (auto [x, w] : GT[i])
				ans[i] = min(ans[i], dp[x] + w);
			if (depth[i] == 1)
				dfs(dfs, i, 0);
		}
		return ans;
	};
	auto GetAnswer = [&](vector<vector<int>>&& M) {
		int n = M.size() - 1;
		vector ans(n + 1, INF);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (j != i)
					ans[j] = min(ans[j], M[i][j]);
		return ans;
	};
	auto Transpose = [&](vector<vector<int>>&& M) {
		int s = M.size();
		for (int i = 0; i < s; ++i)
			for (int j = 0; j < i; ++j)
				swap(M[i][j], M[j][i]);
		return M;
	};
	auto NegativeCycle = [&](const vector<vector<pi>>& G) {
		int n = G.size() - 1;
		vector<int> dp(n + 1, INF);
		vector<tuple<int, int, int>> E;
		dp[1] = 0;
		for (int i = 1; i <= n; ++i)
			for (auto& [x, w] : G[i])
				E.emplace_back(i, x, w);
		int x = -1;
		for (int i = 0; i < n; ++i) {
			x = -1;
			for (const auto& e : E)
				if (dp[get<1>(e)] > dp[get<0>(e)] + get<2>(e))
					dp[get<1>(e)] = dp[get<0>(e)] + get<2>(e), x = 1;
		}
		return x != -1;
	};
	int n;
	cin >> n;
	auto TestInput = [&] {
		vector<vector<pi>> G(n + 1);
		int m;
		cin >> m;
		while (m--) {
			int x, y, z;
			cin >> x >> y >> z;
			G[x].emplace_back(y, z);
		}
		for (auto x : GetAnswer(Solve(G)))
			cout << x << ' ';
		cout << '\n';
		for (auto x : GetSmart(G))
			cout << x << ' ';
		assert(GetAnswer(Solve(G)) == GetSmart(G));
	};
	auto TestRandom = [&] {
		for (long long mask = 1; mask < (1LL << (n * n)); ++mask) {
			if (__builtin_popcountll(mask) < n - 1 || __builtin_popcountll(mask) > n * sqrt(n))
				continue;
			auto check = [&](int i, int j) { return mask & (1LL << (n * (i - 1) + j - 1)); };
			int id = 0, is = 0;
			vector<int> cnt(n + 1);
			for (int i = 1; i <= n; ++i) {
				if (check(i, i)) {
					id = 1;
					break;
				}
				for (int j = 1; j < i; ++j)
					if (check(i, j) || check(j, i))
						cnt[i] = 1, cnt[j] = 1;
			}
			for (int i = 1; i <= n; ++i)
				if (!cnt[i])
					is = 1;
			if (id || is)
				continue;
			for (int t = 0; t < 100; ++t) {
				vector G(n + 1, vector<pi>()), GT(n + 1, vector<pi>());
				for (int i = 1; i <= n; ++i) {
					if (check(i, i)) {
						id = 1;
						break;
					}
					for (int j = 1; j < i; ++j) {
						if (check(i, j)) {
							int cost = rand(-5, 5);
							//cerr << i << ' ' << j << ' ' << cost << '\n';
							G[i].emplace_back(j, cost);
							GT[j].emplace_back(i, cost);
						}
						if (check(j, i)) {
							int cost = rand(-5, 5);
							//cerr << j << ' ' << i << ' ' << cost << '\n';
							G[j].emplace_back(i, cost);
							GT[i].emplace_back(j, cost);
						}
					}
				}

				if (NegativeCycle(G)) {
					//cerr << "NEG";
					continue;
				}
				//while (m--) {
					//int x, y, z;
					//cin >> x >> y >> z;
					//G[x].emplace_back(y, z);
					//GT[y].emplace_back(x, z);
					//auto Solve1 = Solve(G), Solve2 = Transpose(Solve(GT));
				auto Solve1 = GetAnswer(Solve(G)), Solve2 = GetSmart(G);
				//for (int i = 1; i <= n; ++i) {
					//for (int j = 1; j <= n; ++j)
						//cout << Solve1[i][j] << ' ';
					//cout << '\n';
				//}
				if (Solve1 != Solve2) {
					for (int i = 1; i <= n; ++i)
						for (auto [x, w] : G[i])
							cerr << i << ' ' << x << ' ' << w << '\n';
					cerr << "====\n";
					for (auto x : Solve1)
						cerr << x << ' ';
					for (auto x : Solve2)
						cerr << x << ' ';

				}
				assert(Solve1 == Solve2);
				cerr << "SAME\n";
			}
			// cerr << "CHECKED! " << mask << '\n';
		}

		// cerr << "DONE";	//}


	};
	TestInput();
	// TestRandom();

}