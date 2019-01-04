#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 50 + 5 , MAX_B = 50 + 5 ;

int n , BASE ;
ll a[MAX_N] , b[MAX_B] ;

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) scanf("%lld" , &a[i]) ;

	///

	BASE = 51 ;
	for (int i = 0 ; i < n ; ++i)
		for (int j = BASE ; j >= 0 ; --j)
			if (a[i] & (1LL << j)) {
				if (b[j]) a[i] ^= b[j] ;
				else {
					b[j] = a[i] ;
					for (int k = j - 1 ; k >= 0 ; --k) if (b[j] & (1LL << k)) b[j] ^= b[k] ;
					for (int k = BASE ; k > j ; --k) if (b[k] & (1LL << j)) b[k] ^= b[j] ;
					break ;
				}
			}

	ll ans = 0 ;
	for (int i = 0 ; i <= BASE ; ++i) ans ^= b[i] ;
	printf("%lld\n" , ans) ;

	return 0 ;
}