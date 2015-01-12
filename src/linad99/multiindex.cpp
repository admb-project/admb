/**
 * $Id$
 * 
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California
 */

#include <fvar.hpp> 
 //   class multi_index
 //   {
 //     int mind;
 //     int maxd;
 //     int depth;
 //     ivector index;
 //   public:
 //     multi_index(int min,int max,int dim);
 //     ivector& operator () (void) {return index;}
 //     void operator ++ (void);
 //     int get_depth(void) { return depth;}
 //   };
 // 
  multi_index::multi_index(int min,int max,int dim) : index(1,dim), 
    mind(min),maxd(max),depth(min)
  {
    index=min;
  }
  void multi_index::operator ++ (void)
  {
    int imin=index.indexmin();
    int imax=index.indexmax();
    index(imin)++;
    int tmpdepth=1;
    for (int i=imin;i<=imax;i++)
    {
      if (index(i)>maxd)
      {
        if (i<imax)
        {
          index(i+1)++;
        }
        index(i)=mind;
        tmpdepth=i+1;
      }
      else
      {
        break;
      }
    } 
    if (tmpdepth>depth) 
      depth =tmpdepth;
      
  }    
  int multi_index::get_offset(void) 
  {
    int imin=index.indexmin();
    int imax=index.indexmax();
    int offset=index(imin)-mind;
    int mx=min(depth,imax);
    int sz=maxd-mind+1;
    for (int i=imin+1;i<=mx;i++)
    {
#  if (__MSVC32__>=8) || defined(__SUNPRO_CC)
      offset+=int(pow(double(sz),i-imin))*(index(i)-mind);
#  else
      offset+=pow(sz,i-imin)*(index(i)-mind);
#  endif
    }
    return offset;
  }

  void multi_index::initialize(void)
  {
    index=mind;
    depth=mind;
  }
    
 
 // 
 //   void main()
 //   {
 //     multi_index mi(1,3,4);
 // 
 //     mi()=3;
 //     do
 //     {
 //       cout << mi() << "   " << mi.get_depth() << endl;
 //       ++mi;
 //     }
 //     while(mi.get_depth()<5);
 //   }
 //     
