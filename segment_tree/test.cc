#include <iostream>
#define lc p << 1
#define lr p << 1 | 1
#define LL long long
const int N = 1e5 + 10;
LL arr[N];
struct
{
    LL r, l, sum;
} tr[N << 4];
void build(int p, int l, int r)
{
    if (l == r)
    {
        tr[p] = {l, r, arr[l]};
        return;
    }
    int mid = (l + r) / 2;
    build(lc, l, mid);
    build(lr, mid + 1, r);
    tr[p] = {l, r, tr[lc].sum + tr[lr].sum};
}