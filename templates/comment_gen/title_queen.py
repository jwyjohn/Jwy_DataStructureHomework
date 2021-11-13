from pyfiglet import Figlet

f = Figlet(font='larry3d')
s = f.renderText('exam')

s += "\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n"
print(s)
info = ["This is a program to manage exam students.",
        "Can also save student info to a file.",
        "Input command 'i insert_position No. name gender age subject' to insert a student.",
        "Input command 'f No.' to find info about a student.",
        "Input command 'd No.' to delete a student.",
        "Input command 'm No. new_No. new_name new_gender new_age new_subject' to modify student info.",
        "Input command 's' to show statistcal data.",
        "Input command 'l' to list all students.",
        "Use 'w' WITH CAUTION to save data to student_data.txt because it can overwrite existing file."]
wid = len(s.split('\n')[0])
bar = '='*wid+'\n'
tip = "! "+'\n! '.join(info)
s += bar+tip+'\n'
print(s)
print("\"{}\"".format(s.replace('\\', "\\\\").replace('\n', "\\n")))
