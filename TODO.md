#MINISHELL

Built-in commands ✅

    Implement cd ✅

    Implement echo ✅

    Implement pwd ✅

    Implement export ✅

    Implement unset ✅

    Implement env   ✅ 

    Implement exit   ✅


External commands ✅  ❌ Need more improvement and arg handling

    Search for executables in PATH   ✅
    
    Handle absolute and relative paths   ✅
    
    Execute commands using execve   ✅


Redirection ❌

    Implement input redirection (<)   ❌
    
    Implement output redirection (>)   ❌
    
    Implement append output redirection (>>)   ❌
    
    Handle multiple redirections   ❌

    Implement here documents (<<)   ❌

Pipes ✅ ❌ need ot handle exit status and more improvement 👍

    Implement single pipe (|) ✅
    
    Handle multiple pipes   ✅


Environment variables ✅

    Expand environment variables in commands   ✅ Will be handled in parsing  
    
    Manage environment for child processes   ✅


Signal handling ❌

    Handle Ctrl+C (SIGINT)   ❌
    
    Handle Ctrl+\ (SIGQUIT)   ❌
    
    Handle Ctrl+D (EOF)   ❌


Error handling ❌

    Display appropriate error messages  ✅
    
    Set correct exit status   ✅

    
Memory management ❌

    Properly allocate and free memory   ❌
    
    Check for memory leaks   ❌
    

Edge cases ❌

    Handle empty input   ❌
    
    Handle command not found   ✅
    
    Handle permissions issues   ✅


Testing ❌

    Create a comprehensive test suite   ❌
    
    Test with various inputs and edge cases   ❌

    
Code organization ❌
    
    Modularize code into appropriate functions   ❌
    
    Ensure code readability and maintainability   ❌

    Bonus features (if applicable) ❌

    Implement && and || operators   ❌
    
    Add wildcard * expansion   ❌
 