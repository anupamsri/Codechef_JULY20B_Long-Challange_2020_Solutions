#include <bits/stdc++.h>
#define ll long long int
using namespace std;

const int MOD = 998244353;
string s;
ll weight[26];

// Code taken from GeeksForGeeks - https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
int power(int x, unsigned int y, unsigned int m) 
{ 
    if (y == 0) 
        return 1; 
    int p = power(x, y/2, m) % m; 
    p = (p * p) % m; 
  
    return (y%2 == 0)? p : (x * p) % m; 
} 
  
// Function to return gcd of a and b 
int gcd(int a, int b) 
{ 
    if (a == 0) 
        return b; 
    return gcd(b%a, a); 
} 
ll modInverse(int a, int m) 
{ 
    int g = gcd(a, m); 
    if (g != 1) 
        return a;
    else
    { 
        // If a and m are relatively prime, then modulo inverse 
        // is a^(m-2) mode m 
        return  power(a, m-2, m); 
    } 
} 
  
// To compute x^y under modulo m 

ll calc(string  asd){
	ll ans = 0;
	for(char ch : asd){
		ans += weight[ch - 'a'];
	}
	return ans ;
}

void solve(){
	cin >> s;
	for(int i = 0; i < 26; i++){
		cin >> weight[i];
	}
	map< string , pair< ll , ll> >  mp;
	int n = s.size();
	ll cnt = 0;
	for (int i = 0; i < n; i++){
		for (int len = 1; len <= n - i; len++){
			cnt++;
			string temp = s.substr(i, len);
			mp[temp].first++;
			ll w = 0;
			if(mp[temp].first == 1){
				mp[temp].second = calc(temp);
			}
		}
	}

	ll ans = 0;
	for(auto x : mp){
		string check = x.first;
		ll already  = x.second.second;

		for(int i = 1; i < check.size()  ; i++){
			string pref = check.substr(0,i);

			ll count = 0;
			for(int j = 0; j < check.size() - 1; j++){
				string asd = check.substr(j, pref.size());

				if(asd == pref){
					count++;
					j = j + pref.size() - 1;
				}
				else{
					break;
				}
			}
			if(check.substr(check.size() - pref.size(), pref.size()) == pref) count++;
			if(count > 1){

				already += calc(pref);
			}

		}
		ans += already * x.second.first;
	}
	cout << ans << "/" << cnt << "\n";
	ll g = __gcd(ans, cnt);
	ans = ans / g;
	cnt = cnt / g;
	ll q = modInverse(cnt, MOD);
	cout << ans * q << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(0);

	#ifndef ONLINE_JUDGE
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
		
	int t;
	cin>>t;

	while(t--){
		solve();
	}

	return 0;
}