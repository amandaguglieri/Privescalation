# How to

Compile `SeTcbElevation.exe` . I've set up Visual Studio 2022 in a Windows Virtual Machine. 

Now from the terminal: 

```powershell
 cl /nologo /EHsc /FeTcbElevation.exe .\TcbElevate.cpp /DUNICODE /D_UNICODE /link Advapi32.lib ntdll.lib
```
