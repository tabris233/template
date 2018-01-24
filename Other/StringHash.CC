unsigned long long int h[5555],x[5555];
void Hash(char s[],int len){
    h[0]=0;x[0]=1;
    for(int i=1;i<=len;i++){
        x[i]=x[i-1]*29;
        h[i]=h[i-1]+x[i]*(s[i]-'a');
    }
}
bool judge(int l,int r,int l2,int r2){
    if(r-l != r2-l2) return false;
    if( (h[r]-h[l-1])*(x[l2-l]) == (h[r2]-h[l2-1]) )
        return true;
    return false;
}