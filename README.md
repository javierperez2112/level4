# level 4: Mighty Mouse

## Razonamiento:
El programa comienza con un grafo equivalente a un laberinto sin ninguna pared (todos los nodos conectados con sus vecinos). Siguiendo las casillas en orden de distancia descendente respecto a donde se quiere ir, se puede encontrar un camino "optimista. En cada movimiento se sigue este camino optimista, pero cuando se detecta una pared desconocida, el grafo se actualiza eliminando la arista entre los nodos que representan a las dos casillas. Por cada movimiento, las distancias se recalculan usando el grafo actualizado. Como el algoritmo se ejecuta varias veces para ida y vuelta, tendrá suficientes intentos para encontrar un camino óptimo, o sea, con el recorrido mínimo. Además, si ya encontró un camino pero no exploró una parte del laberinto, el camino optimista lo guiará por esa parte y se probará si hay una ruta mejor por esa parte.

## Algoritmo de Dijkstra:
Para calcular las distancias utilizamos una variante del algortimo de Dijkstra, implementada en `updateDistances`. Este algoritmo consiste en recorrer un grafo empezando por el nodo con la mínima distancia (0), visitando los nodos vecinos y asignándoles el mínimo entre la distancia ya establecida y la nueva hasta agotar los nodos visitados. Nosotros lo implementamos con una cola (`queue`) de forma iterativa. 

## Estructuras de datos:

## Lógica de movimiento y optimización:
