# Trabajo Final PEV 2 - LASER RUSH

- **Alumno:** Valentina Sarcuno | **Comision:** 2A
- **Nombre del Proyecto:** [Laser Rush]
- **Modo Elegido:** Idea Propia - Laser Tracer (Party Game de Obstáculos / Láseres)
- **Versión de Unreal:** UE 5.7
- **Link del Repositorio en GitHub:** [Repositorio Laser Rush](https://github.com/valentinasarcuno-jpg/Parcial2-ValentinaSarcuno)
---

# Reglas y Mecánica Principal

- **Mecánica:** los jugadores entran a un Balcón (sala de espera dentro del mismo mapa). Cuando el host toca Empezar, todos son teletransportados a la arena, donde aparecen láseres en 3 direcciones aleatoriamente en conteos de entre 2 y 6 segundos. Hay que esquivarlos. Quien es tocado cae: se lo manda directo al Balcón, desde donde sigue viendo la partida en vivo.
- **Cómo se gana:** gana el último jugador en pie. Al terminar, todos ven una pantalla con el nombre del ganador durante unos segundos. Luego, el host recibe la autorización para empezar una nueva partida.

# Ficha Técnica de Red

### *Arquitectura: Listen Server (1 a 4 jugadores). El host es servidor y jugador a la vez; los demás se conectan por IP.*

- **RepNotify:**
Phase en APEV2_GameState -> OnRep_Phase: avisa a la UI que cambió la fase (muestra u oculta el botón Empezar, la pantalla del ganador y los carteles de estado).
bIsDead en APEV2_PlayerState -> OnRep_IsDead: avisa a la lista de jugadores, que se redibuja y pone en rojo el cartel del jugador caído.
- **Server RPC:**
Server_RequestStartMatch en APEV2_PlayerController -> el host pide empezar. El servidor (GameMode) valida que la fase sea Lobby y que quien pide sea el host; recién ahí teletransporta a todos y pasa a "Jugando".
Server_SetPlayerName en APEV2_PlayerController -> el cliente manda el nombre elegido en el menú. El servidor lo valida (solo letras, números, espacios, "-" y "_", máximo 15 caracteres) y se lo asigna al PlayerState.
- **Client RPC:**
Client_NotifyEliminated en APEV2_PlayerController -> el servidor le avisa solo al jugador que cayó ("Caíste. Mirá la partida desde el Balcón.") en su HUD.
- **NetMulticast RPC:**
Multicast_PlayerEliminated en APEV2_GameState -> el servidor avisa a todos que alguien cayó, y cada máquina muestra en su HUD "(Nombre) ha caído" (es unreliable: es un efecto visual).

Variables replicadas (Replicated): Phase, Winner, RoundStartTime y RoundEndTime en APEV2_GameState; bIsDead y SurvivalTime en APEV2_PlayerState. Los láseres son actores replicados (bReplicates y movimiento replicado), creados solo por el servidor.

Validación con HasAuthority() en el servidor: movimiento y colisión de los láseres, creación de láseres (spawner), cambio de fase, eliminación de jugadores (SetDead), inicio de la ronda, teletransportes y condición de victoria.


# Cómo Probar el Proyecto

### *Prueba rápida en el editor*

- Abrir el mapa Lvl_ThirdPerson (Content/ThirdPerson).
- En Play Mode/Play Settings: Number of Players = 2 (hasta 4) y Net Mode = Play as Listen Server.
- El HOST recibirá en su pantalla un botón que le da la autoridad de comenzar la partida.
- Al morir, cada jugador es teletransportado al balcón. Los carteles de la izquierda con la lista de jugadores se tornará rojiza y avisará cuantos segundos duró el jugador. Aparece un cartel con el nombre del ganador.

### *Prueba de la build*

- Abrir el archivo .exe 
- En el apartado "player tag", escribir el nombre de visualización que se verá en el juego 
- Si vas a jugar como HOST, apreta el botón Host. Si vas a jugar como CLIENT, escribir en el apartado "IP" La IP del Host y luego toca en JOIN
- Una vez ingresado al juego, se podrá ver en pantalla en el lado derecho el nombre de todos los jugadores.
- El HOST recibirá en su pantalla un botón que le da la autoridad de comenzar la partida.
- Al morir, cada jugador es teletransportado al balcón. Los carteles de la izquierda con la lista de jugadores se tornará rojiza y avisará cuantos segundos duró el jugador. Aparece un cartel con el nombre del ganador. 


Que disfrutes el juego!!!!!!!!!!!!! - Val 

PD: Todos los assets del juego (Tanto de la UI como el balcón, texturas, y la arena de juego) fueron realizados por mi (Excepto el PJ, el cual saqué como asset de libre uso de https://sketchfab.com/3d-models/puppet-kid-free-demo-b30af4c13ef64e9cab15cf2bd437a435)
