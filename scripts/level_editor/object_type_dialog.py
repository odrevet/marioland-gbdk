import tkinter as tk
from tkinter import messagebox, simpledialog
from PIL import Image, ImageTk
import sys
import os
import re

class ObjectTypeDialog:
    def __init__(self, parent):
        self.result = None
        
        # Create dialog window
        self.dialog = tk.Toplevel(parent)
        self.dialog.title("Select Object Type")
        self.dialog.geometry("350x250")
        self.dialog.transient(parent)
        
        # Center the dialog
        self.dialog.geometry("+%d+%d" % (
            parent.winfo_rootx() + 50,
            parent.winfo_rooty() + 50
        ))
        
        # Create buttons for object types
        tk.Label(self.dialog, text="Select object type:", font=("Arial", 12)).pack(pady=10)
        
        button_frame = tk.Frame(self.dialog)
        button_frame.pack(pady=10)
        
        object_types = ["ENEMY", "PLATFORM", "PLATFORM_MOVING"]
        
        for i, obj_type in enumerate(object_types):
            btn = tk.Button(
                button_frame,
                text=obj_type,
                width=15,
                command=lambda t=obj_type: self.select_type(t)
            )
            btn.grid(row=i//2, column=i%2, padx=5, pady=5)
        
        # Cancel button
        cancel_btn = tk.Button(
            self.dialog,
            text="Cancel",
            command=self.cancel
        )
        cancel_btn.pack(pady=10)
        
        # Make sure the dialog is visible before grabbing focus
        self.dialog.update_idletasks()
        self.dialog.deiconify()
        self.dialog.lift()
        self.dialog.grab_set()
        
        # Wait for user input
        self.dialog.wait_window()
    
    def select_type(self, obj_type):
        if obj_type == "ENEMY":
            # Prompt for enemy type when ENEMY is selected
            enemy_type = self.prompt_enemy_type()
            if enemy_type is not None:  # None means cancelled
                self.result = (obj_type, enemy_type)
            # If cancelled, result stays None and dialog closes
        else:
            self.result = (obj_type, None)
        
        self.dialog.destroy()
    
    def prompt_enemy_type(self):
        """Prompt for specific enemy type with default value"""
        return simpledialog.askstring(
            "Enemy Type",
            "Enter enemy type:",
            initialvalue="ENEMY_GOOMBO",
            parent=self.dialog
        )
    
    def cancel(self):
        self.result = None
        self.dialog.destroy()