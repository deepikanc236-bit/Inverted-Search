# Inverted Search Index

A modular C implementation of an Inverted Search Index engine designed to read multiple text documents, parse data, and construct an indexed database structure for optimized term lookup.

## Project Structure

* **main.c** - Initial entry point managing menu operations and core driver loop control.
* **create_database.c / .h** - Parsing, data-structure initialization, and dictionary building functions.
* **types.h** - Type definitions, status tags, and structure molds used throughout indexing.

## Compilation

```bash
gcc main.c create_database.c -o inverted_index
```
