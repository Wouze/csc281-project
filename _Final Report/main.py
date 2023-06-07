from tkinter import *
from project import *
from tkinter.scrolledtext import ScrolledText

window = Tk()

window.title("Primitive Root Generator")

# Set the geometry of the window
window.geometry("500x600")

label1 = Label(window, text="Primitive Root Generator")
label1.config(font=("Courier", 18, 'bold'))
label1.config(fg="#0000FF")

label11 = Label(window, text="Enter a Prime number to find its primitive roots")
label2 = Label(window, text="Enter Number")

entry1 = Entry(window)

# Create another label
label3 = Label(window, text="Results")

# Create another text box
entry2 = ScrolledText(window)

def button_click():
    entry2.delete('1.0', END)

    try:
        prime = int(entry1.get())
    except:
        entry2.insert(INSERT,'Please insert numbers only')
        return

    if not is_prime(prime):
        entry2.insert(INSERT,f'{prime} is not prime number!')
        return
    
    primitive_roots = get_all_primitive_roots(prime)

    roots = ', '.join(map(str, primitive_roots))

    result = f'{prime} has {len(primitive_roots)} primitive roots, and they are:\n{roots}'


    entry2.insert(INSERT, result)


button = Button(window, text="Submit", command=button_click)

label1.pack(pady=10)
label11.pack(pady=10)
label2.pack()
entry1.pack()
button.pack(pady=10)
label3.pack()
entry2.pack()

window.mainloop()
