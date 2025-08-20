# 🎵 MP3 Tag Reader & Editor

A lightweight command-line tool for reading and editing ID3 metadata tags in MP3 files, written in C.

## 📋 Table of Contents
- [Features](#-features)
- [Requirements](#-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
- [Examples](#-examples)
- [Supported Tags](#-supported-tags)
- [About ID3 Tags](#-about-id3-tags)
- [Contributing](#-contributing)

## ✨ Features

- 📖 **View Mode**: Display all ID3 tag information from MP3 files
- ✏️ **Edit Mode**: Modify specific metadata tags (title, artist, album, etc.)
- 🔍 **Version Detection**: Automatically detects and handles ID3v1 and ID3v2 formats
- 🛡️ **Error Handling**: Comprehensive validation and error messages
- 💾 **Safe Editing**: Uses temporary files to prevent data corruption
- 📱 **Cross-Platform**: Works on Linux, macOS, and Windows

### Supported Features:
- [x] Handle ID3v1 and ID3v2 tags (except v2.4)
- [x] Display ID3 version information
- [x] View all metadata fields
- [x] Edit individual tags
- [x] Built-in help system
- [x] Image metadata detection
- [x] Robust error handling

## 🔧 Requirements

- **Compiler**: GCC or any C99-compatible compiler
- **OS**: Linux, macOS, or Windows
- **Dependencies**: Standard C library only

## 🚀 Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/MP3-TAG-READER.git
   cd MP3-TAG-READER
   ```

2. **Compile the program**:
   ```bash
   gcc -o mp3_tag_reader main.c view.c edit.c
   ```

3. **Make executable** (Linux/macOS):
   ```bash
   chmod +x mp3_tag_reader
   ```

## 📖 Usage

### Basic Syntax
```bash
./mp3_tag_reader [OPTION] [ARGUMENTS] <mp3_file>
```

### Available Options

| Option | Description | Example |
|--------|-------------|---------|
| `--help` | Display help information | `./mp3_tag_reader --help` |
| `-v` | View mode - display all tags | `./mp3_tag_reader -v song.mp3` |
| `-e` | Edit mode - modify specific tags | `./mp3_tag_reader -e -t "New Title" song.mp3` |

### Edit Mode Tags

| Flag | Tag | Description | Example |
|------|-----|-------------|---------|
| `-t` | Title | Song title | `-t "Bohemian Rhapsody"` |
| `-a` | Artist | Artist name | `-a "Queen"` |
| `-A` | Album | Album name | `-A "A Night at the Opera"` |
| `-y` | Year | Release year | `-y "1975"` |
| `-c` | Comment | Comments | `-c "Classic rock"` |
| `-g` | Genre | Music genre | `-g "Rock"` |

## 💡 Examples

### View MP3 Tags
```bash
# Display all metadata
./mp3_tag_reader -v sample.mp3
```

**Output:**
```
-------------------------SELECTED VIEW DETAILS-------------------------

-----------------------------------------------------------------------
                 MP3 TAG READER AND EDITOR FOR IDV3
-----------------------------------------------------------------------
TITLE          :        Bohemian Rhapsody
ARTIST         :        Queen
ALBUM          :        A Night at the Opera
YEAR           :        1975
CONTENT        :        Rock
COMMENT        :        Classic
-----------------------------------------------------------------------
```

### Edit MP3 Tags
```bash
# Change the title
./mp3_tag_reader -e -t "New Song Title" sample.mp3

# Change the artist
./mp3_tag_reader -e -a "New Artist Name" sample.mp3

# Change multiple tags (run separately)
./mp3_tag_reader -e -t "Title" sample.mp3
./mp3_tag_reader -e -a "Artist" sample.mp3
```

### Get Help
```bash
./mp3_tag_reader --help
```

## 🏷️ Supported Tags

The application supports the following ID3 tags:

| Tag | ID3v1 | ID3v2 | Description |
|-----|-------|-------|-------------|
| Title | ✅ | ✅ | Song/track title |
| Artist | ✅ | ✅ | Artist or band name |
| Album | ✅ | ✅ | Album title |
| Year | ✅ | ✅ | Release year |
| Comment | ✅ | ✅ | Additional comments |
| Genre | ✅ | ✅ | Music genre |

## 📚 About ID3 Tags

ID3 is a metadata container format used with MP3 audio files. It allows information such as title, artist, album, track number, and other details to be embedded directly within the audio file.

### Supported Versions:
- **ID3v1**: Simple, fixed-length format (128 bytes)
- **ID3v2**: Variable-length format with extended features
- **Note**: ID3v2.4 is not currently supported

![ID3 Tag Structure](https://user-images.githubusercontent.com/84446470/205877693-e13d9f2c-1972-4cbc-bf5f-bcde4d715351.png)

## 🤝 Contributing

Contributions are welcome! Please feel free to submit issues, feature requests, or pull requests.

### Development Setup:
1. Fork the repository
2. Create a feature branch: `git checkout -b feature-name`
3. Make your changes and test thoroughly
4. Commit your changes: `git commit -m "Description"`
5. Push to the branch: `git push origin feature-name`
6. Submit a pull request


