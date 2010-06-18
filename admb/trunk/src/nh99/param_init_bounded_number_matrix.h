#ifndef __param_init_bounded_number_matrix_h__
#define __param_init_bounded_number_matrix_h__

class param_init_bounded_number_matrix
{
public:
  param_init_bounded_number_matrix() {;}
  virtual ~param_init_bounded_number_matrix() {;}

/*
public:
  void set_scalefactor(double s);
  void set_scalefactor(const dvector&  s);
  dvector get_scalefactor(void);

  #if defined(OPT_LIB)
  param_init_bounded_number_vector&  operator [] (int i) { return v[i];}
  param_init_bounded_number_vector&  operator () (int i) { return v[i];}
  #else
  param_init_bounded_number_vector&  operator [] (int i);
  param_init_bounded_number_vector&  operator () (int i);
  #endif

  void allocate(int rowmin, int rowmax, int colmin, int colmax, const double_index_type& bmin, const double_index_type& bmax, const index_type& phase_start, const char* s);
  void allocate(int rowmin, int rowmax, int colmin, int colmax, const double_index_type& bmin, const double_index_type& bmax, const char* s);

  int allocated(void) { return (v!=NULL); }
  int indexmin(void) { return (index_min); }
  int indexmax(void) { return (index_max); }
  void set_initial_value(const double_index_type& it);
  void deallocate(void);

private:
  param_init_bounded_number_vector* v;
  int index_min;
  int index_max;
  double_index_type* it;
*/
};

#endif
