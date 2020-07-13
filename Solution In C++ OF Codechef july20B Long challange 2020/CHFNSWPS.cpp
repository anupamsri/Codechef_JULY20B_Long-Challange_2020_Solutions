#include <bits/stdc++.h>
#define ll long long int
using namespace std;

bool check(vector<int > arr1, vector< int > arr2){

	// sort(arr1.begin(), arr1.end());
	// sort(arr2.begin(), arr2.end(), greater<int >());

	if(arr1.size() != arr2.size()){
		return false;
	}
	return true;
}

void solve(){
	int n;
	cin >> n;
	int a[n],b[n];
/*	map<int , set< int > > mpa;
	map<int , set< int > > mpb;
	for(int i  = 0; i < n; i++){
		cin >> a[i];
		mpa[a[i]].insert(i);
	}
	for(int i = 0; i < n; i++){
		cin >> b[i];
		mpb[b[i]].insert(i);
	}
	// sort(a, a + n);
	// sort(b, b + n);
	bool ok = true;
	for(auto x : mpa){
		if((x.second.size() + mpb[x.first].size()) & 1){
			ok = false;
			break;
		}
	}
	if(!ok){
		cout << "-1\n";
		return ;
	}
	ll ans = 0;
	for(int i =0; i < n; i++){
		if()
	}*/
	map < int , int > mpa;
	map < int , int > mpb;
	map < int , int > mp;

	for(int i = 0; i < n; i++){
		cin >> a[i];
		mp[a[i]]++;
	}
	for(int i = 0; i < n; i++){
		cin >> b[i];
		mp[b[i]]++;
	}

	bool ok = true;

	for(auto &x : mp){
		if(x.second% 2 == 0){
			mp[x.first] = (x.second) / 2;
		}
		else{
			ok =false;
			break;
		}
	}

	if(!ok){
		cout << "-1\n";
		return ;
	}
	// make both the map's freq element equal 
	mpa.clear();
	mpb.clear();
	mpa = mp;
	mpb = mp;

	vector< int > change1;
	vector< int > change2;

	//simulate the process
	ll ans = 0;
	for(int i = 0; i < n; i++){
		if(mpa[a[i]] ) mpa[a[i]]--;
		else change1.push_back(a[i]);
	}
	sort(change1.begin(),  change1.end());

	for(int i =0; i < n; i++){
		if(mpb[b[i]] ) mpb[b[i]]--;
		else change2.push_back(b[i]);
	}
	sort(change2.begin(), change2.end(), greater< int >());

	ok = check(change1, change2);

	if(!ok){
		cout << "-1\n";
		return ;
	}
	
	//calc min for two move swaps
	int mn = min(*min_element(a, a + n), *min_element(b, b + n));
	
	for(int i = 0; i < change1.size(); i++){
		ans = ans + min(min(change2[i], change1[i]), 2 * mn);
	}
	cout << ans << "\n";
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