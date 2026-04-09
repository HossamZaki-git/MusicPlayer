# Song Player 🎵

A sleek, cross-platform media player application built with C++ and Qt 6. This project features a responsive QML frontend seamlessly integrated with a robust C++ backend, demonstrating modern Model-View architecture and multimedia handling. 

## ✨ Features

* **Dynamic Media Playback:** Full control over audio playback (Play, Pause, Next, Previous) utilizing Qt Multimedia (`QMediaPlayer`, `QAudioOutput`).
* **Interactive Playlist Management:** Users can seamlessly add or remove tracks from the playlist in real-time.
* **Rich UI/UX:** * Animated, collapsible side panel for playlist viewing.
  * Dynamic album art display with support for looping video backgrounds synchronized to the active track.
  * Custom `ImageButton` components with hover states.
* **Cross-Platform Ready:** Configured via CMake to build natively across Windows, macOS, and Linux.

## 🛠️ Technology Stack

* **Language:** C++17
* **Framework:** Qt 6.10 (Qt Quick, Qt Multimedia)
* **UI/Markup:** QML
* **Build System:** CMake
* **Version Control:** Git & Git LFS (Large File Storage)

## 🏗️ Architecture Highlights

This project is structured to enforce a clean separation of concerns between the user interface and the business logic:

* **Model-View Pattern:** The `PlayerController` class inherits from `QAbstractListModel`, acting as the single source of truth for the playlist data. This allows the QML `ListView` to efficiently render and update the UI based on state changes in the C++ backend.
* **QML Singleton Integration:** The backend controller is registered as a singleton instance (`qmlRegisterSingletonInstance`), providing global, safe access to playback controls and state properties (like `currentSong` and `isPlaying`) directly within QML.
* **Property Bindings & Signals:** Extensively uses Qt's property system (`Q_PROPERTY`) and signals/slots mechanism for reactive UI updates without tight coupling.

## 🚀 Getting Started

### Prerequisites
* **Qt 6.10** or higher (Ensure `Quick` and `Multimedia` modules are installed).
* **CMake 3.16** or higher.
* A compatible C++ compiler (MSVC, MinGW, Clang, or GCC).
* **Git LFS** installed on your machine to pull the media assets.

### Installation & Build

1. **Clone the repository:**
   ```bash
   git clone <YOUR_REPO_URL>
   cd MusicPlayer
