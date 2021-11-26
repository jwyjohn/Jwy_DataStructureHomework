from pyfiglet import Figlet

f = Figlet(font='larry3d')
s = f.renderText('eval')

s += "\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n"
print(s)
info = ["This is a program to eval an expression.",
        "Use \\\"calc [expression]\\\" to caculate an expression with [0-9]+_*/()."]
wid = len(s.split('\n')[0])
bar = '='*wid+'\n'
tip = "! "+'\n! '.join(info)
s += bar+tip+'\n'
print(s)
print("\"{}\"".format(s.replace('\\', "\\\\").replace('\n', "\\n")))
