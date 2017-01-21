# Расстояние Хэмминга

Расстояние Хэмминга между двумя строками равной длины — это количество индексов, в которых символы этих строк не равны.
Определим расстояние от шаблона p до строки s как суммарное расстояние Хэмминга от p до всех подстрок s, имеющих длину |p|. В строке и в шаблоне некоторые символы стёрты. Нужно восстановить стёртые символы так, чтобы расстояние от p до s было минимально возможным.

### Формат входного файла.
В первой строке дана строка s, во второй — шаблон p. Обе строки непусты, имеют длину не более 1000 и состоят из символов '0', '1' и '?'. '?' обозначает стёртые символы, которые нужно восстановить. Длина строки p не превосходит длины строки s.

### Формат выходного файла.
В первой строке выведите минимальное расстояние от p до s после восстановления всех стёртых символов. Во второй и третьей строках соответственно выведите s и p, в которых символы '?' заменены на '0' и '1'.

## Реализация
Заведем структуру EmptySpace. Создадим объект этой структуры для каждого знака '?' в строке и шаблоне, и будем хранить их в массивах `string_spaces` и `pattern_spaces` соответственно.  

В функции `FindDistance()` будем последовательно сравнивать шаблон с подстроками исходной строки.  
- Если сравниваются две цифры - прибавим к hamming_distance 1, если они различны.  
- Если одна цифра, один '?', инкрементируем `comparisons_with_0` или `comparisons_with_1` в зависимости от цифры.  
- Если сравниваются два знака '?', добавляем id одного из '?' в `spaces_compared` другого.  

Затем, используя функцию `BuildNetwork` строим граф нашей сети по таким правилам:  
- Добавляем в наш граф вершины SOURCE и sink.
Проходим по всем элементам `string_spaces` и `pattern_spaces`. Считаем каждый элемент вершиной - vertex - графа.  
- Добавляем ребро из SOURCE в vertex с capacity = `comparisons_with_0`;
- Добавляем ребро из vertex в cource с capacity = 0;  
- Добавляем ребро из vertex в sink с capacity = `comparisons_with_1`;  
- Добавляем ребро из sink в vertex с capacity = 0;  
- Добавляем ребро из vertex во все neighbours из `spaces_compared` с capacity = 1 и обратно.  

Запускаем алгоритм поиска максимального потока для этой сети. Полученный результат прибавляем к hamming_distance. Чтобы определить, какие '?' должны быть 0, а какие 1, запускаем поиск минимального разреза. Он возвращает ту часть графа, которая достижима из SOURCE. Всем этим объектам должны соответствовать 0 в строке и шаблоне. Остальным соответствуют 1.