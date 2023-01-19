// KALAM
# include <bits/stdc++.h>

using namespace std;

const int N = 100 + 77  , Mod = 1000000000 + 7;

// code rewritten to vector style

struct Matrix {
	int n , m , MOD;
	vector < vector < int > > a;
	void print() {
		cerr << "matrix size(" << n << " , " << m << ")\n";
		for(int i = 0;i < n;++ i) {
			for(int j = 0;j < m;++ j)
				cerr << a[i][j] << " ";
			cerr << "\n";
		}
	}
	Matrix(int _n , int _m , int _MOD) {
		n = _n;
		m = _m;
		MOD = _MOD;
		a.clear();
		a.resize(n , vector < int >(m , 0));
	}
	Matrix operator + (const Matrix& X) {
		assert(n == X.n && m == X.m);
		Matrix r(n , m , MOD);
		for(int i = 0;i < n;++ i)
			for(int j = 0;j < m;++ j)
				r.a[i][j] = (a[i][j] + X.a[i][j]) % MOD;
		return r;
	}
	Matrix operator * (const Matrix& X) {
		assert(m == X.n);
		Matrix r(n , X.m , MOD);
		for(int i = 0;i < n;++ i)
			for(int k = 0;k < m;++ k)
				for(int j = 0;j < X.m;++ j)
					r.a[i][j] = (r.a[i][j] + a[i][k] * 1ll * X.a[k][j]) % MOD;
		return r;
	}
	Matrix operator ^ (long long pw) {
		assert(n == m);
		Matrix r(n , m , MOD);
		Matrix aux = (* this);
		for(int i = 0;i < n;++ i)
			r.a[i][i] = 1;
		for(;pw;pw >>= 1 , aux *= aux)
			if(pw & 1)
				r = r * aux;
		return r;
	}
	void operator += (const Matrix& X) { (* this) = (* this) + X; }
	void operator *= (const Matrix& X) { (* this) = (* this) * X; }
	void operator ^= (long long pw) { (* this) = (* this) ^ pw; }
};


int main() {
	Matrix a(2 , 2 , 1000000);
	a.a[0][0] = 1;
	a.a[0][1] = 1;
	a.a[1][0] = 1;
	a.a[1][1] = 0;
	for(int i = 0;i < 10;++ i) {
		Matrix b = a ^ i;
		b.print();
	}
	a.print();
	return (0);
}
