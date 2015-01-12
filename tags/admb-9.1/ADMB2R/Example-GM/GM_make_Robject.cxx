///////////////////////////////////////////////////////////////////////
// * ADMB2R statements that, when included in an  AD Model Builder
//   program, will create an ASCII file with an R data object (R list).
// * Because certain naming and structure conventions are used, the
//   R list is compatible with our FishGraph R graphics routines.
// * The ADMB model is an analysis of Gulf of Mexico menhaden.
// * This file developed by Sustainable Fisheries Branch of NMFS
//   Beaufort (NC) Lab. Last revised September, 2009.
///////////////////////////////////////////////////////////////////////
//  FG: marks FishGraph compatibility notes
///////////////////////////////////////////////////////////////////////

// Open the file using the default AD Model Builder file name, and
// 6 digits of precision
open_r_file(adprogram_name + ".rdat", 6);

// Write the INFO object, an R list containing text strings, including
// automatically generated date & time.
// FG: many of the units given below are used to label plots.
open_r_info_list("info", true);
   wrt_r_item("title", "GOM Menhaden Benchmark Assessment");
   wrt_r_item("species", "Gulf menhaden");
   wrt_r_item("model", "Statistical Catch at Age");
   wrt_r_item("rec.model", "BH-steep");
   wrt_r_item("base.run", "GOMmenhaden.tpl");
   wrt_r_item("units.weight", "g");
   wrt_r_item("units.ssb", "1e9 eggs");
   wrt_r_item("units.ypr", "g");
   wrt_r_item("units.landings", "1000 mt");
   wrt_r_item("units.numbers", "1e9 fish");
   wrt_r_item("units.naa", "1e9 fish");
   wrt_r_item("units.rec", "1e9 fish");
close_r_info_list();

// LIST object of parameters and estimated quantities
open_r_info_list("parms", false);
   wrt_r_item("styr", styr);
   wrt_r_item("endyr", endyr);
   wrt_r_item("styrR", styrR);
   wrt_r_item("q.index", mfexp(q_log_U_age0));
   wrt_r_item("FEC0", FEC0);
   wrt_r_item("FECstyr.FEC0", FEC1FEC0);
   wrt_r_item("FECendyr.FEC0", FECendFEC0);
   wrt_r_item("BH.Phi0", fpr_F0_mean);
   wrt_r_item("BH.R0", R0);
   wrt_r_item("BH.steep", steep);
   wrt_r_item("rec.lag", 1.0);
   wrt_r_item("Fmsy", 1.46);  //Fmsy=Fmed, calculated externally
   wrt_r_item("SSBmsy", 34340.0); //Fecundity limit, calculated externally
   wrt_r_item("Fend.Fmsy", F_full(endyr)/1.46);
   wrt_r_item("FECend.FECmsy", FEC(endyr)/34340.0);
close_r_info_list();

// VECTOR object of likelihood contributions
open_r_vector("like");
   wrt_r_item("lk.total", fval);
   wrt_r_item("lk.U", f_U_age0*lambda(1));
   wrt_r_item("lk.agec.1", f_agec_reduction1*lambda(2));
   wrt_r_item("lk.agec.2", f_agec_reduction2*lambda(3));
   wrt_r_item("lk.L", f_L_reduction*lambda(4));
   wrt_r_item("lk.SRfit", f_R_dev*lambda(5));
   wrt_r_item("lk.SRconstraint", f_R1_dev*lambda(6));
close_r_vector();

// VECTOR object of parameters and estimated quantities
open_r_vector("sel.parms");
   wrt_r_item("selpar.L50.1", selpar_A50_reduction_st1);
   wrt_r_item("selpar.slope.1", selpar_s_reduction_st1);
   wrt_r_item("selpar.L50.2", selpar_A50_reduction_st2);
   wrt_r_item("selpar.slope.2", selpar_s_reduction_st2);
close_r_vector();

// Various matrices

    open_r_matrix("N.age");
    wrt_r_matrix(N, 2, 2);
    wrt_r_namevector(styrR,endyr);
    wrt_r_namevector(0, (nages-1));
    close_r_matrix();

    open_r_matrix("B.age");
    wrt_r_matrix(B, 2, 2);
    wrt_r_namevector(styrR, endyr);
    wrt_r_namevector(0, (nages-1));
    close_r_matrix();

    open_r_matrix("F.age");
    wrt_r_matrix(F_total, 2, 2);
    wrt_r_namevector(styrR,endyr);
    wrt_r_namevector(0, (nages-1));
    close_r_matrix();

    open_r_matrix("Z.age");
    wrt_r_matrix(Z, 2, 2);
    wrt_r_namevector(styrR,endyr);
    wrt_r_namevector(0, (nages-1));
    close_r_matrix();

    open_r_matrix("L.age.pred.num");
    wrt_r_matrix(L_reduction_num, 2, 2);
    wrt_r_namevector(styrR,endyr);
    wrt_r_namevector(0, (nages-1));
    close_r_matrix();

    open_r_matrix("L.age.pred.wgt");
    wrt_r_matrix(L_reduction_wgt, 2, 2);
    wrt_r_namevector(styrR,endyr);
    wrt_r_namevector(0, (nages-1));
    close_r_matrix();

// LIST object of weight-at-age matrices
open_r_list("wgt.age");
    open_r_matrix("wgt.age");
    wrt_r_matrix(wgt_fish, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(0, (nages-1));
    close_r_matrix();

    open_r_matrix("wgt.age.spawn");
    wrt_r_matrix(wgt_spawn, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(0, (nages-1));
    close_r_matrix();
close_r_list();

// LIST object of selectivity matrices and vectors
// FG: This example has only one matrix and no vectors, but
// both may be included. Matrix names must begin
// with "sel.m" and vector names with "sel.v"
open_r_list("sel.age");
    open_r_matrix("sel.m.red");
    wrt_r_matrix(sel_reduction, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(0, (nages-1));
    close_r_matrix();
close_r_list();

// LIST object with predicted and observed age- or length-composition data.
// FG: each observed matrix should be followed immediatedly by the
// corresponding predicted matrix.
//
open_r_list("comp.mats");
    open_r_matrix("acomp.reduction.ob");
    wrt_r_matrix(agec_reduction_obs, 2, 2);
    wrt_r_namevector(agec_reduction_styr,agec_reduction_endyr);
    wrt_r_namevector(0,(nages-1));
    close_r_matrix();

    open_r_matrix("acomp.reduction.pr");
    wrt_r_matrix(agec_reduction_pred, 2, 2);
    wrt_r_namevector(agec_reduction_styr,agec_reduction_endyr);
    wrt_r_namevector(0,(nages-1));
    close_r_matrix();
close_r_list();

// DATA FRAME of time series
open_r_df("t.series", styr, endyr, 2);
   wrt_r_namevector(styr,endyr);
   wrt_r_df_col("year", styr,endyr);
   wrt_r_df_col("F.Fmsy", F_full(styr,endyr)/1.46);
   wrt_r_df_col("F.full", F_full(styr,endyr));
   wrt_r_df_col("F.reduction", F_full(styr,endyr));
   wrt_r_df_col("E.rate", E(styr,endyr));
   wrt_r_df_col("recruits", R_age0(styr,endyr));
   wrt_r_df_col("SSB", FEC(styr,endyr));
   wrt_r_df_col("FEC.FECmsy", FEC(styr,endyr)/34340.0);
   wrt_r_df_col("B", B_sum(styr,endyr));
   wrt_r_df_col("FPR.static", fpr_static(styr,endyr));

   wrt_r_df_col("U.recruits.ob", U_age0_obs);
   wrt_r_df_col("U.recruits.pr", U_age0_pred);

   wrt_r_df_col("L.reduction.ob", L_reduction_obs);
   wrt_r_df_col("L.reduction.pr", L_reduction_pred);

   // comp sample sizes for FG
   wrt_r_df_col("acomp.reduction.n", agec_reduction_nsamp);
close_r_df();

// Data frame of age series (data by age):
open_r_df("a.series", 1, nages, 2);
   wrt_r_namevector(0,nages-1);
   wrt_r_df_col("age", 0, nages-1, 1, false);  // Must use 5 args when ages start at zero
   wrt_r_df_col("weight", wgt_fish_mean);      //for FishGraph
   wrt_r_df_col("wgt.spawn", wgt_spawn_mean);
   wrt_r_df_col("mat.female", mat_f);
   wrt_r_df_col("M", M_vec);
close_r_df();


// Data frame of equilibrium values by F.  Compatible with FG.
open_r_df("eq.series", 1, 211, 2);
   wrt_r_namevector(1,211);
   wrt_r_df_col("F.eq", F_pr);
   wrt_r_df_col("L", Y_eq);
close_r_df();

// Data frame of per-recruit values by F.  Compatible with FG.
open_r_df("pr.series", 1, 211, 2);
   wrt_r_namevector(1,211);
   wrt_r_df_col("F.spr", F_pr);
   wrt_r_df_col("spr", FEC_pr);
   wrt_r_df_col("spr.prop", FEC_pr/max(FEC_pr));
   wrt_r_df_col("ypr", Y_pr);
close_r_df();


// LIST  of catch - landings - discards matrices. Compatible with FG.
open_r_list("CLD.est.mats");

   open_r_matrix("Lw.red");
      wrt_r_matrix(L_reduction_wgt, 1,1);
   close_r_matrix();

   open_r_matrix("Ln.red");
      wrt_r_matrix(L_reduction_num, 1,1);
   close_r_matrix();

close_r_list();

// Close the R object.
close_r_file();
