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
        ll tmp1 = init(node*2, start, (start+end)/2);
        ll tmp2 = init(node*2+1, (start+end)/2+1, end);
        return seg_tree[node] = min(tmp1, tmp2);
    }
}

ll query(int node, int start, int end, int left, int right)
{
    if (left > end || right < start) return INF;
    
    if (left <= start && end <= right) return seg_tree[node];
    
    ll tmp1 = query(node * 2, start, (start + end) / 2, left, right);
    ll tmp2 = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
    return min(tmp1, tmp2);
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