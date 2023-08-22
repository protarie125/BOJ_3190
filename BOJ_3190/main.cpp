#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <deque>
#include <list>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

class Body {
public:
	int r{};
	int c{};
	int dir{};
};

int n;
vvi map;
int k;
list<pii> apples{};
int l;
queue<pair<int, char>> moves;
deque<Body> body{};
const auto dx = vi{ 1, 0, -1, 0 };
const auto dy = vi{ 0, 1, 0, -1 };
int dirNow = 0;

void redrawMap() {
	map = vvi(n, vi(n, 0));

	for (const auto& b : body) {
		map[b.r - 1][b.c - 1] = 1;
	}

	for (const auto& a : apples) {
		map[a.first - 1][a.second - 1] = 2;
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	body.push_back(Body{ 1, 1, 0 });

	cin >> n;
	map = vvi(n, vi(n, 0));
	map[0][0] = 1;

	cin >> k;
	for (auto i = 0; i < k; ++i) {
		int r, c;
		cin >> r >> c;

		apples.push_back({ r, c });
		map[r - 1][c - 1] = 2;
	}

	cin >> l;
	for (auto i = 0; i < l; ++i) {
		int x;
		char dir;
		cin >> x >> dir;

		moves.push({ x, dir });
	}

	auto now = int{ 0 };
	while (true) {
		/*for (const auto& rows : map) {
			for (const auto& x : rows) {
				cout << x << ' ';
			}
			cout << '\n';
		}
		cout << '\n';*/

		++now;

		auto& head = body.front();

		const auto next = Body{ head.r + dy[head.dir], head.c + dx[head.dir], head.dir };

		if (next.r <= 0 || n < next.r ||
			next.c <= 0 || n < next.c) {
			break;
		}

		if (1 == map[next.r - 1][next.c - 1]) {
			break;
		}

		if (2 == map[next.r - 1][next.c - 1]) {
			body.push_front(next);

			apples.remove(pii{ next.r, next.c });
		}
		else {
			body.pop_back();
			body.push_front(next);
		}

		redrawMap();

		if (!moves.empty()) {
			auto m = moves.front();
			if (now == m.first) {
				if ('L' == m.second) {
					--dirNow;
					if (dirNow < 0) {
						dirNow = 3;
					}
				}
				else {
					++dirNow;
					if (3 < dirNow) {
						dirNow = 0;
					}
				}

				auto& head = body.front();
				head.dir = dirNow;

				moves.pop();
			}
		}
	}

	/*for (const auto& rows : map) {
		for (const auto& x : rows) {
			cout << x << ' ';
		}
		cout << '\n';
	}*/

	cout << now;

	return 0;
}