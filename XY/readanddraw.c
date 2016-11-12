#include <FPT.h>
#include <D2d_matrix.h>
#include <math.h>

int numobjects;
int numpoints[10];
int numpolys[10];
int psize[10][2000];
double x[10][3000], y[10][3000], red[10][2000], grn[10][2000], blu[10][2000], xnewarray[10][3000], ynewarray[10][3000];
double xaverage [10],yaverage[10];
int con[10][5000][20];
double swidth, sheight;

void averagepoint (int onum){
   double xsum = 0;
   double ysum = 0;
   int i;
   for (i = 0; i <= numpoints[onum]; i++){
	xsum += x[onum][i];
 	ysum += y[onum][i];
   }

   xaverage[onum] = xsum/numpoints[onum];
   yaverage[onum] = ysum/numpoints[onum];

}

void readObject(FILE *f, int onum)
{
  int i, k;

  fscanf(f, "%d", &numpoints[onum]);

  for(i = 0; i < numpoints[onum]; i++){
    fscanf(f, "%lf %lf", &x[onum][i], &y[onum][i]);
  }

  fscanf(f, "%d", &numpolys[onum]);

  for(i = 0; i < numpolys[onum]; i++){
    fscanf(f, "%d", &psize[onum][i]);
    for(k = 0; k < psize[onum][i]; k++){
      fscanf(f, "%d", &con[onum][i][k]);
    }
  }

  for (i = 0; i < numpolys[onum]; i++){
    fscanf(f, "%lf %lf %lf", &red[onum][i], &grn[onum][i], &blu[onum][i]);
  }
}



void drawObject(int onum){
  int i;

  //Filling object
  int polysize, j, k, a;
  j = 0;
  k = 0;

  double xx[100],yy[100] ;

  for(i = 0; i < numpolys[onum]; i++){
    for(j = 0; j < psize[onum][i]; j++){
	a = con[onum][i][j];
	xx[j] = x[onum][a];
	yy[j] = y[onum][a];
    }
   G_rgb(red[onum][i], grn[onum][i], blu[onum][i]);
   G_fill_polygon(xx,yy, psize[onum][i]);
  }
}

int main(int argc, char *argv[])
{
  FILE *f ;
  int onum = 0;


   //Reads multiple files from command line
   int numofobjects = argc-1;
   int t1;
   for (t1 = 0; t1 < numofobjects; t1++){
	f = fopen (argv[t1+1], "r");
	readObject(f, t1);
   }


   //Identity Matricies and initial translation
   double temp[3][3];
   double temp2[3][3];

   //centers all objects
   for (onum = 0; onum <= numofobjects; onum++){
	D2d_make_identity(temp);
	D2d_make_identity(temp2);
	averagepoint(onum);
	D2d_translate(temp,temp2,300-xaverage[onum],300-yaverage[onum]);
	D2d_mat_mult_points(x[onum], y[onum], temp, x[onum], y[onum], numpoints[onum]);
   }

   //sets onum back to 0 for initial drawing
   onum = 0;



   //Initial drawing of object
   G_init_graphics(600, 600);
   G_rgb(0,0,0);
   G_fill_rectangle(0,0,600,600);
   drawObject(onum);

   char key;
   while (key != 'q'){
	key = G_wait_key();

	//Looks for object number
   	if (key == '0'){
		onum = 0;
	}
        if (key == '1'){
		onum = 1;
	}
   	if (key == '2'){
		onum = 2;
	}
   	if (key == '3'){
		onum = 3;
	}
   	if (key == '4'){
		onum = 4;
	}
   	if (key == '5'){
		onum = 5;
	}
   	if (key == '6'){
		onum = 6;
	}
   	if (key == '7'){
		onum = 7;
	}
   	if (key == '8'){
		onum = 8;
	}

	//Rotates right when R is capitalized and left when lowercase
	if (key == 'r'){
		D2d_make_identity(temp);
   		D2d_make_identity(temp2);
		D2d_translate(temp,temp2,300,300);
		D2d_rotate(temp,temp2,2*(M_PI)/180);
		D2d_mat_mult_points(x[onum], y[onum], temp, x[onum], y[onum], numpoints[onum]);
		D2d_make_identity(temp);
   		D2d_make_identity(temp2);
		averagepoint(onum);
  		D2d_translate(temp,temp2,300-xaverage[onum],300-yaverage[onum]);
		D2d_mat_mult_points(x[onum], y[onum], temp, x[onum], y[onum], numpoints[onum]);
	}
	if (key == 'R'){
		D2d_make_identity(temp);
   		D2d_make_identity(temp2);
		D2d_translate(temp,temp2,300,300);
		D2d_rotate(temp,temp2,-(2*(M_PI)/180));
		D2d_mat_mult_points(x[onum], y[onum], temp, x[onum], y[onum], numpoints[onum]);
		D2d_make_identity(temp);
   		D2d_make_identity(temp2);
		averagepoint(onum);
  		D2d_translate(temp,temp2,300-xaverage[onum],300-yaverage[onum]);
		D2d_mat_mult_points(x[onum], y[onum], temp, x[onum], y[onum], numpoints[onum]);
	}

        //Scales up when S is capitalized and down when lowercase
        if (key == 's'){
		D2d_make_identity(temp);
   		D2d_make_identity(temp2);
  		D2d_scale(temp,temp2,.99,.99);
		D2d_mat_mult_points(x[onum], y[onum], temp, x[onum], y[onum], numpoints[onum]);
		D2d_make_identity(temp);
   		D2d_make_identity(temp2);
	        averagepoint(onum);
  		D2d_translate(temp,temp2,300-xaverage[onum],300-yaverage[onum]);
		D2d_mat_mult_points(x[onum], y[onum], temp, x[onum], y[onum], numpoints[onum]);
	}
        if (key =='S'){
		D2d_make_identity(temp);
   		D2d_make_identity(temp2);
  		D2d_scale(temp,temp2,1.01,1.01);
		D2d_mat_mult_points(x[onum], y[onum], temp, x[onum], y[onum], numpoints[onum]);
		D2d_make_identity(temp);
   		D2d_make_identity(temp2);
	        averagepoint(onum);
  		D2d_translate(temp,temp2,300-xaverage[onum],300-yaverage[onum]);
		D2d_mat_mult_points(x[onum], y[onum], temp, x[onum], y[onum], numpoints[onum]);
	}

       if (key =='q' || key == 'Q'){
		break;
	}





	//clears screen and redraws object
  	G_rgb(0,0,0);
  	G_clear();
        averagepoint(onum);
   	drawObject(onum);
   }

   G_close();
}
