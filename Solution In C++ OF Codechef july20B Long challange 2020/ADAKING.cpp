#include <bits/stdc++.h>
#define ll long long int
using namespace std;

void solve(){
	int n;
	cin >> n;
	char chess[8][8];
	int num = 0;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(i == 0 && j == 0){
				chess[i][j] = 'O';
				num++;
			}
			else if(num >= n){
				chess[i][j] = 'X';
			}
			else{
				chess[i][j] = '.';
				num++;
			}
		}
	}
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			cout << chess[i][j];
		}
		cout << "\n";
	}
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