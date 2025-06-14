#!/usr/bin/env python3
"""
Object Placement Tool
Usage: python placement_tool.py <image_file.png> [source_file.c]
"""

import tkinter as tk
from tkinter import messagebox, simpledialog
from PIL import Image, ImageTk
import sys
import os
import re

class GamePlacementTool:
    def __init__(self, image_path, source_path=None):
        self.root = tk.Tk()
        self.root.title("Retro Game Object Placement Tool")
        self.root.geometry("1000x700")
        
        # Store source file path
        self.source_path = source_path
        self.existing_objects = []
        
        # Load and display image
        try:
            self.original_image = Image.open(image_path)
            self.image_width, self.image_height = self.original_image.size
        except Exception as e:
            messagebox.showerror("Error", f"Cannot load image: {e}")
            sys.exit(1)
        
        # Parse existing objects from source file if provided
        if self.source_path and os.path.exists(self.source_path):
            self.parse_source_file()
        
        # Grid size and zoom
        self.grid_size = 8
        self.zoom_factor = 1.0
        self.min_zoom = 0.25
        self.max_zoom = 4.0
        
        # Setup UI
        self.setup_ui()
        
        # Bind events
        self.canvas.bind("<Button-1>", self.on_canvas_click)
        self.canvas.bind("<Configure>", self.on_canvas_configure)
        self.canvas.bind("<MouseWheel>", self.on_mouse_wheel)  # Windows/Linux
        self.canvas.bind("<Button-4>", self.on_mouse_wheel)    # Linux scroll up
        self.canvas.bind("<Button-5>", self.on_mouse_wheel)    # Linux scroll down
        
        # Key bindings for scrolling and zooming
        self.root.bind("<Key>", self.on_key_press)
        self.root.focus_set()
        
        self.update_display()
    
    def parse_source_file(self):
        """Parse the source file to extract existing object positions"""
        try:
            with open(self.source_path, 'r') as f:
                content = f.read()
            
            # Look for the lookup table definition
            # Pattern to match: level_object level_X_X_lookup[] = { ... };
            pattern = r'level_object\s+\w+_lookup\[\]\s*=\s*\{(.*?)\};'
            match = re.search(pattern, content, re.DOTALL)
            
            if match:
                table_content = match.group(1)
                # Parse individual object entries
                # Pattern to match object entries like: {.x = 23, .y = 13, ...}
                object_pattern = r'\{\.x\s*=\s*(\d+),\s*\.y\s*=\s*(\d+),.*?\}'
                
                for obj_match in re.finditer(object_pattern, table_content, re.DOTALL):
                    x = int(obj_match.group(1))
                    y = int(obj_match.group(2))
                    self.existing_objects.append((x, y))
                
                print(f"Loaded {len(self.existing_objects)} existing objects from {self.source_path}")
            else:
                print(f"No lookup table found in {self.source_path}")
                
        except Exception as e:
            print(f"Error parsing source file: {e}")
    
    def setup_ui(self):
        # Create main frame
        main_frame = tk.Frame(self.root)
        main_frame.pack(fill=tk.BOTH, expand=True)
        
        # Create canvas with scrollbars
        canvas_frame = tk.Frame(main_frame)
        canvas_frame.pack(fill=tk.BOTH, expand=True)
        
        # Scrollbars
        v_scrollbar = tk.Scrollbar(canvas_frame, orient=tk.VERTICAL)
        v_scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        
        h_scrollbar = tk.Scrollbar(canvas_frame, orient=tk.HORIZONTAL)
        h_scrollbar.pack(side=tk.BOTTOM, fill=tk.X)
        
        # Canvas
        self.canvas = tk.Canvas(
            canvas_frame,
            scrollregion=(0, 0, self.image_width, self.image_height),
            yscrollcommand=v_scrollbar.set,
            xscrollcommand=h_scrollbar.set
        )
        self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        
        # Configure scrollbars
        v_scrollbar.config(command=self.canvas.yview)
        h_scrollbar.config(command=self.canvas.xview)
        
        # Info frame
        info_frame = tk.Frame(main_frame)
        info_frame.pack(fill=tk.X, pady=5)
        
        # Control buttons frame
        control_frame = tk.Frame(info_frame)
        control_frame.pack(pady=5)
        
        # Zoom controls
        tk.Button(control_frame, text="Zoom In (+)", command=self.zoom_in).pack(side=tk.LEFT, padx=5)
        tk.Button(control_frame, text="Zoom Out (-)", command=self.zoom_out).pack(side=tk.LEFT, padx=5)
        tk.Button(control_frame, text="Reset Zoom", command=self.reset_zoom).pack(side=tk.LEFT, padx=5)
        
        # Toggle existing objects visibility
        tk.Button(control_frame, text="Toggle Existing Objects", command=self.toggle_existing_objects).pack(side=tk.LEFT, padx=5)
        
        # Zoom level display
        self.zoom_label = tk.Label(control_frame, text="Zoom: 100%")
        self.zoom_label.pack(side=tk.LEFT, padx=10)
        
        # Existing objects count
        self.objects_label = tk.Label(control_frame, text=f"Existing Objects: {len(self.existing_objects)}")
        self.objects_label.pack(side=tk.LEFT, padx=10)
        
        # Instructions
        instructions = tk.Label(
            info_frame,
            text="Click on grid tiles to place objects. Arrow keys: scroll | +/-: zoom | Ctrl+wheel: zoom | Shift+wheel: horizontal scroll | 0: reset zoom | Blue squares: existing objects | Generated C code is copied to clipboard.",
            wraplength=800
        )
        instructions.pack(pady=5)
        
        # Status
        self.status_label = tk.Label(info_frame, text="Ready")
        self.status_label.pack()
        
        # Track visibility of existing objects
        self.show_existing_objects = True
    
    def update_display(self):
        # Clear canvas
        self.canvas.delete("all")
        
        # Calculate scaled dimensions
        scaled_width = int(self.image_width * self.zoom_factor)
        scaled_height = int(self.image_height * self.zoom_factor)
        
        # Resize image based on zoom
        if self.zoom_factor != 1.0:
            resized_image = self.original_image.resize((scaled_width, scaled_height), Image.NEAREST)
            self.photo = ImageTk.PhotoImage(resized_image)
        else:
            self.photo = ImageTk.PhotoImage(self.original_image)
        
        # Display image
        self.canvas.create_image(0, 0, anchor=tk.NW, image=self.photo)
        
        # Draw grid
        self.draw_grid()
        
        # Draw existing objects
        if self.show_existing_objects:
            self.draw_existing_objects()
        
        # Update scroll region
        self.canvas.configure(scrollregion=(0, 0, scaled_width, scaled_height))
        
        # Update zoom label
        self.zoom_label.config(text=f"Zoom: {int(self.zoom_factor * 100)}%")
    
    def draw_grid(self):
        # Calculate scaled dimensions and grid size
        scaled_width = int(self.image_width * self.zoom_factor)
        scaled_height = int(self.image_height * self.zoom_factor)
        scaled_grid_size = self.grid_size * self.zoom_factor
        
        # Calculate the number of grid lines based on original image dimensions
        grid_cols = self.image_width // self.grid_size
        grid_rows = self.image_height // self.grid_size
        
        # Draw vertical lines - use exact positioning based on grid count
        for i in range(grid_cols + 1):
            x = (i * scaled_width) // grid_cols if grid_cols > 0 else 0
            self.canvas.create_line(
                x, 0, x, scaled_height,
                fill="red", width=1, tags="grid"
            )
        
        # Draw horizontal lines - use exact positioning based on grid count  
        for i in range(grid_rows + 1):
            y = (i * scaled_height) // grid_rows if grid_rows > 0 else 0
            self.canvas.create_line(
                0, y, scaled_width, y,
                fill="red", width=1, tags="grid"
            )
    
    def draw_existing_objects(self):
        """Draw highlights for existing objects from the source file"""
        if not self.existing_objects:
            return
        
        # Calculate scaled dimensions
        scaled_width = int(self.image_width * self.zoom_factor)
        scaled_height = int(self.image_height * self.zoom_factor)
        grid_cols = self.image_width // self.grid_size
        grid_rows = self.image_height // self.grid_size
        
        for x, y in self.existing_objects:
            # Make sure coordinates are within bounds
            if 0 <= x < grid_cols and 0 <= y < grid_rows:
                # Calculate rectangle coordinates
                x1 = (x * scaled_width) // grid_cols
                y1 = (y * scaled_height) // grid_rows
                x2 = ((x + 1) * scaled_width) // grid_cols
                y2 = ((y + 1) * scaled_height) // grid_rows
                
                # Draw existing object highlight
                self.canvas.create_rectangle(
                    x1, y1, x2, y2,
                    fill="blue", stipple="gray50", outline="darkblue", width=2,
                    tags="existing_object"
                )
    
    def toggle_existing_objects(self):
        """Toggle visibility of existing objects"""
        self.show_existing_objects = not self.show_existing_objects
        self.update_display()
    
    def on_canvas_click(self, event):
        # Get canvas coordinates (accounting for scroll)
        canvas_x = self.canvas.canvasx(event.x)
        canvas_y = self.canvas.canvasy(event.y)
        
        # Calculate grid coordinates using the same method as grid drawing
        scaled_width = int(self.image_width * self.zoom_factor)
        scaled_height = int(self.image_height * self.zoom_factor)
        grid_cols = self.image_width // self.grid_size
        grid_rows = self.image_height // self.grid_size
        
        # Calculate which grid cell was clicked
        if grid_cols > 0 and grid_rows > 0:
            grid_x = int((canvas_x * grid_cols) // scaled_width)
            grid_y = int((canvas_y * grid_rows) // scaled_height)
            
            # Clamp to valid grid bounds
            grid_x = max(0, min(grid_x, grid_cols - 1))
            grid_y = max(0, min(grid_y, grid_rows - 1))
        else:
            grid_x = grid_y = 0
        
        # Check if there's already an object at this position
        if (grid_x, grid_y) in self.existing_objects:
            self.status_label.config(
                text=f"Object already exists at grid ({grid_x}, {grid_y})"
            )
            return
        
        # Prompt for object type
        object_type = self.prompt_object_type()
        
        if object_type:
            # Generate C code
            c_code = self.generate_c_code(grid_x, grid_y, object_type)
            
            # Copy to clipboard
            self.copy_to_clipboard(c_code)
            
            # Update status
            self.status_label.config(
                text=f"Placed {object_type} at grid ({grid_x}, {grid_y}) - C code copied to clipboard"
            )
            
            # Visual feedback - highlight the clicked tile
            self.highlight_tile(grid_x, grid_y)
    
    def prompt_object_type(self):
        # Create a custom dialog with predefined options
        dialog = ObjectTypeDialog(self.root)
        return dialog.result
    
    def generate_c_code(self, x, y, obj_type):
        # Map object types to C code templates
        templates = {
            "ENEMY": "{.x = %d,\n .y = %d,\n .type = OBJECT_TYPE_ENEMY,\n .data.enemy = {.type = ENEMY_GOOMBO}},",
            "PLATFORM": "{.x = %d,\n .y = %d,\n .type = OBJECT_TYPE_PLATFORM,\n .data.platform = {.type = PLATFORM_VERTICAL}},",
            "PLATFORM_MOVING": "{.x = %d,\n .y = %d,\n .type = OBJECT_TYPE_PLATFORM_MOVING,\n .data.platform_moving = {.range = 6,\n .platform_direction = DIRECTION_VERTICAL}},",
        }
        
        template = templates.get(obj_type, templates["ENEMY"])
        return template % (x, y)
    
    def copy_to_clipboard(self, text):
        self.root.clipboard_clear()
        self.root.clipboard_append(text)
        self.root.update()  # Ensure clipboard is updated
    
    def highlight_tile(self, grid_x, grid_y):
        # Remove previous highlights
        self.canvas.delete("highlight")
        
        # Calculate highlight rectangle using the same method as grid drawing
        scaled_width = int(self.image_width * self.zoom_factor)
        scaled_height = int(self.image_height * self.zoom_factor)
        grid_cols = self.image_width // self.grid_size
        grid_rows = self.image_height // self.grid_size
        
        if grid_cols > 0 and grid_rows > 0:
            x1 = (grid_x * scaled_width) // grid_cols
            y1 = (grid_y * scaled_height) // grid_rows
            x2 = ((grid_x + 1) * scaled_width) // grid_cols
            y2 = ((grid_y + 1) * scaled_height) // grid_rows
            
            self.canvas.create_rectangle(
                x1, y1, x2, y2,
                outline="yellow", width=3, tags="highlight"
            )
    
    def on_canvas_configure(self, event):
        # Update scroll region when canvas is resized
        self.canvas.configure(scrollregion=self.canvas.bbox("all"))
    
    def on_key_press(self, event):
        # Handle arrow key scrolling
        if event.keysym == "Up":
            self.canvas.yview_scroll(-1, "units")
        elif event.keysym == "Down":
            self.canvas.yview_scroll(1, "units")
        elif event.keysym == "Left":
            self.canvas.xview_scroll(-1, "units")
        elif event.keysym == "Right":
            self.canvas.xview_scroll(1, "units")
        # Handle zoom keys
        elif event.keysym == "plus" or event.keysym == "equal":
            self.zoom_in()
        elif event.keysym == "minus":
            self.zoom_out()
        elif event.keysym == "0":
            self.reset_zoom()
    
    def on_mouse_wheel(self, event):
        # Handle mouse wheel scrolling and zooming
        # Priority order: Ctrl+wheel = zoom, Shift+wheel = horizontal scroll, wheel = vertical scroll
        
        if event.state & 0x4:  # Ctrl key is pressed - zoom
            if event.delta > 0 or event.num == 4:  # Zoom in
                self.zoom_in()
            elif event.delta < 0 or event.num == 5:  # Zoom out
                self.zoom_out()
        elif event.state & 0x1:  # Shift key is pressed - horizontal scroll
            if event.delta > 0 or event.num == 4:  # Scroll left
                self.canvas.xview_scroll(-1, "units")
            elif event.delta < 0 or event.num == 5:  # Scroll right
                self.canvas.xview_scroll(1, "units")
        else:  # No modifier keys - vertical scroll
            if event.delta > 0 or event.num == 4:  # Scroll up
                self.canvas.yview_scroll(-1, "units")
            elif event.delta < 0 or event.num == 5:  # Scroll down
                self.canvas.yview_scroll(1, "units")
    
    def zoom_in(self):
        if self.zoom_factor < self.max_zoom:
            old_zoom = self.zoom_factor
            self.zoom_factor = min(self.zoom_factor * 1.25, self.max_zoom)
            self.update_zoom(old_zoom)
    
    def zoom_out(self):
        if self.zoom_factor > self.min_zoom:
            old_zoom = self.zoom_factor
            self.zoom_factor = max(self.zoom_factor / 1.25, self.min_zoom)
            self.update_zoom(old_zoom)
    
    def reset_zoom(self):
        old_zoom = self.zoom_factor
        self.zoom_factor = 1.0
        self.update_zoom(old_zoom)
    
    def update_zoom(self, old_zoom):
        # Get current scroll position as percentage
        x_pos = self.canvas.canvasx(self.canvas.winfo_width() / 2)
        y_pos = self.canvas.canvasy(self.canvas.winfo_height() / 2)
        
        # Update display
        self.update_display()
        
        # Adjust scroll position to maintain center point
        if old_zoom != 0:
            zoom_ratio = self.zoom_factor / old_zoom
            new_x = x_pos * zoom_ratio
            new_y = y_pos * zoom_ratio
            
            # Calculate new scroll positions
            canvas_width = self.canvas.winfo_width()
            canvas_height = self.canvas.winfo_height()
            scaled_width = int(self.image_width * self.zoom_factor)
            scaled_height = int(self.image_height * self.zoom_factor)
            
            if scaled_width > canvas_width:
                x_fraction = (new_x - canvas_width / 2) / (scaled_width - canvas_width)
                x_fraction = max(0, min(1, x_fraction))
                self.canvas.xview_moveto(x_fraction)
            
            if scaled_height > canvas_height:
                y_fraction = (new_y - canvas_height / 2) / (scaled_height - canvas_height)
                y_fraction = max(0, min(1, y_fraction))
                self.canvas.yview_moveto(y_fraction)
    
    def run(self):
        self.root.mainloop()


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
        self.result = obj_type
        self.dialog.destroy()
    
    def cancel(self):
        self.result = None
        self.dialog.destroy()


def main():
    if len(sys.argv) < 2:
        print("Usage: python placement_tool.py <image_file.png> [source_file.c]")
        sys.exit(1)
    
    image_path = sys.argv[1]
    source_path = sys.argv[2] if len(sys.argv) > 2 else None
    
    if not os.path.exists(image_path):
        print(f"Error: Image file '{image_path}' not found.")
        sys.exit(1)
    
    if source_path and not os.path.exists(source_path):
        print(f"Warning: Source file '{source_path}' not found. Continuing without existing objects.")
        source_path = None
    
    # Create and run the application
    app = GamePlacementTool(image_path, source_path)
    app.run()


if __name__ == "__main__":
    main()