import subprocess

def capture_screenshot():
    # Spawn the subprocess running the GLFW wrapper
    process = subprocess.Popen(['../build/opengl_project'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    # Send command to capture screenshot
    process.stdin.write(b'screenshot\n')
    process.stdin.flush()

    # Read the screenshot data from stdout
    screenshot_data = process.stdout.read()

    # Process the screenshot data as needed
    # For example, save it to a file
    with open('screenshot.bmp', 'wb') as f:
        f.write(screenshot_data)

    # Close the subprocess
    process.stdin.close()
    process.stdout.close()

if __name__ == "__main__":
    capture_screenshot()
