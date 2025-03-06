# 🐱 Cat - A Recreation of the Linux `cat` Command  

Recreating the `cat` command in **Linux**.

---

## 🚀 Features
- 📖 **Read files** and display their content in the terminal.
- 🔢 **Line numbering** with `-n` flag.
- 📝 **Write output to a file** with the `-w` flag.
- 🔄 **Reverse output to a file** with the '-r' flag.
- 💲 **Display a $ at the end of each line** with the '-e' flag.
- ❌ **Ignore blank lines** with the '-s' flag.
- 🛠️ Built with **C++**, **CMake**, and **GoogleTest**.
- ௷ Use > to redirect the following files into one file

---

## 🛠️ How to Build
Get started by cloning and building the project.

```sh
# 1️⃣ Clone the repository
git clone https://github.com/yourusername/Cat.git
cd Cat

# 2️⃣ Create a build directory and navigate into it
mkdir build && cd build

# 3️⃣ Generate build files with CMake
cmake ..

# 4️⃣ Compile the project
make

```
---

## How to use
```sh
./Cat [flags] files_you_want_to_open...
```
#### Redirect files
```sh
./Cat [flags] file > file_you_want_to_redirect_into
```
---
