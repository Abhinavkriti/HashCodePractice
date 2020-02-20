class Library:
    def __init__(self, libId, books, scanDays, maxPerDay):
        self.libId = libId
        #List of tuples [id, score]
        books.sort(key=lambda x: x[1], reverse=True)
        self.books = books
        self.bookCount = len(self.books)
        self.scanDays = scanDays
        self.maxPerDay = maxPerDay
        self.score = 0
        
    def __repr__(self):
        
        return "id: {0}\nbookCount: {1}\nrate: {2}\nsignup_time: {3}".format(
            self.libId, self.bookCount, self.scanDays, self.maxPerDay
        )

    def scoreLib(self):
        curIndex = 0
        #Maxdays constant for our deadline day
        for i in range(maxDays - self.scanDays):
            self.score += sum()
