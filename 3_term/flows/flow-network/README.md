# FLOW_NETWORK
## Библиотека, реализующая поиск максимального потока, а также минимального разреза в транспортной сети.
Поиск максимального потока реализован с помощью алгоритма Диница.  
В основе реализации лежит класс FlowNetwork. Разберем его подробно.  
В этом классе есть приватные поля:  
- int source_; // Исток сети  
- int sink_; // Сток  
- int vertex_number_; // Количество вершин  
- std::vector<std::vector<Edge>> adjacency_list_; // Список смежности  
- std::vector<int> distance_; // Расстояния от истока до конкретной вершины  
- std::vector<int> first_not_deleted_edge_; // Массив индексов, указывающих на первое не удаленное ребро в списке смежности для i-ой вершины.  

#### Схема алгоритма
<<<<<<< HEAD
- Изначально по каждому ребру поток нулевой. Алгоритм выполняет несколько итераций следующих шагов:  
- Запускаем обход в ширину, пересчитывающий массив расстояний и проверяющий, достижим ли сток из истока в остаточной сети. Если он оказался недостижим, алгоритм можно завершать. На этом шаге осуществляется, по сути, постороение слоистой сети.  
- Запускаем из истока обход в глубину, осуществляющий поиск блокирующего потока. По пути насыщаем по возможности ребра. Dfs возвращает величину блокирующего потока. Увеличиваем на эту величину наш максимальный поток (изначально 0).  
- Повторяем предыдущий шаг, пока возвращается ненулевое значение. На этом итерация заканчивается.  

#### Время работы 
O(|V|^2 * |E|). 
##### Доказательство
Легко показать, что количество итераций, совершаемых алгоритмом Диница, строго меньше |V|. Этот факт напрямую следует из леммы:  
###### Лемма 
Кратчайшее расстояние от истока до каждой вершины строго увеличивается с выполнением каждой итерации.  
Эту лемму интуитивно можно понимать следующим образом: на i-ой фазе алгоритм Диница выявляет и насыщает все пути из истока в сток длины i.
Поскольку длина кратчайшего пути из s в t не может превосходить n-1, то, следовательно, алгоритм Диница совершает не более n-1 фазы.  
  
Теперь оценим сложность поиска блокирующего потока.  
Каждый обход в глубину завершается либо насыщением как минимум одного ребра (если этот обход достиг стока), либо продвижением вперёд как минимум одного указателя в массиве first_not_deleted_edge (в противном случае). Значит, проталкивание потока (вызов обхода в глубину из функции MaxFlowSearch) работает за O (k + |V|), где k — число продвижений указателей. Учитывая, что всего запусков обхода в глубину в рамках поиска одного блокирующего потока будет O (p), где p — число рёбер, насыщенных этим блокирующим потоком, то весь алгоритм поиска блокирующего потока отработает за O (pk + p|V|), что, учитывая, что все указатели в сумме прошли расстояние O (|E|), даёт асимптотику O (|E| + p|V|). В худшем случае, когда блокирующий поток насыщает все рёбра, асимптотика получается O (|V||E|).  
Итого, перемножая полученные величины, имеем: алгоритм целиком выполняется за O(|V|^2 * |E|).

=======
- Изначально по каждому ребру поток нулевой.  
- На каждом шаге запускаем обход в ширину, пересчитывающий массив расстояний и проверяющий, достижим ли сток из истока в остаточной сети. Если он оказался недостижим, алгоритм можно завершать.  
- Запускаем из истока обход в глубину, осуществляющий поиск блокирующего потока. По пути насыщаем по возможности ребра. Dfs возвращает величину блокирующего потока. Увеличиваем на эту величину наш максимальный поток (изначально 0).  
- Повторяем предыдущий шаг, пока возвращается ненулевое значение.  

Время работы O(V^2 * E).
>>>>>>> remotes/origin/hamming-distance

#### Поиск минимального разреза
Выполняется после нахождения максимального потока. Реализован с помощью обычного Dfs. Запускаем его из истока. Все вершины, которые будут посещены при обходе, войдут в одну часть разреза, остальные - в другую.
