# Sesión 1: Configurar un proyecto para usar OpenGL Core Profile
## Trabajo autónomo
**Como segunda parte de esta práctica, un ejercicio de reflexión sobre estos temas:**
  
  - **Una buena práctica que puedes aplicar es crear un espacio de nombres (llamado "PAG", por ejemplo) para tus clases. Así aseguraras no tener conflictos con otros nombres de clases o tipor de las bibliotecas que utilices**
  - **En nuestra aplicación debería haber una clase _PAG::Renderer_ que se encargue de encapsular todo lo relativo al dibujado de la escena 3D en el contexto gráfico OpenGL. Esa clase debería tenr un método llamado _refrescarVentana()_ que debería llamarse cada vez que la ventana deba redibujarse. El problema es que no podemos registrar como _callback_ para el evento _window_refresh_ al método _PAG::Renderer::refrescarVentana()_, ya que no podemos registrar como _callbacks_ métodos de clases, sino funcionalidades sencillas de C.**

    **¿Cómo solucionar este problema? ¿Cómo podemos llamar desde nuestras funciones _callback_ en C a los métodos de la clase _PAG::Renderer_ que responden a los distintos eventos? Todo ello habría de hacerse de la forma más encapsulada (es decir menos acoplada) posible.**

    **Pistas para plantear la solución:**

      - **¿Cómo debería declararse el objeto de la clase _PAG::Renderer_ que actúa como _renderer_ de la aplicación?**
      - **¿Qué módulo de la aplicación debería inicializarlo?**

Para implemetar un espacio de nombres en nuestras prácticas, en este caso llamado PAG, bastaria con añadir, al principio de los ficheros que vayan a contener las clases que vayamos a implementar, la siguiente declaración:

```
namespace PAG {
  class Renderer {
     ...
  }
}
```

El código anteriormente mostrado, seria el implementado dentro del .h de la clase a implementar, en el .cpp, lo único que habría que añadir para que el código sea válido, a parte de nuestro correspondiente #include "Renderer.h", seria, delante de cada método o parámetro de la clase, la instancia _PAG::Renderer_, por ejemplo, al implementar el método refrescarVentana(), lo escribiriamos de la siguiente forma:

```
...
void PAG::Renderer::refrescarVentana() {
  ...
}
...
```

De esta forma, podremos llamar a los métodos correctos que necesitemos utilizar e implementar sin preocuparnos de confusiones o equivocaciones.

Respondiendo ahora a la segunda pregunta, teniendo en cuenta lo explicado en el enunciado, una solución que podriamos implementar seria la de, declarar en el main.cpp de nuestro proyecto, donde se encuentran las declaraciones de los _callbaks_, un objeto de la clase PAG::Renderer, previamente creado, para acceder a los métodos de su clase desde el mismo.

Una vez hecho esto, podemos crear en la clase PAG::Renderer los métodos necesarios para trasladar las órdenes creadas en los _callbacks_ creados en el main.cpp.

Por último, para que desde el main sigan funcionando los callbacks correctamente, añadiremos una llamada a la clase PAG::Renderer al método deseado, a través del objeto de la clase previamente creado.

A continuación, aquí tenemos un ejemplo:

```
main.cpp
...
#include "Renderer.h"

...
PAG::Renderer* renderer = new Renderer();

...
void window_refresh_callback(GLFWwindow* window) {
  renderer->refrescarVentana(window);
}
...
```

```
Renderer.cpp
...
void PAG::Renderer::refrescarVentana(GLFWwindow* window){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glfwSwapBuffers(window);
  ...
}
...
```

De esta forma, podremos, tal y como se nos pide en el enunciado, encapsular las funciones de lo relativo al dibujado de la escena 3D en el contexto gráfico OpenGL en una clase diferente, sin tener que prescindir de los callback o herramientas necesarias para completar nuestro trabajo.

A continuación, mostramos un diagrama UML para representar de forma gráfica la interacción entre las dos clases:

![image](https://github.com/user-attachments/assets/2274db60-d244-451e-bb41-893db471f2f9)

Este diagrama está incompleto, ya que no sabemos exactamente todos los métodos y parámetros necesarios para implementar la clase PAG::Renderer.

# Sesión 2: Organizando el proceso de rendering y la interfaz con clases especializadas
## Trabajo autónomo

Una vez realizado lo que se nos pedia implementar en nuestro código, podemos modificar correctamente nuestro diagrama UML para representar correctamente la interacción entre nuestras clases:

![image](https://github.com/user-attachments/assets/32aab858-0ea0-40d7-9ea3-d57c2b5c3fe0)
