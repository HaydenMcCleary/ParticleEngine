import re
import imageio
import os

# Directory containing your PNG images
png_dir = 'screenshots/'

# Get list of PNG files
png_files = sorted([os.path.join(png_dir, f) for f in os.listdir(png_dir) if f.endswith('.png')])

# Extract numbers from filenames and sort them numerically
def extract_number(filename):
    match = re.search(r'\d+', filename)
    if match:
        return int(match.group())
    return -1

png_files.sort(key=extract_number)

# Duration (in seconds) per frame
duration = 0.1

# Create GIF
gif_path = 'gif/OpenGL.gif'
with imageio.get_writer(gif_path, mode='I', duration=duration) as writer:
    for png_file in png_files:
        image = imageio.imread(png_file)
        writer.append_data(image)
