from pyfiglet import Figlet

f = Figlet(font='larry3d')
s = f.renderText('avlTree')

s+="\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n"
print(s)
info = ["This is a program to operate an AVL Tree.",
        "Input command 'add 19 7 6 4 ...' to add values to tree.",
        "Input command 'lvr', 'lvr' or to expolre the tree.",
        "Input command 'find 19 7 6 3...' to search value in the tree.",
        "Use 'rm 9 7 5 3...' to remove value in tree.",
        "Use 'init' to clear and init tree WITH CAUTION."]
wid = len(s.split('\n')[0])
bar = '='*wid+'\n'
tip = "! "+'\n! '.join(info)
s += bar+tip+'\n'
print(s)
print("\"{}\"".format(s.replace('\\', "\\\\").replace('\n', "\\n")))

