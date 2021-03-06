# UNREACHABLE by Manuel Cambon

-- ENGLISH --
This repository contains the source code for a personal Unreal Engine 5 project I am working on. 

The goal of this project is to program two basic mechanics:

1). The main character is controlled by the player, and it is able to make basic actions typical of a 3rd person platformer (i.e., run, jump, climb and interact with switches). The project makes extensive use of the package "Motion Warping" included in the last version of UE5. 

2). The main character, depending on the level environment, can have its body in two different states: material state and spirit state. The way the player is able to control the character depends on these two forms, where:

- In the material state the character is able to make all the actions in 1). In the spirit state it is only able to walk and pass through small holes. 
- In the material state the character has a black material, somewhat transparent, and emits some Niagara particles, almost like a black ghost.
- In the spirit form the body is fully transparent. However, you can trace its position via a small ball of light that floats and emits Niagara particles, resembling its soul.
- The change between material and spirit form is defined by the configuration of the lights in the level. When the character is lit, it is in material form. When it is unlit, it is in spirit form.

Please note that this last point involves both external factors (this is, distribution and properties of the lights in the level) and material properties of the character material (which can be read from a Material Parameter Collection). Moreover, since different parts of the body can be lit while other parts unlit, the character can have parts in its material form (black) and other parts in the spirit form (transparent). This proposes an interesting problem that I tackled with some use of mathematics geometry, raycasts and somewhat compounded materials and niagara systems.   

This repository contains the source code structured in one module named "Unreachable" containing all the needed classes. In particular:

- Unreachable.h/.cpp: Main class generated of the projecto "Unreachable". It is the default project class generated by Unreal.
- GeneralCharacter.h/.cpp: Class that holds all the character main functionality. It implements everything of 2), and its child blueprint implements the functionality described in 1) making use of Motion Warping. 
- UnreachableLight.h/.cpp: Class that holds all the properties related to the light and it interaction with the character.
- UnreachableLightTrigger.h/cpp: Unused class. It was an old idea that didn't work out well... 
- UnreachableLevelSequenceActor.h/.cpp: Class child of ALevelSequenceActor. It holds additional functionality for the level sequences needed for translating the character to the initial transform defined in the sequence without making use of camera fades or transitions. 
- UnreachableFunctionLibrary.h/.cpp: Class that holds some general mathematical functions and calculus. 

<p align="center">
  <img src="Unreachable_Gif2.gif">
</p>

<i>Example of how each part of the character reacts to the light in real time. Lit parts are in the material form (black) and unlit parts are in the spirit form (transparent). Some particles are added to simulate a transition in the inferphase between light and darkness.</i>

<p align="center">
  <img src="Unreachable_Gif1.gif">
</p>

<i>A playable level with some gameplay. The character has to go through the door without being spotted by the guard houses.</i>
  
NOTE: All the models have been made by me in Blender. The animations for climb and switch actions are also done by me, while idle and run animations are from Mixamo, and retageted and modified in Blender for better adjustements.

-- ESPA??OL --
Repositorio de prueba para Optivamedia. Contiene el Source code para un proyecto personal de Unreal Engine 5.

Se pretende programar dos mec??nicas b??sicas:
1. El personaje es controlado en el nivel por el jugador, capaz de realizar las acciones b??sicas de un plataformas de tercera persona (correr, saltar, trepar e interactuar con interruptores). La novedad reside en que estos en tres ??ltimos se hace uso del paquete inclu??do en Unreal Engine 5 de "Motion Warping", el cual es ??til para acompasar las animaciones con el target Transform del personaje.   
2. El personaje, dependiendo del entorno, tiene partes de su cuerpo en dos posibles estados: estado material y estado espiritual. La forma en la que el jugador es capaz de controlar al personaje depende de estas dos formas. En particular:

- En el estado material el personaje es capaz de realizar las acciones descritas en 1. En el estado espiritual no es capaz de hacer nada salvo caminar y atravesar peque??as rendijas. Para esto se modifica el radio de la c??psula y se bloquean con un boolean las acciones de saltar, trepar e interactuar cuando est?? en forma espiritual.
- En el estado material el personaje aparece con un material negro, algo transparente y que emite algunas part??culas Ni??gara para dar sensaci??n de que est?? a punto de difuminarse, casi como si fuese un fantasma.
- En el estado espiritual no se ve el cuerpo del personaje (0 de opacidad). En su lugar se ve una bolita de luz flotando, emitiendo part??culas luminiscentes de Ni??gara.
- El cambio entre forma material y espiritual viene dado por la configuraci??n de las luces en el nivel. Cuando el personaje est?? iluminado, est?? en forma material. Cuando est?? en oscuridad est?? en forma espiritual. 

N??tese que el ??ltimo punto depende tanto de factores externos al personaje (distribuci??n y propiedades de luces en el nivel) como de distintas propiedades del material que usa el personaje (a las cuales se pueden acceder desde un Material Parameter Collection). Adem??s se pretende que el efecto sea realista, en el sentido de que si el personaje tiene cierta parte de su cuerpo iluminada, ??sta aparecer?? en su forma material, y si a la vez tiene otra parte de su cuerpo sin iluminar, ??sta aparecer?? en su forma espiritual. Esto hace que la transici??n entre estados no sea tan sencillo como usar Trigger Volumes, sino una fusi??n entre geometr??a, raycasts y cierta complicaci??n a la hora de programar el shader del material del personaje.

Este repositorio contiene el source code estructurado en un ??nico m??dulo "Unreachable" con las clases necesarias. En particular:

- Unreachable.h/.cpp: Clase que te general Unreal al crear el proyecto "Unreachable". No contiene nada adicional a lo que trae Unreal por defecto.
- GeneralCharacter.h/.cpp: Clase que recoge la funcionalidad del personaje. Aqu?? es donde est?? pr??cticamente toda la implementaci??n del punto 2.
- UnreachableLight.h/.cpp: Clase que recoge las propiedades relacionadas con la luz necesarias para hacer los c??clulos de si el jugador tiene partes de su cuerpo iluminadas o no. 
- UnreachableLightTrigger.h/cpp: No sirve de nada. Era una idea tonta que tuve para hacer triggers, pero al final opt?? por hacerlo con las componentes que traen los blueprints por defecto.
- UnreachableLevelSequenceActor.h/.cpp: Clase necesaria para implementar una funcionalidad adicional a ALevelSequenceActor. Esencialmente, mi idea es que antes de empezar una Level Sequence todos los actores se trasladen autom??ticamente a las posiciones iniciales de la secuencia (y as?? evitar que se teletransporten de repente). Probablemente hay formas mejores de hacer esto, pero en su momento esta fue la ??nica soluci??n que se me ocurri??.
- UnreachableFunctionLibrary.h/.cpp: Clase que me sirve para implementar funciones (casi todas operaciones matem??ticas) de una forma m??s directa, y as?? me ahorro el hacerlo en blueprints.

<p align="center">
  <img src="Unreachable_Gif2.gif">
</p>

<i>Demostraci??n de c??mo reacciona en tiempo real cada parte del  personaje ante la presencia/ausencia de luz.</i>

<p align="center">
  <img src="Unreachable_Gif1.gif">
</p>

<i>Peque??a demostraci??n de un nivel jugable. El personaje tiene que abrirse paso por una puerta sin ser detectado por las barreras de seguridad, que est??n iluminadas.</i>
  
NOTA ADICIONAL: Todos los modelos los he hecho Blender. Las animaciones de trepar y accionar interruptor est??n hechas por m??, y las animaciones de idle y correr est??n descargadas de Mixamo, con retarget y algunos ajustes hechos tambi??n en Blender.


