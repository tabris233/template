/****************************************************
Prim 适用于稠密图，边数达到/接近T(n^2)时建议采用
****************************************************/

#define MAX 100
#define MAXCOST 0x7fffffff

int graph[MAX][MAX];
int prim(int graph[][MAX], int n) {
    int lowcost[MAX];
    int mst[MAX];
    int i, j, min, minid, sum = 0;
    for (i = 2; i <= n; i++) {
        lowcost[i] = graph[1][i];
        mst[i] = 1;
    }
    mst[1] = 0;
    for (i = 2; i <= n; i++) {
        min = MAXCOST;
        minid = 0;
        for (j = 2; j <= n; j++) {
            if (lowcost[j] < min && lowcost[j] != 0) {
                min = lowcost[j];
                minid = j;
            }
        }
        cout << "V" << mst[minid] << "-V" << minid << "=" << min << endl;
        sum += min;
        lowcost[minid] = 0;
        for (j = 2; j <= n; j++) {
            if (graph[minid][j] < lowcost[j]) {
                lowcost[j] = graph[minid][j];
                mst[j] = minid;
            }
        }
    }
    return sum;
}

/****
带输出路径的prim
****/
double map[800][800];  
double weight[1000];  
int flag[1000];  
void prim()  { 
    memset(weight,INF,sizeof(weight));  
    int pos=1;  
    double min_weight;  
    int p;  
//--------------表示遍历了第一个点-------------------//  
    for(int i=1;i<=n;i++){  
        weight[i]=map[pos][i];  
        flag[i]=pos;//记录它的父亲节点  
    }  
    flag[pos]=-1;  
//----------------寻找最短的一截路---------------//  
    for(int i=1;i<n;i++){  
        min_weight=INF;  
        p=-1;  
  
        for(int j=1;j<=n;j++){  
            if(flag[j]!=-1&&min_weight>weight[j]){  
                min_weight=weight[j];  
                p=j;  
            }  
        }  
//-------------判断是否有短路到达---------------//  
        if(p!=-1){  
            if(min_weight==0)  
                flag[p]=-1;  
            else{  
                printf("%d %d\n",flag[p],p);  
                flag[p]=-1;  
            }  
        }  
//----------------更新一截路---------------------//  
        for(int j=1;j<=n;j++)  
        if(flag[j]!=-1&&weight[j]>map[p][j]){  
            weight[j]=map[p][j];  
            flag[j]=p;  
        }  
    }  
}  