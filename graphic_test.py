import tkinter as tk

def move_up(event):
    canvas.move(front, 0, -10)  # Move up by 10 pixels

def move_left(event):
    canvas.move(front, -10, 0)  # Move left by 10 pixels

def move_down(event):
    canvas.move(front, 0, 10)  # Move down by 10 pixels

def move_right(event):
    canvas.move(front, 10, 0)  # Move right by 10 pixels

root = tk.Tk()
root.title("Moving Square")

canvas = tk.Canvas(root, width=400, height=400)
canvas.pack()

front = canvas.create_rectangle(50, 50, 150, 150, fill="blue")

root.bind("<w>", move_up)
root.bind("<a>", move_left)
root.bind("<s>", move_down)
root.bind("<d>", move_right)

canvas.focus_set()

root.mainloop()
