#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define F first
#define S second

const ll mxN = 2e5+ 5;
ll n,q;
ll tasty[mxN], tasty_rev[mxN];
ll max_val_1[mxN], max_val_2[mxN];
ll height[mxN], height_rev[mxN];
ll end_time1[mxN], end_time2[mxN];
ll father1[mxN], father2[mxN];
ll bit_tree1[mxN],bit_tree2[mxN];


ll rev(ll idx){
	return n - idx + 1LL;
}

ll calc_bit_2(ll k){
	ll ans = 0LL;
	for(ll asd = k ; asd >= 1; ans = ans + bit_tree2[asd], asd = father2[asd] );
	return  ans;
}

ll calc_bit_1(ll k){
	ll ans = 0LL;
	for(ll asd = k ; asd >= 1; ans = ans + bit_tree1[asd], asd = father1[asd] );
	return  ans;
}

void precalc(ll height[],ll max_val_it[]){
	stack<ll> qwe;
	qwe.push(n * 1LL);
	max_val_it[n] = n + 1LL;
	ll i = n  - 1LL;
	while( i >= 1LL ){
		ll asd = qwe.top();
		if(height[i] > height[asd]){
			ll b=i;
			for( ; !qwe.empty() ; ){
				asd = qwe.top();
				if(height[i] > height[asd]){
					b = max_val_it[asd];
					qwe.pop();
				}
				else{
					max_val_it[i] = b;
					qwe.push(i * 1LL);
					break;
				}
			}
			if(qwe.empty()){
				max_val_it[i] = n + 1LL;
				qwe.push(i * 1LL);
			}
		}
		else{
			max_val_it[i] = i;
			qwe.push(i * 1LL);
		}
		i -= 1LL;
	}
	return ;
}

void fatherent(ll height[],ll father[]){
    set<ll> qwe;
    father[1] = 0LL;
    qwe.insert(1LL);
    ll i = 2LL;
    while(i <= n){
        if(height[i] >= height[*--qwe.end()]){
        	for(; !qwe.empty() ;){
                auto it = *--qwe.end();
                if(height[i] < height[it])
                {
                    int asd = i;
                    asd -= asd & -asd;
                    auto it = qwe.upper_bound(asd);
                    if(it == qwe.begin()){
                        father[i] = 0;
                    }
                    else{
                        father[i] = *--it;
                    }
                    qwe.insert(i);
                    break;
                }
                else{
                    qwe.erase(it);
                }
            }
            if(qwe.size()== 0){
                qwe.insert(i);
            }
		}
        else{
            ll asd = i;
            asd -= asd & -asd;
            auto it = qwe.upper_bound(asd);
            if(it != qwe.begin()){
            	father[i] = *--it;
            }
            else{
                father[i] = 0LL;
            }
            qwe.insert(i);
        }
        i += 1LL;
    }
    return ;
}

void precalc_end(ll end_time[], ll height[]){
	stack< pair < ll, ll > > qwe;
	qwe.push( make_pair( height[1], 1LL) );
	end_time[1] = 0;
	ll i = 2LL;
	while( i <= n ){
		auto zxc = qwe.top();
		if(zxc.F <= height[i])
		{
			for(;!qwe.empty();){
				auto asd = qwe.top();
				if(asd.F <= height[i]) qwe.pop();
				else{
					end_time[i] = asd.S;
					qwe.push( make_pair ( height[i], i ) );
					break;
				}
			}
			if(qwe.empty()){
				end_time[i] = 0;
				qwe.push( make_pair ( height[i], i ) );
			}
		}
		else{
			end_time[i] = zxc.S;
			qwe.push( make_pair ( height[i], i ) );
		}
		i += 1LL;
	}
	return;
}

void solve()
{
	cin >> n >> q;
	for(ll i = 1LL; i <= n; i++){
		cin >> height[i];
		height_rev[ rev(i) ] = height[i];
	}
	for(ll i=1LL; i <= n; i++){
		cin >> tasty[i];
		tasty_rev[ rev(i) ] = tasty[i];
	}

	precalc(height,max_val_1);
	precalc(height_rev,max_val_2);

	fatherent(height,father1);
	fatherent(height_rev,father2);

	precalc_end(end_time1,height);
	precalc_end(end_time2,height_rev);

	for(ll i = 1LL ; i <= n ; i++){
		for(ll asd = i; asd <= n && asd <= max_val_1[i]; bit_tree1[asd] = bit_tree1[asd] + tasty[i], asd += asd & -asd );
		for(ll asd = i; asd <= n && asd <= max_val_2[i]; bit_tree2[asd] = bit_tree2[asd] + tasty_rev[i], asd += asd & -asd );
	}

	ll ch, b, c;

	for(ll qwe = 1; qwe <= q; qwe++){
		cin >> ch;
		if(ch == 2){
			cin >> b >> c;
			ll ans = 0;
			if(b <= c){
			    if(max_val_1[b] < c){
					cout << "-1\n";
					continue;
			    }
				ans = calc_bit_1(c) - calc_bit_1(end_time1[b]);
			}
			else{
				b = rev(b), c = rev(c);
				if(max_val_2[b] >= c){
					ans = calc_bit_2(c) - calc_bit_2(end_time2[b]);
				}
				else{
					cout << -1 << endl;
					continue;
				}
			}
			if(ans >= 0){
				cout << ans << endl;
				continue;
			}
			else{
				cout << "-1\n";
				continue;
			}
		}
		else if(ch == 1){
			cin >> b >> c;
			ll change = c - tasty[b];
			ll change2 = rev(b);
			for(ll asd = b; asd <= n && asd <= max_val_1[b]; bit_tree1[asd] = bit_tree1[asd] + change, asd += asd & -asd );

			change = c - tasty_rev[change2];
			tasty[b] = c;
			tasty_rev[change2] = c;

			for(ll asd = change2; asd <= n && asd <= max_val_2[change2]; bit_tree2[asd] = bit_tree2[asd] + change, asd += asd & -asd );

			continue;
		}
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
		
	ll t = 1;
	// cin>>t;

	while(t--){
		solve();
	}

	return 0;
}