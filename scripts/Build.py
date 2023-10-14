import BuildTool
import DownloadLibs

if(DownloadLibs.DownloadJNILibs() == True):
    BuildTool.build()
else:
    print("Compiled Failed");