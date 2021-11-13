from pyfiglet import Figlet

f = Figlet(font='larry3d')
s = f.renderText('KMP')

s += "\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n"
print(s)
info = ["This is a program to find substring in a file.",
        "Can also create, read, append a file.",
        "Input command 'c mytext.txt' to create mytext.txt.",
        "Input command 'r mytext.txt' to read from mytext.txt.",
        "Input command 'a mytext.txt' to append content to mytext.txt.",
        "Input command 's' to show loaded text.",
        "Input command 'f substr' to serach substr in loaded text.",
        "Use 'c mytext.txt' WITH CAUTION because it can overwrite existing file."]
wid = len(s.split('\n')[0])
bar = '='*wid+'\n'
tip = "! "+'\n! '.join(info)
s += bar+tip+'\n'
print(s)
print("\"{}\"".format(s.replace('\\', "\\\\").replace('\n', "\\n")))
