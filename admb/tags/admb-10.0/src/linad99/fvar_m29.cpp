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
 dvariable mean(_CONST dvar_matrix& m)
 {
   dvariable tmp;
   tmp=sum(m)/double(size_count(m));
   return tmp;
 }
