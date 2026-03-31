# Detection Phase – Catching DLL Hijacking with Sysmon

## Tool Required
- [Sysmon](https://learn.microsoft.com/en-us/sysinternals/downloads/sysmon) by Sysinternals

## Setup
```bash
# Install Sysmon with our custom config
sysmon -accepteula -i tools/sysmon-config.xml
```

## Key Event IDs

### Event ID 7 – Image Loaded
Triggered every time a DLL or EXE image is loaded into a process.

**Suspicious indicator:**
- `notepad++.exe` loads `version.dll` from `C:\Program Files (x86)\Notepad++\`
- instead of `C:\Windows\System32\`

**Sample log entry:**
```
EventID: 7
Image: C:\Program Files (x86)\Notepad++\notepad++.exe
ImageLoaded: C:\Program Files (x86)\Notepad++\version.dll
Signed: false
```

### Event ID 1 – Process Created
Triggered when a new process is spawned.

**Suspicious indicator:**
- `calc.exe` spawned with parent process `notepad++.exe`
- This is anomalous — a text editor should never launch Calculator

**Sample log entry:**
```
EventID: 1
Image: C:\Windows\System32\calc.exe
ParentImage: C:\Program Files (x86)\Notepad++\notepad++.exe
ParentCommandLine: "C:\Program Files (x86)\Notepad++\notepad++.exe"
```

## Viewing Logs
Open **Event Viewer:**
```
Applications and Services Logs > Microsoft > Windows > Sysmon > Operational
```
Filter by Event ID 7 and search for loads outside System32.
