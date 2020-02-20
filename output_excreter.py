

def excrete_output(outfile, libraryList):

    A = len(libraryList)
    text = []
    for library in libraryList:
        line = [library.libId, len(library.includeBooks)]
        line = list(map(str, line))
        text.append(' '.join(line))

        books = list(map(lambda x: str(x[0]), library.includeBooks))
        text.append(' '.join(books))
    
    with open(outfile, 'w') as f:
        f.write('\n'.join(text))


