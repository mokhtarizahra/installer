# Employee Management & User Authentication System (Qt/QML)

> A modern C++/Qt Quick (QML) application demonstrating a robust MVVM architecture for user authentication, employee management, and login history tracking.

## 📖 Overview

**UserLogin** is a C++ and QML desktop application designed to showcase a highly structured and scalable UI architecture. It implements a complete user authentication flow (Login, Sign-up, Logout) combined with a role-based employee management system. The project strictly adheres to the **MVVM (Model-View-ViewModel)** pattern, bridging the C++ backend with QML views via models and context properties.

## ✨ Features (Verified from source)

- **Robust Authentication:** Secure login, logout, and user registration (`registerUser`, `loginUser`, `isUsernameAvailable`).
- **Role-Based Dashboards:** Distinct QML views for Managers and Employees (`ManagerPage.qml`, `UserPage.qml`, `PersonalEmployee.qml`).
- **Advanced Data Models:** Custom `QAbstractListModel` implementations (`Model_User`, `EmployeeModel`) with defined roles for data extraction.
- **Search & Filtering:** Utilizes `QSortFilterProxyModel` (`userproxymodel`, `loginhistoryproxymodel`) for dynamic data filtering in QML.
- **Activity Tracking:** Tracks and records login/logout times and session durations (`LoginTimeRole`, `DurationRole`).
- **Storage Layer:** Decoupled storage logic for users and employees (`userstorage.cpp`, `employeestorage.cpp`).
- **Clean API Exposure:** Uses `Q_INVOKABLE` methods and `ModelManager` to seamlessly execute C++ logic from QML.

## 🧱 Architecture (MVVM Pattern)

The application follows a strict separation of concerns:

| Layer | Components | Responsibility |
|-------|-----------|----------------|
| **View (UI)** | `*.qml` (`main.qml`, `LoginPage.qml`, `Sign_up.qml`, `ManagerPage.qml`, etc.) | Pure QML-based UI, animations, and layout. |
| **ViewModel/Bridge** | `modelmanager.cpp`, `context properties` | Exposes C++ backend and models directly to the QML engine. |
| **Model (Data)** | `model_user.cpp`, `employeemodel.cpp`, `loginhistorymodel.cpp` | Inherits `QAbstractListModel` to provide data lists to QML views dynamically. |
| **Proxy Models** | `userproxymodel.cpp`, `loginhistoryproxymodel.cpp` | Handles sorting and filtering of user/history data. |
| **Storage** | `userstorage.cpp`, `employeestorage.cpp` | Handles the persistence of data (CRUD operations). |

> **Note:** The C++ `QAbstractListModel` acts as the bridge. The UI updates instantly when data changes in C++. Context properties like `modelManager` are injected in `main.cpp` via `engine.rootContext()`.

## 🛠️ Tech Stack

- **Language:** C++ (C++11 standard)
- **UI Framework:** Qt Quick (QML)
- **Build System:** qmake (`.pro`)
- **Design Patterns:** MVVM, Model-Proxy, Shared Pointers (`QSharedPointer`)

## 🚀 Getting Started

### Prerequisites
- Qt 5.15 or Qt 6.x (with Qt Quick, Qt QML, and Qt Core modules)
- C++ Compiler (MSVC, MinGW, or GCC)
- Qt Creator (Recommended)

### Build & Run
```bash
# Clone the repository
git clone https://github.com/mokhtarizahra/UserLogin.git
cd UserLogin

# Build using qmake
qmake UserLogin.pro
make      # (or nmake / mingw32-make on Windows)

# Run the application
./UserLogin # or UserLogin.exe on Windows
📂 Project Structure
text
UserLogin/
├── main.cpp                 # Entry point, initializes QML engine and ModelManager
├── main.qml                 # Root QML window
├── UserLogin.pro            # qmake configuration
├── qml.qrc                  # QML resources (views, images)
├── resources.qrc            # Other resources
│
├── Views (QML)/
│   ├── LoginPage.qml        # Authentication view
│   ├── Sign_up.qml          # Registration view
│   ├── ManagerPage.qml      # Manager dashboard
│   ├── UserPage.qml         # Standard user dashboard
│   └── StatusAllUsers.qml   # Data table/list view
│
├── Models (C++ Backend)/
│   ├── model_user.cpp/.h    # User data model (auth, roles, history)
│   ├── employeemodel.cpp/.h # Employee data model
│   └── loginhistorymodel.cpp/.h # History tracking model
│
├── Proxy & Storage/
│   ├── userproxymodel.cpp/.h# Filtering/Sorting logic
│   ├── employeestorage.cpp/.h# Persistence layer
│   └── genericitem.cpp/.h   # Base data item structure
│
└── Controller/
    └── modelmanager.cpp/.h  # Central manager exposed to QML
👤 Author
Zahra Mokhtari
GitHub: @mokhtarizahra

📄 License
This project is provided under the terms included in the LICENSE file.
