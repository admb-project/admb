// This is used to test the following functions:
// 
// dvector sort(_CONST dvector & v, int NSTACK)
// dvector sort(_CONST dvector & _v, BOR_CONST ivector & _index, int NSTACK)
// ivector sort(_CONST ivector & v, int NSTACK)
// ivector sort(_CONST ivector & _v, BOR_CONST ivector & _index, int NSTACK)
DATA_SECTION
  int n
 !! n=100;
 vector M(1,n)
 ivector N(1,n)
 ivector P(1,n)
 !! random_number_generator rng(177);
 !! M.fill_randn(rng);
 !! N.fill_seqadd(1,1);
 !! P.fill_seqadd(1,1);

PARAMETER_SECTION
 init_vector VM(1,n)
 !! VM=M;
 objective_function_value f

PROCEDURE_SECTION
 f=norm2(sort(value(VM),60))+square(norm2(VM));
 f+=norm2(sort(value(VM),N,60));
 f+=norm2(sort(N,P,60));
 f+=norm2(sort(P,60));
