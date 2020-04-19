#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long  long;

const int INF = 0x3f3f3f3f;
const int MAX = 100'001;

ll num[MAX];
ll seg_tree[MAX * 4];

ll init(int node, int start, int end) {
    if (start == end) {
        return seg_tree[node] = num[start];
    } else {
        return seg_tree[node] = min(init(node*2, start, (start+end)/2), init(node*2+1, (start+end)/2+1, end));
    }
}

ll query(int node, int start, int end, int left, int right)
{
    if (left > end || right < start) return INF;
    
    if (left <= start && end <= right) return seg_tree[node];
    
    return min(query(node * 2, start, (start + end) / 2, left, right), query(node * 2 + 1, (start + end) / 2 + 1, end, left, right));
}

int main()
{
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    int N, M;
    ll answer;

    // input
    cin >> N >> M;

    for (int i = 0; i < N; ++i)
    {
        cin >> num[i];
    }

    init(1, 0, N - 1);

    for (int i = 0; i < M; ++i)
    {
        int a, b;
        cin >> a >> b;
        
        answer = query(1, 0, N - 1, a - 1, b - 1);
        cout << answer << "\n";
    }

    return 0;
}