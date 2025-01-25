# Coconut
A color wrapper for Epitech's banana coding-style-checker

# Example
![Exemple](https://i.imgur.com/KWYrKwL.png)

# Installation
```
git clone git@github.com:Axistorm1/coconut.git
cd coconut
sudo ./install.sh
```

# Dependencies
Coding-style-checker <br>
GCC <br>
Make <br>

# Usage
```
Usage: coconut [option]
  -c        Run coding-style-checker before displaying errors
  -v        Display additional information
  -r        Remove log file after displaying errors
  -s [opt]  Sort output either by "file", "error" or "severity" (default "file")
  -l        Add a line between different errors depending on the sorting flag
```

# TO-DO
-f to display certain files <br>
Change filepath display size <br>

# Known bugs
-v: Some files might be wrongly displayed + not all object files are ignored <br>
This repository has a false positive coding style error (F9) <br>
-l: The first two lines of the output will always have a space between them <br>
coconut.config: hazardous implementation, consider as experimental

# Contribute
You can open issues and make pull requests, a collaborator will review them as fast as possible
