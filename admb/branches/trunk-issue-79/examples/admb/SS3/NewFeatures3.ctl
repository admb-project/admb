
#_data_and_control_files: NewFeatures3.dat // NewFeatures2.ctl
#_SS-V3.02B;_01/15/09;_Stock_Synthesis_by_Richard_Methot_(NOAA);_using_Otter_Research_ADMB_7.0.1
2  #_N_Growth_Patterns
3 #_N_Morphs_Within_GrowthPattern
1 #_Morph_between/within_stdev_ratio (no read if N_morphs=1)
 0.15 0.7 0.15 #vector_Morphdist_(-1_in_first_val_gives_normal_approx)
4 #  number of recruitment assignments (overrides GP*area*seas parameter values)
0 # recruitment interaction requested
#GP seas area for each recruitment assignment
 1 1 1
 2 1 2
 1 2 1
 2 2 2

4 #_N_movement_definitions
0.6 # first age that moves (real age at begin of season, not integer)
# seas,GP,source_area,dest_area,minage,maxage
 1 1 1 2 4 10
 1 1 2 1 4 10
 1 2 1 2 4 10
 1 2 2 1 4 10

3 #_Nblock_Patterns
 3 2 1 #_blocks_per_pattern
# begin and end years of blocks
 1975 1985 1986 1990 1995 2001
 1987 1990 1995 2001
 1999 2000

0.5 #_fracfemale
1 #_natM_type:_0=1Parm; 1=N_breakpoints;_2=Lorenzen;_3=agespecific;_4=agespec_withseasinterpolate
4 #_N_breakpoints
 2 4.5 9 15 # age(real) at M breakpoints
1 # GrowthModel: 1=vonBert with L1&L2; 2=Richards with L1&L2; 3=not implemented; 4=not implemented
1.66 #_Growth_Age_for_L1
25 #_Growth_Age_for_L2 (999 to use as Linf)
0 #_SD_add_to_LAA (set to 0.1 for SS2 V1.x compatibility)
0 #_CV_Growth_Pattern:  0 CV=f(LAA); 1 CV=F(A); 2 SD=F(LAA); 3 SD=F(A)
1 #_maturity_option:  1=length logistic; 2=age logistic; 3=read age-maturity matrix by growth_pattern; 4=read age-fecundity
#_placeholder for empirical age-maturity by growth pattern
1 #_First_Mature_Age
1 #_fecundity option:(1)eggs=Wt*(a+b*Wt);(2)eggs=a*L^b;(3)eggs=a*Wt^b
2 #_parameter_offset_approach (1=none, 2= M, G, CV_G as offset from female-GP1, 3=like SS2 V1.x)
1 #_env/block/dev_adjust_method (1=standard; 2=with logistic trans to keep within base parm bounds)

#_growth_parms
#_LO HI INIT PRIOR PR_type SD PHASE env-var use_dev dev_minyr dev_maxyr dev_stddev Block Block_Fxn
 0.05 0.95 0.1 0.1 -1 99 -4 0 0 0 0 0.5 0 0 # NatM_p_1_Fem_GP:1
 0.05 0.95 0.1 0.1 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_2_Fem_GP:1
 0.05 0.95 0.1 0.1 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_3_Fem_GP:1
 0.05 0.95 0.1 0.1 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_4_Fem_GP:1
 1 45 34.4315 36 0 10 2 0 0 0 0 0.5 0 0 # L_at_Amin_Fem_GP_1
 40 90 71.5265 70 0 10 4 0 0 0 0 0.5 0 0 # L_at_Amax_Fem_GP_1
 0.05 0.25 0.15135 0.15 0 0.8 4 0 0 0 0 0.5 0 0 # VonBert_K_Fem_GP_1
 0.05 0.25 0.1 0.1 0 0.8 -3 0 0 0 0 0.5 0 0 # CV_young_Fem_GP_1
 0.05 0.25 0.1 0.1 0 0.8 -3 0 0 0 0 0.5 0 0 # CV_old_Fem_GP_1
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_1_Fem_GP:2
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_2_Fem_GP:2
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_3_Fem_GP:2
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_4_Fem_GP:2
 -1 1 0 0 -1 99 -2 0 0 0 0 0.5 0 0 # L_at_Amin_Fem_GP_2
 -1 1 0.1 0 -1 99 -4 0 0 0 0 0.5 0 0 # L_at_Amax_Fem_GP_2
 -1 1 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # VonBert_K_Fem_GP_2
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # CV_young_Fem_GP_2
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # CV_old_Fem_GP_2
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_1_Mal_GP:1
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_2_Mal_GP:1
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_3_Mal_GP:1
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_4_Mal_GP:1
 -1 1 0 0 -1 99 -2 0 0 0 0 0.5 0 0 # L_at_Amin_Mal_GP_1
 -1 1 -0.1 0 -1 99 -4 0 0 0 0 0.5 0 0 # L_at_Amax_Mal_GP_1
 -1 1 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # VonBert_K_Mal_GP_1
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # CV_young_Mal_GP_1
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # CV_old_Mal_GP_1
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_1_Mal_GP:2
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_2_Mal_GP:2
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_3_Mal_GP:2
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # NatM_p_4_Mal_GP:2
 -1 1 0 0 -1 99 -2 0 0 0 0 0.5 0 0 # L_at_Amin_Mal_GP_2
 -1 1 0.2 0 -1 99 -4 0 0 0 0 0.5 0 0 # L_at_Amax_Mal_GP_2
 -1 1 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # VonBert_K_Mal_GP_2
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # CV_young_Mal_GP_2
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # CV_old_Mal_GP_2
 -3 3 2.44e-006 2.44e-006 -1 99 -3 0 0 0 0 0.5 0 0 # Wtlen_1_Fem
 -3 4 3.34694 3.34694 -1 99 -3 0 0 0 0 0.5 2 0 # Wtlen_2_Fem
 35 73 55 55 -1 99 -3 0 0 0 0 0.5 0 0 # Mat50%_Fem
 -3 3 -0.25 -0.25 -1 99 -3 0 0 0 0 0.5 0 0 # Mat_slope_Fem
 -3 3 1 1 -1 99 -3 0 0 0 0 0.5 0 0 # Eg/gm_inter_Fem
 -3 3 0 0 -1 99 -3 0 0 0 0 0.5 0 0 # Eg/gm_slope_wt_Fem
 -3 3 2.44e-006 2.44e-006 -1 99 -3 0 0 0 0 0.5 0 0 # Wtlen_1_Mal
 -3 4 3.34694 3.34694 -1 99 -3 0 0 0 0 0.5 0 0 # Wtlen_2_Mal
 -4 4 0 1 -1 99 -3 0 0 0 0 0.5 0 0 # RecrDist_GP_1
 -4 4 0 1 -1 99 -3 0 0 0 0 0.5 0 0 # RecrDist_GP_2
 -4 4 0 1 -1 99 -3 0 0 0 0 0.5 0 0 # RecrDist_Area_1
 -4 4 -4 1 -1 99 -3 0 0 0 0 0.5 0 0 # RecrDist_Area_2
 -4 4 0 1 -1 99 -3 0 0 0 0 0.5 0 0 # RecrDist_Seas_1
 -4 4 -4 1 -1 99 -3 0 0 0 0 0.5 0 0 # RecrDist_Seas_2
 -1 2 1 1 -1 99 -3 0 0 1980 1983 0.5 0 0 # CohortGrowDev
 -5 5 -4 0 0 99 -5 0 0 0 0 0.5 0 0 # MoveParm_A_seas_1_GP_1from_1to_2
 -5 5 -4 0 0 99 -5 0 0 0 0 0.5 0 0 # MoveParm_B_seas_1_GP_1from_1to_2
 -5 5 -4 0 0 99 -5 0 0 0 0 0.5 0 0 # MoveParm_A_seas_1_GP_1from_2to_1
 -5 5 -4 0 0 99 -5 0 0 0 0 0.5 0 0 # MoveParm_B_seas_1_GP_1from_2to_1
 -5 5 -4 0 0 99 -5 0 0 0 0 0.5 0 0 # MoveParm_A_seas_1_GP_2from_1to_2
 -5 5 -4 0 0 99 -5 0 0 0 0 0.5 0 0 # MoveParm_B_seas_1_GP_2from_1to_2
 -5 5 -4 0 0 99 -5 0 0 0 0 0.5 0 0 # MoveParm_A_seas_1_GP_2from_2to_1
 -5 5 -4 0 0 99 -5 0 0 0 0 0.5 0 0 # MoveParm_B_seas_1_GP_2from_2to_1

#_Cond 0  #custom_MG-env_setup (0/1)
#_Cond -2 2 0 0 -1 99 -2 #_placeholder when no MG-environ parameters

1 #_custom_MG-block_setup (0/1)
 -2 2 0 0 -1 99 -2 # Wtlen_2_Fem_BLK_1987
 -2 2 0 0 -1 99 -2 # Wtlen_2_Fem_BLK_1995

#_seasonal_effects_on_biology_parms
 0 0 0 0 0 0 0 61 0 0 #_femwtlen1,femwtlen2,mat1,mat2,fec1,fec2,Malewtlen1,malewtlen2,L1,K
 -2 2 0.0002 0 -1 99 -2 # M-WL2_seas_1
 -2 2 -0.0002 0 -1 99 -2 # M-WL2_seas_2

#_Cond -4 #_MGparm_Dev_Phase

#_Spawner-Recruitment
3 #_SR_function
#_LO HI INIT PRIOR PR_type SD PHASE
 7 15 9.94295 9.3 -1 10 1 # SR_R0
 0.2 1 0.604754 0.55 1 0.2 3 # SR_steep
 0 2 0.5 0.8 -1 0.8 -3 # SR_sigmaR
 -5 5 0 0 1 0.2 -3 # SR_envlink
 -5 5 0 0 -1 1 -3 # SR_R1_offset
 0 0.99 0 0 -1 1 -4 # SR_autocorr
3 #_SR_env_link
2 #_SR_env_target_0=none;1=devs;_2=R0;_3=steepness

1 #do_recdev:  0=none; 1=devvector; 2=simple deviations
1971 # first year of main recr_devs; early devs can preceed this era
2001 # last year of main recr_devs; forecast devs start in following year
3 #_recdev phase
1 # (0/1) to read 11 advanced options
 -10 #_recdev_early_start (0=none; neg value makes relative to recdev_start)
 5 #_recdev_early_phase
 5 #_forecast_recruitment phase (incl. late recr) (0 value resets to maxphase+1)
 1 #_lambda for prior_fore_recr occurring before endyr+1
 1974 #_last_early_yr_nobias_adj_in_MPD
 1980 #_first_yr_fullbias_adj_in_MPD
 2001 #_last_yr_fullbias_adj_in_MPD
 2002 #_first_recent_yr_nobias_adj_in_MPD
 -5 #min rec_dev
 5 #max rec_dev
 0 #_read_recdevs
#_end of advanced SR options

# read specified recr devs
#_Yr Input_value

# all recruitment deviations
#DisplayOnly 0 # InitAgeComp_21
#DisplayOnly 0 # InitAgeComp_20
#DisplayOnly 0 # InitAgeComp_19
#DisplayOnly 0 # InitAgeComp_18
#DisplayOnly 0 # InitAgeComp_17
#DisplayOnly 0 # InitAgeComp_16
#DisplayOnly 0 # InitAgeComp_15
#DisplayOnly 0 # InitAgeComp_14
#DisplayOnly 0 # InitAgeComp_13
#DisplayOnly 0 # InitAgeComp_12
#DisplayOnly 0 # InitAgeComp_11
#DisplayOnly 0 # InitAgeComp_10
#DisplayOnly 0 # InitAgeComp_9
#DisplayOnly 0 # InitAgeComp_8
#DisplayOnly 0 # InitAgeComp_7
#DisplayOnly 0 # InitAgeComp_6
#DisplayOnly 0 # InitAgeComp_5
#DisplayOnly 0 # InitAgeComp_4
#DisplayOnly 0 # InitAgeComp_3
#DisplayOnly 0 # InitAgeComp_2
#DisplayOnly 0 # InitAgeComp_1
#DisplayOnly 0 # RecrDev_1971
#DisplayOnly 0 # RecrDev_1972
#DisplayOnly 0 # RecrDev_1973
#DisplayOnly 0 # RecrDev_1974
#DisplayOnly 0 # RecrDev_1975
#DisplayOnly 0 # RecrDev_1976
#DisplayOnly 0 # RecrDev_1977
#DisplayOnly 0 # RecrDev_1978
#DisplayOnly 0 # RecrDev_1979
#DisplayOnly 0 # RecrDev_1980
#DisplayOnly 0 # RecrDev_1981
#DisplayOnly 0 # RecrDev_1982
#DisplayOnly 0 # RecrDev_1983
#DisplayOnly 0 # RecrDev_1984
#DisplayOnly 0 # RecrDev_1985
#DisplayOnly 0 # RecrDev_1986
#DisplayOnly 0 # RecrDev_1987
#DisplayOnly 0 # RecrDev_1988
#DisplayOnly 0 # RecrDev_1989
#DisplayOnly 0 # RecrDev_1990
#DisplayOnly 0 # RecrDev_1991
#DisplayOnly 0 # RecrDev_1992
#DisplayOnly 0 # RecrDev_1993
#DisplayOnly 0 # RecrDev_1994
#DisplayOnly 0 # RecrDev_1995
#DisplayOnly 0 # RecrDev_1996
#DisplayOnly 0 # RecrDev_1997
#DisplayOnly 0 # RecrDev_1998
#DisplayOnly 0 # RecrDev_1999
#DisplayOnly 0 # RecrDev_2000
#DisplayOnly 0 # RecrDev_2001
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

#Fishing Mortality info
0.1 # F ballpark for tuning early phases
1999 # F ballpark year (neg value to disable)
1 # F_Method:  1=Pope; 2=instan. F; 3=hybrid (hybrid is recommended)
0.9 # max F or harvest rate, depends on F_Method
# no additional F input needed for Fmethod 1
# read overall start F value; overall phase; N detailed inputs to read for Fmethod 2
# read N iterations for tuning for Fmethod 3 (recommend 3 to 7)
#Fleet Year Seas F_value se phase (for detailed setup of F_Method=2)


#_initial_F_parms
#_LO HI INIT PRIOR PR_type SD PHASE
 0 1 0.000 0.01 0 99 -1 # InitF_1CommFish
 0 1 0.000 0.01 0 99 -1 # InitF_2RecrFish

#_Q_setup
 # A=do power, B=env-var, C=extra SD, D=devtype(<0=mirror, 0/1=none, 2=cons, 3=rand, 4=randwalk); E=0=num/1=bio, F=err_type
 #_A  B  C  D  E  F
 1 0 0 4 1 0 # 1 CommFish
 0 0 0 0 1 30 # 2 RecrFish
 0 1 0 2 1 30 # 3 Twl_Svy
 0 0 1 2 0 30 # 4 Recr_Svy

1 #_0=read one parm for each fleet with random q; 1=read a parm for each year of index
#_Q_parms(if_any)
# LO HI INIT PRIOR PR_type SD PHASE
 0 1 0 0.1 0 99 -2 # Q_power_1_CommFish
 0 1 0 0.1 0 99 -2 # Q_envlink_3_Twl_Svy
 0 1 0 0.1 0 99 -2 # Q_extraSD_4_Recr_Svy
 -20 10 -7.493644 0 0 99 1 # Q_base_1_CommFish
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1972
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1973
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1974
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1975
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1976
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1977
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1978
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1979
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1980
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1981
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1982
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1983
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1984
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1985
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1986
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1987
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1988
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1989
 -2 2 0 0 1 0.01 -2 # Q_walk_1y_1990
 -10 10 -0.493644 0 0 99 1 # Q_base_3_Twl_Svy
 -10 10 -0.299345 0 0 99 1 # Q_base_4_Recr_Svy

#_size_selex_types
#_Pattern Discard Male Special
 24 2 0 0 # 1 CommFish
 1 -1 0 0 # 2 RecrFish
 1 0 0 0 # 3 Twl_Svy
 31 0 0 0 # 4 Recr_Svy

#_age_selex_types
#_Pattern ___ Male Special
 11 0 0 0 # 1 CommFish
 10 0 0 0 # 2 RecrFish
 11 0 0 0 # 3 Twl_Svy
 10 0 0 0 # 4 Recr_Svy
#_LO HI INIT PRIOR PR_type SD PHASE env-var use_dev dev_minyr dev_maxyr dev_stddev Block Block_Fxn
 31 85 69.8595 49 1 0.05 2 0 0 0 0 0.5 0 0 # SizeSel_1P_1_CommFish
 -6 4 -0.999998 -2.5 1 0.05 3 0 0 0 0 0.5 0 0 # SizeSel_1P_2_CommFish
 -1 9 8.71831 5 1 0.05 3 0 0 0 0 0.5 0 0 # SizeSel_1P_3_CommFish
 -1 9 4 6 1 0.05 3 0 0 0 0 0.5 0 0 # SizeSel_1P_4_CommFish
 -5 9 -3.72347 -1 1 0.05 2 0 0 0 0 0.5 0 0 # SizeSel_1P_5_CommFish
 -5 9 -0.548745 -1 1 0.05 2 0 0 0 0 0.5 0 0 # SizeSel_1P_6_CommFish
 20 70 45 40 0 99 -3 0 0 0 0 0 0 0 # Retain_1P_1_CommFish
 0.1 10 3 3 0 99 -3 0 0 0 0 0 0 0 # Retain_1P_2_CommFish
 0.001 1 1 1 0 99 -3 0 0 0 0 0 0 0 # Retain_1P_3_CommFish
 -10 10 0 0 0 99 -3 0 0 0 0 0 0 0 # Retain_1P_4_CommFish
 20 70 46 40 0 99 -3 0 0 0 0 0 0 0 # DiscMort_1P_1_CommFish
 0.1 10 0.8 1 0 99 -3 0 0 0 0 0 0 0 # DiscMort_1P_2_CommFish
 0.001 1 0.2 1 0 99 -3 0 0 0 0 0 0 0 # DiscMort_1P_3_CommFish
 -10 10 0 0 0 99 -3 0 0 0 0 0 0 0 # DiscMort_1P_4_CommFish
 19 70 36 30 1 .01 -2 0 0 0 0 0.5 0 0 # SizeSel_2P_1_RecrFish
 0.01 60 5. 10 1 .01 -3 0 0 0 0 0.5 0 0 # SizeSel_2P_2_RecrFish
 19 70 36 30 1 .01 2 0 0 0 0 0.5 0 0 # SizeSel_2P_1_SURVEY1
 0.01 60 5. 10 1 .01 3 0 0 0 0 0.5 0 0 # SizeSel_2P_2_SURVEY1
 0 40 0 5 0 99 -1 0 0 0 0 0.5 0 0 # AgeSel_1P_1_CommFish
 0 40 40 6 0 99 -1 0 0 0 0 0.5 0 0 # AgeSel_1P_2_CommFish
 0 40 0 5 0 99 -1 0 0 0 0 0.5 0 0 # AgeSel_3P_1_Twl_Svy
 0 40 40 6 0 99 -1 0 0 0 0 0.5 0 0 # AgeSel_3P_2_Twl_Svy
#_Cond 0 #_custom_sel-env_setup (0/1)
#_Cond -2 2 0 0 -1 99 -2 #_placeholder when no enviro fxns
#_Cond 0 #_custom_sel-blk_setup (0/1)
#_Cond -2 2 0 0 -1 99 -2 #_placeholder when no block usage
#_Cond -4 # placeholder for selparm_Dev_Phase
#_Cond 0 #_env/block/dev_adjust_method (1=standard; 2=logistic trans to keep in base parm bounds)

# Tag loss and Tag reporting parameters go next
0  # TG_custom:  0=no read; 1=read if tags exist
#_Cond -6 6 1 1 2 0.01 -4 0 0 0 0 0 0 0  #_placeholder if no parameters

0 #_Variance_adjustments_to_input_values
#_1 2 3 4
#_Cond  0 0 0 0 #_add_to_survey_CV
#_Cond  0 0 0 0 #_add_to_discard_stddev
#_Cond  0 0 0 0 #_add_to_bodywt_CV
#_Cond  1 1 1 1 #_mult_by_lencomp_N
#_Cond  1 1 1 1 #_mult_by_agecomp_N
#_Cond  1 1 1 1 #_mult_by_size-at-age_N
30 #_DF_for_discard_like
30 #_DF_for_meanbodywt_like

3 #_maxlambdaphase
1 #_sd_offset

1 # number of changes to make to default Lambdas (default value is 1.0)
# Like_comp codes:  1=surv; 2=disc; 3=mnwt; 4=length; 5=age; 6=SizeFreq; 7=sizeage; 8=catch;
# 9=init_equ_catch; 10=recrdev; 11=parm_prior; 12=parm_dev; 13=CrashPen; 14=Morphcomp; 15=Tag-comp; 16=Tag-negbin
#like_comp fleet/survey  phase  value  sizefreq_method
 1 1 1 0.0001 1

# lambdas (for info only; columns are phases)
#  1 1 1 #_CPUE/survey:_1
#  0 0 0 #_CPUE/survey:_2
#  1 1 1 #_CPUE/survey:_3
#  1 1 1 #_CPUE/survey:_4
#  1 1 1 #_discard:_1
#  0 0 0 #_discard:_2
#  0 0 0 #_discard:_3
#  0 0 0 #_discard:_4
#  1 1 1 #_meanbodywt:1
#  1 1 1 #_meanbodywt:2
#  1 1 1 #_meanbodywt:3
#  1 1 1 #_meanbodywt:4
#  1 1 1 #_lencomp:_1
#  0 0 0 #_lencomp:_2
#  1 1 1 #_lencomp:_3
#  0 0 0 #_lencomp:_4
#  1 1 1 #_agecomp:_1
#  0 0 0 #_agecomp:_2
#  1 1 1 #_agecomp:_3
#  0 0 0 #_agecomp:_4
#  1 0.7 0.7 #_sizefreq:_1
#  1 1 1 #_sizefreq:_2
#  1 1 1 #_size-age:_1
#  1 1 1 #_size-age:_2
#  0 0 0 #_size-age:_3
#  0 0 0 #_size-age:_4
#  1 1 1 #_init_equ_catch
#  1 1 1 #_recruitments
#  1 1 1 #_parameter-priors
#  1 1 1 #_parameter-dev-vectors
#  1 1 1 #_crashPenLambda
0 # (0/1) read specs for more stddev reporting
 # 0 1 -1 5 1 5 # placeholder for selex type, len/age, year, N selex bins, Growth pattern, N growth ages
 # placeholder for vector of selex bins to be reported
 # placeholder for vector of growth ages to be reported
999

