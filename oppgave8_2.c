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
struct process *P; // Peker til array med prosessen


/*
1. Initialize current_time to 0, and array to track finished processes?
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

NOTE: I forgot to use the already defined global variable T....

*/

void simulate() {
   int current_time = 0;
   int is_finished[N];

   for (int i = 0; i < N; i++) {
      is_finished[i] = 0;
   }

   int completed_processes = 0;

   while (completed_processes < N) {
      int shortest_job = -1;

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
         if (P[shortest_job].start == 0) {
            P[shortest_job].start = current_time;
         }

         current_time += P[shortest_job].cpu;

         P[shortest_job].end = current_time;

         is_finished[shortest_job] = 1;
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

   //print statement goes here...
}

