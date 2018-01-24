//实现一 : 4分思想的实现
/***********************************************
4分思想的实现
与一维类似,只不过是把一个矩形横竖分成4部分而已.
-------------------
| son(0) | son(1) |
-------------------
| son(2) | son(3) |
-------------------
************************************************/
int n,m,a[N][N];

int mx[(N<<2)*(N<<2)],mi[(N<<2)*(N<<2)],lazy[(N<<2)*(N<<2)];

void pushup(int rt){
    mx[rt]=max(max(mx[rt<<2|0],mx[rt<<2|1]),max(mx[rt<<2|2],mx[rt<<2|3]));
    mi[rt]=min(min(mi[rt<<2|0],mi[rt<<2|1]),min(mi[rt<<2|2],mi[rt<<2|3]));
}

void pushdown(int rt){
    if(lazy[rt]){
        lazy[rt<<2|0]=lazy[rt];
        lazy[rt<<2|1]=lazy[rt];
        lazy[rt<<2|2]=lazy[rt];
        lazy[rt<<2|3]=lazy[rt];

        mx[rt<<2|0]=lazy[rt];
        mx[rt<<2|1]=lazy[rt];
        mx[rt<<2|2]=lazy[rt];
        mx[rt<<2|3]=lazy[rt];

        mi[rt<<2|0]=lazy[rt];
        mi[rt<<2|1]=lazy[rt];
        mi[rt<<2|2]=lazy[rt];
        mi[rt<<2|3]=lazy[rt];

        lazy[rt]=0;
    }
}

void build(int rt,int x0,int y0,int x1,int y1){
    if(x0> x1||y0> y1) return ;
    if(x0==x1&&y0==y1){
        mx[rt]=a[x0][y0];
        mi[rt]=a[x0][y0];
        return ;
    }
    int xm = x0+x1>>1;
    int ym = y0+y1>>1;
    build(rt<<2|0,x0  ,y0  ,xm,ym);
    build(rt<<2|1,x0  ,ym+1,xm,y1);
    build(rt<<2|2,xm+1,y0  ,x1,ym);
    build(rt<<2|3,xm+1,ym+1,x1,y1);
    pushup(rt);
}

void update(int rt,int x0,int y0,int x1,int y1,int x,int y,int v){ //单点更新
    if(x0> x1||y0> y1) return ;
    if(x0==x1&&y0==y1){
        mx[rt]=v;
        mi[rt]=v;
        return ;
    }
    int xm = x0+x1>>1;
    int ym = y0+y1>>1;
    if(x<=xm&&y<=ym) update(rt<<2|0,x0  ,y0  ,xm,ym,x,y,v);
    if(x<=xm&&y> ym) update(rt<<2|1,x0  ,ym+1,xm,y1,x,y,v);
    if(x> xm&&y<=ym) update(rt<<2|2,xm+1,y0  ,x1,ym,x,y,v);
    if(x> xm&&y> ym) update(rt<<2|3,xm+1,ym+1,x1,y1,x,y,v);
    pushup(rt);
}

void update(int rt,int x0,int y0,int x1,int y1,int X0,int Y0,int X1,int Y1,int v){ //区间更新
    if(x0> x1||y0> y1) return ;
    if(X0<=x0&&x1<=X1&&Y0<=y0&&y1<=Y1){
        lazy[rt]=v;
        mx[rt]=v;
        mi[rt]=v;
        return ;
    }
    int xm = x0+x1>>1;
    int ym = y0+y1>>1;
    if(X0<=xm&&Y0<=ym) update(rt<<2|0,x0  ,y0  ,xm,ym,X0,Y0,X1,Y1,v);
    if(X0<=xm&&Y1> ym) update(rt<<2|1,x0  ,ym+1,xm,y1,X0,Y0,X1,Y1,v);
    if(X1> xm&&Y0<=ym) update(rt<<2|2,xm+1,y0  ,x1,ym,X0,Y0,X1,Y1,v);
    if(X1> xm&&Y1> ym) update(rt<<2|3,xm+1,ym+1,x1,y1,X0,Y0,X1,Y1,v);
    pushup(rt);
}
//区间查询最小值
int query_min(int rt,int x0,int y0,int x1,int y1,int X0,int Y0,int X1,int Y1){
    if(x0> x1||y0> y1) return INF;
    if(X0<=x0&&x1<=X1&&Y0<=y0&&y1<=Y1) return mi[rt];
    
    int xm = x0+x1>>1;
    int ym = y0+y1>>1;
    int ans = INF;
    if(X0<=xm&&Y0<=ym) ans=min(ans,query_min(rt<<2|0,x0  ,y0  ,xm,ym,X0,Y0,X1,Y1));
    if(X0<=xm&&Y1> ym) ans=min(ans,query_min(rt<<2|1,x0  ,ym+1,xm,y1,X0,Y0,X1,Y1));
    if(X1> xm&&Y0<=ym) ans=min(ans,query_min(rt<<2|2,xm+1,y0  ,x1,ym,X0,Y0,X1,Y1));
    if(X1> xm&&Y1> ym) ans=min(ans,query_min(rt<<2|3,xm+1,ym+1,x1,y1,X0,Y0,X1,Y1));
    return ans;
}

int query_max(int rt,int x0,int y0,int x1,int y1,int X0,int Y0,int X1,int Y1){
    if(x0> x1||y0> y1) return -INF;
    if(X0<=x0&&x1<=X1&&Y0<=y0&&y1<=Y1) return mx[rt];
    
    int xm = x0+x1>>1;
    int ym = y0+y1>>1;
    int ans = -INF;
    if(X0<=xm&&Y0<=ym) ans=max(ans,query_max(rt<<2|0,x0  ,y0  ,xm,ym,X0,Y0,X1,Y1));
    if(X0<=xm&&Y1> ym) ans=max(ans,query_max(rt<<2|1,x0  ,ym+1,xm,y1,X0,Y0,X1,Y1));
    if(X1> xm&&Y0<=ym) ans=max(ans,query_max(rt<<2|2,xm+1,y0  ,x1,ym,X0,Y0,X1,Y1));
    if(X1> xm&&Y1> ym) ans=max(ans,query_max(rt<<2|3,xm+1,ym+1,x1,y1,X0,Y0,X1,Y1));
    return ans;
}
int main(){
    int _ = 1,kcase = 0;
    for(scanf("%d",&_);_--;){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
        }
        build(1,1,n,1,n);
        int x,y,l;
        printf("Case #%d:\n",++kcase);
        for(scanf("%d",&m);m--;){
            scanf("%d%d%d",&x,&y,&l);

            int sx=max(1,x-l/2);  
            int sy=max(1,y-l/2);  
            int mx=min(n,x+l/2);  
            int my=min(n,y+l/2); 

            int mmin = query_min(1,1,n,1,n,sx,sy,mx,my);
            int mmax = query_max(1,1,n,1,n,sx,sy,mx,my);

            printf("%d\n",(mmin+mmax)/2);
            update(1,1,n,1,n,x,y,(mmin+mmax)/2);

        }
    }
    return 0;
}
