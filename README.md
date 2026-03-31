# Os-Project: DLL Hijacking Persistence Demo 

> ** Disclaimer:** This project is strictly for **educational purposes** in an isolated VM environment. All techniques demonstrated here are performed on self-owned virtual machines only. Do NOT use on real systems or systems you don't own.

---

## 📌 Overview

This project demonstrates **DLL Hijacking** as a persistence mechanism on Windows, covering both the **attack** (red team) and **detection** (blue team) perspectives as a part of my Sem-4 project(GTU-SET).

**MITRE ATT&CK Reference:** [T1574.001 — Hijack Execution Flow: DLL Search Order Hijacking](https://attack.mitre.org/techniques/T1574/001/)

---

## 🧠 What is DLL Hijacking?

When a Windows application loads a DLL, it searches for it in a specific order:

```
1. Application's own directory       ← Attacker plants malicious DLL here
2. C:\Windows\System32
3. C:\Windows\System16
4. C:\Windows
5. Current working directory
6. Directories in PATH variable
```

If an application searches for a DLL that **doesn't exist in its own folder**, an attacker can place a malicious DLL there. When the app loads, it loads the attacker's DLL instead — running arbitrary code silently.

---

## 🛠️ Environment Setup

| Component | Details |
|---|---|
| OS | Windows 11 (Virtual Machine) |
| Hypervisor | VirtualBox |
| Target App | Notepad++ (x86) (V8) |
| Compiler | MinGW (GCC) |
| Discovery Tool | Process Monitor (ProcMon) — Sysinternals |
| Detection Tool | Sysmon v15.15 — Sysinternals |

---

## 📁 Repository Structure

```
Os-Project/
├── README.md                 # Main project overview
├── report/
│   └── DLL_Hijacking_Report.md  # Converted report in Markdown
├── src/
│   └── evilversion.c         # Malicious DLL source code
├── tools/
│   ├── sysmon-config.xml     # Sysmon ruleset
│   ├── version.def
│   └── build.bat             # Compile script
├── docs/
│   ├── discovery.md          # ProcMon steps
│   ├── detection.md          # Sysmon analysis
│   └── defenses.md           # Mitigation guide
├── images/                   # Screenshots (add your own)
└── LICENSE                   # MIT License for academic use
```

---

## ⚔️ Attack Phase — Step by Step

### Step 1: Discovery with ProcMon

Run **Process Monitor** as Administrator and set filters:

| Filter | Value |
|---|---|
| Result | NAME NOT FOUND |
| Path ends with | .dll |

Launch **Notepad++** and observe missing DLLs.An older version of Notepad++ is used to perform this (V.8). We found:
```
C:\Program Files (x86)\Notepad++\VERSION.dll  →  NAME NOT FOUND ✅
```

### Step 2: Write the Malicious DLL

See [`src/evil_version.c`](src/evil_version.c) for the full source.

The DLL shows a popup and launches `calc.exe` as proof of execution.

### Step 3: Compile

```cmd
mkdir C:\DLLDemo
cd C:\DLLDemo
gcc -shared -o version.dll evil_version.c -luser32
```

### Step 4: Plant the DLL

```cmd
copy C:\DLLDemo\version.dll "C:\Program Files (x86)\Notepad++"
```

### Step 5: Trigger

Close and reopen Notepad++. The malicious DLL executes automatically.

**Result:** Popup appears + Calculator opens — proof of code execution inside Notepad++'s process.

---

## 🛡️ Detection Phase

### Sysmon — Event ID 7 (Image Loaded)

Install Sysmon with the provided config:

```cmd
sysmon64.exe -accepteula -i detection\sysmon-config.xml
```

After triggering the attack, open **Event Viewer:**
```
Applications and Services Logs
  → Microsoft → Windows → Sysmon → Operational
    → Filter by Event ID: 7
```

**Detection indicators:**
```
EventID:      7
Image:        C:\Program Files (x86)\Notepad++\notepad++.exe
ImageLoaded:  C:\Program Files (x86)\Notepad++\version.dll
Signed:       false          ← 🚨 RED FLAG
Company:      (empty)        ← 🚨 RED FLAG
Description:  (empty)        ← 🚨 RED FLAG
```

---

## 🔒 Mitigations

| Mitigation | Description |
|---|---|
| **Safe DLL Search Mode** | Registry setting that deprioritizes app directory in search order |
| **Code Signing Enforcement** | Only load DLLs signed by trusted publishers |
| **Least Privilege** | Users should not have write access to Program Files |
| **EDR Monitoring** | Alert on unsigned DLLs loaded from application directories |
| **Autoruns Auditing** | Regularly scan what DLLs load at startup |

---

## 📊 MITRE ATT&CK Mapping

| Field | Value |
|---|---|
| Tactic | Persistence, Privilege Escalation, Defense Evasion |
| Technique | T1574 — Hijack Execution Flow |
| Sub-technique | T1574.001 — DLL Search Order Hijacking |
| Platform | Windows |
| Detection | DS0011 — Module (Sysmon Event ID 7) |

---

## Quick Start

1. Install [Sysmon](https://learn.microsoft.com/en-us/sysinternals/downloads/sysmon)
2. Apply the ruleset: `sysmon -c tools/sysmon-config.xml`
3. Build the DLL: run `tools/build.bat`
4. Place `version.dll` in `C:\Program Files (x86)\Notepad++\`
5. Launch Notepad++ and observe the payload + Sysmon logs

---

Yashvi Kansara 
