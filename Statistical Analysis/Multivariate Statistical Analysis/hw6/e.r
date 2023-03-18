D831<-read.table("ex8-8.txt", header=F)
fre<-factanal(D831, 3, scores="Bartlett", rotation="none")
com1 <- prcomp(D831, center = TRUE,scale. = TRUE)
summary(com1)
