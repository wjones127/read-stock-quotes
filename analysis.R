quotes <- readLines(file("quotes.txt"))
table(nchar(quotes))
hist(as.numeric(quotes))


version <- c("Original", "Optimized")
benchmark <- c(0.097483,0.005396)
test.df <- data.frame(version, benchmark)

library(ggplot2)

ggplot(test.df, aes(x = version, y = benchmark)) + 
	geom_bar(stat="identity") +
	theme_bw() +
	labs(title = "Best Runtime of Function",
			 y = "Runtime (sec.)") 

ggsave("runtime_plot.png", width = 0.75, height = 0.5, dpi = 100, scale = 5)
