### Name: glmm.admb
### Title: Generalized Linear Mixed Models using AD Model Builder
### Aliases: glmm.admb
### Keywords: models

### ** Examples

  data(epil2)
  glmm.admb(y~Base*trt+Age+Visit,random=~Visit,group="subject",data=epil2,family="nbinom")



