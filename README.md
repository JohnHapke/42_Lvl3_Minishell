# Minishell - A Simple Shell Implementation

## Purpose
> The purpose of the Minishell project is to create a C program that implements a simplified version of bash, providing hands-on experience with process management, file descriptors, and system calls. The program demonstrates understanding of shell mechanics, signal handling, and inter-process communication while recreating core shell functionality.

## Explanation of Behavior
Minishell implements a functional command-line interpreter that mimics essential bash behaviors. The program:
- Displays an interactive prompt waiting for user commands
- Parses and executes commands with proper argument handling
- Manages process creation and execution via fork/exec
- Handles input/output redirections and pipes
- Processes environment variables and built-in commands
- Maintains command history and handles shell signals
- Provides proper error handling and cleanup

## How It Works

### Initialization
The program starts by:
- Setting up the readline library for input handling
- Initializing environment variables
- Configuring signal handlers for interactive mode
- Displaying the shell prompt

### Command Processing Pipeline
1. **Input Reading**: Uses readline() to capture user input with history support
2. **Lexical Analysis (Lexer)**: Tokenizes raw input into discrete tokens (commands, arguments, operators, redirections, quotes, variables)
3. **Token Processing**: Handles quote removal, validates token sequences, and prepares tokens for expansion
4. **Token Expansion**: Processes environment variables ($VAR), exit status ($?), and other expansions on relevant tokens
5. **Command List Generation**: Transforms processed tokens into structured command objects with proper relationships
6. **Execution**: Forks processes and executes commands from the command list with proper I/O redirection

### Core Features

#### Built-in Commands
- `echo` - Display text (with -n option support)
- `cd` - Change directory (relative/absolute paths)
- `pwd` - Print working directory
- `export` - Set environment variables
- `unset` - Remove environment variables
- `env` - Display environment variables
- `exit` - Exit the shell

#### Redirection and Pipes
- `<` - Input redirection
- `>` - Output redirection
- `<<` - Here-doc (delimiter-based input)
- `>>` - Append output redirection
- `|` - Pipe commands together

#### Quote Handling
- Single quotes (`'`): Preserve literal values, prevent metacharacter interpretation
- Double quotes (`"`): Allow variable expansion while preserving most literal values

#### Signal Management
Interactive mode signal handling:
- `Ctrl-C`: Display new prompt on new line
- `Ctrl-D`: Exit the shell
- `Ctrl-\`: No action (ignored)

### Process Management
- Creates child processes using fork() for external commands
- Uses execve() to replace process images
- Implements proper wait() mechanisms for process synchronization
- Manages file descriptors for I/O redirection and pipes

## Compilation and Usage

1. **Compile**: Run `make` to build the program
2. **Execute**: `./minishell` to start the interactive shell
3. **Usage Examples**:
   ```bash
   $> ls -la | grep minishell
   $> echo "Hello World" > output.txt
   $> cat < input.txt | wc -l
   $> export PATH="/usr/bin:$PATH"
   $> cd ../documents && pwd
   ```

## Key Technical Concepts

- **Lexical Analysis**: Clean separation of tokenization from parsing logic
- **Token-based Architecture**: Structured approach to command processing and expansion
- **Process Management**: Fork/exec model for command execution
- **File Descriptor Management**: Proper handling of stdin, stdout, stderr, and pipes
- **Signal Handling**: Implementing bash-like signal responses
- **Memory Management**: Preventing leaks in complex parsing scenarios
- **Error Handling**: Providing meaningful error messages and proper cleanup
- **Environment Variables**: Managing and expanding shell variables
- **Command List Structure**: Efficient representation of parsed commands for execution

## Architecture Highlights
- **Lexer-First Design**: Clean separation between tokenization, expansion, and execution phases
- **Token-Based Processing**: Structured approach allowing precise control over each processing stage
- **Single Global Variable**: Used only for signal number storage (following strict guidelines)
- **Modular Design**: Separate lexing, token processing, expansion, and execution modules
- **Robust Error Handling**: Graceful handling of edge cases and invalid inputs
- **Memory Safety**: Proper allocation/deallocation with no memory leaks

## Requirements
- Compliance with 42 School coding standards (Norm)
- No unexpected crashes (segfaults, bus errors, double frees)
- Proper memory management with no leaks
- Bash-compatible behavior for supported features
- Use of authorized external functions only

## Grade: tbd/100
