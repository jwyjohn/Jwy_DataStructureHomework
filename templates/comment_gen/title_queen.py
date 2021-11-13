from pyfiglet import Figlet

f = Figlet(font='larry3d')
s = f.renderText('sort')

s+="\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n"
print(s)
info = ["This is a program to compare sort algorithms.",
        "Input command 'prep 10000 rand' to generate dataset.",
        "Input command 'show' to inspect dataset.",
        "If you want to see all the available algorithms , use 'help test'.",
        "Use 'test bubble' to run bubble sort on the dataset."]
wid = len(s.split('\n')[0])
bar = '='*wid+'\n'
tip = "! "+'\n! '.join(info)
s += bar+tip+'\n'
print(s)
print("\"{}\"".format(s.replace('\\', "\\\\").replace('\n', "\\n")))

