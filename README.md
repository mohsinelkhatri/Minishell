# 🐚 Minishell

## 📖 What is Minishell?

**Minishell** is a simplified Unix shell implemented in C.  
A shell is a command-line interface that lets users interact with the operating system by typing commands. Minishell simulates basic behaviors of shells like `bash`, such as running commands, handling pipes, redirections, environment variables, and built-in functions.

---

## 🎯 Project Goal

The objective of this project is to:

- Understand the internal mechanics of a Unix shell.
- Learn how to create and manage processes (`fork`, `execve`, `pipe`, `wait`, etc.).
- Handle Unix signals like `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`.
- Parse and execute commands with proper handling of quotes, redirections, and variables.
- Manage environment variables and command history.
- Implement an interactive and functional shell with a clean, minimal, and leak-free codebase.
- Respect strict project constraints such as using only **one global variable** (only for signal handling).

In short: **Recreate a basic shell from scratch, close to how Bash works, while learning low-level system programming.**

---

## 📁 Turn-in Files

- All source files (`*.c`)
- All header files (`*.h`)
- A working `Makefile` with required rules

---

## ⚙️ Makefile Rules

| Rule     | Description                               |
|----------|-------------------------------------------|
| `NAME`   | Builds the executable `minishell`         |
| `all`    | Compiles the program                      |
| `clean`  | Removes object files                      |
| `fclean` | Removes object files and the executable   |
| `re`     | Cleans and rebuilds the project           |

---

## 🧾 Mandatory Features

Your shell must:

- Display a prompt while waiting for input
- Use the `readline()` library to read user input and store command history
- Parse and execute commands
- Find executables using relative/absolute path or the `PATH` variable
- Use **only one** global variable to store signal values
- Correctly handle:
  - **Single quotes (`'`)**: prevent all interpretation
  - **Double quotes (`"`)**: allow variable expansion but prevent other interpretations
- Reject unclosed quotes and unsupported characters like `\` and `;`
- Support redirections:
  - `<`  – input redirection
  - `>`  – output redirection
  - `>>` – append output redirection
  - `<<` – here-document (does not update history)
- Implement **pipes (`|`)** for command chaining
- Handle **environment variables (`$VAR`)** and special variable `$?`
- Support correct behavior for:
  - `Ctrl+C` → display a new prompt
  - `Ctrl+D` → exit the shell
  - `Ctrl+\` → do nothing
- Execute built-in commands (see list below)
- Be free of **memory leaks**

---

## 🛠️ Allowed External Functions

### Readline library:
- `readline`
- `add_history`
- `rl_clear_history`
- `rl_on_new_line`
- `rl_replace_line`
- `rl_redisplay`

### Standard functions:
- `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `exit`

### Process management:
- `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `kill`

### Signal handling:
- `signal`, `sigaction`, `sigemptyset`, `sigaddset`

### File system:
- `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`

### File descriptors:
- `dup`, `dup2`, `pipe`

### Directory handling:
- `opendir`, `readdir`, `closedir`

### Errors:
- `strerror`, `perror`

### Terminal functions:
- `isatty`, `ttyname`, `ttyslot`, `ioctl`

### Environment and termcap:
- `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

---

## 📚 Libft

Use of your own `libft` is allowed and encouraged to simplify string manipulation, memory management, and list operations.

---

## 🧩 Built-in Commands

| Command   | Description                                     |
|-----------|-------------------------------------------------|
| `echo`    | Prints text to the terminal. Supports `-n`.     |
| `cd`      | Changes the current working directory.          |
| `pwd`     | Displays the current directory.                 |
| `export`  | Sets environment variables.                     |
| `unset`   | Removes environment variables.                  |
| `env`     | Prints the current environment.                 |
| `exit`    | Exits the shell.                                |

---

## ⚠️ Signals Handling

| Signal    | Behavior                                      |
|-----------|-----------------------------------------------|
| `Ctrl+C`  | Interrupt current input and display new prompt |
| `Ctrl+D`  | Exit the shell                                 |
| `Ctrl+\`  | Ignored (does nothing)                         |

> You may use only **one global variable** to handle signals.  
> This variable must store the **signal number only**, and must not access any other data.

---

## 🧠 Memory Management

- Your code **must be free of memory leaks**
- Memory leaks caused by the `readline()` library are **not your responsibility**
- Use `valgrind` or similar tools to check for leaks and invalid memory usage

---

## 🧪 Test Cases & Examples

Here are some example commands you can run inside your Minishell to test functionality:

```bash
echo Hello World
echo "$USER"
cd /
pwd
export MYVAR=42
echo $MYVAR
unset MYVAR
echo $MYVAR
ls | grep minishell > result.txt
cat < input.txt | wc -l
echo $?

