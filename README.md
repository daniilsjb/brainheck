# Brainheck

![Preview](/img/preview.png)

I got bored and decided to experiment a little bit with the Windows Terminal and WSL. After 
setting up the terminal to look pretty, I thought it would be fun to write a little program
using only tools available in the WSL. A natural choice for a simple program was a
[Brainf\*\*k](https://en.wikipedia.org/wiki/Brainfuck) interpreter, written in C. It took me
about half an hour to complete, but I thought it looks quite nice, so why not share it?

This implementation is deliberately as simple as possible. I do not perform any error
reporting if the provided BF program is invalid, and indeed the interpreter itself is about
forty lines long. I could run a variety of test programs on it with no issues (including
the Universal Turing Machine and Game of Life, proving it Turing-Complete... twice!).
