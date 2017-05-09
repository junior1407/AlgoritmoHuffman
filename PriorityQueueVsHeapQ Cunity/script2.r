library(ggplot2)
multiplot <- function(..., plotlist=NULL, file, cols=1, layout=NULL) {
  library(grid)
  plots <- c(list(...), plotlist)
  numPlots = length(plots)
  if (is.null(layout)) {
    layout <- matrix(seq(1, cols * ceiling(numPlots/cols)),
                     ncol = cols, nrow = ceiling(numPlots/cols))
  }
  
  if (numPlots==1) {
    print(plots[[1]])
    
  } else {
    grid.newpage()
    pushViewport(viewport(layout = grid.layout(nrow(layout), ncol(layout))))
    for (i in 1:numPlots) {
      matchidx <- as.data.frame(which(layout == i, arr.ind = TRUE))
      print(plots[[i]], vp = viewport(layout.pos.row = matchidx$row,
                                      layout.pos.col = matchidx$col))
    }
  }
}

library(readr)
tableheap <- read_csv("~/GitHub/AlgoritmoHuffman/PriorityQueueVsHeapQ Cunity/cmake-build-debug/saidaheap.csv")
tablepqueue <- read_csv("~/GitHub/AlgoritmoHuffman/PriorityQueueVsHeapQ Cunity/cmake-build-debug/saidapqueue.csv")

g1 <- ggplot(data = tablepqueue, aes(x = size,y = comparisons)) +theme(legend.title=element_blank()) +geom_point(color='cyan3') +xlab("Size")+ ylab("Comparisons")+ggtitle("Gráfico Pqueue") +stat_function(fun=function(x)x, geom="line", aes(colour="O(n)"))

g2<- ggplot(data = tableheap, aes(x = size,y = comparisons)) +theme(legend.title=element_blank()) +geom_point(color='cyan3') +xlab("Size")+ ylab("Comparisons")+ggtitle("Gráfico Heap") +stat_function(fun=function(x)log2(x), geom="line", aes(colour="O(Log(n)"))
