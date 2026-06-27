

# Prblems creating GLFW windows on Microsoft Windows
Since this is GLES, you will need .dll files to cover that.  
On windows, those files are:  
* libEGL.dll
* libGLESv2.dll

It so happens, that VScode has these .dll files.  
You can search for vscodes version, and download those.  

But you will need to copy those .dll files to your build/applications/PROJECT folder, in order to run the application.