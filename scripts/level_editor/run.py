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

from game_placement_tool import GamePlacementTool

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