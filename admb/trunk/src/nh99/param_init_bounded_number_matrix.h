#ifndef __param_init_bounded_number_matrix_h__
#define __param_init_bounded_number_matrix_h__
#include "admodel.h"

/**
 *
 */
class param_init_bounded_number_matrix
{
public:
  param_init_bounded_number_matrix();
  param_init_bounded_number_matrix(const param_init_bounded_number_matrix&);
  virtual ~param_init_bounded_number_matrix()
  {
    deallocate();
  }
public:
  /**
   *
   */
  void allocate(int rowmin, int rowmax, 
                int colmin, int colmax, 
                const double_index_type& bmin, const double_index_type& bmax, 
                const char* s);
  /**
   *
   */
  void allocate(int rowmin, int rowmax, 
                int colmin, int colmax, 
                const double_index_type& bmin, const double_index_type& bmax, 
                const index_type& phase_start,
                const char* s);
  /**
   *
   */
  void set_scalefactor(const double scalefactor);
  /**
   *
   */
  void set_scalefactor(const dmatrix& scalefactor);
  /**
   *
   */
  dmatrix get_scalefactor() const;
  /**
   *
   */
  param_init_bounded_number_vector& operator[](const int i) const;
  /**
   *
   */
  param_init_bounded_number_vector& operator()(const int i) const;
  /**
   *
   */
  param_init_bounded_number& operator()(const int i, const int j) const;
  /**
   *
   */
  bool allocated() const { return v != NULL; }
  /**
   *
   */
  int indexmin() const { return index_min; }
  /**
   *
   */
  int indexmax() const { return index_max; }
private:
  /**
   *
   */
  void deallocate();
private:
  param_init_bounded_number_vector* v;
  int index_min;
  int index_max;
/*
  void set_initial_value(const double_index_type& it);

  double_index_type* it;
*/
};
#endif
