# Does the timing of nlme() under Splus
fm1Oran.lis <- nlsList(circumference ~ SSlogis(age, Asym, xmid, scal) | Tree,data = Orange)
fm2Oran.nlme <- nlme( circumference ~ SSlogis(age, Asym, xmid, scal), data = Orange, fixed = Asym + xmid + scal ~ 1, random = Asym ~ 1, start = fixef(fm1Oran.lis) )
dos.time(nlme( circumference ~ SSlogis(age, Asym, xmid, scal), data = Orange, fixed = Asym + xmid + scal ~ 1, random = Asym ~ 1, start = fixef(fm1Oran.lis) ))
