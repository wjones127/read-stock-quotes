quotes <- readLines(file("quotes.txt"))
table(nchar(quotes))
hist(as.numeric(quotes))
