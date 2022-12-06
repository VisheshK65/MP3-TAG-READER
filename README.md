# MP3-TAG-READER-
MP3 tag reader is a software which will read and display MP3 (ID3) tag information from MP3 files.

**Scope** :
The purpose of this SRS is to completely capture all the requirements pertaining to mp3 tag reader. It will be used for determining the architecture,and preparing design document.

**Development Environment** :
We will be using C programming language and command line interface tool to manupulate metadata of mp3 file.

**Functional Requirements** : 

Mandatory features:
  1. This application, should able to handle all ID3 versions (Exept v2.4) tags.
  2. Display which version of ID3 tag is used.
  3. Display all the metadata information from ID3 tag.
  4. User should able to change tags according to options given.
  5. Should display a help screen on request (-h option).
  6. If any image embedded in file, display details about image (Type, path and size).
  7. If ID3 tag not found display proper error messages.
 
About (mp3) ID3 tag
ID3 is a metadata container most often used in conjunction with the MP3 audio file format. It allows information such as the title, artist, album, track
number, and other information about the file to be stored in the file itself.
There are two unrelated versions of ID3: ID3v1 and ID3v2. 

![image](https://user-images.githubusercontent.com/84446470/205877693-e13d9f2c-1972-4cbc-bf5f-bcde4d715351.png)

