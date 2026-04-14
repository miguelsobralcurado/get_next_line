*This project has been created as part of the 42 curriculum by <msobral-@student.42lisboa.com>.*
<br/><br/>
<h1 align="center">📖 get_next_line</h1>

<p align="center">
  A function that reads a file descriptor one line at a time.
</p>

<p align="center">
  <img src="https://img.shields.io/github/languages/top/miguelsobralcurado/get_next_line?style=for-the-badge" />
  <img src="https://img.shields.io/github/languages/code-size/miguelsobralcurado/get_next_line?style=for-the-badge" />
  <img src="https://img.shields.io/github/last-commit/miguelsobralcurado/get_next_line?style=for-the-badge" />
</p>

---

## 📌 Description

**`get_next_line`** is a 42 project whose objective is to implement a function that reads a single line from a file descriptor each time it is called. When called repeatedly on the same file descriptor, it returns each successive line until the end of the file.

The function signature is:
```c
char *get_next_line(int fd);
```

The challenge is to correctly handle:
- Reading from any valid file descriptor (files, standard input, etc.)
- An arbitrary `BUFFER_SIZE` that can be set at compile time
- Memory management — the returned line must be heap-allocated and freed by the caller
- Retaining unprocessed data between successive calls using a **static buffer**

This project focuses on:
- Understanding static variables in C
- Low-level I/O with `read()`
- Dynamic memory allocation and management
- Edge case handling (empty lines, EOF, errors)

---

## 🚀 Instructions

### 🛠️ Requirements

- A C compiler compliant with the C99 standard.

### ⚙️ Compilation

Clone the repository:
```bash
git clone https://github.com/miguelsobralcurado/get_next_line.git get_next_line
cd get_next_line
```

Include the relevant source files in your project compilation. For the mandatory part:
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o your_program
```

For the bonus part (multiple file descriptors):
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -o your_program
```

You can override the buffer size at compile time:
```bash
gcc -D BUFFER_SIZE=1 ...    # Smallest possible buffer
gcc -D BUFFER_SIZE=9999 ... # Large buffer
```

---

## 🧠 How It Works

The function relies on a `static` buffer that persists between calls to store data that was read from the file descriptor but not yet returned to the caller.

### Strategy Overview

Each call to `get_next_line`:
1. Checks if there is leftover data in the static buffer from a previous call.
2. If the buffer is empty, calls `read()` to fetch up to `BUFFER_SIZE` bytes from the file descriptor.
3. Appends the buffer contents to the accumulating `line` string using `gnl_strjoin`.
4. If a newline character (`\n`) is found, it stops reading and returns the line up to and including `\n`.
5. If no newline is found and `read()` returns 0 (EOF), it returns whatever has been accumulated (the last line without a trailing newline).
6. The static buffer is updated so that any data after the newline is kept for the next call.

### Key Helper Functions

| Function | Description |
|----------|-------------|
| `gnl_strlen` | Returns the length of a string up to and including the first `\n` |
| `gnl_strchr` | Detects a newline and shifts remaining buffer content to the front |
| `gnl_strjoin` | Concatenates two strings up to the first `\n`, freeing the first |
| `clear_buffer` | Zeroes out the static buffer on error |

---

## 🏗 Architecture

```text
get_next_line(fd)
      ↓
Check static buffer[fd]
      ↓
If empty → read() into buffer
      ↓
gnl_strjoin: append buffer to line (up to \n)
      ↓
Newline found? → return line (remainder stays in buffer)
No newline + EOF? → return partial line
Error / invalid fd? → free and return NULL
```

---

## ▶️ Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

Reading from standard input:
```c
char *line = get_next_line(0);
```

---

## ⚠️ Error Handling

`get_next_line` returns `NULL` in case of:
- Invalid file descriptor (`fd < 0`)
- `BUFFER_SIZE <= 0`
- A `read()` error
- A memory allocation failure

Always `free()` the returned line when you are done with it to avoid memory leaks.

---

## 🔁 Bonus Part — Multiple File Descriptors

### 🧾 Description

The bonus version extends the function to handle **multiple file descriptors simultaneously** without losing track of each one's reading position.

This is achieved by replacing the single static buffer with a **2D static array** indexed by file descriptor:
```c
static char buffer[FD_MAX][BUFFER_SIZE + 1];
```

The default `FD_MAX` is `1024`, matching the typical system limit for open file descriptors, and can be overridden at compile time with `-D FD_MAX=<value>`.

### ▶️ Usage

```c
char *line1 = get_next_line(fd1);
char *line2 = get_next_line(fd2);
char *line3 = get_next_line(fd1); // continues reading fd1 from where it left off
```

---

## 📁 Project Structure

```text
get_next_line/
├── get_next_line.c             # Mandatory — core function
├── get_next_line.h             # Mandatory — header
├── get_next_line_utils.c       # Mandatory — helper functions
├── get_next_line_bonus.c       # Bonus — multi-fd core function
├── get_next_line_bonus.h       # Bonus — header
├── get_next_line_utils_bonus.c # Bonus — helper functions
└── README.md
```

---

## 🎯 Key Learnings

- How `static` variables persist state between function calls
- Low-level file reading with `read()` and managing partial reads
- Dynamic string concatenation with careful memory management
- Edge cases: empty lines, files not ending in `\n`, large and tiny buffer sizes
- Handling multiple simultaneous file descriptors

---

## Resources

### On file I/O and static variables:
https://www.geeksforgeeks.org/c/static-variables-in-c/
https://www.man7.org/linux/man-pages/man2/read.2.html
https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/

### On memory management:
https://www.geeksforgeeks.org/c/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/

### On the project:
https://42-cursus.gitbook.io/guide/rank-01/get_next_line
https://harm-smits.github.io/42docs/projects/get_next_line

---

### 🤖 AI Contributions
- Drafting this README.md in markdown format.

---

## 👨‍💻 Author

Miguel Sobral Curado  
[42 Intra](https://profile.intra.42.fr/users/msobral-) / [GitHub](https://github.com/miguelsobralcurado/)  
[Instagram](https://www.instagram.com/miguelsobralcurado/)

Feel free to contact me with suggestions or improvements!

---

## 🛎️ License

This project is part of the [42 Network](https://www.42network.org/) curriculum.

This project is designed to test your learning and skills.
