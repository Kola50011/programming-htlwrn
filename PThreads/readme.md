Implementieren Sie das Kundenschalter System der Post:

ein Wartenummern-Automat:
Gibt ein Ticket mit einer inkrementell wachsenden Nummer an den jeweils nächsten Kunden aus.
Kunde (Kunden-Thread):
Holt sich beim Automaten eine Nummer. Wartet danach bis seine Nummer mit dem freien Schalter auf dem Display erscheint. Erledigt dann am entsprechenden Schalter sein Geschäft.
ein Display:
gibt jeweils ein Signal, wenn ein Schalter frei wird und zeigt inkrementelle Nummer und freien Schalter an.
vier Schalter (Schalter-Thread):
drückt einen Knopf, welcher die Frei-Anzeige am Display auslöst. Nimmt Kunden entgegen und bearbeitet sein Geschäft.
Beachten Sie dabei:
die Schalter sind als jeweils eigenständige Threads zu programmieren
ein Schalter soll so implementiert werden, dass er nur einen Kunden auf einmal bedienen kann
eine Überprüfung der Nummer am Schalter muss nicht implementiert werden
vermeiden Sie jegliches Polling
schreiben Sie das Programm so, dass es beliebig viele Kunden verarbeiten kann. D.h. die Anzahl der Kunden-Threads soll nicht statisch deklariert sein
der main-Thread soll im Sekundentakt Kunden-Threads erstellen (verwenden Sie usleep für das Timing)
der Wartenunmmern- und der Displayautomat sollen jeweils in einer eigenen struct oder class definiert sein.
das ganze soll möglichst konkurrent laufen

Hinweise zur Synchronisierung:
Hier ein paar Funktionen für Locks und Synchronisierung (nur Namen, bitte selbst suchen):

pthread_mutex_init();
pthread_cond_init();
pthread_cond_init();
pthread_cond_wait();
pthread_cond_broadcast();
pthread_cond_signal();
pthread_mutex_lock();
pthread_mutex_unlock();
