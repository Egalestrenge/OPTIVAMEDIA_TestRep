# OPTIVAMEDIA Test Repositoryt 1
Repositorio de prueba para Optivamedia (1). Contiene el proyecto de visual studio para un proyecto personal de Unreal Engine 5.

Se pretende programar dos mecánicas básicas:
1. El personaje es controlado en el nivel por el jugador, capaz de realizar las acciones básicas de un plataformas de tercera persona (correr, saltar, trepar e interactuar con interruptores). La novedad reside en que estos en tres últimos se hace uso del paquete incluído en Unreal Engine 5 de "Motion Warping", el cual traslada y rota al persona de forma automática dado como input el target Transform.   
2. El personaje, dependiendo del entorno, tiene partes de su cuerpo en dos posibles estados: estado material y estado espiritual. La forma en la que el jugador es capaz de controlar al personaje depende de estas dos formas. En particular:

- En el estado material el personaje es capaz de realizar las acciones descritas en 1. En el estado espiritual no es capaz de hacer nada salvo caminar y atravesar pequeñas rendijas. Para esto se modifica el radio de la cápsula y se bloquean con un boolean las acciones de saltar, trepar e interactuar cuando esté en forma espiritual.
- En el estado material el personaje aparece con un material negro, algo transparente y que emite algunas partículas Niágara para dar sensación de que está a punto de difuminarse, casi como si fuese un fantasma.
- En el estado espiritual no se ve el cuerpo del personaje (0 de opacidad). En su lugar se ve una bolita de luz flotando, emitiendo partículas luminiscentes de Niágara.
- El cambio entre forma material y espiritual viene dado por la configuración de las luces en el nivel. Cuando el personaje está iluminado, está en forma material. Cuando está en oscuridad está en forma espiritual. 

Nótese que el último punto depende tanto de factores externos al personaje (distribución y propiedades de luces en el nivel) como de distintas propiedades del material que usa el personaje (a las cuales se pueden acceder desde un Material Parameter Collection). Además se pretende que el efecto sea realista, en el sentido de que si el personaje tiene cierta parte de su cuerpo iluminada, ésta aparecerá en su forma material, y si a la vez tiene otra parte de su cuerpo sin iluminar, ésta aparecerá en su forma espiritual. Esto hace que la transición entre estados no sea tan sencillo como usar Trigger Volumes, sino una fusión entre geometría, raycasts y cierta complicación a la hora de programar el shader del material del personaje.
