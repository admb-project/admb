// Example file to create a file with an R object from
// AD Model Builder

// open the file using the default AD Model Builder file name, and
// 6 digits of precision
open_r_file(adprogram_name + ".rdat", 6);

// Example of an INFO object
open_r_info_list("info", true);
	wrt_r_item("title", "SEDAR 15 Benchmark Assessment");
	wrt_r_item("species", "Red Snapper");
	wrt_r_item("model", "Statistical Catch at Age");
	wrt_r_item("rec.model", "BH-steep");
	wrt_r_item("base.run", "rs00X.tpl");
	wrt_r_item("units.length", "mm");
	wrt_r_item("units.weight0", "kg");
	wrt_r_item("units.biomass", "metric tons");
	wrt_r_item("units.ssb", "metric tons");
	wrt_r_item("units.ypr", "metric tons");
	wrt_r_item("units.landings", "1000 lb");
	wrt_r_item("units.discards", "1000 dead fish");
    wrt_r_item("units.numbers", "number fish");
    wrt_r_item("units.naa", "number fish");
	wrt_r_item("units.rec", "number fish");
close_r_info_list();


// LIST object of parameters and estimated quantities
open_r_info_list("parms", false);
	wrt_r_item("styr", styr);
	wrt_r_item("endyr", endyr);
	wrt_r_item("styrR", styr_rec_dev);
//	//wrt_r_item("M", M);
	wrt_r_item("Linf", Linf);
	wrt_r_item("K", K);
	wrt_r_item("t0", t0);
	wrt_r_item("wgt.a", wgtpar_a);
	wrt_r_item("wgt.b", wgtpar_b);
    wrt_r_item("whole2gutted", wgtpar_whole2gutted);
	wrt_r_item("D.mort.c.hal", Dmort_commHAL);
	wrt_r_item("D.mort.hb", Dmort_HB);
	wrt_r_item("D.mort.rec", Dmort_MRFSS);
	wrt_r_item("q.hal", mfexp(log_q_HAL));
	wrt_r_item("q.hb", mfexp(log_q_HB));
	wrt_r_item("q.rec", mfexp(log_q_MRFSS));
	wrt_r_item("q.rate",q_rate);
	wrt_r_item("F.prop.c.hal", F_commHAL_prop);
	wrt_r_item("F.prop.c.dv", F_commDV_prop);
	wrt_r_item("F.prop.hb", F_HB_prop);
	wrt_r_item("F.prop.rec", F_MRFSS_prop);
	wrt_r_item("F.prop.c.hal.D", F_commHAL_D_prop);
	wrt_r_item("F.prop.hb.D", F_HB_D_prop);
	wrt_r_item("F.prop.rec.D", F_MRFSS_D_prop);
	wrt_r_item("early.F.c.hal.D.ratio",F_commHAL_D_ratio);
	wrt_r_item("early.F.hb.D.ratio",F_HB_D_ratio);
	wrt_r_item("early.F.rec.D.ratio",F_MRFSS_D_ratio);
	wrt_r_item("BH.Phi0", spr_F0);
	wrt_r_item("B0", B0);
	wrt_r_item("Bstyr.B0", totB(styr)/B0);
	wrt_r_item("SSB0", S0);
	wrt_r_item("SSBstyr.SSB0", SSB(styr)/S0);
//	wrt_r_item("S1.S0", S1/S0);
	wrt_r_item("Rstyr.R0", rec(styr)/R0);
//	wrt_r_item("R1.R0", R1/R0);
	wrt_r_item("BH.biascorr",BiasCor);
	wrt_r_item("BH.R0", R0);
	wrt_r_item("BH.steep", steep);
	wrt_r_item("R.autocorr",R_autocorr);
	wrt_r_item("R0", R0); //same as BH.R0, but used in BSR.time.plots
	wrt_r_item("rec.lag", 1.0);
	wrt_r_item("msy", msy_out);
	wrt_r_item("Fmsy", F_msy_out);
	wrt_r_item("Fend.Fmsy", fullF(endyr)/F_msy_out);
	wrt_r_item("Emsy", E_msy_out);
	wrt_r_item("SSBmsy", SSB_msy_out);
	wrt_r_item("SSBend.SSBmsy", SSB(endyr)/SSB_msy_out);
	wrt_r_item("msst", (1.0-M_constant)*SSB_msy_out);
	wrt_r_item("Bmsy", B_msy_out);
	wrt_r_item("Rmsy", R_msy_out);
	wrt_r_item("sprmsy",spr_msy_out);
	wrt_r_item("Dmsy", D_msy_out);
	wrt_r_item("L.bias", L_early_bias);
close_r_info_list();

// VECTOR object of likelihood contributions
open_r_vector("like");
    wrt_r_item("lk.unwgt.data", fval_unwgt);
	wrt_r_item("lk.total", fval);
    wrt_r_item("lk.U.hal", f_HAL_cpue*w_I_HAL);
    wrt_r_item("lk.U.hb", f_HB_cpue*w_I_HB);
    wrt_r_item("lk.U.rec", f_MRFSS_cpue*w_I_MRFSS);
    wrt_r_item("lk.L.c.hal", f_commHAL_L_2*w_L);
    wrt_r_item("lk.L.c.dv", f_commDV_L*w_L);
    wrt_r_item("lk.L.hb", f_HB_L*w_L);
    wrt_r_item("lk.L.rec", f_MRFSS_L*w_L);
    wrt_r_item("lk.D.c.hal", f_commHAL_D*w_D);
    wrt_r_item("lk.D.hb", f_HB_D*w_D);
    wrt_r_item("lk.D.rec", f_MRFSS_D*w_D);
    wrt_r_item("lk.lenc.c.hal", f_commHAL_lenc*w_lc);
    wrt_r_item("lk.lenc.c.dv", f_commDV_lenc*w_lc);
    wrt_r_item("lk.lenc.hb", f_HB_lenc*w_lc);
    wrt_r_item("lk.lenc.rec", f_MRFSS_lenc*w_lc);
    wrt_r_item("lk.agec.c.hal", f_commHAL_agec*w_ac);
    wrt_r_item("lk.agec.c.dv", f_commDV_agec*w_ac);
    wrt_r_item("lk.agec.hb", f_HB_agec*w_ac);
    wrt_r_item("lk.agec.rec", f_MRFSS_agec*w_ac);
    wrt_r_item("lk.SRfit", f_N_dev*w_R);
    wrt_r_item("lk.SRinit", f_N_dev_early*w_R_init);
    wrt_r_item("lk.SRend", f_N_dev_end*w_R_end);
    wrt_r_item("lk.Fend", f_Fend_constraint*w_F);
    wrt_r_item("lk.B1dB0", f_B1dB0_constraint*w_B1dB0);
    wrt_r_item("lk.fullF", f_fullF_constraint*w_fullF);
    wrt_r_item("lk.cvlen.dev", f_cvlen_dev_constraint*w_cvlen_dev);
    wrt_r_item("lk.cvlen.diff", f_cvlen_diff_constraint*w_cvlen_diff);

	wrt_r_item("w.L", w_L);
	wrt_r_item("w.D", w_D);
	wrt_r_item("w.lenc", w_lc);
	wrt_r_item("w.agec", w_ac);
	wrt_r_item("w.U.hal", w_I_HAL);
	wrt_r_item("w.U.hb", w_I_HB);
	wrt_r_item("w.U.rec", w_I_MRFSS);
	wrt_r_item("w.R", w_R);
	wrt_r_item("w.R.init", w_R_init);
	wrt_r_item("w.R.end", w_R_end);
	wrt_r_item("w.F", w_F);
	wrt_r_item("w.B1dB0", w_B1dB0);
	wrt_r_item("w.fullF_extra", w_fullF);
	wrt_r_item("w.cvlen.dev", w_cvlen_dev);
	wrt_r_item("w.cvlen.diff", w_cvlen_diff);
close_r_vector();

// VECTOR object of parameters and estimated quantities
open_r_vector("sel.parms");

	wrt_r_item("selpar.L50.c.hal1", selpar_L50_commHAL1);
	wrt_r_item("selpar.slope.c.hal1", selpar_slope_commHAL1);
	wrt_r_item("selpar.L502.c.hal1", selpar_L502_commHAL1);
	wrt_r_item("selpar.slope2.c.hal1", selpar_slope2_commHAL1);
	wrt_r_item("selpar.L50.c.hal2", selpar_L50_commHAL2);
	wrt_r_item("selpar.slope.c.hal2", selpar_slope_commHAL2);
	wrt_r_item("selpar.L502.c.hal2", selpar_L502_commHAL2);
	wrt_r_item("selpar.slope2.c.hal2", selpar_slope2_commHAL2);
	wrt_r_item("selpar.L50.c.hal3", selpar_L50_commHAL3);
	wrt_r_item("selpar.slope.c.hal3", selpar_slope_commHAL3);
	wrt_r_item("selpar.L502.c.hal3", selpar_L502_commHAL3);
	wrt_r_item("selpar.slope2.c.hal3", selpar_slope2_commHAL3);

	wrt_r_item("selpar.L50.c.dv1", selpar_L50_commDV1);
	wrt_r_item("selpar.slope.c.dv1", selpar_slope_commDV1);
	wrt_r_item("selpar.L502.c.dv1", selpar_L502_commDV1);
	wrt_r_item("selpar.slope2.c.dv1", selpar_slope2_commDV1);

	wrt_r_item("selpar.L50.hb1", selpar_L50_HB1);
	wrt_r_item("selpar.slope.hb1", selpar_slope_HB1);
	wrt_r_item("selpar.L502.hb1", selpar_L502_HB1);
	wrt_r_item("selpar.slope2.hb1", selpar_slope2_HB1);
	wrt_r_item("selpar.L50.hb2", selpar_L50_HB2);
	wrt_r_item("selpar.slope.hb2", selpar_slope_HB2);
	wrt_r_item("selpar.L502.hb2", selpar_L502_HB2);
	wrt_r_item("selpar.slope2.hb2", selpar_slope2_HB2);
	wrt_r_item("selpar.L50.hb3", selpar_L50_HB3);
	wrt_r_item("selpar.slope.hb3", selpar_slope_HB3);
	wrt_r_item("selpar.L502.hb3", selpar_L502_HB3);
	wrt_r_item("selpar.slope2.hb3", selpar_slope2_HB3);

	wrt_r_item("selpar.L50.rec1", selpar_L50_MRFSS1);
	wrt_r_item("selpar.slope.rec1", selpar_slope_MRFSS1);
	wrt_r_item("selpar.L502.rec1", selpar_L502_MRFSS1);
	wrt_r_item("selpar.slope2.rec1", selpar_slope2_MRFSS1);
	wrt_r_item("selpar.L50.rec2", selpar_L50_MRFSS2);
	wrt_r_item("selpar.slope.rec2", selpar_slope_MRFSS2);
	wrt_r_item("selpar.L502.rec2", selpar_L502_MRFSS2);
	wrt_r_item("selpar.slope2.rec2", selpar_slope2_MRFSS2);
	wrt_r_item("selpar.L50.rec3", selpar_L50_MRFSS3);
	wrt_r_item("selpar.slope.rec3", selpar_slope_MRFSS3);
	wrt_r_item("selpar.L502.rec3", selpar_L502_MRFSS3);
	wrt_r_item("selpar.slope2.rec3", selpar_slope2_MRFSS3);

close_r_vector();

//// Example of a MATRIX object with no row or column names
//wrt_r_matrix("F.at.age", F);

//// Example of a MATRIX object with row names, but no column names;
//// rows specified by constructing a series since a vector of years
//// is not a variable
//wrt_r_matrix("N.at.age.1", N, 2);
//wrt_r_namevector(1968, 1979);
//

// Matrix with with row and column names;
// rows specified by constructing a series since the a vector of years
// is not a variable; columns specified by constructing a series since
// a vector of ages isn't supplied
open_r_matrix("N.age");
    wrt_r_matrix(N, 2, 2);
    wrt_r_namevector(styr, (endyr+1));
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("N.age.mdyr");
    wrt_r_matrix(N_mdyr, 2, 2);
    wrt_r_namevector(styr, endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("B.age");
    wrt_r_matrix(B, 2, 2);
    wrt_r_namevector(styr, (endyr+1));
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("Z.age");
    wrt_r_matrix(Z, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("L.age.pred.num");
    wrt_r_matrix(C_total, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("L.age.pred.wgt.mt");
    wrt_r_matrix(L_total, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("L.age.pred.wgt.klb");
    wrt_r_matrix(L_total*mt2klb, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("C.age.pred.num.c.hal");
    wrt_r_matrix(C_commHAL, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("C.age.pred.num.c.dv");
    wrt_r_matrix(C_commDV, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("C.age.pred.num.hb");
    wrt_r_matrix(C_HB, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("C.age.pred.num.rec");
    wrt_r_matrix(C_MRFSS, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
close_r_matrix();

// LIST object with annual selectivity at age by fishery

open_r_list("sel.age");

    open_r_matrix("sel.m.c.hal");
    wrt_r_matrix(sel_commHAL, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("sel.m.c.dv");
    wrt_r_matrix(sel_commDV, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("sel.m.hb");
    wrt_r_matrix(sel_HB, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("sel.m.rec");
    wrt_r_matrix(sel_MRFSS, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("sel.m.c.hal.D");
    wrt_r_matrix(sel_commHAL_D, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("sel.m.rec.D");
    wrt_r_matrix(sel_MRFSS_D, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("sel.m.hb.D");
    wrt_r_matrix(sel_HB_D, 2, 2);
    wrt_r_namevector(styr,endyr);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_vector("sel.v.wgted.L");
    for (iage=1; iage<=nages; iage++)
    {
        wrt_r_item(iage, sel_wgted_L(iage));
    }
    close_r_vector();

    open_r_vector("sel.v.wgted.D");
    for (iage=1; iage<=nages; iage++)
    {
        wrt_r_item(iage, sel_wgted_D(iage));
    }
    close_r_vector();

    open_r_vector("sel.v.wgted.tot");
    for (iage=1; iage<=nages; iage++)
    {
        wrt_r_item(iage, sel_wgted_tot(iage));
    }
    close_r_vector();

close_r_list();


//LIST object with predicted and observed composition data
open_r_list("comp.mats");

    open_r_matrix("lcomp.c.hal.ob");
    wrt_r_matrix(obs_commHAL_lenc, 2, 2);
    wrt_r_namevector(styr_commHAL_lenc,endyr_commHAL_lenc);
    wrt_r_namevector(lenbins);
    close_r_matrix();

    open_r_matrix("lcomp.c.hal.pr");
    wrt_r_matrix(pred_commHAL_lenc, 2, 2);
    wrt_r_namevector(styr_commHAL_lenc,endyr_commHAL_lenc);
    wrt_r_namevector(lenbins);
    close_r_matrix();

    open_r_matrix("lcomp.c.dv.ob");
    wrt_r_matrix(obs_commDV_lenc, 2, 2);
    wrt_r_namevector(yrs_commDV_lenc);
    wrt_r_namevector(lenbins);
    close_r_matrix();

    open_r_matrix("lcomp.c.dv.pr");
    wrt_r_matrix(pred_commDV_lenc, 2, 2);
    wrt_r_namevector(yrs_commDV_lenc);
    wrt_r_namevector(lenbins);
    close_r_matrix();

    open_r_matrix("lcomp.hb.ob");
    wrt_r_matrix(obs_HB_lenc, 2, 2);
    wrt_r_namevector(styr_HB_lenc,endyr_HB_lenc);
    wrt_r_namevector(lenbins);
    close_r_matrix();

    open_r_matrix("lcomp.hb.pr");
    wrt_r_matrix(pred_HB_lenc, 2, 2);
    wrt_r_namevector(styr_HB_lenc,endyr_HB_lenc);
    wrt_r_namevector(lenbins);
    close_r_matrix();

    open_r_matrix("lcomp.rec.ob");
    wrt_r_matrix(obs_MRFSS_lenc, 2, 2);
    wrt_r_namevector(yrs_MRFSS_lenc);
    wrt_r_namevector(lenbins);
    close_r_matrix();

    open_r_matrix("lcomp.rec.pr");
    wrt_r_matrix(pred_MRFSS_lenc, 2, 2);
    wrt_r_namevector(yrs_MRFSS_lenc);
    wrt_r_namevector(lenbins);
    close_r_matrix();

    open_r_matrix("acomp.c.hal.ob");
    wrt_r_matrix(obs_commHAL_agec, 2, 2);
    wrt_r_namevector(yrs_commHAL_agec);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("acomp.c.hal.pr");
    wrt_r_matrix(pred_commHAL_agec, 2, 2);
    wrt_r_namevector(yrs_commHAL_agec);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("acomp.c.dv.ob");
    wrt_r_matrix(obs_commDV_agec, 2, 2);
    wrt_r_namevector(yrs_commDV_agec);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("acomp.c.dv.pr");
    wrt_r_matrix(pred_commDV_agec, 2, 2);
    wrt_r_namevector(yrs_commDV_agec);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("acomp.hb.ob");
    wrt_r_matrix(obs_HB_agec, 2, 2);
    wrt_r_namevector(yrs_HB_agec);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("acomp.hb.pr");
    wrt_r_matrix(pred_HB_agec, 2, 2);
    wrt_r_namevector(yrs_HB_agec);
    wrt_r_namevector(1, nages);
    close_r_matrix();

    open_r_matrix("acomp.rec.ob");
    wrt_r_matrix(obs_MRFSS_agec, 2, 2);
    wrt_r_namevector(styr_MRFSS_agec,endyr_MRFSS_agec);
    wrt_r_namevector(1,nages);
    close_r_matrix();

    open_r_matrix("acomp.rec.pr");
    wrt_r_matrix(pred_MRFSS_agec, 2, 2);
    wrt_r_namevector(styr_MRFSS_agec,endyr_MRFSS_agec);
    wrt_r_namevector(1,nages);
    close_r_matrix();

close_r_list();

//// DATA FRAME of time series
open_r_df("t.series", styr, (endyr+1), 2);
	wrt_r_namevector(styr,(endyr+1));
	wrt_r_df_col("year", styr,(endyr+1));
	wrt_r_df_col("F.full", fullF);
	wrt_r_df_col("F.Fmsy", fullF/F_msy_out);
	wrt_r_df_col("F.c.hal", F_commHAL_out);
	wrt_r_df_col("F.c.dv", F_commDV_out);
	wrt_r_df_col("F.hb", F_HB_out);
	wrt_r_df_col("F.rec", F_MRFSS_out);
	wrt_r_df_col("F.c.hal.D", F_commHAL_D_out);
	wrt_r_df_col("F.hb.D", F_HB_D_out);
	wrt_r_df_col("F.rec.D", F_MRFSS_D_out);
    wrt_r_df_col("E", E);
    wrt_r_df_col("E.Emsy", E/E_msy_out);
    wrt_r_df_col("recruits", rec);
    //wrt_r_df_col("logR.dev", log_dev_N_rec); //excludes yrs deviations not estimated
    wrt_r_df_col("logR.dev", log_dev_R); //places zeros in yrs deviations not estimated
    wrt_r_df_col("SSB", SSB);
    wrt_r_df_col("SSB.SSBmsy", SSB/SSB_msy_out);
     wrt_r_df_col("B", totB);
    wrt_r_df_col("B.B0", totB/B0);
    wrt_r_df_col("SPR.static", spr_static);

    wrt_r_df_col("U.hal.ob", obs_HAL_cpue);
    wrt_r_df_col("U.hal.pr", pred_HAL_cpue);
    wrt_r_df_col("U.hb.ob", obs_HB_cpue);
    wrt_r_df_col("U.hb.pr", pred_HB_cpue);
    wrt_r_df_col("U.rec.ob", obs_MRFSS_cpue);
    wrt_r_df_col("U.rec.pr", pred_MRFSS_cpue);

    wrt_r_df_col("total.L.wgt.mt", L_total_yr);
    wrt_r_df_col("total.L.wgt.klb", L_total_yr*mt2klb);
   wrt_r_df_col("L.c.hal.ob", obs_commHAL_L_2);
    wrt_r_df_col("L.c.hal.pr", pred_commHAL_L_2);
    wrt_r_df_col("L.c.dv.ob", obs_commDV_L);
    wrt_r_df_col("L.c.dv.pr", pred_commDV_L);
    wrt_r_df_col("L.hb.ob", obs_HB_L);
    wrt_r_df_col("L.hb.pr", pred_HB_L);
    wrt_r_df_col("L.rec.ob", obs_MRFSS_L);
    wrt_r_df_col("L.rec.pr", pred_MRFSS_L);

    //dead discards
    wrt_r_df_col("D.c.hal.ob", obs_commHAL_D);
    wrt_r_df_col("D.c.hal.pr", pred_commHAL_D);
    wrt_r_df_col("D.hb.ob", obs_HB_D);
    wrt_r_df_col("D.hb.pr", pred_HB_D);
    wrt_r_df_col("D.rec.ob", obs_MRFSS_D);
    wrt_r_df_col("D.rec.pr", pred_MRFSS_D);

//    //dead discards prior to data
//    wrt_r_df_col("early.D.c.hal", early_pred_commHAL_D);
//    wrt_r_df_col("early.D.hb", early_pred_HB_D);
//    wrt_r_df_col("early.D.rec", early_pred_MRFSS_D);
//
    //comp sample sizes
    wrt_r_df_col("lcomp.c.hal.n", nsamp_commHAL_lenc);
    wrt_r_df_col("lcomp.c.dv.n", nsamp_commDV_lenc_allyr);
    wrt_r_df_col("lcomp.hb.n", nsamp_HB_lenc);
    wrt_r_df_col("lcomp.rec.n", nsamp_MRFSS_lenc_allyr);

    wrt_r_df_col("acomp.c.hal.n", nsamp_commHAL_agec_allyr);
    wrt_r_df_col("acomp.c.dv.n", nsamp_commDV_agec_allyr);
    wrt_r_df_col("acomp.hb.n", nsamp_HB_agec_allyr);
    wrt_r_df_col("acomp.rec.n", nsamp_MRFSS_agec);

    //time varying L50 (selectivity) parms
    //wrt_r_df_col("selpar_L50_HB_dev",selpar_L50_HB_dev);
    //wrt_r_df_col("selpar_L50_c.hal_dev",selpar_L50_commHAL_dev);
close_r_df();

open_r_df("a.series", 1, nages, 2);
	wrt_r_namevector(1,nages);
	wrt_r_df_col("age", 1,nages);
	wrt_r_df_col("length", meanlen);
	wrt_r_df_col("length.cv", len_cv);
	wrt_r_df_col("weight0", wgt_kg);     //for FishGraph
	wrt_r_df_col("wgt.mt", wgt);
	wrt_r_df_col("wgt.klb", wgt_klb);
	wrt_r_df_col("prop.female", prop_f);
	wrt_r_df_col("mat.female", maturity_f);
	wrt_r_df_col("reprod", reprod);
	wrt_r_df_col("M", M);
close_r_df();

open_r_df("eq.series", 1, n_iter_msy, 2);
	wrt_r_namevector(1,n_iter_msy);
	wrt_r_df_col("F.eq", F_msy);
	wrt_r_df_col("E.eq", E_eq);
	wrt_r_df_col("spr", spr_msy);
	wrt_r_df_col("R", R_eq);
	wrt_r_df_col("SSB", SSB_eq);
	wrt_r_df_col("B", B_eq);
	wrt_r_df_col("L", L_eq);
	wrt_r_df_col("D", D_eq);
close_r_df();

open_r_df("pr.series", 1, n_iter_spr, 2);
	wrt_r_namevector(1,n_iter_spr);
	wrt_r_df_col("F.spr", F_spr);
	wrt_r_df_col("E.spr", E_spr);
	wrt_r_df_col("spr", spr_spr);
	wrt_r_df_col("SPR", spr_spr/spr_F0);
	wrt_r_df_col("ypr", L_spr);
close_r_df();


open_r_list("CLD.est.mats");
    open_r_matrix("Lw.c.hal");
        wrt_r_matrix(L_commHAL, 1,1);
    close_r_matrix();

    open_r_matrix("Lw.c.dv");
        wrt_r_matrix(L_commDV, 1,1);
    close_r_matrix();

    open_r_matrix("Lw.hb");
        wrt_r_matrix(L_HB, 1,1);
    close_r_matrix();

    open_r_matrix("Lw.rec");
        wrt_r_matrix(L_MRFSS, 1,1);
    close_r_matrix();

    open_r_matrix("Lw.total");
        wrt_r_matrix(L_total, 1,1);
    close_r_matrix();

    open_r_matrix("Ln.c.hal");
        wrt_r_matrix(C_commHAL, 1,1);
    close_r_matrix();

    open_r_matrix("Ln.c.dv");
        wrt_r_matrix(C_commDV, 1,1);
    close_r_matrix();

    open_r_matrix("Ln.hb");
        wrt_r_matrix(C_HB, 1,1);
    close_r_matrix();

    open_r_matrix("Ln.rec");
        wrt_r_matrix(C_MRFSS, 1,1);
    close_r_matrix();

    open_r_matrix("Ln.total");
        wrt_r_matrix(C_total, 1,1);
    close_r_matrix();

    open_r_matrix("Dn.c.hal");
        wrt_r_matrix(C_commHAL_D,1,1);
    close_r_matrix();

    open_r_matrix("Dn.hb");
        wrt_r_matrix(C_HB_D, 1,1);
    close_r_matrix();

    open_r_matrix("Dn.rec");
        wrt_r_matrix(C_MRFSS_D, 1,1);
    close_r_matrix();
close_r_list();


////// Example of a DATA FRAME object composed of two items.
////// The data frame will span 1 to the number of ages. The vectors
////// span 2 to the number of ages, so NAs will be written for the first
////// data point in the two vectors. The row names will be included,
////// similar to the matrix object just before this one.
////open_r_df("aseries", 1, nages, 2);
////	wrt_r_df_col("N.pred", predicted_N);
////	wrt_r_df_col("N.ratio", ratio_N);
////	wrt_r_namevector(3, 9);
////close_r_df();
////
////// Example of a LIST object
////open_r_list("C.at.age.mats");
////
////	// matrix with row and column names
////    wrt_r_matrix("Est", C, 1, 1);
////
////	// another matrix with row and column names
////	wrt_r_matrix("Obs", obs_catch_at_age, 1, 1);
////
////close_r_list();
////
//

// close file
close_r_file();
