# Minishell - A Simple Shell Implementation

This was a group project which was developed with my teammate and team lead Igor (https://github.com/iherman-p). We began with a basic roadmap and followed an agile, adaptive approach throughout the development of the project. Most of the work was done in pair programming mode to ensure clarity, consistency, and shared ownership.

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
1. **Input Reading**: Captures user input using `readline()` with command history support.
2. **Tokenization**: The input line is split into tokens (words, redirections an pipes) via a tokenizer, not a standalone lexer module.
3. **Token Validation and Processing**: Validates token sequence correctness.
4. **Token Expansion**: Applies environment variable expansion (`$VAR`), special expansions like `$?`, and quote handling.
5. **Command Parsing**: Converts the expanded token list into a command list, including handling of redirections and pipes.
6. **Execution**: Executes the command list by forking and setting up appropriate I/O redirection, with proper cleanup.

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
- **Tokenizer-Based Design**: Tokenization is performed by a dedicated tokenizer function, without using a separate lexer module.
- **Modular Command Pipeline**: Clearly separated stages for tokenization, validation, expansion, parsing, and execution.
- **Single Global Variable**: Used exclusively for storing the signal number (adhering to 42-school constraints).
- **Memory Safety**: All allocated memory is freed after use; tested with Valgrind to ensure no memory leaks.
- **Error Robustness**: Errors in any stage (invalid syntax, expansion failures, command errors) are handled gracefully with proper exit statuses.

## Requirements
- Compliance with 42 School coding standards (Norm)
- No unexpected crashes (segfaults, bus errors, double frees)
- Proper memory management with no leaks
- Bash-compatible behavior for supported features
- Use of authorized external functions only

## Grade: 100/100

#### Used Tests
minishell-tester: [https://github.com/michmos/42_pipex_tester/tree/main](https://github.com/LucasKuhn/minishell_tester)
