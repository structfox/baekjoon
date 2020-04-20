#include <iostream>
#include <algorithm>

using namespace std;
using ll = long  long;

const int INF = 0x3f3f3f3f;
const int MAX = 100'001;

ll num[MAX];
ll min_tree[MAX * 4];
ll max_tree[MAX * 4];

ll min_init(int node, int start, int end) {
    if (start == end) {
        return min_tree[node] = num[start];
    } else {
        ll tmp1 = min_init(node*2, start, (start+end)/2);
        ll tmp2 = min_init(node*2+1, (start+end)/2+1, end);
        return min_tree[node] = min(tmp1, tmp2);
    }
}

ll min_query(int node, int start, int end, int left, int right)
{
    if (left > end || right < start) return INF;
    
    if (left <= start && end <= right) return min_tree[node];
    
    ll tmp1 = min_query(node * 2, start, (start + end) / 2, left, right);
    ll tmp2 = min_query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
    return min(tmp1, tmp2);
}

ll max_init(int node, int start, int end) {
    if (start == end) {
        return max_tree[node] = num[start];
    } else {
        ll tmp1 = max_init(node*2, start, (start+end)/2);
        ll tmp2 = max_init(node*2+1, (start+end)/2+1, end);
        return max_tree[node] = max(tmp1, tmp2);
    }
}

ll max_query(int node, int start, int end, int left, int right)
{
    if (left > end || right < start) return -INF;
    
    if (left <= start && end <= right) return max_tree[node];
    
    ll tmp1 = max_query(node * 2, start, (start + end) / 2, left, right);
    ll tmp2 = max_query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
    return max(tmp1, tmp2);
}

int main()
{
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    int N, M;
    ll min_answer;
    ll max_answer;

    // input
    cin >> N >> M;

    for (int i = 0; i < N; ++i)
    {
        cin >> num[i];
    }

    min_init(1, 0, N - 1);
    max_init(1, 0, N - 1);

    for (int i = 0; i < M; ++i)
    {
        int a, b;
        cin >> a >> b;
        
        min_answer = min_query(1, 0, N - 1, a - 1, b - 1);
        max_answer = max_query(1, 0, N - 1, a - 1, b - 1);
        cout << min_answer << " " << max_answer << "\n";
    }

    return 0;
}