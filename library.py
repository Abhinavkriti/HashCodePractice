
class Library:
    def __init__(self, libId, books, scanDays, maxPerDay, maxDays):
        self.libId = libId;
        self.numBooks = len(books);
        self.books = books;
        #List of tuples [id, score]
        self.books.sort(key=lambda x: x[1], reverse=True);
        self.scanDays = scanDays;
        self.maxPerDay = maxPerDay;
        # self.scoreLib(daysLeft=maxDays, usedBooks=[])

    def __repr__(self):
        return "id: {0}\nbookCount: {1}\nrate: {2}\nsignup_time: {3}".format(
            self.libId, self.numBooks, self.scanDays, self.maxPerDay
    )

    def scoreLib(self, daysLeft, usedBooks):
        #Maxdays constant for our deadline day
        self.includeBooks = []
        if daysLeft <= self.scanDays:
            return 0
        end_index = self.maxPerDay * (daysLeft - self.scanDays)
        self.includeBooks = [score for (book, score) in self.books if book not in usedBooks][:end_index]
        self.score = sum(self.includeBooks)

