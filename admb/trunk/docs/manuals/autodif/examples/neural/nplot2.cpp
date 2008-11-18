#include <fvar.hpp>
#include <iomanip.h>
#include <graphics.h>
#include <conio.h>

extern unsigned _stklen=20000;

void select_color(dvector& a, int& color, double& answer, const double amin);
dvector Phi(dvector& v);

void neural_plot(ivector& num_nodes, int & num_levels,
  dmatrix& x, d3_array& W, dmatrix B);

int inc = 5;

void main(int argc, char * argv[])
{
  if (argc > 1)
  {
    inc = atoi(argv[1]);
  }

  int num_levels;
  int nvar;


  ifstream infile("struct.nrl");
  infile >> num_levels;
  ivector num_nodes(1,num_levels);
  infile >> num_nodes;
  if (!infile)
  {
    cerr << " Error reading in data from file struct.nrl\n";
    exit(1);
  }
  infile.close();

  dmatrix x(1,num_levels,1,num_nodes); // these are the nodes

  ivector iv(2,num_levels);
  for (int i=2;i<=num_levels;i++)
  {
    iv(i)=num_nodes(i); // Put the desired elements of num_nodes into iv
  }
  // Now declare B
  dmatrix B(2,num_levels,1,iv);

  ivector nrows(1,num_levels-1);
  ivector ncols(1,num_levels-1);
  for (i=1;i<num_levels;i++)
  {
    nrows(i)=num_nodes(i+1);
    ncols(i)=num_nodes(i);
  }

  // Now declare W
  d3_array W(1,num_levels-1,1,nrows,1,ncols);

  ifstream infile1("weights.par");


//  nvar=nvar_calc(B,W);// calculate the number of parameters to be estimated

  infile1 >> W;
  if (!infile1)
  {
     cerr << "ERROR reading weights from file weights.par\n"; exit(1);
  }
  infile1 >> B;
  if (!infile1)
  {
     cerr << "ERROR reading bias terms from file weights.par\n"; exit(1);
  }

  //independent_variables y(1,nvar);  //make the vector of independent variables

  //yinit(W,B,y,num_levels,num_nodes);// Put the initial values into the vector
                    // of independent variables

  neural_plot(num_nodes,num_levels,x,W,B);

}

dvector Phi(dvector& v)
{
  // This squashing function maps into the interval (-1,1)
  int min=v.indexmin();
  int max=v.indexmax();
  dvector tmp(min,max);
  for (int i=min;i<=max;i++)
  {
    //tmp(i)=0.63662*atan(v(i)); //0.63662 is 2/PI maps into (-1,1)
    tmp(i)=0.31831*atan(v(i)); //0.36831 is 1/PI maps into (-.5,.5)
    // tmp(i)=0.31831*atan(v(i))+0.5; // This maps into (0,1) instead of (-1,1)
  }
  return(tmp);
}

void neural_plot(ivector& num_nodes, int & num_levels,
  dmatrix& x, d3_array& W, dmatrix B)
{
  int gmode;
  int gdriver = DETECT;
  initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
  int range = getmaxy()/2;
  double unit_size = 2;
  double unit_test = unit_size*unit_size;
  double scale = unit_size/((double)range);

  int xoffset = getmaxx()/2;
  int yoffset = getmaxy() - range;
  int color;
  int px, py;
  double xx, yy;
  double xtest, ytest;
  double answer;
  double amin = 0.0;
  #ifdef SAVE_POINTS
  ofstream rf("points.red");
  ofstream gf("points.grn");
  ofstream bf("points.blu");
  ofstream gray("points.gra");
  #endif
  for (py = - range; py <= range && !kbhit(); py+=inc)
  {
    yy = (double)py * scale;
    ytest = yy * yy;
    for (px = - range; px <= range; px+=inc)
    {
      xx = (double)px * scale;
      xtest = xx * xx;
      if ( (fabs(xtest+ytest) <= unit_test) && (px != 0) && (py != 0) )
      {
        x[1][1] = xx;
        x[1][2] = yy;
        for (int i=1;i<num_levels; i++)
        {
          x[i+1]=Phi(W[i]*x[i]+B[i+1]);
        }

        select_color(x[num_levels], color, answer,  amin);

      }
      else
        color = EGA_DARKGRAY;

      putpixel(px+xoffset, yoffset-py, color);
      #ifdef SAVE_POINTS
      if (color == EGA_LIGHTRED)
        rf << xx << " " << yy << "\n";
      else if (color == EGA_LIGHTGREEN)
        gf << xx << " " << yy << "\n";
      else if (color == EGA_LIGHTBLUE)
        bf << xx << " " << yy << "\n";
      else if (color == EGA_LIGHTGRAY)
        gray << xx << " " << yy << "\n";
      #endif
    }
  }

  #ifdef SAVE_POINTS
  rf.close();
  gf.close();
  bf.close();
  gray.close();
  #endif

  if (kbhit()) getch();

  settextjustify(CENTER_TEXT, CENTER_TEXT);
  int num_learn;
  dvector correct_response(1,num_nodes[num_levels]);

  ifstream infile("learning.smp");
  infile >> num_learn;

  for (int k=1;k<=num_learn; k++)
  {
    infile >> x[1];
    if (!infile)
    {
    	cerr << "Error reading x[1] from file learning.smp\n";
    	exit(1);
    }
    infile >> correct_response;
    if (!infile)
    {
    	cerr << "Error reading correct_response from file learning.smp\n";
    	exit(1);
    }

    px = x[1][1]/scale+xoffset;
    py = yoffset - x[1][2]/scale;

    select_color(correct_response, color, answer,  amin);

    setcolor(color);
    outtextxy(px, py, "*");
  }



  while (!kbhit()) /* do nothing */ ;

  restorecrtmode();
}

void select_color(dvector& a, int& color, double& answer, const double amin)
{
  if ( (a[1] > amin) && (a[2] < 0) && (a[3] < 0) )
  {
    answer = a[1];
    color = EGA_LIGHTRED;
  }
  else if ( (a[1] < 0) && (a[2] > amin) && (a[3] < 0) )
  {
    answer = a[2];
    color = EGA_LIGHTGREEN;
  }
  else if ( (a[1] < 0) && (a[2] < 0) && (a[3] > amin) )
  {
    answer = a[3];
    color = EGA_LIGHTBLUE;
  }
  else
  {
    answer = 0;
    color = EGA_LIGHTGRAY;
  }
}