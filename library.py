maxDays = 4
used_books = []

class Library:
    def __init__(self, libId, books, scanDays, maxPerDay):
        self.libId = libId;
        self.numBooks = len(books);
        self.books = books;
        #List of tuples [id, score]
        self.books.sort(key=lambda x: x[1], reverse=True);
        self.scanDays = scanDays;
        self.maxPerDay = maxPerDay;
        self.score = 0;

    def __repr__(self):
        return "id: {0}\nbookCount: {1}\nrate: {2}\nsignup_time: {3}".format(
            self.libId, self.numBooks, self.scanDays, self.maxPerDay
    )
    def scoreLib(self):
        curIndex = 0
        #Maxdays constant for our deadline day
        for i in range(maxDays - self.scanDays):
            maxIndex = min(curIndex+self.maxPerDay, self.numBooks-1)
            include_books = (score for book, score in self.books[curIndex: maxIndex] if book not in used_books)
            self.score += sum(include_books)
            curIndex = maxIndex
            #End if we've used all our books early.
            if curIndex >= self.numBooks:
                return self.score;
        return self.score;

