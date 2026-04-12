# Music Player 🎵

A sleek, cross-platform media player application built with C++ and Qt 6. This project features a responsive QML frontend seamlessly integrated with a robust C++ backend, demonstrating modern Model-View architecture and multimedia handling.

---

## ✨ Features

- **Dynamic Media Playback:** Full control over audio playback (Play, Pause, Next, Previous) utilizing Qt Multimedia (`QMediaPlayer`, `QAudioOutput`).
- **Interactive Playlist Management:** Add or remove tracks from the playlist in real-time via an animated, collapsible side panel.
- **Online Song Search:** Search for songs by name through the [Jamendo API](https://www.jamendo.com/). Results appear in a dedicated slide-up search panel, and any track can be added to the playlist with a single tap.
- **Rich UI/UX:**
  - Animated, collapsible playlist side panel.
  - Animated slide-up search results panel with a live "Searching…" / "No results" status indicator.
  - Dynamic album art display with support for looping video backgrounds synchronized to the active track.
  - Custom `ImageButton` components with hover states.
  - Context-aware top bar that swaps the menu icon for a close button while search is active.
- **Cross-Platform Ready:** Configured via CMake to build natively across Windows, macOS, and Linux.

---


## Online Search Integration

A fully functional search workflow, powered by the Jamendo public API:
- **`AudioSearchModel`** — A`QAbstractListModel` subclass that manages network requests (`QNetworkAccessManager`) and exposes results to QML. It handles in-flight request cancellation (aborting the previous request when a new search is triggered), result clearing between searches, and error recovery, with an `isSearching` property that keeps the UI in sync throughout.
- **`SearchPanel.qml`** — A new slide-up panel that displays search results. Each result shows the track thumbnail, title, and artist name. Tapping a result adds it to the playlist and closes the panel. A status message is shown during the search and when no results are returned.
- **`SearchField.qml`** — A reusable styled text input component with an embedded search icon, focus highlight, and a disabled state that activates while a search is in progress.
- The top bar now hosts the `SearchField` and a close button that are toggled on/off alongside the search panel, replacing the menu button while search is active.
---
## 🛠️ Technology Stack

| Layer | Technology |
|---|---|
| Language | C++17 |
| Framework | Qt 6.10 (Qt Quick, Qt Multimedia) |
| UI / Markup | QML |
| Networking | Qt Network (`QNetworkAccessManager`) |
| Build System | CMake 3.16+ |
| Asset Storage | Git & Git LFS |

---

## 🏗️ Architecture Highlights

- **Model-View Pattern:** `PlayerController` inherits from `QAbstractListModel`, acting as the single source of truth for playlist data. `AudioSearchModel` follows the same pattern for search results, keeping network logic completely out of QML.
- **QML Singleton Integration:** Both backend controllers are registered as singletons via `qmlRegisterSingletonInstance`, providing global, safe access to playback controls and search state directly within QML.
- **Property Bindings & Signals:** Extensively uses Qt's property system (`Q_PROPERTY`) and signals/slots for reactive UI updates without tight coupling.

---

## 🚀 Getting Started

### Prerequisites

- **Qt 6.10** or higher — ensure the **Qt Quick** and **Qt Multimedia** modules are installed.
- **CMake 3.16** or higher.
- A compatible C++ compiler (MSVC, MinGW, Clang, or GCC).
- **Git LFS** — required to pull the media assets (audio, video, and image files tracked under `assets/`).

### Installation & Build

1. **Install Git LFS** (if not already installed):
   ```bash
   # macOS (Homebrew)
   brew install git-lfs

   # Ubuntu / Debian
   sudo apt install git-lfs

   # Windows — download the installer from https://git-lfs.com
   ```
   Then activate it for your user account (only needed once per machine):
   ```bash
   git lfs install
   ```

2. **Clone the repository:**
   ```bash
   git clone https://github.com/HossamZaki-git/MusicPlayer.git
   cd MusicPlayer
   ```
   Git LFS will automatically download the binary assets stored under `assets/` during the clone. If you cloned before installing Git LFS, run:
   ```bash
   git lfs pull
   ```

3. **Configure with CMake:**
   ```bash
   cmake -B build -DCMAKE_PREFIX_PATH=/path/to/Qt6
   ```
   Replace `/path/to/Qt6` with your actual Qt installation path, e.g. `~/Qt/6.10.0/gcc_64` on Linux or `C:\Qt\6.10.0\msvc2022_64` on Windows.

4. **Build:**
   ```bash
   cmake --build build --config Release
   ```

5. **Run:**
   ```bash
   # Linux / macOS
   ./build/appMusicPlayer

   # Windows
   .\build\Release\appMusicPlayer.exe
   ```

> **Note for Windows users:** Make sure the Qt `bin` directory is in your `PATH`, or copy the required Qt DLLs next to the executable using `windeployqt`.


