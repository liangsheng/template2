/*============================================================*\
 | 2̨������������
   2̨����, n������, ��������S1����, ����S2����. ����֮��������
������. ��������깤ʱ��. ����һ����������: 2̨������������ж�
��ʽ�㷨(Johnson�㷨), 3̨�����ϵĻ�����NP-hard��. Johnson�㷨:
(1) ����ҵ������ӹ�ʱ��ֳ������Ӽ�,
    ��һ����������S1������ʱ�����S2����,
  ��������ҵ�ŵ��ڶ�������.
  ����ɵ�һ�������������ҵ, ����ɵڶ������������ҵ.
(2) ���ڵ�һ������, ���е���ҵ˳���ǰ���S1�ϵ�ʱ��Ĳ�������;
  ���ڵڶ�������, ���е���ҵ˳���ǰ���S2�ϵ�ʱ��Ĳ�������.
\*============================================================*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 10005
using namespace std;

struct NODE
{
    int t1, t2;
};

int n;
NODE a[N], b[N];

bool cmp1(NODE p1, NODE p2) { return p1.t1 < p2.t1; }

bool cmp2(NODE p1, NODE p2) { return p1.t2 > p2.t2; }

int main()
{
    int i, e1, e2, p1, p2;
    while (scanf("%d", &n) != EOF && n)
    {
        for (i = 0; i < n; i++) scanf("%d%d", &a[i].t1, &a[i].t2);
        e1 = 0, e2 = n;
        for (i = 0; i < n; i++)
        {
            if (a[i].t1 < a[i].t2) b[e1++] = a[i];
            else b[--e2] = a[i];
        }
        sort(b, b + e1, cmp1), sort(b + e1, b + n, cmp2);
        p1 = b[0].t1 + b[1].t1, p2 = b[0].t1 + b[0].t2;
        for (i = 2; i < n; i++)
        {
            p2 = max(p1, p2) + b[i - 1].t2;
            p1 += b[i].t1;
        }
        p2 = max(p1, p2) + b[n - 1].t2;
        printf("%d\n", p2);
    }
    system("pause");
    return 0;
}
