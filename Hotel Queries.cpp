#include<bits/stdc++.h>
using namespace std;
const int N = 2e6+7;
long long n,a[N],m;
struct haha {
    long long val;
    long long lazy;
};
haha seg[N];
void do_lazy(int id)
{
    long long he = seg[id].lazy;
    if(he != 0)
    {
        seg[id*2].val = seg[id*2].lazy = he;
        seg[id*2+1].val = seg[id*2+1].lazy = he;
    }
    seg[id].lazy = 0;
}
void build(int id,int l,int r)
{
    if(l > r) return;
    if(l==r)
    {
        seg[id].val = a[l];
        return;
    }
    int mid = (l+r)/2;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
    seg[id].val = max(seg[id*2].val, seg[id*2+1].val);
}
void update(int id,int l,int r,int u,int v,long long value)
{

    if(l>v || r<u) return;
    if(l>=u && r<=v) {
        seg[id].val = seg[id].lazy = value;
        return;
    }
    int mid = (l+r)/2;
    update(id*2,l,mid,u,v,value);
    update(id*2+1,mid+1,r,u,v,value);

    seg[id].val = max(seg[id*2].val, seg[id*2+1].val);
}
int get(int id,int l,int r,int u,int v)
{
    if(l>v || r<u) return 0;

    if(l>=u && r<=v) return seg[id].val;

    int mid = (l+r)/2;
    return max(get(id*2,l,mid,u,v), get(id*2+1,mid+1,r,u,v));
}
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int x;
        cin>>x;

        int l = 1,r = n, ans = 0;

        while(l <= r)
        {
            int mid = (l+r)/2;

            if(get(1,1,n,l,mid) >= x) {
                    ans = mid;
                    r = mid-1;
            } else if(get(1,1,n,mid+1,r) >= x) l = mid+1; else break;
        }

        if(ans != 0) {
            cout<<ans<<" ";
            a[ans] -= x;
            update(1,1,n,ans,ans,a[ans]);
        } else cout<<ans<<" ";
    }
    return 0;
}
