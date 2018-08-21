# DependencyAnalyzer
Extracts lexical content from source code files and performs type and dependency analysis

- Performs type analysis to find all the types and and global functions defined in each of a collection of C++ source files
- For each file in a specified file collection, finds, all other files on which they depend
- Uses NoSQL database to store and retrieve dependency information
- Finds Strong Components (using Tarjan's algorithm) defined by the relationships evaluated in the dependency anaysis
- Persists results to an XML file
