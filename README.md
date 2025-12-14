# C File Manager (Command-Line)

Command-line file manager written in C using standard file I/O.
Implements file and line operations on text files in the current working directory.

## Features

### **File Operations**
- Create new file
- Copy file to new file
- Delete file
- Show file contents
- Rename file

### **Line Operations**
- Append line to file
- Insert line in file at specified line number
- Delete line in file at specified line number
- Show line in file at specified line number
- Find line in file containing specified text
- Show number of lines in file

### **General Operations**
- Automatic changelog of all operations (stored in change_log.txt, updated after every operation)

## Design Notes
- Operates in the current working directory
- Temporary file (`temp.txt`) and change log (`change_log.txt`) are reserved filenames.

## How to run
1. Compile with `gcc FileManager.c -o FileManager.exe`
2. Execute the program with `./FileManager.exe` (or `FileManager.exe` on Windows).
3. Input is read via the terminal, and integer menus guide operation selection.
4. Follow the on-screen menu to perform operations.
