void margesort(int a[],int f[],int p,int r){
    if(p==r) {f[p]=a[r];return ;}
    int mid = (p+r)>>1;
    margesort(a,f,p,mid);
    margesort(a,f,mid+1,r);

    int l1=p,l2=mid+1;
    for(int i=p;i<=r;i++){
        if(l1<=mid&&l2<=r){
            if(a[l1]<a[l2]) f[i]=a[l1++];
            else f[i]=a[l2++];
        }
        else if(l1<=mid)   f[i]=a[l1++];
        else if(l2<=r)     f[i]=a[l2++];
    }
    for(int i=p;i<=r;i++) a[i]=f[i];
    return ;
}