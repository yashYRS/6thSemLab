#include<iostream>
using namespace std ;

int main() {
	int m, n , p ;
	cout<<" Enter m"; cin>>m ;
	cout<<" Enter n" ; cin>>n ;
	cout<<" Enter p " ; cin>>p ;
	int a[m][n], b[n][p] , c[m][p];
	for(int i = 0 ; i < m ; i++) {
		for(int j = 0 ; j < n ; j++) {
			a[i][j] = i*j + 1;
		}
	}
	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < p ; j++) {
			b[i][j] = 2*i*j ;
		}
	}
	cout<<" The Result - \n" ;
	for (int i = 0 ; i < m ; i++) {
		for(int j = 0 ; j < p ; j++) {
			c[i][j] = 0 ;
			for(int k = 0 ; k < n ; k++) {
				c[i][j] = c[i][j] + a[i][k]*b[k][j] ;
			}
			cout<<" "<<c[i][j] ;
		}
		cout<<endl ;
	}
	return 0 ;
}
