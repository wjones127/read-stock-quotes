quotes <- readLines(file("quotes.txt"))
table(nchar(quotes))
hist(as.numeric(quotes))


version <- c("Original", "Optimized")
benchmark <- c(0.098104,0.005397)
test.df <- data.frame(version, benchmark)

library(ggplot2)

ggplot(test.df, aes(x = version, y = benchmark)) + 
	geom_bar(stat="identity") +
	theme_bw() +
	labs(title = "Best Runtime of Function",
			 y = "Runtime (s)") 