//多项式gcd
#define vi vector<int>
int n;

int inv(int x){return qmod(x,n-2,n);}
vi vimod(vi f,vi g){
    int fz = f.size(),gz = g.size();
    for(int i=0;i<fz;i++){
        if(fz-i-gz < 0) break;
        int a=f[i]*inv(g[0])%n;
        for(int j=0;j<gz;j++){
            int now=i+j;
            f[now]=((f[now]-a*g[j]%n)%n+n)%n;
        }
    }
    vi ans;
    int p=-1;
    for(int i=0;i<fz;i++)if(f[i]!=0){p=i;break;}
    if(p>=0) for(int i=p;i<fz;i++)ans.pb(f[i]);
    return ans;
}

vi gcd(vi f,vi g){
    if(g.size()==0) return f;
    return  gcd(g,vimod(f,g));
}
vi f,g;
int main(){
    int kcase = 0;
    while(~scanf("%d",&n)&&n){
        f.clear(),g.clear();
        int d,x;
        scanf("%d",&d);
        for(int i=0;i<=d;i++){
            scanf("%d",&x);
            f.pb(x);
        }
        scanf("%d",&d);
        for(int i=0;i<=d;i++){
            scanf("%d",&x);
            g.pb(x);
        }
        vi ans = gcd(f,g);
        int tmp = inv(ans[0]);
        printf("Case %d: %d",++kcase,ans.size()-1);
        for(int i=0;i<ans.size();i++){
            printf(" %d",ans[i]*tmp%n);
        }
        puts("");
    }

    return 0;
}