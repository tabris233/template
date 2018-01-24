struct KDtree{
    int ans,cnt,root,X,Y;
    struct tree{
        int d[2],mn[2],mx[2];
        int l,r;
        int newnode(int x,int y){
            d[0]=x,d[1]=y;
            mx[0]=mn[0]=x;
            mx[1]=mn[1]=y;
        }
    }T[N+M];

    static bool cmp0(const KDtree::tree &a,const KDtree::tree &b){
        return a.d[0]<b.d[0]||a.d[0]==b.d[0]&&a.d[1]<b.d[1];
    }
    static bool cmp1(const KDtree::tree &a,const KDtree::tree &b){
        return a.d[1]<b.d[1]||a.d[1]==b.d[1]&&a.d[0]<b.d[0];
    }
    
    void init(){cnt = 0;}

    int newnode(int x,int y){T[++cnt].newnode(x,y);}

    void up(int p,int q){
        if(0==q) return ;
        T[p].mn[0]=min(T[p].mn[0],T[q].mn[0]);
        T[p].mn[1]=min(T[p].mn[1],T[q].mn[1]);
        T[p].mx[0]=max(T[p].mx[0],T[q].mx[0]);
        T[p].mx[1]=max(T[p].mx[1],T[q].mx[1]);
    }

    int bd(int l,int r,int D){
        int m = r+l >> 1;
        if(D)nth_element(T+l+1,T+m+1,T+r+1,cmp1);
        else nth_element(T+l+1,T+m+1,T+r+1,cmp0);
        T[m].l = (l==m)?0:bd(l,m-1,1-D);
        T[m].r = (r==m)?0:bd(m+1,r,1-D);
        up(m,T[m].l); up(m,T[m].r);
        return m;
    }

    int build(){root = bd(1,cnt,0);}

    void insert(int k){
        int p = root,D = 0;
        for(;1;D=1-D){
            up(p,k);
            if(T[k].d[D]<=T[p].d[D]){
                if(0==T[p].l){T[p].l=k;return;}
                p=T[p].l;
            }
            else {
                if(0==T[p].r){T[p].r=k;return;}  
                p=T[p].r;
            }
        }
    }

    int dis(int p,int x,int y){// 点(x,y)与p所在子树的范围的距离
        int res = 0;
        if(x > T[p].mx[0]) res += x - T[p].mx[0];
        if(x < T[p].mn[0]) res += T[p].mn[0] - x;
        if(y > T[p].mx[1]) res += y - T[p].mx[1];
        if(y < T[p].mn[1]) res += T[p].mn[1] - y;
        return res;
    }

    void ask(int p){
        int d0 = abs(X-T[p].d[0]) + abs(Y-T[p].d[1]);
        if(d0<ans) ans = d0;
        int dl=(T[p].l)?dis(T[p].l,X,Y):INF;
        int dr=(T[p].r)?dis(T[p].r,X,Y):INF;
        if(dl<dr){
            if(dl<ans) ask(T[p].l);
            if(dr<ans) ask(T[p].r);
        }
        else {
            if(dr<ans) ask(T[p].r);
            if(dl<ans) ask(T[p].l);
        }
    }

    int query(int x,int y){
        ans = INF;
        X = x,Y = y;
        ask(root);
        return ans;
    }
}kd;