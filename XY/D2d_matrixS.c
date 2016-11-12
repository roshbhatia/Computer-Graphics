
#include <D2d_matrix.h>
#include <math.h>

/*

 ( x')          (x)
 ( y')  =   M * (y)
 ( 1 )          (1)

instead of (x',y',1) = (x,y,1) * M

*/


int D2d_print_mat (double a[3][3])
{
  int r,c ;
  for (r = 0 ; r < 3 ; r++ ) {
      for (c = 0 ; c < 3 ; c++ ) {
           printf(" %12.4lf ",a[r][c]) ;
      }
      printf("\n") ;
  }

  return 1 ;
}

int D2d_copy_mat (double a[3][3], double b[3][3])
// a = b
{
  int r,c ;
  for (r = 0 ; r < 3 ; r++ ) {
      for (c = 0 ; c < 3 ; c++ ) {
           a[r][c] = b[r][c] ;
      }
  }

  return 1 ;
}

int D2d_mat_mult(double res[3][3], double a[3][3], double b[3][3]){
  int i, j, k;
  double total;
  double temp [3][3];
  for (i = 0; i < 3; i ++) {
    for (j = 0; j < 3; j ++) {
      total = 0;
      for (k = 0; k < 3; k ++) {		
      	total += a[j][k] * b[k][i];
      }
      temp[j][i] = total;
    }
  }
  D2d_copy_mat(res,temp);
  return 1;
}

int D2d_make_identity (double a[3][3])
// a = I
{
  int r,c ;
  for (r = 0 ; r < 3 ; r++ ) {
      for (c = 0 ; c < 3 ; c++ ) {
           if (r == c) a[r][c] = 1.0 ;
               else    a[r][c] = 0.0 ;
      }
  }

  return 1 ;
}

int D2d_translate (double a[3][3], double b[3][3], double dx, double dy)
// a = translation*a
// b = b*translation_inverse
{
  double temp[3][3];

  D2d_make_identity(temp);

  temp[0][2] = dx;
  temp[1][2] = dy;
  D2d_mat_mult(a,temp,a);

  temp[0][2] = -dx;
  temp[1][2] = -dy;
  D2d_mat_mult(b,b,temp);

  return 1;
}


int D2d_scale(double a[3][3], double b[3][3], double sx, double sy){

  double temp[3][3];

  D2d_make_identity(temp);

  temp[0][0] = sx;
  temp[1][1] = sy;

  D2d_mat_mult(a,temp,a);

  temp[0][0] = 1/sx;
  temp[1][1] = 1/sy;

  D2d_mat_mult(b,temp,b);

  return 1;

}


int D2d_rotate(double a[3][3], double b[3][3], double radians){
  double temp[3][3];

  D2d_make_identity(temp);

  temp[0][0] = cos(radians);
  temp[0][1] = - sin(radians);
  temp[1][0] = sin (radians);
  temp[1][1] = cos(radians);

  D2d_mat_mult(a,temp,a);

  temp[0][0] = 1/cos(radians);
  temp[0][1] = 1/( - sin(radians));
  temp[1][0] = 1/sin (radians);
  temp[1][1] = 1/cos(radians);

  D2d_mat_mult(b,temp,b);

  return 1;

}


int D2d_negate_x(double a[3][3], double b[3][3]){
  double temp[3][3];

  D2d_make_identity(temp);

  temp[0][0] = 1;
  temp[1][1] = -1;
  temp[2][2] = 1;

  D2d_mat_mult(a,temp,a);

  D2d_mat_mult(b,temp,b);

  return 1;

}


int D2d_negate_y(double a[3][3], double b[3][3]){

  double temp[3][3];

  D2d_make_identity(temp);

  temp[0][0] = -1;
  temp[1][1] = 1;
  temp[2][2] = 1;

  D2d_mat_mult(a,temp,a);

  D2d_mat_mult(b,temp,b);

  return 1;
}


int D2d_mat_mult_points(double *X, double *Y, double m[3][3], double *x, double *y, int numpoints){
  int i, j, k;
  double tx, ty;

  for (i = 0; i < numpoints; i++){
   j = x[i];
   X[i] = m[0][0]* x[i] + m[0][1] * y[i] + m[0][2];
   Y[i] = m[1][0] * x[i] + m[1][1] * y[i]+ m[1][2];
  }
  return 1;
}
