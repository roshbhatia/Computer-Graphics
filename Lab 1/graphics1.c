#include <stdio.h>

int factorial (int n){
  int f, k;
  f = 1;
  for (k=1; k<=n; k++){
    f = f * k;
  }

  return f;
}

int choose (int n, int k){
  int v;
  v = factorial(n/(factorial (n-k))* factorial (k));

  return v;
}

int main(){
  int af, ai, bf, bi, ac, bc;

  af = 5;
  ai = 3;

  bf = 6;
  bi = 2;

  ac = choose (af,ai);
  printf("%d\n", ai);

  bc = choose (bf, bi);
  printf ("%d\n", bc);


}
