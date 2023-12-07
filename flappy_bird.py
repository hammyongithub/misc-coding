import tkinter as tk
import random

root = tk.Tk()
root.title("Gravity Simulation")

canvas = tk.Canvas(root, width=1000, height=500, bg="white")
canvas.pack()

# Game objects
circle = canvas.create_oval(190, 50, 210, 70, fill="blue")
coords_display = canvas.create_text(50, 10, text="")
start_text = canvas.create_text(500, 250, text="Press 'S' to start and 'Q' to quit. Use 'Space' to jump", font=("Arial", 20), fill="black")

# Game variables
gravity = 0.1
velocity = 0
pipes = []
game_active = False

# Movement
def jump(event):
    global velocity
    if game_active:
        velocity = -4

# Pipes and Collision
def create_pipe():
    if game_active:
        canvas_height = canvas.winfo_height()
        upper_pipe_height = random.randint(100, 300)
        gap_size = 100

        lower_pipe_height = canvas_height - (upper_pipe_height + gap_size)
        upper_pipe = canvas.create_rectangle(1000, 0, 1050, upper_pipe_height, fill="green")
        lower_pipe_y_start = upper_pipe_height + gap_size
        lower_pipe = canvas.create_rectangle(1000, lower_pipe_y_start, 1050, lower_pipe_y_start + lower_pipe_height, fill="green")
        
        pipes.append((upper_pipe, lower_pipe))
        root.after(2000, create_pipe)

def move_pipes():
    for upper_pipe, lower_pipe in pipes:
        canvas.move(upper_pipe, -5, 0)  # Adjust speed as needed
        canvas.move(lower_pipe, -5, 0)

        if canvas.coords(upper_pipe)[2] < 0:
            canvas.delete(upper_pipe)
            canvas.delete(lower_pipe)
            pipes.remove((upper_pipe, lower_pipe))

def check_collision():
    x1, y1, x2, y2 = canvas.coords(circle)
    for upper_pipe, lower_pipe in pipes:
        upx1, upy1, upx2, upy2 = canvas.coords(upper_pipe)
        lpx1, lpy1, lpx2, lpy2 = canvas.coords(lower_pipe)
        if (x1 < upx2 and x2 > upx1 and y1 < upy2 and y2 > upy1) or \
            (x1 < lpx2 and x2 > lpx1 and y1 < lpy2 and y2 > lpy1):
            return True
    return False

# Gravity and Bounce
def update_position():
    global velocity
    if game_active:
        x1, y1, x2, y2 = canvas.coords(circle)
        velocity += gravity
        canvas.move(circle, 0, velocity)

        _, _, _, new_y2 = canvas.coords(circle)
        if new_y2 >= canvas.winfo_height():
            canvas.move(circle, 0, canvas.winfo_height() - new_y2)
            velocity = -velocity * 0.35

        if check_collision():
            reset_game()
        else:
            move_pipes()
            root.after(10, update_position)

# Utility
def update_coords(event):
    x, y = event.x, event.y
    canvas.itemconfigure(coords_display, text=f"({x}, {y})")

# Game Status
def show_start_text():
    canvas.itemconfigure(start_text, state='normal')

def hide_start_text():
    canvas.itemconfigure(start_text, state='hidden')

def reset_game():
    global velocity, pipes, game_active
    velocity = 0
    for pipe in pipes:
        canvas.delete(pipe[0])
        canvas.delete(pipe[1])
    pipes.clear()
    canvas.coords(circle, 190, 50, 210, 70)
    game_active = False
    show_start_text()

def start(event):
    global game_active
    if not game_active:
        game_active = True
        hide_start_text()
        create_pipe()
        update_position()

def close_program(event):
    root.destroy()

# Bindings
root.bind("<space>", jump)
root.bind("<s>", start)
root.bind("<Motion>", update_coords)
root.bind("<q>", close_program)

show_start_text()
root.mainloop()
