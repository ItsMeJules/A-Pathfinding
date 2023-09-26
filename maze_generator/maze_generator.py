import sys
import os
import random

if len(sys.argv) != 4:
    print("Usage: python3 generate_maze.py <width> <height> <depth>")
    sys.exit(1)

width = int(sys.argv[1])
height = int(sys.argv[2])
depth = int(sys.argv[3])

def generate_maze(width, height, depth):
    maze = []
    for _ in range(depth):
        zLayer = []
        for _ in range(height):
            xLayer = ''.join(random.choice('01') for _ in range(width))
            zLayer.append(xLayer)
        maze.append(zLayer)
    return maze

def is_wall(maze, x, y, z):
    return maze[z][y][x] == '1'

def find_valid_position(maze):
    while True:
        x = random.randint(0, width - 1)
        y = random.randint(0, height - 1)
        z = random.randint(0, depth - 1)
        if not is_wall(maze, x, y, z):
            return x, y, z

def write_maze_to_file(maze):
    fileName = f"maze{width}x{height}x{depth}"

    start_x, start_y, start_z = find_valid_position(maze)
    end_x, end_y, end_z = find_valid_position(maze)
    
    with open(fileName, 'w') as file:
        file.write(f"{width},{height},{depth}\n")
        file.write(f"{start_x},{start_y},{start_z}\n")
        file.write(f"{end_x},{end_y},{end_z}\n\n")
        for layer in maze:
            file.write('\n'.join(layer))
            file.write('\n\n')
        file.write('\r\n')

maze = generate_maze(width, height, depth)
write_maze_to_file(maze)
