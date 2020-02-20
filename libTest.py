class lib():
    def __init__(self, libId, books, scanDays, maxPerDay):
        self.libId = libId;
        #List of tuples [id, score]
        self.books = books.sort(key=lambda x: x[1], reverse=True);
        self.scanDays = scanDays;
        self.maxPerDay = maxPerDay;
        self.score = 0;

def scoreLib(self):
    curIndex = 0
    #Maxdays constant for our deadline day
    for i in range(maxDays - self.scanDays):
        self.score += sum()

