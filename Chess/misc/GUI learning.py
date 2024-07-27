from tkinter import *

root = Tk()

##myLabel1 = Label(root, text="Hello World!")
##myLabel2 = Label(root, text="My Name is Ryan.")
##
##myLabel1.grid(row=0,column=0)
##myLabel2.grid(row=1,column=5)

def myClick():
    myLabel = Label(root, text="Look! I clicked a Button!!")
    myLabel.pack()

myButton = Button(root,text="Click Me!",command=myClick)
myButton.pack()

root.mainloop()
