#include <cstdio>
#include <cstring>

typedef long long LL;

const int MAXN = 14, MOD = 99991, MAXS = 160000;  //pow(3, 13)

int n, m;
int h[MOD], size[2];
char a[MAXN][MAXN];

struct State
{
    unsigned mask;    //当前状态,4进制
    int nxt;          //下一个节点
    LL opt;           //当前状态的数目
} s[2][MAXS];

inline void update(int p, unsigned mask, LL opt)
{
    int i, val = mask % MOD;
    for (i = h[val]; i != -1; i = s[p][i].nxt)
    {
        if (s[p][i].mask == mask)
        {
            s[p][i].opt += opt;
            return;
        }
    }
    s[p][size[p]].mask = mask;
    s[p][size[p]].opt = opt;
    s[p][size[p]].nxt = h[val];
    h[val] = size[p]++;
}

inline int get(unsigned mask, int x)
{
    return (mask >> (x << 1)) & 3;
}

inline int change(unsigned mask, int x, int val)
{
    mask = mask ^ (get(mask, x) << (x << 1));
    if (val) return mask ^ (val << (x << 1));
    return mask;
}

inline int find(unsigned mask, int x, int val)
{
    int t = (val == 1 ? 1 : -1), b = 1;
    for (x += (val == 1) + t; x >= 0 && x <= m && b; x += t)  //方便在p == q时的寻找
    {
        int p = get(mask, x);
        if (p == val) b++;
        else if (p == 3 - val) b--;
    }
    return b ? x : x - t;
}

inline void init(int p)
{
    memset(h, -1, sizeof(h));
    size[p] = 0;
    memset(s[p], 0, sizeof(s[p]));
}

int main()
{
    int i, j, k, p, q, t;
    int x, y, f;

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%s", a[i] + 1);
    for (i = 0; i <= n + 1; i++)
        for (j = 0; j <= m + 1; j++)
            if (i == 0 || i > n || j == 0 || j > m) a[i][j] = '*';
            else if (a[i][j] == '.') x = i, y = j;
    f = 1;
    init(f);
    update(f, 0, 1);
    for (i = 1; i <= n; i++)
    {
        f ^= 1;
        init(f);
        for (k = 0; k < size[f ^ 1]; ++k)
            update(f, s[f ^ 1][k].mask << 2, s[f ^ 1][k].opt);
        for (j = 1; j <= m; j++)
        {
            f ^= 1;
            init(f);
            for (k = 0; k < size[f ^ 1]; ++k)
            {
                p = get(s[f ^ 1][k].mask, j - 1), q = get(s[f ^ 1][k].mask, j);
                if (a[i][j] == '.')
                {
                    if (p == 0 && q == 0)
                    {
                        if (a[i + 1][j] == '.' && a[i][j + 1] == '.')
                            update(f, change(change(s[f ^ 1][k].mask, j - 1, 1), j, 2), s[f ^ 1][k].opt);
                    }
                    else if (p == 0)
                    {
                        if (a[i][j + 1] == '.') update(f, s[f ^ 1][k].mask, s[f ^ 1][k].opt);
                        if (a[i + 1][j] == '.')
                            update(f, change(change(s[f ^ 1][k].mask, j - 1, q), j, 0), s[f ^ 1][k].opt);
                    }
                    else if (q == 0)
                    {
                        if (a[i + 1][j] == '.') update(f, s[f ^ 1][k].mask, s[f ^ 1][k].opt);
                        if (a[i][j + 1] == '.')
                            update(f, change(change(s[f ^ 1][k].mask, j - 1, 0), j, p), s[f ^ 1][k].opt);
                    }
                    else if (p == q)
                    {
                        t = find(s[f ^ 1][k].mask, j - 1, p);
                        if (t >= 0 && t <= m)
                            update(f, change(change(change(s[f ^ 1][k].mask, j - 1, 0), j, 0), t, p), s[f ^ 1][k].opt);
                    }
                    else if (p == 2 || (i == x && j == y))
                        update(f, change(change(s[f ^ 1][k].mask, j - 1, 0), j, 0), s[f ^ 1][k].opt);
                }
                else if (p == 0 && q == 0) update(f, s[f ^ 1][k].mask, s[f ^ 1][k].opt);
            }
        }
    }
    t = h[0];
    while (s[f][t].mask) t = s[f][t].nxt;
    printf("%I64d\n", s[f][t].opt);
    return 0;
}
