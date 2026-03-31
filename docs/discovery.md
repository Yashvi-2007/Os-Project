# Discovery Phase – Finding the Missing DLL

## Tool Required
- [Process Monitor (ProcMon)](https://learn.microsoft.com/en-us/sysinternals/downloads/procmon) by Sysinternals

## Steps

### 1. Open ProcMon as Administrator

### 2. Set Filters
Go to **Filter > Filter...** and add:
| Column | Condition | Value |
|--------|-----------|-------|
| Process Name | is | notepad++.exe |
| Result | is | NAME NOT FOUND |

### 3. Launch Notepad++
Start Notepad++ while ProcMon is capturing.

### 4. Analyze Results
Look for entries where:
- **Path** ends in `.dll`
- **Result** is `NAME NOT FOUND`
- **Path** starts with the Notepad++ install directory

### 5. Identify Target
You will see:
```
notepad++.exe    CreateFile    C:\Program Files (x86)\Notepad++\version.dll    NAME NOT FOUND
```
This confirms `version.dll` is searched in the app folder but does not exist — a perfect hijack target.

## Why This Works
Windows DLL search order checks the **application's own directory first**.
If the DLL is missing there, Windows moves on to System32.
By placing our malicious DLL in the app folder, we intercept the load before System32 is ever checked.
