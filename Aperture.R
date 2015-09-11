#----------------------------------------------------------------------

read.ascii.image <- function(path) {
	
	path = basename(path)
	path = paste("R", path, sep="/")
	asciifile = strsplit(path,'.',fixed=T)
	asciifile = asciifile[[1]][1]
	asciifile = paste(asciifile,"txt", sep=".")
		
	if(file.access(asciifile,0) == -1) {
		cat(sprintf("ERROR: El fichero ASCII %s no existe\n", asciifile))
		return(NULL)
	}
	
	as.matrix(read.table(asciifile,header=F))	
}


#----------------------------------------------------------------------

select.image <- function(file) {

	data.set = read.table(file,header=T,row.names=1)
    tag = select.list(row.names(data.set), title="¿ IMAGEN ?")

  	
  	if(length(tag) == 0) {
  		return(NULL)
  	}  
        tag
}


#----------------------------------------------------------------------

select.marginal <- function(file, tag=NULL) {

	marginal.data.set = read.table(file,header=T)
	attach(marginal.data.set)  
	
  	D = marginal[imagen == tag]   	
  	detach(marginal.data.set)
    D
}

#----------------------------------------------------------------------

read.data.set <- function(file, tag) {

    data.set = read.table(file,header=T,row.names=1)
	data.set[tag,]
}

#----------------------------------------------------------------------

marginal.plot<-function(M, MF, Sky, side, tag) {

  tag = basename(tag)
  # Pinta los elementos interesantes
  
  plot(1:length(M), M, xlab="posicion pixel",
       ylab=expression(sum(pix[n])), type="b",
       main=sprintf("Distribucion Marginal %s imagen %s", side, tag))
  
  skyth = 3*Sky$skydev  
  
  abline(v=MF$centroid,   col="blue",  lty=5) 
  abline(v=MF$centroid+MF$Rrecom, col="brown", lty=2)
  abline(v=MF$centroid-MF$Rrecom, col="brown", lty=2)
  abline(v=MF$upper+1, col="grey", lty=3)
  abline(v=MF$lower-1, col="grey", lty=3)
 
  
  ##abline(h=c$threshold,         col="red",   lty=2) 
  abline(h=skyth, col="red", lty=2)
  abline(h=0)
 
  text(10,skyth, "Sky", pos=3)  
  
}

#----------------------------------------------------------------------


continue.with.image <- function(tag) {

	si = sprintf("Ver imagen %s",tag)
	no = sprintf("No ver imagen %s",tag)
	resp = select.list( c(si,no), title="¿ CONTINUAR ?" )	
  	
  	if(length(resp) == 0) {
  		return(FALSE)
  	}
  	if(resp == si) {
 		TRUE
 	} else {
 		FALSE
 	}
}

#----------------------------------------------------------------------

set.aspect.ratio <-function(img) {
	
	pin = par('pin')
	cols = ncol(img)
	rows = nrow(img)
	
	ratio=min(cols, rows)/max(cols, rows)
	if(pin[1] > pin[2]) {
		pin[1] = ratio*pin[2]
	} else {
		pin[2] = ratio*pin[1]
	}
	
	par(pin=pin)
}


pinta.imagen <- function (img, c, sky, tag, sep=4, width=4) {

        tag = basename(tag)
	oldpar = set.aspect.ratio(img)
	
	# Notar que para pintar, las x y las y estan permutadas
	
	x = 1:ncol(img)
	y = 1:nrow(img)	
	
	# limites de valores para la paleta
	zlim=c(sky$sky-2*sky$skydev, sky$sky+4*sky$skydev)
	
	#image(y,x,img, zlim=zlim, col = rainbow(256,gamma=1,start=1/6),  xlab="filas", ylab="columnas")
	image(y,x,img, col = gray(1:256/256),  zlim=zlim, xlab="filas", ylab="columnas")
    box()
    title(main = sprintf("Aperturas para %s",tag), font.main = 4)


	R = c$Drecom/2
	
	# aperture circle
        
        discraper <- function(y) {
          discr = R*R-(y-c$centerY)*(y-c$centerY)
          discr[discr < 0] <- 0
          discr
        }
        
	posaper <- function(y) c$centerX+sqrt(discraper(y))
	negaper <- function(y) c$centerX-sqrt(discraper(y))

	# annulus innerc circle

        discranui <- function(y) {
          discr = (R+sep)*(R+sep)-(y-c$centerY)*(y-c$centerY)
          discr[discr < 0] <- 0
          discr
        }

        posanui <- function(y) c$centerX+sqrt(discranui(y))
        neganui <- function(y) c$centerX-sqrt(discranui(y))
    
       #annulus   outer circle

       discranuo <- function(y) {
          discr = (R+sep+width)*(R+sep+width)-(y-c$centerY)*(y-c$centerY)
          discr[discr < 0] <- 0
          discr
       }
        
        posanuo <- function(y) c$centerX+sqrt(discranuo(y))
 	neganuo <- function(y) c$centerX-sqrt(discranuo(y))

	# draws the circles
	
	col1="green"
	col2="red"
    curve(posaper, from=c$centerY-R, to=c$centerY+R,add=T,col=col1)
    curve(negaper, from=c$centerY-R, to=c$centerY+R,add=T,col=col1)
    
    curve(posanui, from=c$centerY-R-sep, to=c$centerY+R+sep,add=T,col=col1)
    curve(neganui, from=c$centerY-R-sep, to=c$centerY+R+sep,add=T,col=col1)
     
    curve(posanuo, from=c$centerY-R-sep-width, to=c$centerY+R+sep+width,add=T,col=col1)
    curve(neganuo, from=c$centerY-R-sep-width, to=c$centerY+R+sep+width,add=T,col=col1)
    
    # centroid line
     
  	abline(h=c$centerX,lty=2,col=col2)
  	abline(v=c$centerY,lty=2,col=col2)
  	
  	par(oldpar)

}



main <- function() {

  oldpar =  par(mfrow=c(2,1), mar=c(5, 4, 4, 2))
  
  tag = select.image("R/Centroid.txt")
  
  MX = select.marginal("R/MarginalX.txt", tag)
  MY = select.marginal("R/MarginalY.txt", tag)
  
  MX.Fea = read.data.set("R/FeaturesX.txt", tag)
  MY.Fea = read.data.set("R/FeaturesY.txt", tag)
    
  Sky    = read.data.set("R/SkyRegion.txt", tag)
  Ctrd   = read.data.set("R/Centroid.txt",  tag)
  
  
  # Pinta los marginales

  marginal.plot(MX, MX.Fea, Sky, "X", tag)
  marginal.plot(MY, MY.Fea, Sky, "Y", tag)
  
  # continua con la imagen si asi se desea
  
  if(continue.with.image(tag)) {   
  	img = read.ascii.image(tag)
  	if(!is.null(img)) { 
    	par(mfrow=c(1,1)) 
  		pinta.imagen(img, Ctrd, Sky, tag) 
  	}
  }
  
  par(oldpar)
}


main()

