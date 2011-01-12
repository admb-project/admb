/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
mat_shape::mat_shape(int rl,int ru,int cl,int cu)
{
  row_min=rl;
  row_max=ru;
  col_min=cl;
  col_max=cu;
  nrows=ru-rl+1;
  ncols=cu-cl+1;
  ncopies=0;
}

/**
 * Description not yet available.
 * \param
 */
void mat_shape::colshift(int min)
{
  col_max=col_max-col_min+min;
  col_min=min;
}

/**
 * Description not yet available.
 * \param
 */
void dmatrix::rowshift(int min )
{
  m = m + rowmin() - min;
  index_max+=min-index_min;
  index_min=min;
}

/**
 * Description not yet available.
 * \param
 */
void mat_shape::rowshift(int min)
{
  row_max=row_max-row_min+min;
  row_min=min;
}

/**
 * Description not yet available.
 * \param
 */
 void dmatrix::colshift( int min)
 {
   for (int i=rowmin(); i<=rowmax(); i++)
   {
     this->elem(i).shift(min);
   }
   //shape->colshift(min);
 }
