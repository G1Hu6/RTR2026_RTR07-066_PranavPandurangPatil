cl.exe /c /EHsc Window.c
link.exe Window.obj User32.lib GDI32.lib /SUBSYSTEM:WINDOWS
Window.exe

