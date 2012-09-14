##################################################################################
###   Sample R program for testing and demonstrating the "FishGraph" collection
###   of R graphics functions for analysis of stock-assessment results.
###   M.H. Prager, June, 2007 -- K.W. Shertzer/M.H. Prager, Jan, 2008.
###   This is modified for the red snapper example included with ADMB2R.
##################################################################################

##### Specify where the FishGraph functions are located:
##### The following is the default location for the auto-installer:
codepath <-  paste(Sys.getenv("homedrive"), Sys.getenv("homepath"),
    "\\My Documents\\FishGraph\\functions",sep = "")
# Note: instead of the above, you can use a simple text string, such as:
# codepath <- "C:\\Documents and Settings\\Joe Blow\\Fishgraph\\functions"
# Note:  You must use two "\" to get one under R.  Or use "/" instead.

##### Read in the data from the ASCII .rdat file: #####
rs <- dget("rs196.rdat")

########## Source the graphics functions #########################
source(file.path(codepath, "fgsupport.r"))
source(file.path(codepath, "rdat2ascii.r"))
source(file.path(codepath, "BSR.time.plots.r"))
source(file.path(codepath, "CLD.total.plots.r"))
source(file.path(codepath, "Comp.plots.r"))
source(file.path(codepath, "Comp.yearly.plots.r"))
source(file.path(codepath, "F.time.plots.r"))
source(file.path(codepath, "Growth.plots.r"))
source(file.path(codepath, "index.plots.r"))
source(file.path(codepath, "Landings.plots.r"))
source(file.path(codepath, "NFZ.age.plots.r"))
source(file.path(codepath, "PerRec.plots.r"))
source(file.path(codepath, "EqRec.plots.r"))
source(file.path(codepath, "Selectivity.plots.r"))
source(file.path(codepath, "StockRec.plots.r"))
FGSetDefaults()             # set up default colors, etc.

ptype = "jpg"    #NULL (no quotes) for no plots saved to files
dtype = "TRUE" #draft type
########## Close open graphics devices & delete plot history ###########
graphics.off()
.SavedPlots <- NULL

########## Call the functions #########################

#windows(width = 8, height = 10, record = TRUE, xpos = 10, ypos = 10)
#FGoptions$graphics$fglayout=c(5,3)
#Comp.yearly.plots(rs, graphics.type = ptype, plot.neff=FALSE, compact = TRUE,
#                  print.n=TRUE, print.angle=FALSE)

windows(width = 8, height = 6, record = TRUE, xpos = 10, ypos = 10)
source(file.path(codepath, "fgsupport.r"))

Comp.plots(rs, graphics.type = ptype, draft = dtype, use.color=FALSE)

Index.plots(rs, graphics.type = ptype, log.resid = FALSE, draft = dtype)

Landings.plots(rs, graphics.type = ptype, L.units="1000 lb", 
    D.units="1000 dead fish", draft = dtype)

F.time.plots(rs, graphics.type = ptype, start.drop = 0, use.color = FALSE,
    draft = FALSE, F.references=NULL)

NFZ.age.plots(rs,graphics.type=ptype, use.color=TRUE, 
    user.plots=c("N.age.mdyr"), draft = dtype)
    
Growth.plots(rs, graphics.type = ptype, plot.all = TRUE, draft = dtype)

PerRec.plots(rs, graphics.type = ptype, use.color = TRUE,
    user.PR = list("SPR"), draft = dtype)

EqRec.plots(rs, graphics.type = ptype, use.color = TRUE, draft = dtype,
    user.Eq = list("spr", "E.eq"))

StockRec.plots(rs, graphics.type = ptype, draw.lowess = FALSE, use.color = TRUE,
    start.drop = 0, draft = dtype)

windows(width = 8, height = 5, record = TRUE, xpos = 10, ypos = 10)
CLD.total.plots(rs, graphics.type = ptype, first.year = rs$parms$styr,
    plot.proportion = TRUE, use.color=FALSE, draft = dtype)
BSR.time.plots(rs, start.drop = 0, use.color = TRUE, graphics.type = ptype, 
  draft = dtype)


#windows(width = 6, height = 3, record = TRUE, xpos = 10, ypos = 10)
#Selectivity.plots(rs, graphics.type = ptype, draft = dtype)


##### Uncomment the following line to run a function for saving the data
##### object into an ASCII file (for spreadsheet users, etc.)

#rdat2ascii(rs)

###########################
###ADDITIONAL PLOTS
# windows(width = 8, height = 5, record = TRUE, xpos = 10, ypos = 10)
# R <- rs$t.series$recruits[2:63]
# S <- rs$t.series$SSB[1:62]
# h <- rs$parms$BH.steep
# R0 <- rs$parms$BH.R0
# BC=rs$parms$BH.biascorr
# Phi0=rs$parms$BH.Phi0
# S.sim=seq(0,max(S)+10, length=1000)
# R.S.sim=BC*0.8*R0*h/(0.2*Phi0*R0*(1-h) + (h-0.2)*S.sim)
# plot(S.sim,log(R.S.sim), type="l",lwd=2,
#    ylim = c(log(min(c(R.S.sim,R/S))),log(max(c(R.S.sim,R/S)))),
#    ylab = "log(Recruits/Spawner)", xlab="Spawners (mt)")
# points(S,log(R/S))
# savePlot("rs-figs/rs.logRperS", type=ptype)
# plot(S.sim,log(R.S.sim), type="l",lwd=2,
#    ylim = c(6,log(max(c(R.S.sim,R/S)))),
#    xlim = c(0,1200),
#    ylab = "log(Recruits/Spawner)", xlab="Spawners (mt)")
# points(S,log(R/S))
# savePlot("rs-figs/rs.logRperS.zoom", type=ptype)
rm(codepath)
