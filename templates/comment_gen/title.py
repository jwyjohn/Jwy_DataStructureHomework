from pyfiglet import Figlet

f = Figlet(font='larry3d')
s = f.renderText('queen')

s+="\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n"
print(s)
info = ["This is a program to solve the n-queen problem.",
        "Input command 'solve 8 n' to calculate the solutions in the n=8 case.",
        "If you want to see all the solution chess board in detail, use 'solve 8 n'.",
        "You can change 8 to any int (< than 32) to get more general solutions."]
wid = len(s.split('\n')[0])
bar = '='*wid+'\n'
tip = "! "+'\n! '.join(info)
s += bar+tip+'\n'
print(s)
print("\"{}\"".format(s.replace('\\', "\\\\").replace('\n', "\\n")))
