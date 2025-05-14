
# Simple C Shell

This is a simple command-line shell implemented in C as part of a "Build Your Own Shell" challenge. It provides basic shell functionality, including a command prompt, handling of built-in commands, searching for executables in the system's PATH, and executing external programs.

## Features Implemented

Based on the provided code and project stages, the following features are implemented:

* **REPL (Read-Eval-Print Loop):** The shell continuously prompts the user, reads input, processes it, and prints output.
* **Command Prompt:** Displays a `$` prompt waiting for user input.
* **Handling Invalid Commands:** Prints `<command_name>: command not found` for unrecognized commands.
* **`exit` Built-in:** Supports the `exit 0` command to terminate the shell with a status code of 0.
* **`echo` Built-in:** Implements the `echo` command to print arguments to standard output.
* **`type` Built-in:**
    * Identifies built-in commands (`echo`, `exit`, `type`, `pwd`).
    * Searches for executable commands in the directories specified by the `PATH` environment variable and prints their full path if found.
* **`pwd` Built-in:** Prints the current working directory.
* **External Command Execution:** Supports executing external programs found in the PATH, including passing a single argument (demonstrated with `custom_exe_*` examples).

## How to Build and Run

1.  **Save the code:** Save your C code as a file, for example, `my_shell.c`.
2.  **Compile:** Open a terminal and compile the code using a C compiler like GCC:

    ```bash
    gcc my_shell.c -o my_shell
    ```
3.  **Run:** Execute the compiled program:

    ```bash
    ./my_shell
    ```

    The shell prompt `$` should appear, waiting for your commands.

## Usage

Once the shell is running, you can type the implemented commands:

* `$ pwd` - Prints the current directory.
* `$ echo hello world` - Prints "hello world".
* `$ type echo` - Prints "echo is a shell builtin".
* `$ type ls` - Prints the path to the `ls` executable (if in your PATH).
* `$ type my_invalid_command` - Prints "my\_invalid\_command: not found".
* `$ custom_exe_1234 some_argument` - Executes the `custom_exe_1234` program with `some_argument` (assuming `custom_exe_1234` is in your PATH and accepts arguments).
* `$ exit 0` - Exits the shell.

## Project Stages (Based on Uploaded Content)

This shell was developed incrementally through several stages, adding functionality step-by-step:

* **Stage 1:** Printing the prompt and waiting for input.
* **Stage 2:** Handling invalid commands.
* **Stage 3:** Implementing the REPL loop.
* **Stage 4:** Implementing the `exit 0` built-in.
* **Stage 5:** Implementing the `echo` built-in.
* **Stage 6:** Implementing the `type` built-in for builtins and unfound commands.
* **Stage 7:** Extending `type` to search the PATH.
* **Stage 8:** Adding support for running external programs with arguments.
* **Stage 9:** Implementing the `pwd` built-in.

## Potential Future Improvements

This shell is a work in progress, and there are many features planned or under consideration for future development:

* **Navigation:**
    * Implementing the `cd` built-in to change the current directory.
    * Support for absolute paths with `cd`.
    * Support for relative paths with `cd`.
    * Support for changing to the home directory (`cd` or `cd ~`).
* **Quoting:**
    * Handling single quotes (`'...'`) to preserve literal values.
    * Handling double quotes (`"..."`) for partial preservation and variable expansion.
    * Handling backslashes (`\`) outside of quotes for escaping.
    * Handling backslashes within single quotes (usually treated literally).
    * Handling backslashes within double quotes (for escaping specific characters).
    * Executing external programs specified within quotes.
* **Redirection:**
    * Redirecting standard output (`>`).
    * Redirecting standard error (`2>`).
    * Appending standard output (`>>`).
    * Appending standard error (`2>>`).
* **Autocompletion:**
    * Completing built-in command names.
    * Completing command arguments (e.g., filenames).
    * Handling cases with missing completion candidates.
    * Completing executable filenames from the PATH.
    * Handling multiple possible completions.
    * Providing completions for partial inputs.
* **Pipelines:**
    * Connecting the output of one command to the input of another (`|`) for dual-command pipelines.
    * Supporting pipelines involving built-in commands.
    * Handling pipelines with multiple commands (`cmd1 | cmd2 | cmd3`).
* Adding other built-in commands (`export`, `unset`, etc.).
* Robust parsing of complex command lines.
* Handling background processes (`&`) and job control.
* Implementing shell variables and expansions.

This list outlines the path for making the shell more robust and feature-rich.

## License

This project is licensed under the [MIT License](./LICENSE).

-----