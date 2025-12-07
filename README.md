<h1 align="center">🐚 Minishell – A Tiny Shell Implementation (42 / 1337 School)</h1>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge">
  <img src="https://img.shields.io/badge/Project-Minishell-green?style=for-the-badge">
  <img src="https://img.shields.io/badge/Status-Mandatory%20Only-orange?style=for-the-badge">
</p>

<p style="font-size:16px;">
The <strong>minishell</strong> project focuses on building a simplified version of the Bash shell.  
It teaches process control, parsing, environment management, signals, and executing commands.  
This README describes the <strong>mandatory part only</strong>, without bonuses.
</p>

<hr>

<h2 align="center">✨ Project Summary</h2>

<p>
Your minishell must behave like a simplified Bash terminal.  
It should read input, parse it, interpret shell syntax, and execute commands with correct behavior.
</p>

<p>
You must handle:
</p>

<ul>
  <li>Command execution</li>
  <li>Builtins</li>
  <li>Pipes</li>
  <li>Redirections</li>
  <li>Environment variables</li>
  <li>Signals</li>
  <li>Error messages</li>
</ul>

<p>No bonus features (history search, logical operators, wildcard expansions, etc.) are included.</p>

<hr>

<h2 align="center">📥 Input Handling & Parsing</h2>

<p>Your minishell must:</p>

<ul>
  <li>Display a prompt</li>
  <li>Read user input via <strong>readline()</strong></li>
  <li>Expand environment variables (<code>$VAR</code>)</li>
  <li>Handle single quotes <code>' '</code> (no expansion)</li>
  <li>Handle double quotes <code>" "</code> (with expansion)</li>
  <li>Split commands by pipes <code>|</code></li>
  <li>Interpret redirections:
    <ul>
      <li><code>></code> → redirect output (truncate)</li>
      <li><code>>></code> → redirect output (append)</li>
      <li><code><</code> → redirect input</li>
      <li><code><<</code> → heredoc</li>
    </ul>
  </li>
  <li>Build an abstract representation of the command pipeline</li>
</ul>

<p>Invalid syntax must trigger error messages without crashing the shell.</p>

<hr>

<h2 align="center">⚙️ Command Execution</h2>

<p>Minishell must replicate Bash-like execution:</p>

<ul>
  <li>Run binaries using <strong>fork()</strong>, <strong>execve()</strong> & <strong>wait()</strong></li>
  <li>Search commands through the <code>PATH</code> environment variable</li>
  <li>Apply redirections before executing a command</li>
  <li>Handle multiple pipes:
    <pre>| cmd1 | cmd2 | cmd3 | ...</pre>
  </li>
  <li>Correctly propagate return values (<code>$?</code>)</li>
</ul>

<p>Each command in a pipeline must run in its own process.</p>

<hr>

<h2 align="center">🧩 Builtins (Mandatory)</h2>

<p>Your minishell must implement these builtins:</p>

<ul>
  <li><strong>echo</strong> (with -n option)</li>
  <li><strong>cd</strong></li>
  <li><strong>pwd</strong></li>
  <li><strong>export</strong></li>
  <li><strong>unset</strong></li>
  <li><strong>env</strong></li>
  <li><strong>exit</strong></li>
</ul>

<p>
Builtins must execute **without forking** when used alone,  
and **inside forks** when part of a pipeline.
</p>

<hr>

<h2 align="center">📦 Environment Variables</h2>

<p>Your shell must maintain its own environment list:</p>

<ul>
  <li>Retrieve original environment upon startup</li>
  <li>Allow adding variables (export)</li>
  <li>Allow removing variables (unset)</li>
  <li>Expand variables in input (<code>$USER</code>, <code>$PATH</code>, <code>$?</code>)</li>
</ul>

<p>Unset or empty variables must behave exactly like Bash.</p>

<hr>

<h2 align="center">📡 Signals Handling</h2>

<p>You must reproduce Bash-like signal behavior:</p>

<ul>
  <li><strong>CTRL+C</strong> → interrupts prompt, prints new line</li>
  <li><strong>CTRL+D</strong> → exits minishell (EOF)</li>
  <li><strong>CTRL+\</strong> → ignored (no core dump)</li>
</ul>

<p>When running a child process:</p>

<ul>
  <li>CTRL+C must kill child only</li>
  <li>CTRL+\ must show "Quit (core dumped)" like Bash</li>
</ul>

<hr>

<h2 align="center">📃 Redirections & Heredoc</h2>

<ul>
  <li><strong>Infile:</strong> <code>< file</code></li>
  <li><strong>Outfile:</strong> <code> > file </code></li>
  <li><strong>Append:</strong> <code> >> file </code></li>
  <li><strong>Heredoc:</strong> <code> << delimiter </code></li>
</ul>

<p>Rules:</p>

<ul>
  <li>Heredoc must behave like Bash</li>
  <li>Heredoc stops expansion when using quotes</li>
  <li>Redirection errors must display proper messages</li>
</ul>

<hr>

<h2 align="center">🔍 Error Messages</h2>

<p>Your minishell must print meaningful errors:</p>

<ul>
  <li>Command not found</li>
  <li>No such file or directory</li>
  <li>Permission denied</li>
  <li>Syntax errors</li>
  <li>Export errors</li>
</ul>

<p>The exit code must match Bash behavior.</p>

<hr>

<h2 align="center">🚀 Running Minishell</h2>

<pre style="background:#1e1e1e; color:white; padding:12px; border-radius:8px;">
make
./minishell
</pre>

<p>Example session:</p>

<pre style="background:#1e1e1e; color:white; padding:12px; border-radius:8px;">
minishell$ echo hello
hello

minishell$ export NAME=42
minishell$ echo $NAME
42

minishell$ ls | wc -l
8
</pre>

<hr>

<h2 align="center">📚 What You Learn in Minishell</h2>

<ul>
  <li>Building a real shell from scratch</li>
  <li>Command parsing & tokenization</li>
  <li>Process creation and pipes</li>
  <li>Environment variable management</li>
  <li>Deadlocks, zombies, and signal handling</li>
  <li>Memory management in large systems</li>
  <li>Reproducing Bash logic</li>
</ul>

<hr>

<h2 align="center">📜 License</h2>

<p style="font-size:16px;">
This documentation is prepared for students of <strong>42 Network / 1337 School</strong>.  
You may reuse or modify it for learning or project submission.
</p>

<hr>

<h1 align="center">🐚 Happy Coding — May Your Shell Never Segfault! 🚀</h1>
