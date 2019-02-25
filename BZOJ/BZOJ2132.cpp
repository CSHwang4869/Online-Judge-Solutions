#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int dx[4] = {0 , 0 , 1 , -1} , dy[4] = {1 , -1 , 0 , 0} ;
const int MAX_N = 100 + 10 , MAX_P = 1e4 + 10 , MAX_M = 1e5 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

Link *head[MAX_P] ;
int T , ti , tot , sum , ap[MAX_P] , dep[MAX_P] ;
int n , m , cur , bh[MAX_N][MAX_N] , col[MAX_N][MAX_N] ;
int A[MAX_N][MAX_N] , B[MAX_N][MAX_N] , C[MAX_N][MAX_N] ;

void ins(int x , int y , int f) {
	list[cur].num = y ;
	list[cur].cap = f ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur^1] ;
	head[y] = &list[cur++] ;
}

int dfs(int x , int f) {
	if (x == T || !f) return f ;

	int s = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(f , h->cap)) ;
		s += nf ; h->reg->cap += nf ;
		f -= nf ; h->cap -= nf ;
	}
	if (f) dep[x] = -1 ;

	return s ;
}

bool bfs() {
	que.push(0) ;
	ap[0] = ++ti ; dep[0] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || ap[nx] == ti) continue ;

			que.push(nx) ;
			ap[nx] = ti ; dep[nx] = dep[x] + 1 ;
		}
	}

	return ap[T] == ti ;
}

int dinic() {
	int s = 0 ;
	for (; bfs() ; s += dfs(0 , INF)) ;

	return s ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) scanf("%d" , &A[i][j]) , sum += A[i][j] ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) scanf("%d" , &B[i][j]) , sum += B[i][j] ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) scanf("%d" , &C[i][j]) ;

	col[1][1] = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			bh[i][j] = ++tot ;

			for (int k = 0 ; k < 4 ; ++k) {
				int ni = i + dx[k] , nj = j + dy[k] ;
				if (ni < 1 || nj < 1 || ni > n || nj > m) continue ;

				col[ni][nj] = col[i][j] ^ 1 ;
			}
		}
	T = ++tot ;

	///

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			if (col[i][j]) std::swap(A[i][j] , B[i][j]) ;
			ins(0 , bh[i][j] , A[i][j]) ; ins(bh[i][j] , T , B[i][j]) ;

			for (int k = 0 ; k < 4 ; ++k) {
				int ni = i + dx[k] , nj = j + dy[k] ;
				if (ni < 1 || nj < 1 || ni > n || nj > m) continue ;

				sum += C[i][j] ;
				ins(bh[i][j] , bh[ni][nj] , C[i][j]) ;
				ins(bh[ni][nj] , bh[i][j] , C[i][j]) ;
			}
		}

	printf("%d\n" , sum - dinic()) ;

	return 0 ;
}