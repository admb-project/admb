c:\ss2\ss3.exe -cbs 5000000000 -gbs 50000000000 %1 %2 %3 %4
del ss3.r0*
del ss3.p0*
del ss3.b0*

%  gradient_structure::set_GRADSTACK_BUFFER_SIZE(20000000000);
%  gradient_structure::set_CMPDIF_BUFFER_SIZE(170000000);
