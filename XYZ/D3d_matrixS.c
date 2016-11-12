
#include <D3d_matrix.h>
#include <math.h>

/*

 ( x')          (x)
 ( y')  =   M * (y)
 ( 1 )          (1)

instead of (x',y',1) = (x,y,1) * M

*/


int D3d_print_mat (double a[4][4])
{
  int r,c ;
  for (r = 0 ; r < 4 ; r++ ) {
      for (c = 0 ; c < 4 ; c++ ) {
           printf(" %12.4lf ",a[r][c]) ;
      }
      printf("\n") ;
  }

  return 1 ;
}

int D3d_copy_mat (double a[4][4], double b[4][4])
// a = b
{
  int r,c ;
  for (r = 0 ; r < 4 ; r++ ) {
      for (c = 0 ; c < 4 ; c++ ) {
           a[r][c] = b[r][c] ;
      }
  }

  return 1 ;
}

int D3d_mat_mult(double res[4][4], double a[4][4], double b[4][4]){
  int i, j, k;
  double total;
  double temp [4][4];
  for (i = 0; i < 4; i ++) {
    for (j = 0; j < 4; j ++) {
      total = 0;
      for (k = 0; k < 4; k ++) {		
      	total += a[j][k] * b[k][i];
      }
      temp[j][i] = total;
    }
  }
  D3d_copy_mat(res,temp);
  return 1;
}

int D3d_make_identity (double a[4][4])
// a = I
{
  int r,c ;
  for (r = 0 ; r < 4 ; r++ ) {
      for (c = 0 ; c < 4 ; c++ ) {
           if (r == c) a[r][c] = 1.0 ;
               else    a[r][c] = 0.0 ;
      }
  }

  return 1 ;
}

int D3d_translate (double a[4][4], double b[4][4], double dx, double dy, double dz)
// a = translation*a
// b = b*translation_inverse
{
  double temp[4][4];

  D3d_make_identity(temp);

  temp[0][3] = dx;
  temp[1][3] = dy;
  temp[2][3] = dz;
  D3d_mat_mult(a,temp,a);

  temp[0][3] = -dx;
  temp[1][3] = -dy;
  temp[2][3] = -dz;
  D3d_mat_mult(b,b,temp);

  return 1;
}


int D3d_scale(double a[4][4], double b[4][4], double sx, double sy, double sz){

  double temp[4][4];

  D3d_make_identity(temp);

  temp[0][0] = sx;
  temp[1][1] = sy;
  temp[2][2] = sz;

  D3d_mat_mult(a,temp,a);

  temp[0][0] = 1/sx;
  temp[1][1] = 1/sy;
  temp[2][2] = 1/sz;


  D3d_mat_mult(b,temp,b);

  return 1;

}

int D3d_rotateX(double a[4][4], double b[4][4], double radians){
  double temp[4][4];

  D3d_make_identity(temp);

  temp[0][0] = 1;
  temp[0][1] = 0;
  temp[0][2] = 0;
  temp[0][3] = 0;
  temp[1][0] = 0;
  temp[1][1] = cos(radians);
  temp[1][2] = - sin (radians);
  temp[1][3] = 0;
  temp[2][0] = 0;
  temp[2][1] = sin (radians);
  temp[2][2] = cos(radians);
  temp[2][3] = 0;
  temp[3][0] = 0;
  temp[3][1] = 0;
  temp[3][2] = 0;
  temp[3][3] = 1;

  D3d_mat_mult(a,temp,a);

  temp[0][0] = 1;
  temp[0][1] = 0;
  temp[0][2] = 0;
  temp[0][3] = 0;
  temp[1][0] = 0;
  temp[1][1] = cos(radians);
  temp[1][2] = (- sin (radians));
  temp[1][3] = 0;
  temp[2][0] = 0;
  temp[2][1] = sin (radians);
  temp[2][2] = cos(radians);
  temp[2][3] = 0;
  temp[3][0] = 0;
  temp[3][1] = 0;
  temp[3][2] = 0;
  temp[3][3] = 1;

  D3d_mat_mult(b,temp,b);

  return 1;

}

int D3d_rotateY(double a[4][4], double b[4][4], double radians){
  double temp[4][4];

  D3d_make_identity(temp);

  temp[0][0] = cos(radians);
  temp[0][1] = 0;
  temp[0][2] = sin(radians);
  temp[0][3] = 0;
  temp[1][0] = 0;
  temp[1][1] = 1;
  temp[1][2] = 0;
  temp[1][3] = 0;
  temp[2][0] = - sin(radians);
  temp[2][1] = 0;
  temp[2][2] = cos (radians);
  temp[2][3] = 0;
  temp[3][0] = 0;
  temp[3][1] = 0;
  temp[3][2] = 0;
  temp[3][3] = 1;

  D3d_mat_mult(a,temp,a);

  temp[0][0] = cos(radians);
  temp[0][1] = 0;
  temp[0][2] = sin(radians);
  temp[0][3] = 0;
  temp[1][0] = 0;
  temp[1][1] = 1;
  temp[1][2] = 0;
  temp[1][3] = 0;
  temp[2][0] = - sin(radians);
  temp[2][1] = 0;
  temp[2][2] = cos (radians);
  temp[2][3] = 0;
  temp[3][0] = 0;
  temp[3][1] = 0;
  temp[3][2] = 0;
  temp[3][3] = 1;

  D3d_mat_mult(b,temp,b);

  return 1;

}


int D3d_rotateZ(double a[4][4], double b[4][4], double radians){
  double temp[4][4];

  D3d_make_identity(temp);

  temp[0][0] = cos(radians);
  temp[0][1] = - sin(radians);
  temp[0][2] = 0;
  temp[0][3] = 0;
  temp[1][0] = sin(radians);
  temp[1][1] = cos(radians);
  temp[1][2] = 0;
  temp[1][3] = 0;
  temp[2][0] = 0;
  temp[2][1] = 0;
  temp[2][2] = 1;
  temp[2][3] = 0;
  temp[3][0] = 0;
  temp[3][1] = 0;
  temp[3][2] = 0;
  temp[3][3] = 1;

  D3d_mat_mult(a,temp,a);

  temp[0][0] = cos(radians);
  temp[0][1] =  (- sin(radians));
  temp[0][2] = 0;
  temp[0][3] = 0;
  temp[1][0] = sin(radians);
  temp[1][1] = cos(radians);
  temp[1][2] = 0;
  temp[1][3] = 0;
  temp[2][0] = 0;
  temp[2][1] = 0;
  temp[2][2] = 1;
  temp[2][3] = 0;
  temp[3][0] = 0;
  temp[3][1] = 0;
  temp[3][2] = 0;
  temp[3][3] = 1;

  D3d_mat_mult(b,temp,b);

  return 1;

}




int D3d_negate_x(double a[4][4], double b[4][4]){
  double temp[4][4];

  D3d_make_identity(temp);

  temp[0][0] = -1;
  temp[1][1] = 1;
  temp[2][2] = 1;
  temp[3][3] = 1;
  

  D3d_mat_mult(a,temp,a);

  D3d_mat_mult(b,temp,b);

  return 1;

}


int D3d_negate_y(double a[4][4], double b[4][4]){

  double temp[4][4];

  D3d_make_identity(temp);

  temp[0][0] = 1;
  temp[1][1] = -1;
  temp[2][2] = 1;
  temp[3][3] = 1;

  D3d_mat_mult(a,temp,a);

  D3d_mat_mult(b,temp,b);

  return 1;
}


int D3d_negate_z(double a[4][4], double b[4][4]){

  double temp[4][4];

  D3d_make_identity(temp);

  temp[0][0] = 1;
  temp[1][1] = 1;
  temp[2][2] = -1;
  temp[3][3] = 1;

  D3d_mat_mult(a,temp,a);

  D3d_mat_mult(b,temp,b);

  return 1;
}


int D3d_mat_mult_points(double *X, double *Y, double *Z, double m[4][4], double *x, double *y, double *z, int numpoints){
  int i, j, k; 

  double t1, t2;

  for (i = 0; i < numpoints; i++){
   j = x[i];

   t1 = m[0][0]* x[i] + m[0][1] * y[i] + m[0][2] * z[i] + m[0][3];
   t2 = m[1][0] * x[i] + m[1][1] * y[i] + m[1][2] * z[i] + m[1][3];
   Z[i] = m[2][0] * x[i] + m[2][1] * y[i]+ m[2][2] * z[i] + m[2][3];
   X[i] = t1;
   Y[i] = t2;
  
  }
  return 1;
}
