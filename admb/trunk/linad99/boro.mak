







CC=bcc32



.cpp.obn : 

  $(CC) -4 -H -Hc -c -f -v -W -RT -o$*.obn $<



.c.obn : 

  $(CC) -4 -H -Hc -c -f -Ox -W -o$*.obn $<



#		*List Macros*



t.exe: mod_hess.obn mod_sd.obn model.obn model10.obn model2.obn model3.obn \

   fmm_disp.obn model4.obn model5.obn model6.obn model7.obn model8.obn model9.obn \

   t.obn newfmin.obn

	tlink32 /Tpe /v @parfx1.rsp 



