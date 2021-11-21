from pyfiglet import Figlet

f = Figlet(font='larry3d')
s = f.renderText('maze')

s += "\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n"
print(s)
info = ["This is a program to simulate the Joseph problem.",
        "FIRST, use 'init [H] [W]', to initialize a H*W maze. (H,W >= 10)",
        "Then use 'solve', to solve the maze.",
        "Use 'show', to show the maze."]
wid = len(s.split('\n')[0])
bar = '='*wid+'\n'
tip = "! "+'\n! '.join(info)
s += bar+tip+'\n'
print(s)
print("\"{}\"".format(s.replace('\\', "\\\\").replace('\n', "\\n")))
