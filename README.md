# ✨ AstroVision - Your Cosmic Guide

A modern web application built with C++ and Vanilla JS that explores the mysteries of the zodiac, calculates compatibility, and provides daily horoscopes.

---

## 🚀 Getting Started
> All of the following steps must be done in the **MSYS2 UCRT64 terminal**.
1.  **Backend**: Open `astrovision.exe` to start the Crow-based API server.
    - compile using: g++ main.cpp -o astrovision.exe -std=c++17 -I include -DASIO_STANDALONE -lws2_32 -lmswsock
    - The server will start on `http://localhost:8080`.
2.  **Frontend**: Once the backend is running, open [index.html](frontend/index.html) in your browser.
    - All cosmic features are served through this portal.
    - Start using ./astrovision.exe in the terminal
---

## 🔮 Components

### 🏡 Home
The entry point of the application where you can navigate to all cosmic tools.

### ♈ Zodiac Sign Calculator (`zodiac.html`)
- Discover your zodiac sign by entering your birthdate.
- View key information about each sign:
    - **Element**: Fire, Earth, Air, or Water.
    - **Ruling Planet**: The celestial body that guides the sign.
    - **Traits**: A summary of the sign's personality.

### ❤️ Cosmic Compatibility (`compatibility.html`)
- Check the relationship compatibility between two zodiac signs.
- Features a **Compatibility Meter** that calculates a percentage based on cosmic alignment.
- Provides a brief summary of the relationship dynamic.

### 📅 Daily Horoscope (`horoscope.html`)
- Read daily guided messages for your specific zodiac sign to help you navigate your day.

---

## 🛠️ Technology Stack
- **Backend API**: C++17, Crow Framework (RESTful).
- **Design System**: Vanilla CSS3 with shared tokens for a responsive, space-themed UI.
- **Frontend Logic**: Vanilla JavaScript (ES6+), Fetch API.
