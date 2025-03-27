# Introduction to Software Systems - Homework Assignments (044101)

## Technion - Israel Institute of Technology | Spring 2023

---

### Overview

This repository contains solutions for homework assignments from the Technion's "Introduction to Software Systems" course (044101, Spring 2023). Assignments cover C/C++ programming, scripting, system tools, ADTs, and reverse engineering.

---

### Homework Assignments

1.  **HW0: C Language Refresher** (`HW0/`)
    *   Implemented C solutions for digit frequency counting, a number theory problem (`N^N`), and using variadic functions for min/max/sum calculations.
    *   *Concepts: C fundamentals, algorithms, variadic functions.*

2.  **HW1: Bash Scripting - News Scraper** (`HW1/`)
    *   Developed a Bash script to scrape news articles from ynetnews.com, count occurrences of specific names, and output results to CSV.
    *   *Concepts: Bash scripting, `wget`, `grep`, text processing.*

3.  **HW2: Bash & C - Grade Statistics** (`HW2/`)
    *   Created a system using Bash and C to process grade files, calculate statistics (mean, median, min/max, pass rate), and generate histograms.
    *   *Concepts: Bash/C integration, file I/O, argument parsing, basic statistics.*

4.  **HW3: Abstract Data Type (ADT) - Generic Stack** (`HW3/`)
    *   Implemented a generic Stack ADT in C with support for user-defined element types (demonstrated with a `Student` type) and created a `Makefile` for compilation.
    *   *Concepts: ADTs, generic C (`void*`, function pointers), Makefiles, Stacks.*

5.  **HW4: ADT & Shared Objects - Grade Management** (`HW4/`)
    *   Built a grade management system logic as a C shared library (.so), utilizing a provided Linked List shared library ADT. Focused on library creation and dynamic linking.
    *   *Concepts: Shared libraries (.so), dynamic linking, ADT usage, Makefiles.*

6.  **HW6: C++ Firewall Implementation** (`HW6/`)
    *   Implemented C++ classes for parsing and matching firewall rules based on IP addresses and ports, integrated with a Bash script driver.
    *   *Concepts: C++ OOP, string parsing, basic networking concepts.*

7.  **HW9: Machine Basics - Reverse Engineering "Vault"** (`HW9/`)
    *   Reverse engineered a provided binary executable ("Escape Room" style) using GDB and static analysis to find six hidden passwords.
    *   *Concepts: Reverse engineering, x86 assembly basics, GDB, binary analysis.*

---

### Technologies Used

*   **Languages:** C, C++, Bash Scripting
*   **Debugging Tools:** GDB, Valgrind
*   **System Tools:** Standard Linux command-line utilities (`wget`, `grep` etc.)
*   **Version Control:** Git

