for /R %%i IN (UseLibs.txt) DO type %%i >> dest.txt
RemDoubled.exe dest.txt releaseNotes.txt
erase dest.txt