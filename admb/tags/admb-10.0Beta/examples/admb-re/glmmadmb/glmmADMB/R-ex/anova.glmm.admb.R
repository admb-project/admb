### Name: anova.glmm.admb
### Title: Anova for glmm.admb objects
### Aliases: anova.glmm.admb
### Keywords: models

### ** Examples

  data(epil2)
  f1<-glmm.admb(y~Base*trt+Age+Visit,random=~Visit,group="subject",data=epil2,family="nbinom")
  f2<-glmm.admb(y~Base*trt+Age,random=~Visit,group="subject",data=epil2,family="nbinom")
  anova(f2,f1)



