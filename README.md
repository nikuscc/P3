PAV - P3: detección de pitch
============================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 3](https://github.com/albino-pav/P3).
Siga las instrucciones de la [Práctica 2](https://github.com/albino-pav/P2) para realizar un `fork` de la
misma y distribuir copias locales (*clones*) del mismo a los distintos integrantes del grupo de prácticas.

Recuerde realizar el *pull request* al repositorio original una vez completada la práctica.

Ejercicios básicos
------------------

- Complete el código de los ficheros necesarios para realizar la detección de pitch usando el programa
  `get_pitch`.

   * Complete el cálculo de la autocorrelación e inserte a continuación el código correspondiente.
   
   ![image](https://user-images.githubusercontent.com/92537816/143492987-76e6ce60-f657-4099-aaa0-f97ffd33daa7.png)

   * Inserte una gŕafica donde, en un *subplot*, se vea con claridad la señal temporal de un segmento de
     unos 30 ms de un fonema sonoro y su periodo de pitch; y, en otro *subplot*, se vea con claridad la
	 autocorrelación de la señal y la posición del primer máximo secundario.

	 NOTA: es más que probable que tenga que usar Python, Octave/MATLAB u otro programa semejante para
	 hacerlo. Se valorará la utilización de la librería matplotlib de Python.

    ![image](https://user-images.githubusercontent.com/92537816/143685646-4dfd0eff-d162-4186-bd46-c6e5e79b2daf.png)
    
    Podem veure que el període de pitch és aproximadament 6ms, que és aprox. l'invers de la posició del màxim en l'autocorrelació.
        
    <img width="68" alt="2021-11-27" src="https://user-images.githubusercontent.com/92537816/143686131-6043852c-79db-4c3e-b2ba-85c9d35dfa29.png">
    
    ![image](https://user-images.githubusercontent.com/92537816/144066736-f531fddb-0398-49b2-951e-9a7ca0720c8f.png)

   * Determine el mejor candidato para el periodo de pitch localizando el primer máximo secundario de la
     autocorrelación. Inserte a continuación el código correspondiente.
     
    ![image](https://user-images.githubusercontent.com/92537816/143685795-a407fe32-98e6-4ede-bcca-27df1fb66ff4.png)

   * Implemente la regla de decisión sonoro o sordo e inserte el código correspondiente.
   
   Utilitzant 3 valors de threshold, un per l'energia, un altre per l'autocorrelació normalitzada, i un altre per l'autocorrelació en el màxim.
   Com que les trames de sons sords tenen l'autocorrelació és molt diferent a la seva energia podem detectar-los fàcilment. També podem detectar trames de silenci ja que la seva energia és baixa i està per sota del threshold que hem marcat.
   
    ![image](https://user-images.githubusercontent.com/92537816/143685836-317d63c7-06da-4e16-a71f-11ff35a637d8.png)

- Una vez completados los puntos anteriores, dispondrá de una primera versión del detector de pitch. El 
  resto del trabajo consiste, básicamente, en obtener las mejores prestaciones posibles con él.

  * Utilice el programa `wavesurfer` para analizar las condiciones apropiadas para determinar si un
    segmento es sonoro o sordo. 
	
	  - Inserte una gráfica con la detección de pitch incorporada a `wavesurfer` y, junto a ella, los 
	    principales candidatos para determinar la sonoridad de la voz: el nivel de potencia de la señal
		(r[0]), la autocorrelación normalizada de uno (r1norm = r[1] / r[0]) y el valor de la
		autocorrelación en su máximo secundario (rmaxnorm = r[lag] / r[0]).
		
	Creant un .out, podem separar les columnes per extreure els nostres paràmetres amb la següent ordre:
	![image](https://user-images.githubusercontent.com/92537816/144089997-14125780-20f8-42e0-b1c9-58217fc297af.png)

	![image](https://user-images.githubusercontent.com/92537816/144089248-e9f07c9b-dd7b-47a5-9137-426781c9be8b.png)
	Podem veure (de dalt a baix): la forma d'ona, el nivell de potència de la senyal, r1norm i rmaxnorm.		

	![image](https://user-images.githubusercontent.com/92537816/144092111-8d295d17-768c-4571-b6a4-9f58c14b8e68.png)
	Aquí podem veure la nostra detecció de pitch a sobre (amb les millors prestacions aconseguides), i la que fa wavesurfer a sota.

      - Use el detector de pitch implementado en el programa `wavesurfer` en una señal de prueba y compare
	    su resultado con el obtenido por la mejor versión de su propio sistema.  Inserte una gráfica
		ilustrativa del resultado de ambos detectores.
  
  * Optimice los parámetros de su sistema de detección de pitch e inserte una tabla con las tasas de error
    y el *score* TOTAL proporcionados por `pitch_evaluate` en la evaluación de la base de datos 
	`pitch_db/train`..
	
	Amb paràmetres optimitzats i sense pre ni postprocessat, el nostre sistema de detecció de Pitch té una puntuació de 90.86%
	
	![image](https://user-images.githubusercontent.com/92537816/144068625-ceec9a4d-694b-42c6-b885-ab5f0977d908.png)

   * Inserte una gráfica en la que se vea con claridad el resultado de su detector de pitch junto al del
     detector de Wavesurfer. Aunque puede usarse Wavesurfer para obtener la representación, se valorará
	 el uso de alternativas de mayor calidad (particularmente Python).
   	
	![image](https://user-images.githubusercontent.com/92537816/144068860-582dd19c-9bde-40c0-a47a-fec567f80941.png)

Ejercicios de ampliación
------------------------

- Usando la librería `docopt_cpp`, modifique el fichero `get_pitch.cpp` para incorporar los parámetros del
  detector a los argumentos de la línea de comandos.
  
  Esta técnica le resultará especialmente útil para optimizar los parámetros del detector. Recuerde que
  una parte importante de la evaluación recaerá en el resultado obtenido en la detección de pitch en la
  base de datos.

  * Inserte un *pantallazo* en el que se vea el mensaje de ayuda del programa y un ejemplo de utilización
    con los argumentos añadidos.
    
    Incorporem els paràmetres que gobernen la decisió voiced/unvoiced. 
    ![image](https://user-images.githubusercontent.com/92537816/144070289-31e17f80-f93d-4809-b29a-61e0d7051502.png)

- Implemente las técnicas que considere oportunas para optimizar las prestaciones del sistema de detección
  de pitch.

  Entre las posibles mejoras, puede escoger una o más de las siguientes:

  * Técnicas de preprocesado: filtrado paso bajo, *center clipping*, etc.
  
  Implementem center-clipping sense offset i filtre pas baix amb freqüència de tall de 2kHz
  ![image](https://user-images.githubusercontent.com/92537816/144077286-ff0149f9-229c-4414-a02c-7e960cb66855.png)
  ![image](https://user-images.githubusercontent.com/92537816/144077494-296f7ae6-f596-46a4-ba66-d87be46dc0e1.png)

  * Técnicas de postprocesado: filtro de mediana, *dynamic time warping*, etc.
  
  ![image](https://user-images.githubusercontent.com/92537816/144077631-d6b78042-e02b-4eb2-aa78-f34581624b61.png)

  * Optimización **demostrable** de los parámetros que gobiernan el detector, en concreto, de los que
    gobiernan la decisión sonoro/sordo.
  * Cualquier otra técnica que se le pueda ocurrir o encuentre en la literatura.

  Encontrará más información acerca de estas técnicas en las [Transparencias del Curso](https://atenea.upc.edu/pluginfile.php/2908770/mod_resource/content/3/2b_PS%20Techniques.pdf)
  y en [Spoken Language Processing](https://discovery.upc.edu/iii/encore/record/C__Rb1233593?lang=cat).
  También encontrará más información en los anexos del enunciado de esta práctica.

  Incluya, a continuación, una explicación de las técnicas incorporadas al detector. Se valorará la
  inclusión de gráficas, tablas, código o cualquier otra cosa que ayude a comprender el trabajo realizado.

  También se valorará la realización de un estudio de los parámetros involucrados. Por ejemplo, si se opta
  por implementar el filtro de mediana, se valorará el análisis de los resultados obtenidos en función de
  la longitud del filtro.
   

Evaluación *ciega* del detector
-------------------------------

Antes de realizar el *pull request* debe asegurarse de que su repositorio contiene los ficheros necesarios
para compilar los programas correctamente ejecutando `make release`.

Con los ejecutables construidos de esta manera, los profesores de la asignatura procederán a evaluar el
detector con la parte de test de la base de datos (desconocida para los alumnos). Una parte importante de
la nota de la práctica recaerá en el resultado de esta evaluación.
