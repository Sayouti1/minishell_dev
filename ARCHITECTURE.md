# Minishell architecture

The shell is organised as a one-way pipeline. Each stage owns one kind of
work and passes a small data structure to the next stage:

```text
readline()
    |
    v
syntax validation -> lexer -> expansion -> command builder -> executor
                                      |                    |
                                      v                    v
                                  t_command          built-in / PATH binary
```

## 1. Read/evaluate loop

`srcs/main.c` owns the interactive loop. It installs signal handlers, reads a
line, stores non-empty lines in Readline history, and calls `process_line()`.
The global `g_vars` structure contains shell state shared by the stages:
environment, last exit status, current token/command lists, saved standard
descriptors, and temporary file descriptors.

## 2. Syntax validation

`srcs/parsing/check_input/` rejects input before allocating an execution
pipeline. It checks unclosed quotes, unsupported `&&`/`||`, misplaced pipes,
and redirections without a target. A syntax failure sets `$?` to `2` and the
line is discarded.

## 3. Lexer

`token_line()` in `srcs/parsing/lexer/lexer.c` scans left to right:

- whitespace separates words;
- `|`, `<`, `>`, `<<`, and `>>` become operator tokens;
- quotes are tracked while scanning a word, so operators inside quotes remain
  part of that word.

Tokens are linked `t_token` nodes. A token may have a `NULL` value after an
  expansion; this is intentional and lets the redirect checker report an
  ambiguous redirect rather than crashing.

## 4. Expansion

`expand_var()` expands `$NAME` and `$?`, while preserving single-quoted text
and applying the heredoc rules. Unquoted expansion results may be split into
multiple word tokens. Expansion happens before command construction because
it can change the number of arguments and can make a redirect target invalid.

## 5. Command builder

`token_to_command_convert()` groups tokens separated by `TOKEN_PIPE` into a
doubly-linked list of `t_command` nodes. Each node contains:

- `command`: executable or built-in name;
- `args`: arguments excluding the command name;
- `redirection`: ordered redirections, so the last applicable redirect wins;
- `fd_in`/`fd_out`: descriptors used by the executor.

`add_redirection()` consumes an operator and its following word. The builder
also removes quote characters from command and argument strings.

## 6. Execution

`process_command()` selects the single-command or pipeline path. Redirection
files and heredocs are prepared before a child runs. For a pipeline, each
command gets a pipe for its output (except the last) and the previous pipe for
its input (except the first); the parent closes its copies and waits for all
children.

`execute_command()` then chooses the command implementation:

1. apply/check redirections;
2. use `command_handler()` for a built-in;
3. resolve an external command through `PATH` (or use an explicit path);
4. `fork()` and call `execve()` in the child;
5. translate `waitpid()`/`execve()` results into shell exit status.

Built-ins run in the parent for a standalone command, so `cd`, `export`, and
`unset` can modify the shell environment. In a pipeline they run in a child.
The dispatch table lives in `srcs/execution/builtin/command_handler.c`; adding
a built-in requires its implementation, a wrapper/table entry, and the
prototype in `include/include.h`.

## Ownership rules

- The input line is freed by `check_and_token()`.
- Tokens are freed after command construction/execution.
- Commands own their argument and redirection lists and are released by
  `free_cmds()`.
- Temporary heredoc and pipe descriptors are tracked and closed centrally.

This separation makes debugging easier: inspect tokens for lexer/expansion
problems, inspect `t_command` for parser problems, and inspect file
descriptors/processes for execution problems.
