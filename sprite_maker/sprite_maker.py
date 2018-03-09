#!/usr/bin/env python
# -*- coding: utf-8 -*-

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk as gtk

def MAIN_WIDTH(): return 800
def MAIN_HEIGHT(): return 800

def EDIT_HEIGHT(): return 200
def EDIT_WIDTH(): return 200

def SPRITE_SIZE(): return 20

class Colour_Chooser(gtk.Window):
    def __init__(self, button):
        super(Colour_Chooser, self).__init__()
        self.set_size_request(EDIT_HEIGHT(), EDIT_WIDTH())
        self.set_title('Choose A Colour')
        
        self.button = button
        
        self.connect('delete-event', self.close_window)
        self.show_all()
    
    def close_window(self, widget, data):
        self.destroy

class Pixel_Button(gtk.Button):
    def __init__(self):
        super(Pixel_Button, self).__init__()
        self.connect('clicked', self.open_editor, None)
        
        self.colour = None
        
    def open_editor(self, widget, data):
        #print 'pressed ', self
        colour_chooser = Colour_Chooser(self)
        
        #pass

class Sub_Menu(gtk.MenuItem):
    def __init__(self, name):
        super(Sub_Menu, self).__init__(name)
        
        self.menu = gtk.Menu()
        self.set_submenu(self.menu)
        
    def append(self, menu_item):
        self.menu.append(menu_item)
        
class Menu_Item(gtk.MenuItem):
    def __init__(self, name, func):
        super(Menu_Item, self).__init__(name)
        self.connect("activate", func, None)
        

class Editor_Window(gtk.Window):
    def __init__(self):
        super(Editor_Window, self).__init__()
        self.set_size_request(MAIN_WIDTH(), MAIN_HEIGHT())
        self.set_title('Sprite Editor')
        
        #vbox = gtk.VBox(False, 2)
        vbox = gtk.VBox()
        self.add(vbox)
        
        self.add_menu_bar(vbox)
        table = gtk.Table(10, 10)
        vbox.pack_end(table, True, True, 0)
        
        self.add_buttons(table)
        
        
        self.connect('delete-event', self.close_window)
        self.show_all()
        
    def load_file(self):
        pass
        
    def save_file(self):
        pass
        
    def add_buttons(self, table):
        self.pixels = [[Pixel_Button() for x in range(SPRITE_SIZE())] for y in range(SPRITE_SIZE())]
        for j in range(SPRITE_SIZE()):
            for i in range(SPRITE_SIZE()):
                p = self.pixels[j][i]
                p.show()
                table.attach(p, i, i + 1, j, j + 1)
    
    def add_menu_bar(self, vbox):
        menubar = gtk.MenuBar()
        file_menu = self.make_file_menu()
        menubar.append(file_menu)
        
        
        
        vbox.pack_start(menubar, False, False, 0)
        
    def make_file_menu(self):
        menu = Sub_Menu('File')
        
        save = Menu_Item('Save', self.save_file)
        menu.append(save)
        
        quit = Menu_Item('Exit', self.close_window)
        menu.append(quit)
        
        return menu
        
    def close_window(self, widget, data):
        self.destroy
        gtk.main_quit()

def main(args):
    Editor_Window()
    gtk.main()
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
