# OPTIVAMEDIA Test Repository
Repositorio de prueba para Optivamedia (1). Contiene el Source code para un proyecto personal de Unreal Engine 5.

Se pretende programar dos mecánicas básicas:
1. El personaje es controlado en el nivel por el jugador, capaz de realizar las acciones básicas de un plataformas de tercera persona (correr, saltar, trepar e interactuar con interruptores). La novedad reside en que estos en tres últimos se hace uso del paquete incluído en Unreal Engine 5 de "Motion Warping", el cual es útil para acompasar las animaciones con el target Transform del personaje.   
2. El personaje, dependiendo del entorno, tiene partes de su cuerpo en dos posibles estados: estado material y estado espiritual. La forma en la que el jugador es capaz de controlar al personaje depende de estas dos formas. En particular:

- En el estado material el personaje es capaz de realizar las acciones descritas en 1. En el estado espiritual no es capaz de hacer nada salvo caminar y atravesar pequeñas rendijas. Para esto se modifica el radio de la cápsula y se bloquean con un boolean las acciones de saltar, trepar e interactuar cuando esté en forma espiritual.
- En el estado material el personaje aparece con un material negro, algo transparente y que emite algunas partículas Niágara para dar sensación de que está a punto de difuminarse, casi como si fuese un fantasma.
- En el estado espiritual no se ve el cuerpo del personaje (0 de opacidad). En su lugar se ve una bolita de luz flotando, emitiendo partículas luminiscentes de Niágara.
- El cambio entre forma material y espiritual viene dado por la configuración de las luces en el nivel. Cuando el personaje está iluminado, está en forma material. Cuando está en oscuridad está en forma espiritual. 

Nótese que el último punto depende tanto de factores externos al personaje (distribución y propiedades de luces en el nivel) como de distintas propiedades del material que usa el personaje (a las cuales se pueden acceder desde un Material Parameter Collection). Además se pretende que el efecto sea realista, en el sentido de que si el personaje tiene cierta parte de su cuerpo iluminada, ésta aparecerá en su forma material, y si a la vez tiene otra parte de su cuerpo sin iluminar, ésta aparecerá en su forma espiritual. Esto hace que la transición entre estados no sea tan sencillo como usar Trigger Volumes, sino una fusión entre geometría, raycasts y cierta complicación a la hora de programar el shader del material del personaje.

Este repositorio contiene el proyecto de Visual Studio estructurado en un único módulo "Unreachable" con las clases necesarias. En particular:

- Unreachable.h/.cpp: Clase que te general Unreal al crear el proyecto "Unreachable". No contiene nada adicional a lo que trae Unreal por defecto.
- GeneralCharacter.h/.cpp: Clase que recoge la funcionalidad del personaje. Aquí es donde está prácticamente toda la implementación del punto 2.
- UnreachableLight.h/.cpp: Clase que recoge las propiedades necesarias para hacer los cáclulos de si el jugador tiene partes de su cuerpo iluminadas. 
- UnreachableLightTrigger.h/cpp: No sirve de nada. Era una idea tonta que tuve para hacer triggers, pero al final opté por hacerlo con las componentes que traen los blueprints por defecto.
- UnreachableLevelSequenceActor.h/.cpp: Clase necesaria para implementar una funcionalidad adicional a ALevelSequenceActor. Esencialmente, mi idea es que antes de empezar una Level Sequence todos los actores se trasladen automáticamente a las posiciones iniciales de la secuencia (y así evitar que se teletransporten de repente). Probablemente hay formas mejores de hacer esto, pero en su momento esta fue la única solución que se me ocurrió.
- UnreachableFunctionLibrary.h/.cpp: Clase que me sirve para implementar funciones (casi todas operaciones matemáticas) de una forma más directa, y así me ahorro el hacerlo en blueprints.

<center>![](Unreachable_Gif1.gif)<center>

<i>Pequeña demostración de un nivel jugable. El personaje tiene que abrirse paso por una puerta sin ser detectado por las barreras de seguridad, que están iluminadas.</i>
  

