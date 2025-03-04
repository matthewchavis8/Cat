# 🐱 Cat - A Custom Implementation of the Linux `cat` Command  

Recreating the `cat` command in **Linux** with **C++**, using **CMake** for build management and **GoogleTest** for testing.  

---

## 🚀 Features
- 📖 **Read files** and display their content in the terminal.
- 🔢 **Line numbering** with `-n` flag.
- 📝 **Write output to a file** with the `-w` flag.
- 🛠️ Built with modern **C++20**, **CMake**, and **GoogleTest**.

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