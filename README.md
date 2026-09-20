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

## Team

- Abdelaziz Sayouti
- Ahmed Ez-Zouine

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for
details.
