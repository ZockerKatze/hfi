import pygame
import numpy as np
import math

# Initialize Pygame
pygame.init()

# Screen settings
WIDTH, HEIGHT = 649, 480  # Screen size
screen = pygame.display.set_mode((WIDTH, HEIGHT))  # Create a window
pygame.display.set_caption("3D Cube")  # Set the window title

# Colors
WHITE = (255, 255, 255)  # Color for the cube edges
BLACK = (0, 0, 0)        # Background color

# Clock for controlling frame rate
clock = pygame.time.Clock()

# Cube vertices: Define the 8 corners of the cube
vertices = [
    [-1, -1, -1],
    [-1, -1,  1],
    [-1,  1, -1],
    [-1,  1,  1],
    [ 1, -1, -1],
    [ 1, -1,  1],
    [ 1,  1, -1],
    [ 1,  1,  1],
]

# Cube edges: Connect the vertices to form the edges of the cube
edges = [
    (0, 1), (1, 3), (3, 2), (2, 0),  # Back face
    (4, 5), (5, 7), (7, 6), (6, 4),  # Front face
    (0, 4), (1, 5), (2, 6), (3, 7),  # Connecting edges
]

# Convert vertices to a numpy array for easier math operations
vertices = np.array(vertices)

# Define rotation matrices for rotating around each axis
def rotate_x(angle):
    """Rotation matrix for X-axis."""
    c, s = math.cos(angle), math.sin(angle)
    return np.array([
        [1, 0,  0],
        [0, c, -s],
        [0, s,  c]
    ])

def rotate_y(angle):
    """Rotation matrix for Y-axis."""
    c, s = math.cos(angle), math.sin(angle)
    return np.array([
        [ c, 0, s],
        [ 0, 1, 0],
        [-s, 0, c]
    ])

# Function to project 3D points onto the 2D screen
def project(point, width, height):
    """
    Converts 3D coordinates (x, y, z) to 2D screen coordinates.
    Uses a simple perspective projection.
    """
    fov = 256  # Field of view: Controls how "zoomed in" the cube looks
    distance = 4  # Distance from the viewer
    factor = fov / (distance + point[2])  # Calculate perspective scale
    x = int(point[0] * factor + width / 2)  # Center on screen
    y = int(-point[1] * factor + height / 2)
    return (x, y)

# Main loop
running = True
angle_x, angle_y = 0, 0  # Initial rotation angles for X and Y axes
rotation_speed = 0.05  # Speed of rotation when keys are pressed

while running:
    screen.fill(BLACK)  # Clear the screen with the background color

    # Check for key presses to control the rotation
    keys = pygame.key.get_pressed()
    if keys[pygame.K_w]:  # Rotate upwards (decrease X rotation)
        angle_x -= rotation_speed
    if keys[pygame.K_s]:  # Rotate downwards (increase X rotation)
        angle_x += rotation_speed
    if keys[pygame.K_a]:  # Rotate left (decrease Y rotation)
        angle_y -= rotation_speed
    if keys[pygame.K_d]:  # Rotate right (increase Y rotation)
        angle_y += rotation_speed

    # Check for events like quitting the game
    for event in pygame.event.get():
        if event.type == pygame.QUIT:  # If the window is closed
            running = False

    # Rotate the cube by applying rotation matrices
    rotation_x = rotate_x(angle_x)  # Rotation matrix for X-axis
    rotation_y = rotate_y(angle_y)  # Rotation matrix for Y-axis

    # Apply the rotations to the cube's vertices
    rotated_vertices = np.dot(vertices, rotation_x)  # Rotate around X-axis
    rotated_vertices = np.dot(rotated_vertices, rotation_y)  # Then around Y-axis

    # Project the rotated 3D points to 2D
    projected_points = [project(v, WIDTH, HEIGHT) for v in rotated_vertices]

    # Draw the cube's edges on the screen
    for edge in edges:
        pygame.draw.line(screen, WHITE, projected_points[edge[0]], projected_points[edge[1]], 2)

    # Update the display
    pygame.display.flip()

    # Limit the frame rate to 60 FPS
    clock.tick(60)

# Quit Pygame
pygame.quit()
