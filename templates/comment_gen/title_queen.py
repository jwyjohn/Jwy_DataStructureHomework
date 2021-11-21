from pyfiglet import Figlet

f = Figlet(font='larry3d')
s = f.renderText('joseph')

s += "\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n"
print(s)
info = ["This is a program to simulate the Joseph problem.",
        "Use 'solve [N] [S] [M] [K]', to solve a Joseph case with N participants,",
        " start from position S, kill every M position, and have K survivors. ",
        "(note: N>K>0, N>=S>=1 and M>0)"]
wid = len(s.split('\n')[0])
bar = '='*wid+'\n'
tip = "! "+'\n! '.join(info)
s += bar+tip+'\n'
print(s)
print("\"{}\"".format(s.replace('\\', "\\\\").replace('\n', "\\n")))
