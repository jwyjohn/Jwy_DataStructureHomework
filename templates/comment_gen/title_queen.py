from pyfiglet import Figlet

f = Figlet(font='larry3d')
s = f.renderText('network')

s+="\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n"
print(s)
info = ["This is a program to optimize a plan for electric network.",
        "Input command 'adv A' to add a city named A.",
        "Input command 'ade A B 100' to add connect A WITH B at 100 million cost.",
        "Input command 'show' to inspect the graph.",
        "Use 'run A' to run optimization strating from city A.",
        "Use 'init' to clear graph WITH CAUTION."]
wid = len(s.split('\n')[0])
bar = '='*wid+'\n'
tip = "! "+'\n! '.join(info)
s += bar+tip+'\n'
print(s)
print("\"{}\"".format(s.replace('\\', "\\\\").replace('\n', "\\n")))

