# Shell

[Description]

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
- **Responsibilities**: [Description]
- **Assigned to**: Jane Smith

### Part 7: Piping
- **Responsibilities**: Implement piping functionality to enable the seamless flow of data between commands. Done through allocating pipe file descriptors, using fork() to spawn child processes, and using dup2() to route output of one command to the input of the next.
- **Assigned to**: Alexey Cherepanov

### Part 8: Background Processing
- **Responsibilities**: [Description]
- **Assigned to**: Alex Brown, John Doe

### Part 9: Internal Command Execution
- **Responsibilities**: [Description]
- **Assigned to**: Alex Brown

### Part 10: External Timeout Executable
- **Responsibilities**: [Description]
- **Assigned to**: Alex Brown, Jane Smith

### Extra Credit
- **Responsibilities**: Implement a support for unlimited number of pipes, support for piping and I/O redirection in a single line, and an ability to execute the shell from within a running shell process repeatedly
- **Assigned to**: Alexey Cherepanov, Devan Erle, Travern Martini

## File Listing
```
shell/
│
├── src/
│ ├── main.c
│ └── shell.c
│
├── include/
│ └── shell.h
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
This will build the executable in ...
### Execution
```bash
make run
```
This will run the program ...

## Development Log
Each member records their contributions here.

### [Devan Erle]

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-11 | Prompt appears in form of $user@$machine:$pwd>  |
| 2026-09-14 | Implemented environment variable expansion for tokens  |
| 2026-09-21 | Path search for executables in the first token of input implemented  |
| 2026-09-24 | External command execution implemented, might need to add more stuff to .c file for IO redirection  |
| 2026-09-26 | Work on implementing IO redirection, pushed to a remote branch (not main)  |
| 2026-09-27 | Output redirection implemented, still need to do input redirection  |

### [Travern Martini]

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-22 | Implemented tilde expansion (~/test1 becomes /home/user/test1)  |
| YYYY-MM-DD | [Description of task]  |
| YYYY-MM-DD | [Description of task]  |


### [Alexey Cherepanov]

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-11 | Setting up development environment, starting to work on tilde expansion (not finished or implemented)  |
| 2026-09-27 | Implemented piping and related extra credit  |
| YYYY-MM-DD | [Description of task]  |


## Meetings
Document in-person meetings, their purpose, and what was discussed.

| Date       | Attendees            | Topics Discussed | Outcomes / Decisions |
|------------|----------------------|------------------|-----------------------|
| 2026-09-09 | [Alexey Cherepanov, Travern Martini, Devan Erle]              | Project requirements   | Timeline/Division of Labor  |
| YYYY-MM-DD | [Names]              | [Agenda items]   | [Actions/Next steps]  |



## Bugs
- **Bug 1**: This is bug 1.
- **Bug 2**: This is bug 2.
- **Bug 3**: This is bug 3.

## Extra Credit
- **Extra Credit 1**: Support unlimited number of pipes - Alexey Cherepanov
- **Extra Credit 2**: Support piping and I/O redirection in a single command - Alexey Cherepanov
- **Extra Credit 3**: Shell-ception - Devan Erle, Trevan Martini

## Considerations
[Description]
