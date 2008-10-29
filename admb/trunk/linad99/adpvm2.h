#if defined(USE_ADPVM)

#if !defined(__ADPVM2__)
#  define __ADPVM2__

#include <admodel.h>

#if defined(__cplusplus)  
//  extern "C" {
#  endif
#if defined(__BORLANDC__) 
#  if !defined(__linux__)
#   include <pvm3bor.h>
#   include <pvm3.h>
#  endif
#else
#  include <pvm3.h>
#endif
#if defined(__cplusplus)  
//}
#endif

#if defined(WIN32)  && !defined(__linux__)
#  include <windows.h>
#endif


int adpvm_initsend( int mode);
int adpvm_recv( int id,int n );
void adpvm_pack_number_derivative(void);
void adpvm_send_derivatives(void);
void adpvm_receive_derivatives(void);
void adpvm_send(int id,int n);
void adpvm_unpack_vector_derivatives(void);
void initialize_pvm_buffer(void);
void  adpvm_end_receive(void);
void  pvm_end_receive(void);
void adpvm_unpack_number_derivative(void);
void adpvm_pack_vector_derivatives(void);

void pvm_pack(const prevariable& _v);
void pvm_pack(const dvar_vector& _v);
void pvm_pack(const dvar_matrix & _m);
void pvm_pack(const dvar3_array & _m);
void pvm_pack(const dvar4_array & _m);
void pvm_pack(const dvar5_array & _m);

void pvm_unpack(const int& _v);
void pvm_unpack(const prevariable& _v);
void pvm_unpack(const dvar_vector& _v);
void pvm_unpack(const dvar_matrix & _m);
void pvm_unpack(const dvar3_array & _m);
void pvm_unpack(const dvar4_array & _m);
void pvm_unpack(const dvar5_array & _m);

void pvm_pack(double v);
void pvm_pack(const dvector& _v);
void pvm_pack(const dmatrix & _m);
void pvm_pack(const d3_array & _m);
void pvm_pack(const d4_array & _m);
void pvm_pack(const d5_array & _m);

void pvm_unpack(const double& _v);
void pvm_unpack(const dvector& _v);
void pvm_unpack(const dmatrix & _m);
void pvm_unpack(const d3_array & _m);
void pvm_unpack(const d4_array & _m);
void pvm_unpack(const d5_array & _m);
    
void pvm_pack(int v);
void pvm_pack(const ivector& _v);
void pvm_pack(const imatrix & _m);
void pvm_pack(const i3_array & _m);
//void pvm_pack(const i4_array & _m);
//void pvm_pack(const i5_array & _m);

void pvm_unpack(const int& _v);
void pvm_unpack(const ivector& _v);
void pvm_unpack(const imatrix & _m);
void pvm_unpack(const i3_array & _m);
//void pvm_unpack(const i4_array & _m);
//void pvm_unpack(const i5_array & _m);
    
void adpvm_pack(const prevariable& _v);
void adpvm_pack(const dvar_vector& _v);
void adpvm_pack(const dvar_matrix & _m);
void adpvm_pack(const dvar3_array & _m);
void adpvm_pack(const dvar4_array & _m);
void adpvm_pack(const dvar5_array & _m);

void adpvm_unpack(const int& _v);
void adpvm_unpack(const prevariable& _v);
void adpvm_unpack(const dvar_vector& _v);
void adpvm_unpack(const dvar_matrix & _m);
void adpvm_unpack(const dvar3_array & _m);
void adpvm_unpack(const dvar4_array & _m);
void adpvm_unpack(const dvar5_array & _m);

void adpvm_pack(double v);
void adpvm_pack(const dvector& _v);
void adpvm_pack(const dmatrix & _m);
void adpvm_pack(const d3_array & _m);
void adpvm_pack(const d4_array & _m);
void adpvm_pack(const d5_array & _m);

void adpvm_unpack(const double& _v);
void adpvm_unpack(const dvector& _v);
void adpvm_unpack(const dmatrix & _m);
void adpvm_unpack(const d3_array & _m);
void adpvm_unpack(const d4_array & _m);
void adpvm_unpack(const d5_array & _m);
    
void adpvm_pack(int v);
void adpvm_pack(const ivector& _v);
void adpvm_pack(const imatrix & _m);
void adpvm_pack(const i3_array & _m);
//void adpvm_pack(const i4_array & _m);
//void adpvm_pack(const i5_array & _m);

void adpvm_unpack(const int& _v);
void adpvm_unpack(const ivector& _v);
void adpvm_unpack(const imatrix & _m);
void adpvm_unpack(const i3_array & _m);
#if defined(linux)
#  define __declspec(dllexport) 
#endif

int load_adpvm_library(void);


int adpvm_slave_vinitsend(int mode);
  
int adpvm_slave_cinitsend(int mode);
  
void adpvm_slave_vsend(int ptid);

void adpvm_slave_csend(int ptid);

int adpvm_slave_vrecv(int ptid);

int adpvm_slave_crecv(int ptid);

int adpvm_master_vinitsend(int mode);

int adpvm_master_cinitsend(int mode);

void adpvm_master_csend(int id);

void adpvm_master_vsend(int id);

int adpvm_master_vrecv(int id);

int adpvm_master_crecv(int id) ;

void  adpvm_master_end_vreceive(void);

void  adpvm_slave_end_vreceive(void);

void  adpvm_master_end_creceive(void);

void  adpvm_slave_end_creceive(void);

void adpvm_unpack(char * v,int n);

void adpvm_pack(char * v,int n);

#endif
#endif  // #if defined(USE_ADPVM)
