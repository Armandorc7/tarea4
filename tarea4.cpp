#include <iostream>
#include <cmath>
using namespace std;


/*
    PROBLEMA 1 — Incrementos Dependientes
    T(n) = SUM_{i=1}^{n} floor(n/i)  =  n*H(n)  =  Θ(n log n)

    Para i fijo, j da floor(n/i) pasos. Sumando sobre i:
      T(n) <= n * SUM 1/i = n*H(n) <= n*(ln n + 1)  =>  O(n log n)
      T(n) >= n*H(n) - n  = Ω(n log n)
    H(n) = Θ(log n) es el factor que eleva la complejidad a n log n.
*/
void algorithm_A(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i)
            count++;
}


/*
    PROBLEMA 2 — Región Triangular
    T(n) = SUM_{i=1}^{n} (n-i+1) = SUM_{k=1}^{n} k = n(n+1)/2 = Θ(n^2)
*/
void algorithm_B(int n) {
    int count = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n - i + 1; ++j)
            count++;
}


/*
    PROBLEMA 3 — Algoritmo Iterativo
    T(n) = SUM_{k=1}^{floor(log n)} floor(n/2^k)  =  Θ(n)

    Cota superior (serie geométrica):
      SUM_{k=1}^{inf} n/2^k  =  n  =>  O(n)
    Cota inferior (primer término):
      T(n) >= floor(n/2) = Ω(n)

    Inducción: SUM_{k=0}^{floor(log n)} n/2^k = 2n*(1 - 1/2^{m+1}) < 2n  ✓
*/
void algorithm_C(int n) {
    int i = n;
    while (i > 1) {
        i = i / 2;
        for (int j = 0; j < i; ++j) { /* operacion constante */ }
    }
}


/*
    PROBLEMA 4 — Bucles Dependientes
    T(n) = SUM_{i=1}^{n} ceil(log2 i)  =  Θ(n log n)

    Para i fijo: k se duplica hasta k >= i => ceil(log2 i) pasos.
      log2(n!) <= T(n) <= log2(n!) + n
      log(n!) = Θ(n log n)  [Stirling]  =>  T(n) = Θ(n log n)
*/
void algorithm_D(int n) {
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        int k = 1;
        while (k < i) { count++; k *= 2; }
    }
}


/*
    PROBLEMA 5 — Condiciones Dependientes
    T(n) = Θ(n^2)

    Bucle interno: i iteraciones para cada i  =>  SUM i = n(n+1)/2.
    Condición (i+j)%2==0 cuando i,j tienen la misma paridad:
      i par:   i/2 veces  |  i impar: (i+1)/2 veces
      C(n) = n(n+2)/4  (n par)  o  (n+1)^2/4  (n impar)  =>  Θ(n^2)

    Big-Θ: T(n) = Θ(n^2)  (el doble bucle es la parte dominante)
    Big-O: T(n) <= SUM_{i=1}^{n} i = n(n+1)/2 <= n^2  =>  O(n^2)
*/
void algorithm_E(int n) {
    int count = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            if ((i + j) % 2 == 0) count++;
}


/*
    PROBLEMA 6 — Recursión con División
    T(n) = T(n/3) + c,  T(1) = Θ(1)  =>  T(n) = Θ(log n)

    Expansión: T(n) = T(n/3^k) + k*c
    Caso base n/3^k = 1  =>  k = ceil(log3 n)
      T(n) = Θ(1) + c*ceil(log3 n) = Θ(log n)

    Profundidad máxima: D(n) = ceil(log3 n)
*/
int R(int n) {
    if (n <= 1) return 1;
    return R(n / 3) + 1;
}


/*
    PROBLEMA 7 — Recursión con Trabajo Lineal
    T(n) = n*T(n/2) + cn,  T(1) = Θ(1)
    => T(n) = Θ( n^{(log2(n)+1)/2} )

    Nota: a = n depende del input => Teorema Maestro NO aplica.

    Expansión (n = 2^m): el factor que multiplica T(n/2^k) es
      PROD_{j=0}^{k-1} n/2^j  =  n^k / 2^{k(k-1)/2}

    En k = log2(n) = m:
      n^m / 2^{m(m-1)/2}  =  2^{m^2} / 2^{(m^2-m)/2}
                           =  2^{(m^2+m)/2}
                           =  n^{(log2(n)+1)/2}

    Función superpolinomial y subexponencial.
*/
int S(int n) {
    if (n <= 1) return 1;
    int sum = 0;
    for (int i = 0; i < n; ++i) sum += S(n / 2);
    return sum;
}


/*
    RESUMEN
    P1: algorithm_A  =>  Θ(n log n)
    P2: algorithm_B  =>  Θ(n^2)
    P3: algorithm_C  =>  Θ(n)
    P4: algorithm_D  =>  Θ(n log n)
    P5: algorithm_E  =>  Θ(n^2)
    P6: R            =>  Θ(log n)
    P7: S            =>  Θ( n^{(log2(n)+1)/2} )
*/
int main() {
    int n = 100, count;

    count = 0;
    for (int i = 1; i <= n; i++) for (int j = i; j <= n; j += i) count++;
    cout << "A: " << count << "  esperado~n*ln(n)=" << (int)(n*log(n)) << endl;

    count = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n-i+1; ++j) count++;
    cout << "B: " << count << "  n*(n+1)/2=" << n*(n+1)/2 << endl;

    count = 0;
    { int i = n; while (i > 1) { i /= 2; for (int j = 0; j < i; ++j) count++; } }
    cout << "C: " << count << "  ~n=" << n << endl;

    count = 0;
    for (int i = 1; i <= n; ++i) { int k=1; while (k<i) { count++; k*=2; } }
    cout << "D: " << count << "  ~n*log2(n)=" << (int)(n*log2(n)) << endl;

    count = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= i; ++j) if ((i+j)%2==0) count++;
    cout << "E: " << count << "  n*(n+2)/4=" << n*(n+2)/4 << endl;

    return 0;
}