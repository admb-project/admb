#C growth parameters are estimated
#_data_and_control_files: simple.dat // simple.ctl
#_SS-V3.01-O-opt;_12/16/08;_Stock_Synthesis_by_Richard_Methot_(NOAA);_using_Otter_Research_ADMB_7.0.1
1  #_N_Growth_Patterns
1 #_N_Morphs_Within_GrowthPattern
#_Cond 1 #_Morph_between/within_stdev_ratio (no read if N_morphs=1)
#_Cond  1 #vector_Morphdist_(-1_in_first_val_gives_normal_approx)

#_Cond 0  #  N recruitment designs goes here if N_GP*nseas*area>1
#_Cond 0  #  placeholder for recruitment interaction request
#_Cond 1 1 1  # example recruitment design element for GP=1, seas=1, area=1

#_Cond 0 # N_movement_definitions goes here if N_areas > 1
#_Cond 1.0 # first age that moves (real age at begin of season, not integer) also cond on do_migration>0
#_Cond 1 1 1 2 4 10 # example move definition for seas=1, morph=1, source=1 dest=2, age1=4, age2=10

2 #_Nblock_Patterns
 3 2 #_blocks_per_pattern
# begin and end years of blocks
 1975 1985 1986 1990 1995 2001
 1987 1990 1995 2001

0.5 #_fracfemale
1 #_natM_type:_0=1Parm; 1=N_breakpoints;_2=Lorenzen;_3=agespecific;_4=agespec_withseasinterpolate
2 #_N_breakpoints
 4 15 # age(real) at M breakpoints
1 # GrowthModel: 1=vonBert with L1&L2; 2=Richards with L1&L2; 3=not implemented; 4=not implemented
1.6 #_Growth_Age_for_L1
25 #_Growth_Age_for_L2 (999 to use as Linf)
0 #_SD_add_to_LAA (set to 0.1 for SS2 V1.x compatibility)
0 #_CV_Growth_Pattern:  0 CV=f(LAA); 1 CV=F(A); 2 SD=F(LAA); 3 SD=F(A)
1 #_maturity_option:  1=length logistic; 2=age logistic; 3=read age-maturity matrix by growth_pattern; 4=read age-fecundity
#_placeholder for empirical age-maturity by growth pattern
1 #_First_Mature_Age
1 #_fecundity option:(1)eggs=Wt*(a+b*Wt);(2)eggs=a*L^b;(3)eggs=a*Wt^b
1 #_parameter_offset_approach (1=none, 2= M, G, CV_G as offset from female-GP1, 3=like SS2 V1.x)
2 #_env/block/dev_adjust_method (1=standard; 2=with logistic trans to keep within base parm bounds)

#_growth_parms
#_LO HI INIT PRIOR PR_type SD PHASE env-var use_dev dev_minyr dev_maxyr dev_stddev Block Block_Fxn
 0.05 0.15 0.1 0.1 0 0.8 -3 0 0 0 0 0.5 0 0 # NatM_p_1_Fem_GP:1
 0.05 0.15 0.1 0.1 0 0.8 -3 0 0 0 0 0.5 0 0 # NatM_p_2_Fem_GP:1
 1 45 34.4315 36 0 10 2 0 0 0 0 0.5 0 0 # L_at_Amin_Fem_GP_1
 40 90 71.5265 70 0 10 4 0 0 0 0 0.5 0 0 # L_at_Amax_Fem_GP_1
 0.05 0.25 0.15135 0.15 0 0.8 4 0 0 0 0 0.5 0 0 # VonBert_K_Fem_GP_1
 0.05 0.25 0.1 0.1 0 0.8 -3 0 0 0 0 0.5 0 0 # CV_young_Fem_GP_1
 0.05 0.25 0.1 0.1 0 0.8 -3 0 0 0 0 0.5 0 0 # CV_old_Fem_GP_1
 0.05 0.15 0.1 0.1 0 0.8 -3 0 0 0 0 0.5 0 0 # NatM_p_1_Mal_GP:1
 0.05 0.15 0.1 0.1 0 0.8 -3 0 0 0 0 0.5 0 0 # NatM_p_2_Mal_GP:1
 1 45 35.1136 36 0 10 2 0 0 0 0 0.5 0 0 # L_at_Amin_Mal_GP_1
 40 90 70.4486 70 0 10 4 0 0 0 0 0.5 0 0 # L_at_Amax_Mal_GP_1
 0.05 0.25 0.157831 0.15 0 0.8 4 0 0 0 0 0.5 0 0 # VonBert_K_Mal_GP_1
 0.05 0.25 0.1 0.1 0 0.8 -3 0 0 0 0 0.5 0 0 # CV_young_Mal_GP_1
 0.05 0.25 0.1 0.1 0 0.8 -3 0 0 0 0 0.5 0 0 # CV_old_Mal_GP_1
 -3 3 2.44e-006 2.44e-006 0 0.8 -3 0 0 0 0 0.5 0 0 # Wtlen_1_Fem
 -3 4 3.34694 3.34694 0 0.8 -3 0 0 0 0 0.5 0 0 # Wtlen_2_Fem
 50 60 55 55 0 0.8 -3 0 0 0 0 0.5 0 0 # Mat50%_Fem
 -3 3 -0.25 -0.25 0 0.8 -3 0 0 0 0 0.5 0 0 # Mat_slope_Fem
 -3 3 1 1 0 0.8 -3 0 0 0 0 0.5 0 0 # Eg/gm_inter_Fem
 -3 3 0 0 0 0.8 -3 0 0 0 0 0.5 0 0 # Eg/gm_slope_wt_Fem
 -3 3 2.44e-006 2.44e-006 0 0.8 -3 0 0 0 0 0.5 0 0 # Wtlen_1_Mal
 -3 4 3.34694 3.34694 0 0.8 -3 0 0 0 0 0.5 0 0 # Wtlen_2_Mal
 0 0 0 0 -1 0 -4 0 0 0 0 0 0 0 # RecrDist_GP_1
 0 0 0 0 -1 0 -4 0 0 0 0 0 0 0 # RecrDist_Area_1
 0 0 0 0 -1 0 -4 0 0 0 0 0 0 0 # RecrDist_Seas_1
 0 0 0 0 -1 0 -4 0 0 0 0 0 0 0 # CohortGrowDev

#_Cond 0  #custom_MG-env_setup (0/1)
#_Cond -2 2 0 0 -1 99 -2 #_placeholder when no MG-environ parameters

#_Cond 0  #custom_MG-block_setup (0/1)
#_Cond -2 2 0 0 -1 99 -2 #_placeholder when no MG-block parameters

#_seasonal_effects_on_biology_parms
 0 0 0 0 0 0 0 0 0 0 #_femwtlen1,femwtlen2,mat1,mat2,fec1,fec2,Malewtlen1,malewtlen2,L1,K
#_Cond -2 2 0 0 -1 99 -2 #_placeholder when no seasonal MG parameters

#_Cond -4 #_MGparm_Dev_Phase

#_Spawner-Recruitment
3 #_SR_function
#_LO HI INIT PRIOR PR_type SD PHASE
 3 31 8.98831 10.3 0 10 1 # SR_R0
 0.2 1 0.6 0.7 2 0.2 4 # SR_steep
 0 2 0.6 0.8 0 0.8 -4 # SR_sigmaR
 -5 5 0.1 0 0 1 -3 # SR_envlink
 -5 5 0 0 0 1 -4 # SR_R1_offset
 0 0 0 0 -1 0 -99 # SR_autocorr
1 #_SR_env_link
1 #_SR_env_target_0=none;1=devs;_2=R0;_3=steepness

1 #do_recdev:  0=none; 1=devvector; 2=simple deviations
1971 # first year of main recr_devs; early devs can preceed this era
2001 # last year of main recr_devs; forecast devs start in following year
3 #_recdev phase
1 # (0/1) to read 11 advanced options
 0 #_recdev_early_start (0=none; neg value makes relative to recdev_start)
 -4 #_recdev_early_phase
 0 #_forecast_recruitment phase (incl. late recr) (0 value resets to maxphase+1)
 1 #_lambda for prior_fore_recr occurring before endyr+1
 1970 #_last_early_yr_nobias_adj_in_MPD
 1971 #_first_yr_fullbias_adj_in_MPD
 2001 #_last_yr_fullbias_adj_in_MPD
 2002 #_first_recent_yr_nobias_adj_in_MPD
 -5 #min rec_dev
 5 #max rec_dev
 0 #_read_recdevs
#_end of advanced SR options

# read specified recr devs
#_Yr Input_value

# all recruitment deviations
#DisplayOnly -0.28147 # RecrDev_1971
#DisplayOnly 0.358653 # RecrDev_1972
#DisplayOnly -0.0613461 # RecrDev_1973
#DisplayOnly 0.0765681 # RecrDev_1974
#DisplayOnly 0.792201 # RecrDev_1975
#DisplayOnly 0.0675588 # RecrDev_1976
#DisplayOnly 0.278372 # RecrDev_1977
#DisplayOnly -0.272589 # RecrDev_1978
#DisplayOnly -0.327367 # RecrDev_1979
#DisplayOnly 0.485895 # RecrDev_1980
#DisplayOnly 0.497595 # RecrDev_1981
#DisplayOnly -0.587451 # RecrDev_1982
#DisplayOnly -0.732346 # RecrDev_1983
#DisplayOnly -0.645347 # RecrDev_1984
#DisplayOnly 0.602779 # RecrDev_1985
#DisplayOnly 0.0265801 # RecrDev_1986
#DisplayOnly 0.474477 # RecrDev_1987
#DisplayOnly -0.0120026 # RecrDev_1988
#DisplayOnly -0.125787 # RecrDev_1989
#DisplayOnly 0.367247 # RecrDev_1990
#DisplayOnly -0.74953 # RecrDev_1991
#DisplayOnly -0.543472 # RecrDev_1992
#DisplayOnly -0.609505 # RecrDev_1993
#DisplayOnly 0.340329 # RecrDev_1994
#DisplayOnly -0.0701799 # RecrDev_1995
#DisplayOnly -0.159475 # RecrDev_1996
#DisplayOnly 0.44237 # RecrDev_1997
#DisplayOnly 0.1719 # RecrDev_1998
#DisplayOnly -0.419804 # RecrDev_1999
#DisplayOnly 0.302961 # RecrDev_2000
#DisplayOnly 0.312186 # RecrDev_2001
#DisplayOnly 0 # ForeRecr_2002
#DisplayOnly 0 # ForeRecr_2003
#DisplayOnly 0 # ForeRecr_2004
#DisplayOnly 0 # ForeRecr_2005
#DisplayOnly 0 # ForeRecr_2006
#DisplayOnly 0 # ForeRecr_2007
#DisplayOnly 0 # ForeRecr_2008
#DisplayOnly 0 # ForeRecr_2009
#DisplayOnly 0 # ForeRecr_2010
#DisplayOnly 0 # ForeRecr_2011
#DisplayOnly 0 # ForeRecr_2012
#DisplayOnly 0 # ForeRecr_2013

#Fishing Mortality info
0.3 # F ballpark for tuning early phases
2001 # F ballpark year (neg value to disable)
3 # F_Method:  1=Pope; 2=instan. F; 3=hybrid (hybrid is recommended)
2.9 # max F or harvest rate, depends on F_Method
4
# no additional F input needed for Fmethod 1
# read overall start F value; overall phase; N detailed inputs to read for Fmethod 2
# read N iterations for tuning for Fmethod 3 (recommend 3 to 7)
#Fleet Year Seas F_value se phase (for detailed setup of F_Method=2)


#_initial_F_parms
#_LO HI INIT PRIOR PR_type SD PHASE
 0 1 0 0.01 0 99 2 # InitF_1FISHERY1

#_Q_setup
 # A=do power, B=env-var, C=extra SD, D=devtype(<0=mirror, 0/1=none, 2=cons, 3=rand, 4=randwalk); E=0=num/1=bio, F=err_type
 #_A  B  C  D  E  F
 0 0 0 0 1 0 # 1 FISHERY1
 0 0 0 2 1 0 # 2 SURVEY1
 0 0 0 2 0 0 # 3 SURVEY2

#_Cond 0 #_If q has random component, then 0=read one parm for each fleet with random q; 1=read a parm for each year of index
#_Q_parms(if_any)
# LO HI INIT PRIOR PR_type SD PHASE
 -7 5 -0.14509 0 -1 1 1 # Q_base_2_SURVEY1
 -7 5 -6.43681 0 -1 1 1 # Q_base_3_SURVEY2

#_size_selex_types
#_Pattern Discard Male Special
 1 0 0 0 # 1 FISHERY1
 1 0 0 0 # 2 SURVEY1
 0 0 0 0 # 3 SURVEY2

#_age_selex_types
#_Pattern ___ Male Special
 11 0 0 0 # 1 FISHERY1
 11 0 0 0 # 2 SURVEY1
 11 0 0 0 # 3 SURVEY2
#_LO HI INIT PRIOR PR_type SD PHASE env-var use_dev dev_minyr dev_maxyr dev_stddev Block Block_Fxn
 19 80 55. 50 1 .01 2 0 0 0 0 0.5 0 0 # SizeSel_1P_1_FISHERY1
 0.01 60 20. 15 1 .01 3 0 0 0 0 0.5 0 0 # SizeSel_1P_2_FISHERY1
 19 70 36 30 1 .01 2 0 0 0 0 0.5 0 0 # SizeSel_2P_1_SURVEY1
 0.01 60 5. 10 1 .01 3 0 0 0 0 0.5 0 0 # SizeSel_2P_2_SURVEY1
 0 40 0 5 0 99 -1 0 0 0 0 0.5 0 0 # AgeSel_1P_1_FISHERY1
 0 40 40 6 0 99 -1 0 0 0 0 0.5 0 0 # AgeSel_1P_2_FISHERY1
 0 40 0 5 0 99 -1 0 0 0 0 0.5 0 0 # AgeSel_2P_1_SURVEY1
 0 40 40 6 0 99 -1 0 0 0 0 0.5 0 0 # AgeSel_2P_2_SURVEY1
 0 40 0 5 0 99 -1 0 0 0 0 0.5 0 0 # AgeSel_3P_1_SURVEY2
 0 40 0 6 0 99 -1 0 0 0 0 0.5 0 0 # AgeSel_3P_2_SURVEY2

#_Cond 0 #_custom_sel-env_setup (0/1)
#_Cond -2 2 0 0 -1 99 -2 #_placeholder when no enviro fxns


# Tag loss and Tag reporting parameters go next
0  # TG_custom:  0=no read; 1=read if tags exist
#_Cond -6 6 1 1 2 0.01 -4 0 0 0 0 0 0 0  #_placeholder if no parameters

1 #_Variance_adjustments_to_input_values
#_1 2 3
  0 0 0 #_add_to_survey_CV
  0 0 0 #_add_to_discard_stddev
  0 0 0 #_add_to_bodywt_CV
  1 1 1 #_mult_by_lencomp_N
  1 1 1 #_mult_by_agecomp_N
  1 1 1 #_mult_by_size-at-age_N
30 #_DF_for_discard_like
30 #_DF_for_meanbodywt_like

4 #_maxlambdaphase
1 #_sd_offset

3 # number of changes to make to default Lambdas (default value is 1.0)
# Like_comp codes:  1=surv; 2=disc; 3=mnwt; 4=length; 5=age; 6=SizeFreq; 7=sizeage; 8=catch;
# 9=init_equ_catch; 10=recrdev; 11=parm_prior; 12=parm_dev; 13=CrashPen; 14=Morphcomp; 15=Tag-comp; 16=Tag-negbin
#like_comp fleet/survey  phase  value  sizefreq_method
 1 2 2 1 1
 4 2 2 1 1
 4 2 3 1 1

# lambdas (for info only; columns are phases)
#  0 0 0 0 #_CPUE/survey:_1
#  1 1 1 1 #_CPUE/survey:_2
#  1 1 1 1 #_CPUE/survey:_3
#  1 1 1 1 #_lencomp:_1
#  1 1 1 1 #_lencomp:_2
#  0 0 0 0 #_lencomp:_3
#  1 1 1 1 #_agecomp:_1
#  1 1 1 1 #_agecomp:_2
#  0 0 0 0 #_agecomp:_3
#  1 1 1 1 #_size-age:_1
#  1 1 1 1 #_size-age:_2
#  0 0 0 0 #_size-age:_3
#  1 1 1 1 #_init_equ_catch
#  1 1 1 1 #_recruitments
#  1 1 1 1 #_parameter-priors
#  1 1 1 1 #_parameter-dev-vectors
#  1 1 1 1 #_crashPenLambda
1 # (0/1) read specs for more stddev reporting
 1 1 -1 5 1 5 # selex type, len/age, year, N selex bins, Growth pattern, N growth ages
 -5 16 27 38 46 # vector with selex std bin picks (-1 in first bin to self-generate)
 1 2 14 26 40 # vector with growth std bin picks (-1 in first bin to self-generate)
999

