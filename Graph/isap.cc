#include <stdio.h>      
#include <string.h>      
#include <algorithm>      
#define clear(A, X) memset (A, X, sizeof A)      
#define copy(A, B) memcpy (A, B, sizeof A)      
using namespace std;      
      
const int maxE = 1000000;      
const int maxN = 100000;      
const int maxQ = 1000000;      
const int oo = 0x3f3f3f3f;      
       
struct Edge {      
   int v;//弧尾      
   int c;//容量      
   int n;//指向下一条从同一个弧头出发的弧      
} edge[maxE];//边组      
      
     
int adj[maxN], cntE;//前向星的表头      
int Q[maxQ], head, tail;//队列      
int d[maxN], cur[maxN], pre[maxN], num[maxN];      
int sourse, sink, nv;//sourse：源点，sink：汇点，nv：编号修改的上限      
int n, m;      
      
void addedge (int u, int v, int c) {//添加边      
    //正向边      
    edge[cntE].v = v;      
    edge[cntE].c = c;//正向弧的容量为c      
    edge[cntE].n = adj[u];      
    adj[u] = cntE++;      
          
    //反向边      
    edge[cntE].v = u;      
    edge[cntE].c = 0;//反向弧的容量为0      
    edge[cntE].n = adj[v];      
    adj[v] = cntE++;      
}      
       
void rev_bfs () {//反向BFS标号      
    clear (num, 0);      
    clear (d, -1);//没标过号则为-1      
    d[sink] = 0;//汇点默认为标过号      
    num[0] = 1;      
    head = tail = 0;      
    Q[tail++] = sink;      
       
    while (head != tail) {      
        int u = Q[head++];      
        for (int i = adj[u]; ~i; i = edge[i].n) {      
            int v = edge[i].v;      
            if (~d[v]) continue;//已经标过号      
            d[v] = d[u] + 1;//标号      
            Q[tail++] = v;      
            num[d[v]]++;      
        }      
    }      
}      
      
int ISAP() {      
    copy (cur, adj);//复制，当前弧优化      
    rev_bfs ();//只用标号一次就够了，重标号在ISAP主函数中进行就行了      
    int flow = 0, u = pre[sourse] = sourse, i;      
      
    while (d[sink] < nv) {//最长也就是一条链，其中最大的标号只会是nv - 1，如果大于等于nv了说明中间已经断层了。      
        if (u == sink) {//如果已经找到了一条增广路，则沿着增广路修改流量      
            int f = oo, neck;      
            for (i = sourse; i != sink; i = edge[cur[i]].v) {      
                if (f > edge[cur[i]].c){      
                    f = edge[cur[i]].c;//不断更新需要减少的流量      
                    neck = i;//记录回退点，目的是为了不用再回到起点重新找      
                }      
            }      
            for (i = sourse; i != sink; i = edge[cur[i]].v) {//修改流量      
                edge[cur[i]].c -= f;      
                edge[cur[i] ^ 1].c += f;      
            }      
            flow += f;//更新      
            u = neck;//回退      
        }      
        for (i = cur[u]; ~i; i = edge[i].n) if (d[edge[i].v] + 1 == d[u] && edge[i].c) break;      
        if (~i) {//如果存在可行增广路，更新      
            cur[u] = i;//修改当前弧      
            pre[edge[i].v] = u;      
            u = edge[i].v;      
        }      
        else {//否则回退，重新找增广路      
            if (0 == (--num[d[u]])) break;//GAP间隙优化，如果出现断层，可以知道一定不会再有增广路了      
            int mind = nv;      
            for (i = adj[u]; ~i; i = edge[i].n) {      
                if (edge[i].c && mind > d[edge[i].v]) {//寻找可以增广的最小标号      
                    cur[u] = i;//修改当前弧      
                    mind = d[edge[i].v];      
                }      
            }      
            d[u] = mind + 1;      
            num[d[u]]++;      
            u = pre[u];//回退      
        }      
    }      
          
    return flow;      
}      
      
void init () {//初始化      
    clear (adj, -1);      
    cntE = 0;      
}      
      
void work () {      
    int u, v, c;      
    init ();      
    for (int i = 0; i < m; ++ i) scanf ("%d%d%d", &u, &v, &c), addedge (u, v, c);      
    sourse = 1; sink = n; nv = sink + 1;      
    printf ("%d\n", ISAP ());      
}        
int main() {      
    while (~scanf("%d%d", &m, &n)) work ();      
    return 0;      
}    