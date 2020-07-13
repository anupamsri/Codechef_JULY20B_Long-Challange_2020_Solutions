#include <bits/stdc++.h>
#define ll long long int
using namespace std;

ll calc(int n){
	ll ans = 0;
	while(n > 0){
		ans += n % 10;
		n /= 10;
	}
	return ans;
}

void solve(){
	int n ;
	cin >> n;
	ll a = 0, b = 0;
	while(n--){
		int x, y;
		cin >> x >> y;
		ll q = calc(x);
		ll w = calc(y);
		if(q > w){
			a++;
		}
		else if(q < w){
			b++;
		}
		else{
			a++;
			b++;
		}
	}
	if(a > b){
		cout << "0 " << a;
	}
	else if(a < b){
		cout << "1 " << b;
	}
	else{
		cout << "2 " << a;
	}
	cout << "\n";
	return ;
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