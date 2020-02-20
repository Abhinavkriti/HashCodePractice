
from read_input import input_reader
from library import Library
from output_excreter import excrete_output
file_list = [
    'a_example.txt',
    # 'b_read_on',
    # 'c_incunabula'
]

for filename in file_list:

    input_values = input_reader(filename)

    # for a, b in input_values.items():
    #     print(a, b)

    bookCount = input_values['bookCount']
    libraryCount = input_values['libraryCount']
    daysLeft = input_values['dayCount']
    scores = input_values['scores']
    libraries = input_values['libraries']

    # print('*'*30)


    libraryList = []
    usedBooks = set()
    nullLibrary = Library(-1, [], 0, 0, 0)
    nullLibrary.scoreLib(daysLeft, usedBooks)
    while daysLeft > 0 and libraries:

        bestLibrary = nullLibrary
        index = -1
        for i, library in enumerate(libraries):
            library.scoreLib(daysLeft, usedBooks)
            if library.score > bestLibrary.score:
                bestLibrary = library
                index = i
        libraries.pop(index)
        libraryList.append(bestLibrary)
        print('daysLeft', daysLeft)
        print('-'*15)
        print('used', usedBooks)
        print('include', bestLibrary.includeBooks)
        usedBooks.update(tuple(bestLibrary.includeBooks))

        daysLeft -= bestLibrary.scanDays


    # for library in libraryList:
    #     print(library)

    def calculate_score(libs):

        return sum([lib.score for lib in libs])

    print(calculate_score(libraryList))

    excrete_output(filename + '.out', libraryList)

# def rankLibs(libs):
#     libs.sort(key=lambda x: x.score, reverse=True)
