
  
  class dependent_variables_information
  {
    int max_num_dependent_variables;
    int depvar_count;
    ptr_vector grad_buffer_position;
    lvector cmpdif_buffer_position;
    lvector grad_file_position;
    lvector cmpdif_file_position;
    lvector grad_file_count;
    lvector cmpdif_file_count;
    dependent_variables_information(int ndv);
    friend class gradient_structure;
  };

