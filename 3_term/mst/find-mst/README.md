# Минимальное остовное дерево

Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.

### Формат входного файла.
Первая строка входного файла содержит два натуральных числа 𝑛 и 𝑚 — количество вершин и ребер графа соответственно (1 ≤ n ≤ 20000, 0 ≤ m ≤ 100000).  
Следующие 𝑚 строк содержат описание ребер по одному на строке.  
Ребро номер 𝑖 описывается тремя натуральными числами 𝑏𝑖, 𝑒𝑖 и 𝑤𝑖 — номера концов ребра и его вес соответственно (1 ≤ 𝑏𝑖, 𝑒𝑖 ≤ 𝑛, 0 ≤ 𝑤𝑖 ≤ 100000).

### Формат выходного файла.
Выведите единственное целое число - вес минимального остовного дерева.

### Реализация
Используется библиотека kruskal.
