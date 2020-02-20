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
        self.score = self.scoreLib(daysLeft=maxDays, usedBooks=[])

    def __repr__(self):
        return "id: {0}\nbookCount: {1}\nrate: {2}\nsignup_time: {3}".format(
            self.libId, self.numBooks, self.scanDays, self.maxPerDay
    )

    def scoreLib(self, daysLeft, usedBooks):
        #Maxdays constant for our deadline day
        include_books = (score for (book, score) in self.books[maxPerDay * (daysLeft - self.scanDays)] if book not in used_books)
        self.score = sum(include_books)

