AUTORE

Giuseppe Bertolini

MODELLO SIR
Il progetto consiste nell’implementazione del modello SIR.
Il modello teorico, che descrive la diffusione di un’epidemia all’interno di una popolazione chiusa, si basa su tre equazioni differenziali, con lo scopo di calcolare lo stato di ogni singola persona, giorno per giorno, durante la pandemia.
Ogni persona ogni giorno può assumere solamente uno dei tre stati fra i seguenti:
•	Suscettibili (persone che si possono infettare)
•	Infetti (persone che sono infette e possono infettare)
•	Rimossi (persone guarite o morte, non possono più né infettarsi né infettare)
Lo stato di una persona può mutare in una sola direzione:
Suscettibile -> Infetto -> Rimosso/a
Le tre equazioni differenziali sulle quali si basa il modello sono le seguenti:

![dmodel](https://user-images.githubusercontent.com/97054738/148762843-2bb422d5-c618-4071-bb05-0a894dd3b30c.png)
 
Dove ds = 1 giorno.
β rappresenta una misura della probabilità di contagio per una persona suscettibile, dopo essere stato a contatto con un positivo.
λ rappresenta una misura della probabilità di guarigione o morte di un infetto.

DIVISIONE IN PARTI DEL PROGRAMMA
Il programma è diviso in due parti principali.

PARTE 1
La prima parte è composta da 4 file: main.cpp, pandemic.cpp, pandemic.test.cpp, pandemic.hpp.
La struct population_state è stata implementata all’interno del file pandemic.hpp. I membri interni sono degli int che rappresentano il numero di totale delle persone presenti, il numero di suscettibili, infetti e rimossi.
All’interno del file pandemic.hpp è stata implementata anche la definizione della classe pandemic e le dichiarazioni dei suoi metodi; la sua funzionalità è quella di calcolare il numero di suscettibili, infetti e rimossi giorno per giorno.
Nel file pandemic.cpp sono state implementate le definizioni di tutti i metodi.
La funzionalità del metodo values_checking è di controllare se tutti i valori inseriti in input sono validi e appartenenti ad un range accettabile dal programma.
La funzionalità del metodo population_check è di calcolare lo stato di ogni singola persona, giorno per giorno, basandosi sulle tre equazioni differenziali sulle quali si basa il modello SIR.
Unit test sono stati implementati nel file pandemic.test.cpp. 
I test sono stati implementati per controllare il corretto funzionamento del metodo values_checking.
I valori richiesti in input, dopo aver compilato con il seguente comando e aver eseguito il file eseguibile sono:

![command 1](https://user-images.githubusercontent.com/97054738/148762671-3957924d-b2f0-47f0-bd0b-1604ae95a8ef.png)
 
sono: β, λ, il numero di persone all’interno della popolazione, il numero di persone suscettibili, infetti, rimossi e la durata in giorni che l’utente vuole imporre.
La seguente immagine costituisce un esempio di input valido:

![input1](https://user-images.githubusercontent.com/97054738/148762919-0dbb3f28-56e3-4f0f-b79f-d006cea2ad91.png)
 
Ogni valore è strettamente richiesto.
Ogni valore inserito non appartenente ad un range accettabile dal programma porta ad un suo immediato arresto gestito tramite delle eccezioni implementate nei metodi della classe definita.
L’output è una tabella dove sono indicati i valori di suscettibili, infetti e rimossi giorno per giorno.
La seguente immagine costituisce un esempio di output:

![output pandemic](https://user-images.githubusercontent.com/97054738/148763092-70987656-001a-4323-888c-341ffa650a89.png)
 
Per compilare il file necessari all’esecuzione dei test l’utente può eseguire il seguente comando:

![command 12](https://user-images.githubusercontent.com/97054738/148762976-16e0868c-8aa7-4982-8e47-420234dc354c.png)
 
SECONDA PARTE
La seconda parte del programma è stata implementata per dare l’opportunità all’utente di visualizzare in output una rappresentazione grafica dell’evoluzione della pandemia.
Questa seconda parte è a sua volta divisa in due parti, tra le quali non c’è differenza nell’implementazione delle classi, metodi e free function che consentono di calcolare lo stato della singola persona (e della popolazione). 
La differenza è che la seconda parte consente all’utente di visualizzare graficamente i risultati mediante SFML (uso raccomandato).
PARTE 2 (NO SFML)
La seconda parte è composta da 4 file: graph_main.cpp graph_simulation.cpp, graph_simulation.test.cpp, graph_simulation.hpp.
Nel file graph_simulation.hpp è stata implementata la definizione della classe world, le dichiarazioni dei suoi membri e delle free function.
La funzionalità principale della classe world è quella di contenere le informazioni riguardanti lo stato dei singoli individui all’interno della popolazione.
Il membro interno m_grid della classe m_world è un vettore che rappresenta una griglia toroidale e ogni suo elemento rappresenta una persona.
La free function neighbours_infected ha la funzionalità di calcolare quante persone infette sono adiacenti ad una persona suscettibile.
La free function successive_stage ha la funzionalità di calcolare l’evoluzione dello stato delle persone durante la pandemia e dipende anche dai valori β e λ.
Durante l’implementazione della free function successive_stage è stata effettuata la scelta di aumentare il valore di persone infette adiacenti a un suscettibile, calcolato dalla funzione precedentemente descritta, in base alla variazione dei parametri β e λ.
Se β >= 0.5 una persona suscettibile ha alta probabilità di infettarsi a seguito di un contatto con una persona infetta. Se λ <= 0.5, una persona infetta ha una bassa probabilità di guarire. Ciò implica una maggiore permanenza nello stato di infezione. Questo è stato interpretato come un implicito aumento della probabilità di contagio, in quanto, durante il contatto con la persona suscettibile, la persona infetta permane costantemente nello stato di infezione, non guarendo in un tempo sufficientemente breve per non contagiare la persona suscettibile; in seguito a tale implicito aumento della probabilità di contagio, non potendo modificare il valore di beta durante l’esecuzione della funzione, è stato aumentato il valore degli adiacenti infetti ad un suscettibile. 
Nel caso in cui β >= 0.5 e λ > 0.5, i due valori, in base al ragionamento precedente, si bilanciano. La probabilità di infezione a seguito di un contatto è elevata, ma viene implicitamente ridotta dall’alto valore di λ, il quale si traduce in una veloce guarigione dell’infetto che può avvenire anche nel lasso di tempo, prolungato o meno, durante il quale la persona suscettibile e quella infetta sono a contatto, non concedendo il tempo necessario al virus di diffondersi.
Se i due valori sono nell’ultimo range indicato, il valore dei vicini infetti adiacenti non viene aumentato.
I due valori si bilanciano anche nel caso in cui β < 0.5 e λ <= 0.5 in quanto una bassa probabilità di contagio viene controbilanciata da una lunga permanenza nello stato di infezione della persona infetta. 
Se i due valori sono nell’ultimo range indicato, il valore dei vicini infetti adiacenti non viene aumentato.
I loop implementati nelle free function identificano una persona mediante un indice bidimensionale che viene convertito in un indice monodimensionale dai metodi person.
Nel file graph_simulation.test.cpp sono stati implementati gli unit test, atti a verificare il corretto funzionamento delle funzioni e dei metodi precedentemente descritti, mediante modifica dello stato delle persone nella griglia toroidale iniziale, composta da 9 individui e controllando la corretta evoluzione del loro stato.

I valori richiesti in input, dopo aver compilato con il seguente comando 

![command 2](https://user-images.githubusercontent.com/97054738/148764046-e2e31f31-8de6-4690-b8d0-ea337bd1cb0d.png)

e aver eseguito il file eseguibile, sono: i valori di β e λ, il numero di stadi della pandemia che si vogliono visualizzare e il numero di persone presenti ai lati della griglia, il cui elevamento al quadrato corrisponde al numero totale di persone (vedi costruttore in graph_simulation.cpp).
La seguente immagine costituisce un esempio di input valido:


![input2](https://user-images.githubusercontent.com/97054738/148764169-ee2bd2fd-89f0-412a-b811-dfbb6f0b7efe.png)

L’output è costituito dalla rappresentazione grafica dell’evoluzione della pandemia.
Il grafico si aggiorna dopo ogni secondo. Tale condizione è stata imposta mediante l’implementazione di 
std::this_thread::sleep_for(std::chrono::milliseconds(1000))
La seguente immagine costituisce un esempio di output:
  
![output simulation](https://user-images.githubusercontent.com/97054738/148764273-f5cb5bc0-4d9c-4f16-9f59-2c7dd3b4c6a5.png)

Nella precedente immagine il carattere vuoto rappresenta una persona suscettibile, ‘*’ rappresenta una persona infetta, ‘°’ rappresenta una persona rimossa.
Per compilare i file necessari all’esecuzione dei test, l’utente può inserire il comando:

![command 2 test](https://user-images.githubusercontent.com/97054738/148763007-3dfa03a1-9fd8-4ee5-91bd-1fe131c7f1b4.png)
 
PARTE 2 SFML
La parte relativa alla visualizzazione grafica mediante SFML è composta da 5 file: main_sfml.cpp, graph_simulation.cpp, display.cpp,
graph_simulation.hpp, display.hpp.
I files graph_simulation.cpp e graph_simulation.hpp sono implementati allo stesso modo dei file presenti nella parte precedente.
La definizione della classe display e le dichiarazioni dei suoi metodi sono state implementate all’interno del file display.hpp.
Le definizioni dei metodi print e show_message sono state implementate nel file display.cpp.
La funzionalità del metodo print è di disegnare, sulla finestra grafica, un quadrato verde per ogni persona rimossa e un quadrato rosso per ogni persona infetta. 
I quadrati bianchi rappresentano le persone suscettibili. Per la creazione di quadrati bianchi non è stata impostata nessuna sf::RectangleShape, in quanto, tali quadrati verranno a formarsi in seguito alla creazione dei quadrati verdi e rossi, dopo aver impostato su White il colore della finestra.
La funzionalità del metodo show_message è quella di mostrare sulla finestra un messaggio che suggerisce all’utente di premere un tasto qualsiasi per far iniziare la simulazione.
Il display è impostato sulle dimensioni 640 * 640, indipendentemente dal numero di persone presenti nella simulazione; tale numero influisce solamente sulla dimensione dei lati dei quadrati che rappresentano le persone.
i valori richiesti in input, dopo aver inserito i seguenti comandi
 
![cp32](https://user-images.githubusercontent.com/97054738/148763290-09b8b9a2-bf2b-4bbf-8a25-45e8010c0ab1.png)
![c3](https://user-images.githubusercontent.com/97054738/148763320-b833de83-ad88-4b7b-ad0a-6b88e455af8d.png)

e aver eseguito il file eseguibile, sono: il numero di persone presenti sul lato della griglia (il cui elevamento al quadrato rappresenta il numero di persone presenti), β e λ. 
La seguente immagine costituisce un esempio di input valido:

![input3](https://user-images.githubusercontent.com/97054738/148762924-928ba636-3ead-452a-975c-71f39b3b83fe.png)
 
     Si consiglia di impostare il primo valore in input su 40.
La seguente immagine costituisce un esempio di output:

![output sfml](https://user-images.githubusercontent.com/97054738/148763184-877f30ce-319b-443b-b529-baff6356dfda.png)
 











