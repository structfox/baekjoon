#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using ll = long long;


// a: 배열 a
// tree: 세그먼트 트리
// node: 세그먼트 트리 노드 번호
// node가 담당하는 합의 범위가 start ~ end
ll init(vector<ll> &a, vector<ll> &tree, int node, int start, int end) {
    if (start == end) {
        return tree[node] = a[start];
    } else {
        return tree[node] = init(a, tree, node*2, start, (start+end)/2) + init(a, tree, node*2+1, (start+end)/2+1, end);
    }
}

// node가 담당하는 구간이 start~end이고, 구해야하는 합의 범위는 left~right
ll sum(vector<ll> &tree, int node, int start, int end, int left, int right) {
    if (left > end || right < start) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    return sum(tree, node*2, start, (start+end)/2, left, right) + sum(tree, node*2+1, (start+end)/2+1, end, left, right);
}

void update(vector<ll> &tree, int node, int start, int end, int index, ll diff) {
    if (index < start || index > end) return;
    tree[node] = tree[node] + diff;
    if (start != end) {
        update(tree,node*2, start, (start+end)/2, index, diff);
        update(tree,node*2+1, (start+end)/2+1, end, index, diff);
    }
}

int main()
{
    int N, M, K;
    vector<ll> num;
    // input
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++)
    {
        ll tmp;
        cin >> tmp;
        num.push_back(tmp);
    }

    int h = (int)ceil(log2(N));
    int tree_size = (1 << (h+1));
    vector<ll> seg_tree(tree_size);

    init(num, seg_tree, 1, 0, N - 1);

    for (int i = 0; i < M + K; i++)
    {
        int a;

        cin >> a;
        if (a == 1)
        {
            int b;
            ll c;
            cin >> b >> c;
            b -= 1;
            ll diff = c - num[b];
            num[b] = c;
            update(seg_tree, 1, 0, N - 1, b, diff);
        }
        else if (a == 2)
        {
            int b, c;
            cin >> b >> c;
            cout << sum(seg_tree, 1, 0, N - 1, b - 1, c - 1) << "\n";
        }
    }
    
    
    return 0;
}