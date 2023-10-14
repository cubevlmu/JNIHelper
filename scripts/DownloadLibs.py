import urllib.request
import zipfile
import io
import os
import shutil

def DownloadJNILibs():
    zip_url = "https://github.com/FlybirdGameStudio/studioweb.github.io/releases/download/files/17.0.zip"
    target_directory = "jni"
    
    try:
        shutil.rmtree("jni")
    except:
        print("no need cleanup!")

    with urllib.request.urlopen(zip_url) as response:
        if response.status == 200:
            zip_content = io.BytesIO(response.read())
            os.makedirs(target_directory, exist_ok=True)

            with zipfile.ZipFile(zip_content, 'r') as zip_ref:
                zip_ref.extractall(target_directory)
        
            shutil.rmtree("jni/__MACOSX")
            print("JNI Libs Init Success!")
            return True
        else:
            print(f"JNI Libs Init Failed. Status code: {response.status}")
            return False
