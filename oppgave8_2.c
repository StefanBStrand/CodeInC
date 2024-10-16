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

/*
1. Initialize current_time to 0
2. Mark all processes as not finished (initialize is_finished[] to 0)
3. While there are unfinished processes:
   a. Find the process with the shortest CPU time that has already arrived
   b. If a process is found:
      - Set its start time to current_time (if it hasn’t started yet)
      - Add its CPU time to current_time
      - Set its end time
      - Mark it as finished
   c. If no process has arrived yet, move current_time to the next process’s arrival time
4. Print the results (start/end times) and calculate averages

*/

void simulate() {
   int current_time = 0; // variable to track the system time
   int is_finished[N];  // Boolean array to mark if each process is finished.

   // Initialize the array to mark all processes as unfinished. (Set them to 0)
   for (int i = 0; i < N; i++) {
      is_finished[i] = 0;
   }

   int completed_processes = 0; // to track how many processes are finished

   // Loop until all processes are finished:
   while (completed_processes < N) {
      int shortest_job = -1; // this variable will store the index of the process with the shortest job
      // - 1 is just a placeholder - meaning if in a check it is = -1, then we have not found a process with the
      // shortest job

      // Step 1: Find the shortest job that has arrived and is not finished:
      for (int i = 0; i < N; i++) {
         if (is_finished[i] == 0 && P[i].arrive <= current_time) { //job has arrived if .arrive is < current time.
            if (shortest_job == -1 || P[i].cpu < P[shortest_job].cpu) {
               shortest_job = i;
            }
         }
      }

      // Step 2: if a valid shortest job was found:
      if (shortest_job != -1) {
         //Setting start time for the process
         if (P[shortest_job].start == 0) {
            P[shortest_job].start = current_time;
         }

         //Update current time by adding the cpu time of the selected process
         current_time += P[shortest_job].cpu;

         // Set/update end time for selected process:
         P[shortest_job].end = current_time;

         // Mark the process as finished
         is_finished[shortest_job] = 1; //Updating the array trackin finished jobs, setting current job to 1 (true)
         completed_processes++;

      }

      // Step 3: if no process has arrived, jump to the next arrival time.
      // Find the smallest arrival time for processes that are not finished.
      else {
         int next_arrival = -1;
         for (int i = 0; i < N; i++) {
            if (is_finished[i] == 0) {
               if (next_arrival == -1 || P[i].arrive < P[next_arrival].arrive) {
                  next_arrival = i;
               }
            }
         }

         current_time = P[next_arrival].arrive;
      }

   }

   //print statement goes here.
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
