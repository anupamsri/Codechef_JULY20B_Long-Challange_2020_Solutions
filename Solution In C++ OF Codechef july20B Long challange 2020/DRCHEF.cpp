#include <bits/stdc++.h>
#define ll long long int
using namespace std;

void solve(){
	ll n, x, res = 0;
	cin >> n >> x;
	multiset< ll > multi;
	for(int i = 0; i < n; i++){
		ll qwe;
		cin >> qwe;
		multi.insert(qwe * 2);
	}
	while(!multi.empty()){
		multiset< ll > :: iterator qwe = multi.lower_bound(x);
		if(qwe == multi.end()){
			break;
		}
		res++ ;
		if(x >= *qwe/2){
			multi.erase(qwe);
		}
		x = min(*qwe, 2 * x);
	}
	cout << res + multi.size() << "\n";
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