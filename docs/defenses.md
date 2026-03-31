# Defense & Mitigation Guide

## 1. Restrict Write Access to Application Folders
Prevent non-admin users from writing to application directories.
```powershell
# Remove write access for standard users on Notepad++ folder
icacls "C:\Program Files (x86)\Notepad++" /deny Users:(W)
```

## 2. Enable Safe DLL Search Mode
Prevents Windows from searching the current directory for DLLs.
```reg
HKLM\SYSTEM\CurrentControlSet\Control\Session Manager
Value: SafeDllSearchMode = 1
```

## 3. Enable CWDIllegalInDllSearch
Blocks DLL loading from the current working directory entirely.
```reg
HKLM\SYSTEM\CurrentControlSet\Control\Session Manager
Value: CWDIllegalInDllSearch = 0xFFFFFFFF
```

## 4. DLL Code Signing
Configure Windows Defender Application Control (WDAC) to only allow signed DLLs.

## 5. Continuous Sysmon Monitoring
- Monitor **Event ID 7** for DLLs loaded outside System32/trusted paths
- Alert on **Event ID 1** for anomalous parent-child process relationships
- Integrate with a SIEM (e.g. Splunk, Elastic) for automated alerting

## 6. Principle of Least Privilege
- Run applications as standard users, not administrators
- Use AppLocker to whitelist allowed executables and DLLs

## 7. Regular Audits
Periodically scan application directories for unexpected DLL files:
```powershell
Get-ChildItem "C:\Program Files*" -Recurse -Filter "*.dll" |
Where-Object { $_.LastWriteTime -gt (Get-Date).AddDays(-7) }
```
