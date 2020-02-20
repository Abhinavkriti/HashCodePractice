

def excrete_output(outfile, libraryList):

    A = len(libraryList)
    text = []
    for library in libraryList:
        line = [library.libId, len(library.includeBooks)]

        books = list(map(lambda x: x[0], library.includeBooks))
        line.extend(books)

        text.append(' '.join(line))
    
    with open(outfile, 'w') as f:
        f.write('\n'.join(text))


