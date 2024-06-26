# level 4: Mighty Mouse

## Grupo 1: EDAchads
### Integrantes:
* Ignacio Rojana
* Rocco Gastaldi
* Javier Pérez

### Comandos para compilar y ejecutar el programa:
Build: `g++ API.cpp Main.cpp Maze.cpp Mouse.cpp -o Main`

Run: `./Main`

## Razonamiento:
El programa comienza con un grafo equivalente a un laberinto sin ninguna pared (todos los nodos conectados con sus vecinos). Siguiendo las casillas en orden de distancia descendente respecto a donde se quiere ir, se puede encontrar un camino "optimista. En cada movimiento se sigue este camino optimista, pero cuando se detecta una pared desconocida, el grafo se actualiza eliminando la arista entre los nodos que representan a las dos casillas. Por cada movimiento, las distancias se recalculan usando el grafo actualizado. Como el algoritmo se ejecuta varias veces para ida y vuelta, tendrá suficientes intentos para encontrar un camino óptimo, o sea, con el recorrido mínimo. Además, si ya encontró un camino pero no exploró una parte del laberinto, el camino optimista lo guiará por esa parte y se probará si hay una ruta mejor por esa parte. Además, para mejorar el rendimiento en la última vuelta, implementamos una lista de movimientos de la anteúltima vuelta que se va a seguir a ciegas en la última para ahorrar el tiempo de procesamiento de los demás algoritmos.

## Algoritmo de Dijkstra:
Para calcular las distancias utilizamos una variante del algortimo de Dijkstra, implementada en `updateDistances`. Este algoritmo consiste en recorrer un grafo empezando por el nodo con la mínima distancia (0), visitando los nodos vecinos y asignándoles el mínimo entre la distancia ya establecida y la nueva hasta agotar los nodos visitados. Nosotros lo implementamos con una cola (`queue`) de forma iterativa, encolando cada repetición los nodos a visitar en la próxima. Además, como los pesos de todas las aristas es 1 y la distancia es proporcional a la cantidad de repeticiones del bucle ya hechas, podemos ignorar los nodos con distancia ya asignada.

## Estructuras de datos:
Para el algoritmo de Dijkstra y la lista de movimientos usamos la estructura `queue`. En el caso del cálculo de distancias, se utilizó para llevar un registro de los nodos a visitar y eliminar los ya visitados. Para la lista de movimientos nos sirve ya que sólo necesitamos acceder una vez a cada uno, pero en el mismo orden en el que se realizaron antes.
El grafo usado para representar el laberinto está implementado con una matriz de `GraphNode`, usando las coordenadas (`Square`) de otros nodos a modo de referencia en lugar de punteros. Estas coordenadas se almacenan en una lista tipo `vector`, ya que necesitamos acceder bastante seguido a los nodos vecinos de un nodo, pero necesitamos eliminar a lo sumo 4 vecinos por cada nodo existente.

## Lógica de movimiento y optimización:
La función `makeMove` recibe un movimiento en forma de coordenadas (por ejemplo, {1, 0} para ir hacia la derecha), evalúa si es posible y lo realiza devolviendo `true` si se puede hacer, o devolviendo `false` si no. En nuestro programa, ignoramos el valor de retorno porque ya se sabe que el movimiento que se le da es posible. La función `leastDistanceMove` devuelve el movimiento posible con menor distancia por el momento. En cada movimiento, se encola una representación de ese movimiento en la cola `moveList`, que después será seguida por `followMoveList`, pero haciendo los movimientos de avance seguidos de una sola vez. Las `moveList` se ignorarán en todos los intentos excepto el anteúlimo, ya que se seguirá el mismo camino para la última vuelta.

## Detalles
En el laberinto se verán verdes las casillas marcadas como "objetivo" a través de `updateDistances`, y de azul uno de los caminos optimistas encontrados. Como la búsqueda de caminos optimistas funciona con la misma lógica que `leastDistanceMove`, sabemos que el robot va a intentar seguir el camino marcado. En cada casilla se verá la distancia actual del nodo correspondiente a esa misma casilla, o *_inf_* si se trata de un nodo desconectado, o sea, si no existe ningún camino posible entre el objetivo y esa casilla. Las distancias no tienen por qué ser las correctas en todos los casos, por ejemplo, si ya se sabe que no hay forma de acceder al objetivo desde la parte superior del tablero, el algoritmo no buscará caminos por ahí ya que aunque sean optimistas, los ya conocidos son mejores.
