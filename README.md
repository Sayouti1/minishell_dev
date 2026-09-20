# Minishell

A small Unix shell written in C as part of the 42/1337 cursus. Minishell reads
commands, parses them, expands environment variables, and executes programs
with pipes and redirections.

## Features

- Interactive prompt with command history
- Built-ins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`
- Pipes: `|`
- Redirections: `<`, `>`, `>>`, and heredocs: `<<`
- Single and double quotes
- Environment-variable expansion
- Signal handling for interactive use

## Requirements

- A C compiler
- `make`
- GNU Readline

On macOS, install Readline with Homebrew if needed:

```bash
brew install readline
```

## Build and run

```bash
make
./minishell
```

To remove build files:

```bash
make fclean
```

## How the shell works

The input follows this pipeline:

`readline -> syntax check -> lexer -> expansion -> command builder -> executor`

The lexer produces words and operator tokens. The command builder groups those
tokens around pipes into commands with arguments and redirections. The executor
opens redirections, connects pipes, dispatches built-ins, resolves external
commands through `PATH`, and waits for child processes. See
[ARCHITECTURE.md](ARCHITECTURE.md) for the data structures, ownership rules,
and the role of each source directory.

## Team

- Abdelaziz Sayouti
- Ahmed Ez-Zouine

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for
details.
