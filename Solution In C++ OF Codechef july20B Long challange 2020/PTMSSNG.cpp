#include <bits/stdc++.h>
#define ll long long int
using namespace std;

void solve(){
	int n ;
	cin >> n;
	int x_ans = 0;
	int y_ans = 0;
	for(int i = 1; i <= 4 * n -1; i++){
		int x, y;
		cin >> x >> y;
		x_ans = x_ans ^ x;
		y_ans = y_ans ^ y;
	}
	cout << x_ans << " " << y_ans << "\n";
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