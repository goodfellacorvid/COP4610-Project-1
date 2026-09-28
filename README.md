# Shell

A simple shell that interacts with the unix operating system and supports internal and external execution commands, IO redirection, piping, and background jobs. Built in C. 

## Group Members
- **Devan Erle**: de24a@fsu.edu
- **Traven Martini**: tvm23a@fsu.edu
- **Alexey Cherepanov**: ab19@fsu.edu
## Division of Labor

### Part 1: Prompt
- **Responsibilities**: Implement prompt for the user which accesses environment variables to appear in the form of $USER@$MACHINE:$PWD>
- **Assigned to**: Devan Erle

### Part 2: Environment Variables
- **Responsibilities**: The tokens are parsed for any environment variables, and expanded accordingly if they exist. If the variable is invalid, replace token with '0\' to flag as error.
- **Assigned to**: Devan Erle

### Part 3: Tilde Expansion
- **Responsibilities**: Expand any input of ~ or ~/ with the home environment variable. Replace the original token with the expanded token.
- **Assigned to**: Travern Martini

### Part 4: $PATH Search
- **Responsibilities**: Take the first token of the input and search for the executable in the directories of the $PATH environment variable. Retrieve the complete pathname of the executable.
- **Assigned to**: Devan Erle

### Part 5: External Command Execution
- **Responsibilities**: Take in a pathname for an executable and a list of input tokens. Fork() a child process, and then execute the command with execv() and pathname and token list as inputs. Display error message if unsuccessful.
- **Assigned to**: Devan Erle

### Part 6: I/O Redirection
- **Responsibilities**: Parse input for redirection tokens displayed in any order. If there is an input file, verify that it's readable before storing the name of the input file and output file. At the same time, build a tokenlist that excludes any redirection tokens (<,>, outfile, and infile) and can be safely passed to execv. Set the stdin and stdout to infile and outfile if they exist, and then close when the forked process in execv is done.
- **Assigned to**: Devan Erle

### Part 7: Piping
- **Responsibilities**: Implement piping functionality to enable the seamless flow of data between commands. Done through allocating pipe file descriptors, using fork() to spawn child processes, and using dup2() to route output of one command to the input of the next.
- **Assigned to**: Alexey Cherepanov

### Part 8: Background Processing
- **Responsibilities**: Incorporate background processing functionality with a seamless integration with I/O redirection and piping.
- **Assigned to**: Alexey Cherepanov

### Part 9: Internal Command Execution
- **Responsibilities**: Implement internal command execution (cd/exit/jobs), display last 3 valid commands
- **Assigned to**: Travern Martini

### Extra Credit
- **Responsibilities**: Implement a support for unlimited number of pipes, support for piping and I/O redirection in a single line, and an ability to execute the shell from within a running shell process repeatedly
- **Assigned to**: Alexey Cherepanov, Devan Erle, Travern Martini

## File Listing
```
shell/
│
├── src/
│ ├── bg_processing.c
│ ├── env_var.c
│ ├── extern_exec.c
│ ├── intern_exec.c
│ ├── io_redir.c
│ ├── lexer.c
│ ├── path_search.c
│ ├── piping.c
│ └── tildex.c
│
├── include/
│ ├── bg_processing.h
│ ├── env_var.h
│ ├── extern_exec.h
│ ├── intern_exec.h
│ ├── io_redir.h
│ ├── lexer.h
│ ├── path_search.h
│ ├── piping.h
│ └── tildex.h
│
├── README.md
└── Makefile
```
## How to Compile & Execute

### Requirements
- **Compiler**: gcc
- **Dependencies**: N/A

### Compilation
```bash
make
```
This will build the executable in /bin
### Execution
```bash
make run
```
OR
```bash
./bin/shell
```
This will run the program.

## Development Log

### [Devan Erle]

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-11 | Prompt appears in form of $user@$machine:$pwd>  |
| 2026-09-14 | Implemented environment variable expansion for tokens  |
| 2026-09-21 | Path search for executables in the first token of input implemented  |
| 2026-09-24 | External command execution implemented, might need to add more stuff to .c file for IO redirection  |
| 2026-09-26 | Work on implementing IO redirection, pushed to a remote branch (not main)  |
| 2026-09-27 | Output redirection implemented, still need to do input redirection  |
| 2026-09-28 | Finished IO redirection, code cleanup, updated readme  |

### [Travern Martini]

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-22 | Implemented tilde expansion (~/test1 becomes /home/user/test1)  |
| 2026-09-24 | Implemented internal command execution  |


### [Alexey Cherepanov]

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-11 | Setting up development environment, starting to work on tilde expansion (not finished or implemented)  |
| 2026-09-27 | Implemented piping and related extra credit  |
| 2026-09-28 | Implemented background processing  |


## Meetings
Document in-person meetings, their purpose, and what was discussed.

| Date       | Attendees            | Topics Discussed | Outcomes / Decisions |
|------------|----------------------|------------------|-----------------------|
| 2026-09-09 | [Alexey Cherepanov, Travern Martini, Devan Erle]              | Project requirements   | Timeline/Division of Labor  |



## Bugs
No known bugs

## Extra Credit
- **Extra Credit 1**: Support unlimited number of pipes - Alexey Cherepanov
- **Extra Credit 2**: Support piping and I/O redirection in a single command - Alexey Cherepanov
- **Extra Credit 3**: Shell-ception - Devan Erle, Trevan Martini

## Considerations
No additional considerations
