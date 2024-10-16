#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur som lagrer data om en prosess
struct process
{
   int id;      // Prosess-ID
   int arrive;  // Tidspunkt da prosessen ble satt inn i kø
   int cpu;     // Total CPU-tid som prosessen krever
   int start;   // Tidspunkt da prosessen startet å kjøre
   int end;     // Tidspunkt da prosessen er ferdig
};

// Globale variabler
int T = 0;         // Systemtid, starter simulering ved tid lik 0
int N;             // Antall prosesser
struct process *P; // Peker til array med prosessene

// read_file(): Leser data for N prosesser fra fil. Prosessene skal
// ligge sortert på ankomsttid. Alle data må være ikke-negative
// heltall. Alle tider oppgis i hele tidsenheter. Filformat:
//
//    N
//    id arrive CPU
//    id arrive CPU
//    id arrive CPU
//    ...
//
void read_file(char *filename)
{
   int i, last_arrive = 0;
   FILE *p_file;

   // Åpner fil og sjekker for feil i åpning
   p_file = fopen(filename, "r");
   if (p_file == NULL)
   {
      printf("Feil ved åpning av filen \"%s\"\n", filename);
      exit(-1);
   }

   // Leser antall prosesser
   fscanf(p_file, "%d", &N);

   // Oppretter array med plass til alle prosessene
   P = (struct process *) malloc(N * sizeof(struct process));

   // Leser inn en og en prosess. Prosessene skal ligge sortert på
   // ankomsttid i filen, hvis ikke gis en feilmelding.
   for (i = 0; i < N; i++)
   {
      fscanf(p_file, "%d %d %d", &P[i].id, &P[i].arrive, &P[i].cpu);
      P[i].start = P[i].end = 0;

      if (P[i].arrive < last_arrive)
      {
	 printf("Feil i ankomsttider, prosess %d\n", P[i].id);
         exit(-1);
      }
      last_arrive = P[i].arrive;
   }
   fclose(p_file);
}

// simulate(): Simulering av batch scheduling. "Kjører" til alle
// prosessene er ferdige.
//

//*****************************************

  // Skal skrive ut rekkefølgen som prosessen vil kjøres i med FCSF
  // For hver prosess skal det skrives ut en linje med prosess_id, ankomsttid, CPU-tid, start-tidspunkt og slutt-tidspunkt.
  // Til slutt skal programmet beregne og skrive ut gjennomsnittlige verdier for turn-around og ventetid

// P.id, P.arrive and P.cpu

void simulate() {
   int current_time = 0;

   for (int i = 0; i < N; i++) {
      if (current_time < P[i].arrive) {
         P[i].start = P[i].arrive;
      }
      else {
         P[i].start = current_time;
      }

      current_time += P[i].start + P[i].cpu;
      P[i].end = current_time;
   }

   printf("P  Arrive  CPU  Start  End\n");

   for (int i = 0; i < N; i++) {
      printf("%d  %d  %d  %d  %d\n)",
         P[i].id, P[i].arrive, P[i].cpu, P[i].start, P[i].end);
   }

   double avg_turn_around_time;
   double avg_wait_time;

   for (int i = 0; i < N; i++) {
    avg_turn_around_time = (P[i].end + P[i].arrive);
    avg_wait_time = (P[i].start - P[i].arrive);
   }

   avg_turn_around_time /= N;
   avg_wait_time /= N;

   printf("Average turn-around time is: %.2f\n", avg_turn_around_time);
   printf("Average wait time is: %.2f\n", avg_wait_time);

   }



// main(): Leser filnavn med prosessdata, leser fil og kjører scheduling
//
int main()
{
   char filename[100];

   // Leser filnavn fra bruker
   printf("File? ");
   scanf("%s", filename);

   // Leser inn prosessdataene
   read_file(filename);

   // Simulerer batch-scheduling
   simulate();
}