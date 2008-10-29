#if !defined(__ADPVM__)
#  define __ADPVM__
void adpvm_pack_number_derivative(void);
void adpvm_send_derivatives(void);
void adpvm_recv(int id,int n);
void adpvm_receive_derivatives(void);
void adpvm_send(int id,int n);
void adpvm_unpack_vector_derivatives(void);
void initialize_pvm_buffer(void);
void  adpvm_end_receive();
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
    
extern "C" {
typedef 
  __declspec(dllexport) 
  int (*ADPVM_SETOPT )(int,int);

typedef 
  __declspec(dllexport) 
  int (*ADPVM_RECV)(int,int);

typedef 
  __declspec(dllexport) 
  int (*ADPVM_CATCHOUT)(FILE*);

typedef 
  __declspec(dllexport) 
  int (*ADPVM_SEND)(int,int);

typedef 
  __declspec(dllexport) 
  int (*ADPVM_CONFIG )(int*,int*,struct pvmhostinfo **);

typedef 
  __declspec(dllexport) 
  int (*ADPVM_SPAWN )(char *,char **,int,char *,int,int *);

typedef 
  __declspec(dllexport) 
  int (*ADPVM_PARENT) (void);

typedef 
  __declspec(dllexport) 
  int (*ADPVM_INITSEND) (int);

typedef 
  __declspec(dllexport) 
  int (*ADPVM_UPKDOUBLE) (double*,int,int);

typedef 
  __declspec(dllexport) 
  int (*ADPVM_PKINT) (int*,int,int);

typedef 
  __declspec(dllexport) 
  int (*ADPVM_PKSTR) (char*);

typedef 
  __declspec(dllexport) 
  int (*ADPVM_UPKSTR) (char*);

typedef 
  __declspec(dllexport) 
  int (*ADPVM_PKDOUBLE) (double*,int,int);

typedef 
  __declspec(dllexport) 
  int (*ADPVM_UPKINT) (int*,int,int);


extern ADPVM_PARENT ppvm_parent;
extern ADPVM_SEND ppvm_send;
extern ADPVM_RECV ppvm_recv;
extern ADPVM_PKINT ppvm_pkint;
extern ADPVM_PKSTR ppvm_pkstr;
extern ADPVM_UPKSTR ppvm_upkstr;
extern ADPVM_PKDOUBLE ppvm_pkdouble;
extern ADPVM_UPKINT ppvm_upkint;
extern ADPVM_UPKDOUBLE ppvm_upkdouble;
extern ADPVM_SETOPT ppvm_setopt;
extern ADPVM_CONFIG ppvm_config;
extern ADPVM_SPAWN ppvm_spawn;
extern ADPVM_INITSEND ppvm_initsend;
extern ADPVM_CATCHOUT ppvm_catchout;

}
int load_adpvm_library(void);

void send_dv3_to_master(const dvar3_array& v);
#endif
