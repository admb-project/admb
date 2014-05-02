#include <admodel.h>
/**
 * Description not yet available.
 * \param
 */
class adpvm_manager
{
  adstring_array slave_names;
  adpvm_slave_args * slave_argv;
public:
  struct pvmhostinfo *hostp;
  int nhost;
  int mode;  // 1 = master 2 = slave
  int copy;
  int slave_number;
  int narch;
  imatrix id;
  int num_slave_processes;
  ivector num_per_host;
  int start_slave_processes(const ad_comm& mp);
  imatrix slave_assignments;
  adtimer tm;
  int timing_flag;
  void master_slave_variable_interface(const ad_comm& mp);
  void master_slave_variable_interface(void);
  void get_variable_values_from_master(void);
  void send_variable_values_to_slaves(void);
  adpvm_manager(int);
  ~adpvm_manager();
      int start_slave_processes_for_random_effects(const ad_comm& mp);
};

void send_dmatrix_to_slaves(const dmatrix&  x,ivector& jmin,ivector& jmax);
dvariable receive_f_from_slaves(void);
void send_x_to_slaves(const dvar_vector& x);
void send_dvector_to_slaves(const dvector& x);
void send_dvector_to_master(const dvector& x);
void send_dmatrix_to_master(const dmatrix& x);
dvar_vector get_x_from_master(void);
dvector get_dvector_from_master(void);
dmatrix get_dmatrix_from_master(void);
void send_f_to_master(const dvariable& x);
void send_int_to_master(int i);
dvar_matrix get_f_from_slaves();
d3_array get_dmatrix_from_slaves();
d3_array get_dmatrix_from_slaves(const imatrix& flags);
dmatrix get_dvector_from_slaves();
void admaster_slave_variable_interface(const ad_comm& mp);
void admaster_slave_variable_interface(void);
int get_int_from_master(void);
imatrix get_int_from_slaves(void);
void send_int_to_slaves(int  x);
void send_int_to_slaves(const ivector& x);
int check_pvm_message(int i,int j);
