/****************************************************
kruskal 适用于稀疏图，边数接近T(k*n)时采用 （k为常数
****************************************************/
struct node {
    int u,v,w;
}e[N*4];
bool cmp(node a,node b){
    return a.w>b.w;
}
int pre[N];
int findi(int x){
    int r=x;
    while(r!=pre[r])r=pre[r];
    for(int i=x,j;i!=r;i=j){
        j=pre[i];
        pre[i]=r;
    }
    return r;
}
void join(int x,int y){
    x=findi(x),y=findi(y);
    pre[x]=y;
}
void MST(){
    sort(e+1,e+m+1,cmp);
    for(int i=1,sum=0;i<=m&&sum<n-1;i++){
        if(findi(e[i].u)==findi(e[i].v)) continue;
        join(e[i].u,e[i].v);
        add(e[i].u,e[i].v,e[i].w);
        sum++;
    }
}