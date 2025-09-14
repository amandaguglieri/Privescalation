# EoPLoadDriver

Credit goes to Tarlogic <3. this is the main repo : https://github.com/TarlogicSecurity/EoPLoadDriver

This repo is just to have the prebuilt compiled exes to avoid manual compilation.


Proof of concept for abusing SeLoadDriverPrivilege (Privilege Escalation in Windows)

# Usage

```bash
EOPLOADDRIVER.exe RegistryServicePath DriverImagePath
eg: EOPLOADDRIVER.exe System\\CurrentControlSet\\MyService C:\\Users\\Username\\Desktop\\Driver.sys
```
