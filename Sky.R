
Sky    = read.table("R/SkyRegion.txt", header=T, row.names=1)
Ctrd   = read.table("R/Centroid.txt",  header=T, row.names=1)

oldpar =  par(mfrow=c(2,1), mar=c(5, 4, 4, 2))
 

plot(1:length(Sky$sky), Sky$sky, xlab="secuencia de imagenes",
       ylab="fondo de cielo", type="b",
       main="Estimacion de fondo de cielo")
grid()


plot(1:length(Sky$skydev), Sky$skydev, xlab="secuencia de imagenes",
       ylab="desviacion tipica", type="b",
       main="Estimacion de sigma de fondo de cielo")
grid()
       
par(oldpar)