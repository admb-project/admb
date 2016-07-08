/*
 * $Id$
 *
 * Authors: Anders Nielsen <anders@nielsensweb.org>
 */
/**
 * \file
 * Inverse logit function.
 */
#include <fvar.hpp>

/**
 * Inverse logit function
 */
dvariable invlogit(dvariable x){
  return 1/(1+exp(-x));
} 
