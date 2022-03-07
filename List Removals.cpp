#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
const int N = 2e6+7;
int n,a[N];
pair<int,int> st[N];
void lazy(int id)
{
    if(st[id].se != 0)
    {
        int val = st[id].se;
        st[id*2].fi += val;
        st[id*2].se += val;
        st[id*2+1].fi += val;
        st[id*2+1].se += val;
    }
    st[id].se = 0;
}
void build(int id,int l,int r)
{
    if(l > r) return;
    if(l==r)
    {
        st[id].fi = 1;
        return;
    }
    int mid = (l+r)/2;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
    st[id].fi = st[id*2].fi + st[id*2+1].fi;
}
int get(int id,int l,int r,int u,int v)
{
    lazy(id);
    if(l>v || r<u) return 0;
    if(l>=u && r<=v) return st[id].fi;
    int mid = (l+r)/2;
    return get(id*2,l,mid,u,v) + get(id*2+1,mid+1,r,u,v);
}
void update(int id,int l,int r,int u,int v,int k)
{
    if(l>v || r<u) return;
    if(l>=u && r<=v) {
        st[id].fi += k;
        st[id].se += k;
        return;
    }
    int mid = (l+r)/2;
    update(id*2,l,mid,u,v,k);
    update(id*2+1,mid+1,r,u,v,k);
    st[id].fi = st[id*2].fi + st[id*2+1].fi;
}
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        int x; cin>>x;
        int l = 1;
        int r = n;
        int tmp = 0, ans = 0;
        while(l<=r)
        {
            int mid = (l+r)/2;
            int value = get(1,1,n,l,mid);
            if(value + tmp >= x) {
                    ans = mid;
                    r = mid -  1;
            } else
            {
                tmp += value;
                l = mid + 1;
            }
        }
        cout<<a[ans]<<" ";
        update(1,1,n,ans,ans,-1);
    }
    return 0;
}
