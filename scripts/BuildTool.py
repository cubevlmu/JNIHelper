import os
import subprocess
import shutil
import platform

def build():
    build_dir = "build"
    os.makedirs(build_dir, exist_ok=True)
    os.chdir(build_dir)

    cmake_path = shutil.which("cmake")
    compiler = "cl" if platform.system() == "Windows" else "gcc"  # MSVC for Windows, gcc for Linux

    if cmake_path is None:
        print("CMake not found!")
        return

    try:
        subprocess.run([cmake_path, "-DCMAKE_BUILD_TYPE=Release", "-DBUILDLIB=ON", ".."], check=True)
        subprocess.run(["cmake", "--build", "."], check=True)
        print("Build completed successfully.")
    except subprocess.CalledProcessError as e:
        print(f"Error during build: {e}")