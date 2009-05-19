

#AUTODEPEND



#		*Translator Definitions*

CC = bcc32

TASM = TASM32

TLIB = tlib

TLINK = tlink32

#BGI = c:\BC31\BGI

MFPATH=e:\newm94a

ADPATH=h:\linad94x

ZPATH=c:\zinc\source

TPATH=e:\tools94



.cpp.obx:

	$(CC) +BCC32.CFG -H -Hc -v -RT- -x- -N  -c -vi- -w- -DDOS32PP -o$*.obx {$< }



#$(CC) -DOPT_LIB -v -c -d -ml -2 -f287 -vi- -w- -H=ZFE.SYM {$< }



#		*List Macros*



#zfe16.mak \

# $(ZPATH)\i_btcat.o32 \



EXE_dependencies =  \

 $(MFPATH)\mf16.lib \

 zfe16.mak \

 exe_srch.obx \

 mf_cursr.obx \

 mfhelp.obx \

 setopts.obx \

 fflagopt.obx \

 ffopt2.obx \

 ffopt3.obx \

 scrolls.obx \

 $(ZPATH)\d_win.obx \

 $(ZPATH)\d_text.obx \

 $(ZPATH)\z_text.obx \

 $(ZPATH)\z_help.obx \

 $(ZPATH)\d_string.obx \

 $(ZPATH)\d_win1.obx \

 $(ZPATH)\d_button.obx \

 $(ZPATH)\d_bgidsp.obx \

 $(ZPATH)\z_button.obx \

 $(ZPATH)\z_decor.obx \

 $(ADPATH)\ivector.obx \

 $(ADPATH)\imat.obx \

 $(MFPATH)\lmult_io.obx \

$(MFPATH)\lmult.obx \

 $(MFPATH)\fcon2.obx \

 $(MFPATH)\fcons.obx \

 tempfit.obx \

 modsrch.obx \

 stk2.obx \

 dmat_dsp.obx \

 lfshstat.obx \

 interact.obx \

 temphist.obx \

 fi_build.obx \

 $(MFPATH)\newmult.obx \

 $(MFPATH)\lmul_io2.obx \

 d4arr.obx \

 d3arr.obx \

 sel_form.obx \

 $(TPATH)\string3.obx \

 $(TPATH)\string4.obx \

 $(MFPATH)\mult_io.obx \

 reportw.obx \

 get_ffra.obx \

 mf_line.obx \

 in_strat.obx \

 fit_sel.obx \

 fit_sel2.obx \

 mf_help.hpp \

 error.obx \

 cpuehist.obx \

 effort.obx \

 humps.obx \

 subest.obx \

 dvect9.obx \

 biomhist.obx \

 biodynam.obx \

 recrhist.obx \

 stockhst.obx \

 globals.obx \

 catchab.obx \

 prn_wndw.obx \

 prn_scrn.obx \

 catcheff.obx \

 mf_str.obx \

 zfe.obx \

 t_scale.obx \

 results.obx \

 nextprev.obx \

 le_loop.obx \

 le_loop2.obx \

 le_loop3.obx \

 mean_co1.obx \

 systsear.obx \

 all_samp.obx \

 composit.obx \

 globinit.obx \

 getlfsh2.obx \

 zil_util.obx \

 ext_numb.obx \

 setcolor.obx \

 set_patt.obx \

 catch.obx \

 norm_sel.obx \

 mf_win.obx \

 lfsh.obx \

 logstrem.obx \

 mf_butt.obx \

 fullscr.obx \

 $(ZPATH)\z_int.obx \

 sparmenu.obx \

 mf_graph.obx \

 axes.obx \

 sample.obx \

 na.obx \

 frq_t.obx \

 ncdt_sel.obx \

 fit.obx \

 init_ser.obx \

 samp_sel.obx



#		*Explicit Rules*





zfe.exe: $(EXE_dependencies)

	$(TLINK) -s -Tpe -ax -v -S:26000 @&&|

c0x32.obj+

zfe.obx+

globals.obx +

mf_str.obx+

$(MFPATH)\newmult.obx +

$(MFPATH)\lmul_io2.obx +

$(ZPATH)\d_text.obx +

$(ZPATH)\z_text.obx +

$(ZPATH)\i_btcat.o32 +

$(ZPATH)\z_help.obx +

$(MFPATH)\lmult.obx +

$(ZPATH)\d_string.obx +

$(ZPATH)\d_win.obx +

$(ZPATH)\d_win1.obx +

$(ZPATH)\d_button.obx +

$(ZPATH)\z_button.obx +

$(ZPATH)\d_bgidsp.obx +

$(ZPATH)\z_decor.obx +

$(ZPATH)\z_int.obx +

$(ADPATH)\ivector.obx +

$(ADPATH)\imat.obx +

nextprev.obx +

$(MFPATH)\lmult_io.obx +

$(MFPATH)\mult_io.obx +

interact.obx +

setopts.obx +

fflagopt.obx +

ffopt2.obx +

ffopt3.obx +

mf_cursr.obx +

reportw.obx +

tempfit.obx +

$(TPATH)\string4.obx +

$(TPATH)\string3.obx +

mf_line.obx +

get_ffra.obx +

$(MFPATH)\fcon2.obx +

$(MFPATH)\fcons.obx +

temphist.obx +

mfhelp.obx +

error.obx +

stk2.obx +

dmat_dsp.obx +

sel_form.obx +

subest.obx +

scrolls.obx +

d4arr.obx +

in_strat.obx +

catch.obx+

modsrch.obx +

mf_win.obx +

exe_srch.obx +

norm_sel.obx +

biodynam.obx +

fit_sel.obx +

fi_build.obx +

fit_sel2.obx +

cpuehist.obx +

effort.obx +

humps.obx+

lfshstat.obx +

biomhist.obx +

recrhist.obx +

stockhst.obx +

catchab.obx +

mean_co1.obx +

systsear.obx +

t_scale.obx +

logstrem.obx+

catcheff.obx +

fit.obx+

ncdt_sel.obx+

samp_sel.obx+

sample.obx+

fullscr.obx+

prn_wndw.obx +

prn_scrn.obx +

results.obx +

le_loop.obx +

le_loop2.obx +

le_loop3.obx +

all_samp.obx +

composit.obx+

globinit.obx+

getlfsh2.obx +

zil_util.obx+

ext_numb.obx+

setcolor.obx+

set_patt.obx+

lfsh.obx+

init_ser.obx+

mf_butt.obx+

sparmenu.obx+

mf_graph.obx+

axes.obx+

na.obx+

frq_t.obx

zfe32

zfe32.map

\tools94\b32o45\adt32.lib+

dpmi32.lib+

c:\zinc\source\d32_zil.lib+

c:\zinc\source\d32_bgi.lib+

bgi32.lib+

cw32.lib+

\newm94a\mf32.lib+

h:\linad94x\b32o45\ado32.lib,

|



estfile.exe: estfile.obx lfsh.obj

	$(TLINK) /v/x/c/C @&&|

c0pl.obx+

estfile.obx+

lfsh.obx

estfile,estfile

phapi+

emu286+

emu+

mathl+

bcl286+

orl16.lib+

mf16.lib+

ads16.lib+

fp87.lib,protmode

|



#small.obx: $(BGI)\litt.chr

#	$(BGI)\bgiobj /f $(BGI)\litt small.obx  _SmallFont  small_text



mf_help.dat: mf_help.txt

	d:\xzinc36\bin\genhelp mf_help.txt



mf_help.hpp: mf_help.txt

	d:\xzinc36\bin\genhelp mf_help.txt



#bgiobj /f litt system _SystemFont system_text

#bgiobj /f litt dialog _DialogFont dialog_text

#bgiobj /f litt small  _SmallFont  small_text



all : zfe.exe mf_help.dat



