#include <FPT.h>
#include <D3d_matrix.h>
#include <math.h>


//Lifted from Jeff's qsort_thing_test.c
typedef
struct {
  int objnum ;
  int polynum ;
  double dist ;
}
THING ;

int numobjects;
int numpoints[10];
int numpolys[10];
int psize[10][2000];
double x[10][10000], y[10][10000],z[10][10000], red[10][10000], grn[10][10000], blu[10][10000], xnewarray[10][10000], ynewarray[10][10000], znewarray [10][10000];
double xaverage [10],yaverage[10],zaverage[10];
int con[10][10000][20];
double swidth, sheight;
double xbar[10][10000];
double ybar[10][10000];
THING allpolys[1000000];
int allpolyslength;
int totalpolys;



double distance (double x, double y,double z){
	return (sqrt ((x*x)+(y*y)+(z*z)));
}

//Lifted from Jeff's qsort_thing_test.c, used in qsort later on
//changed t to where it returns sorted list in reverse order
int compare (const void *p, const void *q)
{
  THING *a, *b ;

  a = (THING*)p ;
  b = (THING*)q ;

  if  (((*a).dist) < ((*b).dist)) return 1 ;
  else if (((*a).dist) > ((*b).dist)) return -1 ;
  else return 0 ;
}

void init_array()
{
  int i,j,l;
  allpolyslength=0;
  for (i = 0; i <= numobjects;i++){
	for (j = 0; j <= numpolys[i]; j++){
			allpolys[allpolyslength].objnum = i;
			allpolys[allpolyslength].polynum = psize[i][j];
			allpolys[allpolyslength].dist = z[i][con[i][j][0]];
			//printf("%d %d %lf\n\n",allpolys[allpolyslength].objnum, allpolys[allpolyslength].polynum, allpolys[allpolyslength].dist);
			//printf("%d\n", allpolyslength);
			allpolyslength++;
        }
  }
  qsort (allpolys, allpolyslength , sizeof(THING),compare);
}


void averagepoint (int onum){
   double xsum = 0;
   double ysum = 0;
   double zsum = 0;
   int i;
   for (i = 0; i <= numpoints[onum]; i++){
	xsum += x[onum][i];
 	ysum += y[onum][i];
	zsum += z[onum][i];
   }

   xaverage[onum] = xsum/numpoints[onum];
   yaverage[onum] = ysum/numpoints[onum];
   zaverage[onum] = zsum/numpoints[onum];

}

void readObject(FILE *f, int onum)
{
  int i, k;

  fscanf(f, "%d", &numpoints[onum]);
 // printf ("\n\n%d", numpoints[onum]);

  for(i = 0; i < numpoints[onum]; i++){
    fscanf(f, "%lf %lf %lf", &x[onum][i], &y[onum][i], &z[onum][i]);
   // printf ("\n\n %lf %lf %lf", x[onum][i], y[onum][i], z[onum][i]);
  }

  fscanf(f, "%d", &numpolys[onum]);
 // printf("\n%d", numpolys[onum]);

  for(i = 0; i < numpolys[onum]; i++){
    fscanf(f, "%d", &psize[onum][i]);
    //printf("POLYSIZE:%d", psize[onum][i]);
    for(k = 0; k < psize[onum][i]; k++){
      fscanf(f, "%d", &con[onum][i][k]);
     // printf("\n\n%d", con[onum][i][k]);
    }
  }
}



void drawObject(int onum){

  int i;
  int j, a;
  j = 0;
  int k = 0;
  init_array();

  for(i = 0; i < numpolys[onum]; i++){
    for(j = 0; j <= totalpolys; j++){
	     a = con[onum][i][j];
	      xbar[onum][j] = ((300/tan(1.047)*(x[onum][a]/z[onum][a])) + 300);
	       ybar[onum][j] = ((300/tan(1.047)*(y[onum][a]/z[onum][a])) + 300);
  	k++;
    }
   //Filled shapes are red
   G_rgb(1,0,0);
   G_fill_polygon(xbar[onum],ybar[onum],allpolys[k].polynum);
   //Outline is black
   G_rgb(0,0,0);
   G_polygon(xbar[onum],ybar[onum],allpolys[k].polynum);


  }
}

void drawObjectWireFrame(int onum){
  G_rgb(0,1,0);
  int i;
  int j, a;
  j = 0;
  int k = 0;
  init_array();

  for(i = 0; i < numpolys[onum]; i++){
    for(j = 0; j < psize[onum][i]; j++){
	a = con[onum][i][j];
	xbar[onum][j] = ((300/tan(1.047)*(x[onum][a]/z[onum][a])) + 300);
	ybar[onum][j] = ((300/tan(1.047)*(y[onum][a]/z[onum][a])) + 300);
    }

  	G_polygon(xbar[onum],ybar[onum],psize[onum][i]);
  }
}

int main(int argc, char *argv[])
{
  FILE *f ;
  int onum = 0;
  printf ("\n\nCOMMANDS:\n\nUSE Q TO QUIT\nNUMBER KEYS TO SELECT OBJECT NUMBER\nARROW KEYS TO TRANSLATE FORWARD, BACK, LEFT, AND RIGHT\nSPACE TO ROTATE RIGHT IN X AXIS/V TO ROTATE UP IN Y AXIS/B TO ROTATE IN Z AXIS\nW TO TOGGLE WIREFRAME\n\n");

   //Reads multiple files from command line
   int numofobjects = argc-1;
   int t1;
   for (t1 = 0; t1 < numofobjects; t1++){
	f = fopen (argv[t1+1], "r");
	readObject(f, t1);
   }


   //Identity Matricies and initial translation
   double temp[4][4];
   double temp2[4][4];

  //centers all objects
   for (onum = 0; onum <= numofobjects; onum++){
	    D3d_make_identity(temp);
	     D3d_make_identity(temp2);
	    averagepoint(onum);
	    D3d_translate(temp,temp2,xaverage[onum],yaverage[onum],zaverage[onum] + 1.5);
	     D3d_mat_mult_points(x[onum], y[onum],z[onum], temp, x[onum], y[onum],z[onum], numpoints[onum]);
   }

   //sets onum back to 0 for initial drawing
   onum = 0;



   //Initial drawing of object
   G_init_graphics(600, 600);
   G_rgb(0,0,0);
   G_fill_rectangle(0,0,600,600);
   drawObject(onum);

   int key;
   int wireframeTrue = 0;

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


	//Translate functions, uses arrow keys for forward,back,left,right and z,x for up,down
	if (key == 65362){
		D3d_make_identity(temp);
		D3d_make_identity(temp2);
		averagepoint(onum);
	        D3d_translate(temp,temp2,0,0,.01);
		D3d_mat_mult_points(x[onum], y[onum],z[onum], temp, x[onum], y[onum],z[onum], numpoints[onum]);
	} // UP
	if (key == 65364){
		D3d_make_identity(temp);
		D3d_make_identity(temp2);
		averagepoint(onum);
	        D3d_translate(temp,temp2,0,0,- .01);
		D3d_mat_mult_points(x[onum], y[onum],z[onum], temp, x[onum], y[onum],z[onum], numpoints[onum]);
	} // DOWN
	if (key == 65361){
		D3d_make_identity(temp);
		D3d_make_identity(temp2);
		averagepoint(onum);
	        D3d_translate(temp,temp2,- .01,0,0);
		D3d_mat_mult_points(x[onum], y[onum],z[onum], temp, x[onum], y[onum],z[onum], numpoints[onum]);
	} // Left
	if (key == 65363){
		D3d_make_identity(temp);
		D3d_make_identity(temp2);
		averagepoint(onum);
	        D3d_translate(temp,temp2,.01,0,0);
		D3d_mat_mult_points(x[onum], y[onum],z[onum], temp, x[onum], y[onum],z[onum], numpoints[onum]);
	} // RIGHT
	if (key == 90 || key == 122){
		D3d_make_identity(temp);
		D3d_make_identity(temp2);
		averagepoint(onum);
	        D3d_translate(temp,temp2,0,.01,0);
		D3d_mat_mult_points(x[onum], y[onum],z[onum], temp, x[onum], y[onum],z[onum], numpoints[onum]);
	} // Vertical up
	if (key == 88 || key == 120){
		D3d_make_identity(temp);
		D3d_make_identity(temp2);
		averagepoint(onum);
	        D3d_translate(temp,temp2,0,- .01,0);
		D3d_mat_mult_points(x[onum], y[onum],z[onum], temp, x[onum], y[onum],z[onum], numpoints[onum]);
	} // Vertical down

	if (key == ' ') {
		D3d_make_identity(temp);
		D3d_make_identity(temp2);
  		D3d_translate(temp,temp2,-xaverage[onum],-yaverage[onum],-zaverage[onum]);
		D3d_rotateY(temp,temp2,M_PI/180);
		D3d_mat_mult_points(x[onum], y[onum],z[onum], temp, x[onum], y[onum],z[onum], numpoints[onum]);
		D3d_make_identity(temp);
		D3d_make_identity(temp2);

  		D3d_translate(temp,temp2,xaverage[onum],yaverage[onum],zaverage[onum]);
		D3d_mat_mult_points(x[onum], y[onum],z[onum], temp, x[onum], y[onum],z[onum], numpoints[onum]);
  	}//Rotates in the Y axis

	if (key == 86 || key == 118) {
		D3d_make_identity(temp);
		D3d_make_identity(temp2);
  		D3d_translate(temp,temp2,-xaverage[onum],-yaverage[onum],-zaverage[onum]);
		D3d_rotateX(temp,temp2,M_PI/180);
		D3d_mat_mult_points(x[onum], y[onum],z[onum], temp, x[onum], y[onum],z[onum], numpoints[onum]);
		D3d_make_identity(temp);
		D3d_make_identity(temp2);

  		D3d_translate(temp,temp2,xaverage[onum],yaverage[onum],zaverage[onum]);
		D3d_mat_mult_points(x[onum], y[onum],z[onum], temp, x[onum], y[onum],z[onum], numpoints[onum]);
  	}//Rotates in the X axis

	if (key == 66 || key == 98) {
		D3d_make_identity(temp);
		D3d_make_identity(temp2);
  		D3d_translate(temp,temp2,-xaverage[onum],-yaverage[onum],-zaverage[onum]);
		D3d_rotateZ(temp,temp2,M_PI/180);
		D3d_mat_mult_points(x[onum], y[onum],z[onum], temp, x[onum], y[onum],z[onum], numpoints[onum]);
		D3d_make_identity(temp);
		D3d_make_identity(temp2);

  		D3d_translate(temp,temp2,xaverage[onum],yaverage[onum],zaverage[onum]);
		D3d_mat_mult_points(x[onum], y[onum],z[onum], temp, x[onum], y[onum],z[onum], numpoints[onum]);
  	}//Rotates in the Z axis



	//clears screen and redraws object
  	G_rgb(0,0,0);
  	G_clear();
        averagepoint(onum);

	//toggles wireframe on w/W keypress, random extra stuff so I could see if the objects were rendering inside each other

        if (key == 'w'){
		if (wireframeTrue == 0){
			wireframeTrue = 1;
		}
		else{
			wireframeTrue = 0;
		}

	}

        if (wireframeTrue == 1){
		drawObjectWireFrame(onum);
	}
	else{
   		drawObject(onum);
	}
   }

   G_close();
}
