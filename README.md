# DAC-Project

Made by: Max Lucio Martins de Assis, Gustavo Adrien Polli and Andrey Toshiro Okamura.

This project is a fictional system which simulates a enrollment system and a enrollment control system for a student from UNICAMP, being capable of generate a school record to the user as well.

## Things to Know

All the subjects have codes to identify them, those code have the following format: "XX000".

Example: SI100

UNICAMP uses a credit system, where the students must have a certain amount of credit to finish his course, every subject has a amount of credit and a student can have up to 32 credits per semester on subjects he's enrolled.

Some subjects have prerequisites, so to attend classes of a certain subject, the student must have attended it's prerequisites.

This program is capable of working on any Operational System.

## Compilation and Execution

1 - To compile, type the following command on your terminal:

~~~
gcc *.c -o dac-project
~~~

2.1 - If your terminal isn't a Command Prompt, type the following to execute:

~~~
./dac-project
~~~

2.2 - If your terminal is a Command Prompt, type the following to execute:

~~~
dac-project
~~~

**Alternatively you can import this program on your IDE to execute it.**

Current Version: 1.1

## Changelog

**Version 1.1 (14/12/2019) [FORMAT (DD/MM/YY)]**

-> The program is in english as well as the comments.

-> Overall improvement of the program in all options, fixed bugs and conflicts when reading files.

-> Clear function added to prevent terminal pollution, works on any OS.

-> netbeans-branch removed.

**Version 1.0 (23/11/2018) [FORMAT (DD/MM/YY)]**

-> Initial version of the program, all the program functions were implemented, but the program is in brazilian portuguese as well as the comments.