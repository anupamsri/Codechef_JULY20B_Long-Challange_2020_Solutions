#include <iostream>
#include <math.h>
#include <iomanip>
#include <bits/stdc++.h>
#include <string.h>
#include <string>
#include <algorithm>
#define ll long long int
#define pb push_back
#define fi first
#define se second
#define N 100005
#define inf 1e18
#define mem(a,b) memset(a,b,sizeof(a))
#define debug(x) cout << (#x) << " = " << x << endl;
#define debug2(i,j) cout << (#i) << "=" << i << " , " << (#j) << "=" << j << endl;

using namespace std;

ll binomialCoeff(ll n,ll k)
{
    ll res = 1;
    if(k >n - k)
        k = n - k;
    for(int i = 0; i < k; ++i)
    {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

ll power(ll x,ll y)
{
    ll temp;
    if(y == 0)
        return 1;
    temp = power(x, y/2);
    if (y%2 == 0)
        return temp*temp;
    else
        return x*temp*temp;
}


/* nCr % mod
ll fact[6*N];
ll inv[6*N],invfac[6*N];
ll mod = 998244353;

void factorial()
{
    fact[0] = invfac[0] = fact[1] = invfac[1] = 1;
    inv[1] = 1;
    for(int i=2;i<=5*N + 10;i++)
    {
        fact[i] = (fact[i-1]*i)%mod;
        inv[i] = (inv[mod%i]*(mod - mod/i))%mod;
        invfac[i] = (invfac[i-1]*inv[i])%mod;
    }
}*/

void Sieve(int n)
{
    vector<ll> primes;
    vector<bool> prime(n+1,true);
    for (int p=2; p*p<=n; p++)
    {
        if (prime[p] == true)
        {
            for (int i=p*p; i<=n; i += p)
                prime[i] = false;
        }
    }
    for (int p=2; p<=n; p++)
       if (prime[p])
          primes.push_back(p);
}

//******************    CHECK CONSTRAINTS   *********************//

const int Nmax = 200005;
ll mod = 1e9 + 7;

int n,q;
ll h[Nmax];
ll hrev[Nmax];
ll a[Nmax];
ll arev[Nmax];
int lim1[Nmax];
int lim2[Nmax];
int last1[Nmax];
int last2[Nmax];
int par1[Nmax];
int par2[Nmax];

ll fen1[Nmax],fen2[Nmax];

void parent(ll height[],int par[])
{
    set<int> s;
    par[1] = 0;
    s.insert(1);
    for(int i=2;i<=n;i++)
    {
        if(height[i] < height[*--s.end()])
        {
            int k = i;
            k -= k&-k;
            auto it = s.upper_bound(k);
            if(it == s.begin())
                par[i] = 0;
            else
                par[i] = *--it;
            s.insert(i);
        }
        else
        {
            while(s.size())
            {
                auto it = *--s.end();
                if(height[i] < height[it])
                {
                    int k = i;
                    k -= k&-k;
                    auto it = s.upper_bound(k);
                    if(it == s.begin())
                        par[i] = 0;
                    else
                        par[i] = *--it;
                    s.insert(i);
                    break;
                }
                else
                    s.erase(it);
            }
            if(s.size()==0)
                s.insert(i);
        }
    }
}

void allocate(int n,ll height[],int limit[])
{
    stack<int> st;
    st.push(n);
    limit[n] = n+1;
    for(int i=n-1;i>=1;i--)
    {
        int ind = st.top();
        if(height[i] <= height[ind])
        {
            limit[i] = i;
            st.push(i);
        }
        else
        {
            int b=i;
            while(!st.empty())
            {
                ind = st.top();
                if(height[i] <= height[ind])
                {
                    limit[i] = b;
                    st.push(i);
                    break;
                }
                b = limit[ind];
                st.pop();
            }
            if(st.size()==0)
            {
                limit[i] = n+1;
                st.push(i);
            }
        }
    }
}

void allocate_last(int last[],ll height[])
{
    stack<pair<ll,int>> st;
    st.push({height[1],1});
    last[1] = 0;
    for(int i=2;i<=n;i++)
    {
        auto val = st.top();
        if(val.first > height[i])
        {
            last[i] = val.second;
            st.push({height[i],i});
        }
        else
        {
            while(!st.empty())
            {
                auto val = st.top();
                if(val.first > height[i])
                {
                    last[i] = val.second;
                    st.push({height[i],i});
                    break;
                }
                else
                    st.pop();
            }
            if(st.size() == 0)
            {
                last[i] = 0;
                st.push({height[i],i});
            }
        }
    }
}

ll sum1(int k)
{
    ll s = 0;
    int kk = k;
    while(k>=1)
    {
        s += fen1[k];
        //k -= k&-k;
        k = par1[k];
    }
    return s;
}

ll sum2(int k)
{
    ll s = 0;
    int kk = k;
    while(k>=1)
    {
        s += fen2[k];
        //k -= k&-k;
        k = par2[k];
    }
    return s;
}

void add1(int k,ll x)   //increase value of index k by x
{
    int kk = k;
    while(k<=n)
    {
        fen1[k] += x;
        k += k&-k;
        if(k > lim1[kk])
            break;
    }
}

void add2(int k,ll x)   //increase value of index k by x
{
    int kk = k;
    while(k<=n)
    {
        fen2[k] += x;
        k += k&-k;
        if(k > lim2[kk])
            break;
    }
}

void check()
{
    for(int i=1;i<=n;i++)
        debug2(lim1[i],lim2[i]);
    for(int i=1;i<=n;i++)
        debug2(i,fen1[i]);
    for(int i=1;i<=n;i++)
        debug2(i,fen2[i]);
}

int main()
{
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> n >> q;
    for(int i=1;i<=n;i++)
    {
        cin >> h[i];
        hrev[n-i+1] = h[i];
    }
    for(int i=1;i<=n;i++)
    {
        cin >> a[i];
        arev[n-i+1] = a[i];
    }
    allocate(n,h,lim1);
    allocate(n,hrev,lim2);

    parent(h,par1);
    parent(hrev,par2);

    allocate_last(last1,h);
    allocate_last(last2,hrev);

    for(int i=1;i<=n;i++)
        add1(i,a[i]) , add2(i,arev[i]);

    //check();

    while(q--)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            int b;
            ll k;
            cin >> b >> k;
            ll x = k-a[b];
            ll b1 = n-b+1;
            add1(b,x);
            x = k - arev[b1];
            a[b] = k;
            arev[b1] = k;
            add2(b1,x);
        }
        else
        {
            int start,end;
            cin >> start >> end;
            ll val = 0;
            if(start <= end)
            {
                if(lim1[start] < end)
                {
                    cout << -1 << "\n";
                    continue;
                }
                val = sum1(end) - sum1(last1[start]);
            }
            else
            {
                start = n-start+1;
                end = n-end+1;
                if(lim2[start] < end)
                {
                    cout << -1 << "\n";
                    continue;
                }
                val = sum2(end) - sum2(last2[start]);
            }
            if(val >= 0)
                cout << val << "\n";
            else
                cout << -1 << "\n";
        }
    }
}