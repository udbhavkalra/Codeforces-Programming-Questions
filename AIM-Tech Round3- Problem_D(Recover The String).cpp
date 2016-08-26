#include <bits/stdc++.h>
using namespace std;

/*
	Ques URL:http://codeforces.com/contest/709/problem/D

	Approach:
	start from first, we have count of 01,10 and number of 0,1's (which will be calculated using roots D)
	now iterate in right to left, and add 0/1 according to:
	if count of 01 > 10:
	append "0" to result, and 0's--(minus minus), #of 01 -= #1's, think of as removing this current bit appended, so 01's -= #1's
	||ly for "1"
	if both are same, your wish whether to take 1 or 0, I am taking '0' if 0's > 1's else '1'... so on
	#Impossible cases:
	if(root values can't be found, it's not possible to find a corresponding string)
	also, if at any point of time, '01's/'10's are there but '0's/ '1's are not there
*/

typedef long double ld;
#define fori(i,a,b) for(int i=a; i<b; i++)
#define MP make_pair
#define pld pair < ld, ld >
#define PB push_back
#define F first
#define S second

pld roots(ld a, ld b, ld c){
	ld one = ld (0-b),two = ld (sqrt(pow(b,2)-4*a*c));
	return MP(ld(one+two)/ld(2*a), ld(one-two)/ld(2*a));
}

int main(){
	ld a,b,c,d,zero=0,one=0,size=0;
	pld getRoots;
	cin>>a>>b>>c>>d;
	if(a==0 && (b>0 || c>0) ) zero = 1;
	else if(a>0){
		getRoots = roots(1.0,-1.0,ld(0-2*a));												//get number of 0's
		zero = (getRoots.F > 0) ? getRoots.F : getRoots.S;
	}

	if(d==0 && (b>0 || c>0) ) one = 1;
	else if(d>0){
		getRoots = roots(1.0,-1.0,ld(0-2*d));												//get number of 1's
		one = (getRoots.F > 0) ? getRoots.F : getRoots.S;
	}

	if(a==0 && b==0 && c==0 && d==0){cout<<"0"; return 0;}
	if(floor(zero) != zero || floor(one) != one || (pow(zero,2)-zero) != (2*a) || (pow(one,2)-one) != (2*d))
		{cout<<"Impossible"; return 0;}

	size = zero + one;
	vector <bool> res;
	fori(i,0,size){
		if( ((zero==0) && (b > 0)) || ((one==0) && (c > 0))){cout<<"Impossible"; return 0;}

		if(b < c && c-zero>=0)	res.PB(1), one--, c -= zero;								//if '10' count is higher
		else if(b > c && b>=one)	res.PB(0), zero--, b -= one;										//else if '01' count is higher
		else if(b != 0){
			if(zero < one && c>=zero)	res.PB(1), one--, c -= zero;
			else	res.PB(0), zero--, b -= one;
		}

		if(b==0 && c==0){
			while(one>0 && zero==0)	res.PB(1), one--;
			while(zero>0 && one==0)	res.PB(0), zero--;
		}
	}
	if(b!=0 || c!=0 || one!=0 || zero!=0){cout<<"Impossible"; return 0;}
	fori(i,0,size){
		if(res[i])	cout<<"1";
		else cout<<"0";
	}
	return 0;
}