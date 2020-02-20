from library import Library

def rankLibs(libs):
    libs.sort(key=lambda x: x.scoreLib(), reverse=True)

lib1 = Library(0, [[0,5],[1,2],[4,3]], 3, 1)
lib2 = Library(1, [[0,5],[1,2],[5,10]], 1, 2)
libs = [lib1, lib2]
rankLibs(libs)
print(lib1)
print('Ranked libs: ', list(libs))
