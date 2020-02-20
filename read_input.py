

def input_reader(filename):
    
    with open(filename) as f:
        text = f.readlines()
    info = list(map(int, text[0].split()))
    B = info[0]
    L = info[1]
    D = info[2]
    scores = list(map(int, text[1].split()))

    sections = text[2:]
    index = 0
    libraries = {}
    for i in range(L):
        num_books, signup_time, scan_rate = list(map(int, sections[index].split()))

        book_ids = list(map(int, sections[index+1].split()))
        books = [(book_id, scores[book_id]) for book_id in book_ids]
        libraries[i] = Library(
            libId=i, 
            books=books, 
            scanDays=signup_time, 
            maxPerDay=scan_rate
        )
        index += 2

    return {
        'bookCount' : B,
        'libraryCount' : L,
        'dayCount' : D,
        'scores' : scores,
        'libraries' : libraries
    }