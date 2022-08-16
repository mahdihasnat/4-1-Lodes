#!/bin/python3

# from tkinter import *
# from PIL import Image, ImageTk

# root=Tk()

# root.title("My Image")

# image = Image.open("Output_11.bmp")
# # get width and height of image
# (width, height) = image.size
# w = Canvas(root, width=width, height=height)
# w.create_image((0, 0), image=ImageTk.PhotoImage(image))

# w.pack(expand=1)

# root.mainloop()

# 

import imghdr
from tkinter import *
from turtle import width

# pip install pillow
from PIL import Image, ImageTk

class Window(Frame):
	def __init__(self, master=None):
		Frame.__init__(self, master)
		self.master = master
		self.pack(fill=BOTH, expand=1)
		
		load = Image.open("Output_11.bmp")
		self.load = load
		render = ImageTk.PhotoImage(load)
		img = Label(self, image=render)
		self.img = img
		img.image = render
		img.place(x=0, y=0)

	def get_geomety(self):
		(width,height) = self.load.size
		return "{}x{}".format(width+2,height+2)
	def reload(self,root):
		# update frame with image
		self.load = Image.open("Output_11.bmp")
		render = ImageTk.PhotoImage(self.load)
		self.img.configure(image=render)
		self.img.image=render

		root.geometry(self.get_geomety())

		print("reloaded")
		root.after(1000,lambda:self.reload(root))

root = Tk()
app = Window(root)

root.wm_title("Tkinter window")
root.attributes('-topmost', True)
root.geometry(app.get_geomety())
root.after(1000,lambda :app.reload(root))

root.mainloop()