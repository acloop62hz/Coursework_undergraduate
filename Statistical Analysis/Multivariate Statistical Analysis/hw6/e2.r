data <- read.csv("data.csv",encoding = "UTF-8",na.strings=c(""," ","NA"),header=T)
com1 <- prcomp(data[,2:9], center = TRUE,scale. = TRUE)
summary(com1)
