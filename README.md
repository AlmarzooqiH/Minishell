# Minishell

This project is about creating a shell, where our shell will do some basic operations such as changing directories, handling pipes, redirections, and some other commands.

We called our shell Martho because it comes from our intra names, hamalmar and mthodi where we took Mar from hamal(Mar) and Tho from m(Tho)di.

Special thanks to [ii-mnwr](https://github.com/ii-mnwr) for being my project partner.

## Features

- **Basic Shell Operations**: Execute commands like `ls`, `echo`, `pwd`, etc.
- **Change Directories**: Use `cd` to navigate through the file system.
- **Pipes**: Handle pipes (`|`) to connect multiple commands.
- **Redirections**: Support input (`<`), output (`>`), and append (`>>`) redirections.
- **Built-in Commands**: Implement built-in commands like `cd`, `echo`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Environment Variables**: Manage and expand environment variables.
- **Signal Handling**: Properly handle signals like `Ctrl+C` and `Ctrl+D`.

## Screenshots

![Minishell Screenshot](https://github.com/AlmarzooqiH/Minishell/blob/main/Minishell.png)


## Getting Started

To get started with Minishell, follow these steps:

1. **Clone the repository**:
    ```sh
    git clone https://github.com/AlmarzooqiH/Minishell.git
    cd minishell
    ```

2. **Compile the project**:
    ```sh
    make
    ```

3. **Run the shell**:
    ```sh
    ./minishell
    ```

## Usage

Here are some examples of how to use Minishell:

- **Basic Commands**:
    ```sh
    Martho shell# ls -la
    Martho shell# echo "Hello, World!"
    ```

- **Change Directory**:
    ```sh
    Martho shell# cd /path/to/directory
    ```

- **Pipes**:
    ```sh
    Martho shell# ls -la | grep minishell
    ```

- **Redirections**:
    ```sh
    Martho shell# echo "Hello, World!" > output.txt
    Martho shell# cat < input.txt
    ```
