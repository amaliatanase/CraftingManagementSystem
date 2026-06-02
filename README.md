# Handmade Craft Store Management 🎨

A robust, interactive C++ desktop application for managing a handmade craft store's inventory, featuring a clean Graphical User Interface (GUI) built with Qt.

## 📸 Interface Preview
<div align="center">
<img width="802" height="437" alt="Screenshot 2026-06-02 at 20 18 15" src="https://github.com/user-attachments/assets/f37b50cf-ac76-4d10-a231-ab629bd45c12" />
<img width="799" height="435" alt="Screenshot 2026-06-02 at 20 18 31" src="https://github.com/user-attachments/assets/340eec72-21f4-40fd-843a-342d1ce19290" />
<img width="798" height="434" alt="Screenshot 2026-06-02 at 20 18 49" src="https://github.com/user-attachments/assets/829c9ffd-04b1-4e74-8cfa-759eca2c6413" />
</div>

## 🎮 Core Features
* **Inventory Management:** Seamlessly Add, Remove, and Update craft items. Includes an auto-population feature: clicking an item in the list automatically fills the input forms for quick editing.
* **Advanced Dynamic Filtering:** Filter items by Name, Category, or Max Price. The system allows combining multiple criteria simultaneously using logical `AND` / `OR` operators.
* **Time-Travel (Undo/Redo):** Navigate back and forth through your actions history with a robust undo/redo system, ensuring complete control over the inventory state without data loss.
* **Polymorphic Persistence:** Store your inventory data dynamically in either `CSV` or `JSON` format.

## 🛠️ Technologies & Architecture
* **Language:** C++ (utilizing RAII principles and Smart Pointers: `std::shared_ptr`, `std::unique_ptr` for memory safety).
* **GUI Framework:** Qt 6
* **Core Architecture:** Strict **3-Layered Architecture** ensuring a clean separation of concerns between the User Interface, Controller (Business Logic), and Repository (Data Access).
* **Design Patterns:** Command Pattern (for Undo/Redo), Specification & Composite Patterns (for scalable filtering), and Factory Pattern (for repository instantiation).
* **Data Management:** File I/O operations and Qt JSON library (`QJsonDocument`, `QJsonObject`) for persistent data storage.

## 🚀 How to Build and Run
* **Build System:** The project is configured using **CMake**, making it easily compatible with modern IDEs like CLion.
* **Dependencies:** You must have **Qt6** installed on your system.
* **Setup:** Before building, open `CMakeLists.txt` and update the `CMAKE_PREFIX_PATH` variable to point to your local Qt6 installation directory.
* **Data Configuration:** When the application runs in the console, you will be prompted to enter a filename (e.g., `produse.csv` or `produse.json`). Make sure to place this file in your executable's working directory (usually `cmake-build-debug` in CLion), or provide the absolute path to the file.

## 📚 Code Documentation
The entire source code is fully documented following professional Doxygen standards.

👉 **[Click Here to view the full HTML Doxygen Documentation](https://amaliatanase.github.io/CraftingManagementSystem/docs/html/index.html)**
