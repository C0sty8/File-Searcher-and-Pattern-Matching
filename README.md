## Algorithmic Implementation Details

### Time and Space Complexities

| Operation | Standard Trie | RBT-Optimized Trie (This Project) |
| --- | --- | --- |
| **Branching Space per Node** | $O(m)$ where m is array size | $O(k)$ where k is active children count |
| **Branch Lookup Time** | $O(1)$ | $O(\log k)$ |
| **Total Search Phase Time** | $O(\text{Text Length})$ | $O(\text{Text Length} \times \log k)$ |

Where $m$ is the full alphabet size (256 for extended ASCII) and $k$ is the actual number of children extending out of a unique prefix node.

## How to Use the Program

Upon execution, the terminal loads an interactive control panel:

```text
1. Set directory path
2. Add string
3. Delete String
4. Search in file
5. Search in directory
6. Exit
Current path: [Selected Path]
Strings: [List of current keywords inside the Trie]
```

### Suggested Workflow Example:

1. **Load Keywords:** Select Option `2` and input words you want to search for (e.g., `apple`, `alpha`, `test`). Each insertion triggers an automatic recalculation of the Aho-Corasick failure transitions.
2. **Define Search Target Path:** Select Option `1` and enter the relative or absolute target folder or file path (e.g., `./data_logs` or `sample.txt`).
3. **Execute Search:**
* Select Option `4` if your path targets an individual text file.
* Select Option `5` if your path targets a whole directory.

4. **View Outputs:** The program will stream across your documents and immediately output hit summaries:
```text
Path: ./data_logs/log1.txt | Matches: 14
Path: ./data_logs/info.txt | Matches: 3

```

5. **Soft Invalidation:** Use Option `3` to remove strings from matching considerations without complete tree destructions.
