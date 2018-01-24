/******************************************************
康托展开是对全排列的一个hash
康托展开的公式是 X=an*(n-1)!+an-1*(n-2)!+…+ai*(i-1)!+…+a2*1!+a1*0! 
其中，ai为当前未出现的元素中是排在第几个（从0开始）。 
******************************************************/
int jiecheng[10] = {1,1,2,6,24,120,720,5040,40320,362880};
int a[10],b[10];
int Cantor_expansion(int a[],int len){
    int x=0;
    for(int i=0; i<len; i++)
        for(int j=i+1; j<len; j++)if(a[j]<a[i])
             x+=jiecheng[len-1-i];
    return x ;
}
bool h[len+5];//len就是序列长度
void Cantor_inexpansion(int x,int len){
    memset(h,0,sizeof(h));
    int ind ,tem;
    for(int i=0,j; i<len; i++){
        tem = x/jiecheng[len-1-i];
        x  %=   jiecheng[len-1-i];
        for(j=1,ind=0;; j<=len; j++){
            if(h[j]) continue;
            if(ind==tem){a[i]=j;break;}
            ind++;
        }
        h[a[i]]=1;
    }
    return ;
}