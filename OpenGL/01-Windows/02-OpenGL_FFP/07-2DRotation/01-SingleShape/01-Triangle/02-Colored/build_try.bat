cl.exe /c /EHsc OGL_Try.c
rc.exe OGL.rc
link.exe OGL_Try.obj OGL.res User32.lib GDI32.lib /SUBSYSTEM:WINDOWS
OGL_Try.exe

