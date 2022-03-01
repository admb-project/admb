

# Load TMB
library( TMB )

# Set working directory (change on other machine!)
setwd( "." )

############
# Example 1 -- average CPUE for canary rockfish
############

# Data
if( FALSE ){
  #remotes::install_github("nwfsc-assess/geostatistical_delta-GLMM")
  data(WCGBTS_Canary_example, package="FishStatsUtils")
  CPUE = WCGBTS_Canary_example$HAUL_WT_KG
  saveRDS( CPUE, file="CPUE.rds")
}
CPUE = readRDS( file="CPUE.rds")

######### Method 1 -- Pre-made functions in R
library(mgcv)
Gam = gam( CPUE ~ 1, family="tw" )
summary(Gam)

###### Method 2 -- Optimize using TMB
compile( "Tweedie_demo.cpp" )
dyn.load( dynlib("Tweedie_demo") )
Params = list("ln_mu"=0, "ln_phi"=0, "power_prime"=0)
Data = list( "y_i"=CPUE )
Obj = MakeADFun( data=Data, parameters=Params, DLL="Tweedie_demo")
Opt = TMBhelper::fit_tmb( Obj )

# Compare mean
Opt$par['ln_mu']
Gam$coef

# Compare power
1 + plogis(Gam$family$getTheta())
1 + plogis(Opt$par['power_prime'])



