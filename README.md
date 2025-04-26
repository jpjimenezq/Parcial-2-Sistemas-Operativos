# Comparación de Asignación de Memoria en Procesamiento de Imágenes (PARCIAL 2)

Este proyecto compara el rendimiento y uso de memoria entre dos métodos de asignación dinámica de memoria: `new/delete` (estándar en C++) y el sistema de asignación `Buddy System`, aplicado al procesamiento de imágenes (rotación y escalado).

## Videos

### Primera parte
https://youtu.be/Ve0UeIsj1EI

### Segunda parte
https://youtu.be/6pMjUgpHGyU

## Resultados Observados

## ¿Qué diferencia observaste en el tiempo de procesamiento entre los dos modos de asignación de memoria?

En las pruebas realizadas, el Buddy System fue más rápido que el uso tradicional de `new/delete`. Esto se debe a que el Buddy System reduce la fragmentación y mejora la eficiencia en la asignación y liberación de bloques de memoria, especialmente cuando se realizan múltiples operaciones seguidas como rotar y escalar.

## ¿Cuál fue el impacto del tamaño de la imagen en el consumo de memoria y el rendimiento?

El tamaño de la imagen influye directamente en el consumo de memoria y en el tiempo de procesamiento. Imágenes más grandes requieren más espacio para almacenar píxeles y más tiempo para aplicar transformaciones. Esto se nota más con `new/delete`, que no optimiza las asignaciones pequeñas, mientras que el Buddy System gestiona mejor bloques grandes y repetitivos.

## ¿Por qué el Buddy System es más eficiente o menos eficiente que el uso de new/delete en este caso?

El Buddy System es más eficiente en este caso porque:
- Agrupa las asignaciones en bloques de potencia de 2.
- Evita fragmentación externa.
- Hace más rápida la asignación y liberación.

## ¿Cómo podrías optimizar el uso de memoria y tiempo de procesamiento en este programa?

- Reutilizar buffers en vez de reasignar memoria constantemente.
- Aplicar técnicas de programación paralela para operaciones de transformación (lo nuevo que estamos viendo en el curso).
- Evitar copias innecesarias de matrices de píxeles o mejor dicho un mejor uso de creacion de matrices.

## ¿Qué implicaciones podría tener esta solución en sistemas con limitaciones de memoria o en dispositivos embebidos?

En sistemas con recursos limitados, como dispositivos embebidos, el uso de un sistema como Buddy puede ser muy útil por su control fino del uso de memoria. Permite mantener un orden y minimizar desperdicio.

## ¿Cómo afectaría el aumento de canales (por ejemplo, de RGB a RGBA) en el rendimiento y consumo de memoria?

Aumentar los canales implica más memoria por píxel, lo cual incrementa el uso total de memoria. También se incrementa el tiempo de procesamiento, ya que hay que copiar, rotar o escalar más información por cada píxel. En imágenes grandes, esto puede tener un impacto considerable.

## ¿Qué ventajas y desventajas tiene el Buddy System frente a otras técnicas de gestión de memoria en proyectos de procesamiento de imágenes?

**Ventajas:**
- Rápida asignación y liberación.
- Menor fragmentación externa.
- Control sobre el tamaño y distribución de bloques.
- Mejor en imagenes mas pesadas.

**Desventajas:**
- Posible desperdicio de memoria por redondeo a potencias de 2.
- Mayor complejidad en la implementación comparado con `new/delete`.
- Puede no ser tan eficiente para asignaciones de tamaño irregular o muy pequeñas.

