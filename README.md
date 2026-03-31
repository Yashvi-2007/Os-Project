# Os-Project: DLL Hijacking Persistence Demo

Academic lab report on Windows DLL Search Order Hijacking (MITRE ATT&CK T1574.001).[file:1]

## Environment
- Windows 11 VM (VirtualBox)
- Target: Notepad x86
- Tools: Process Monitor, MinGW GCC, Sysmon v15.15[file:1]

## Quick Demo
1. Discovery: Run ProcMon, filter "NAME NOT FOUND .dll" → Find `version.dll` missing.
2. Attack: Compile `evilversion.c` → Plant in Notepad dir.[file:1]
3. Detection: Sysmon Event ID 7 (Signed: false).[file:1]
4. Defense: `icacls` deny write; SafeDllSearchMode=1.[file:1]

**Warning: For lab use only. Isolated VM required.**

