#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur som lagrer data om en page frame

struct page_frame
{
   int id;   // Page-ID/-number
   int load; // Tidspunkt da pagen ble lagt inn i RAM
   int last; // Tidspunkt da pagen siste ble referert til
   int R;    // Referenced bit
   int M;    // Modified bit
};

// Globale variabler

int T = 300;           // Systemtid, settes til passende verdi
int N;                 // Antall prosesser
struct page_frame *PF; // Peker til array med page frames

// read_file(): Leser data for N page frames fra fil. Pages skal
// ligge sortert på ankomsttid. Alle data må være ikke-negative
// heltall. Alle tider oppgis i hele tidsenheter. Filformat:
//
//    N
//    id load last R M
//    id load last R M
//    id load last R M
//    ...
//
void read_file(char *filename)
{
   int i;
   FILE *p_file;

   // Åpner fil og sjekker for feil i åpning
   p_file = fopen(filename, "r");
   if (p_file == NULL)
   {
      printf("Feil ved åpning av filen \"%s\"\n", filename);
      exit(-1);
   }

   // Leser antall page frames
   fscanf(p_file, "%d", &N);

   // Oppretter array med plass til alle pages
   PF = (struct page_frame *) malloc(N * sizeof(struct page_frame));

   // Leser inn en og en page frame.
   for (i = 0; i < N; i++)
      fscanf(p_file, "%d %d %d %d %d", &PF[i].id, &PF[i].load,
	      &PF[i].last, &PF[i].R, &PF[i].M);
   fclose(p_file);
}

//first_in_first_out(): Simulering av page replacement med FIFO
//

void first_in_first_out()
{
   int min_load_time = PF[0].load;
   int chosen_index = 0;

   for (int i = 1; i < N; i++) {

      if (PF[i].load < min_load_time) {
         min_load_time = PF[i].load;
         chosen_index = i;
      }
   }
   printf("First-In-First_Out\n Page  %d  Loaded:  %d  Last ref: %d  R: %d  M: %d", PF[chosen_index].id,
      PF[chosen_index].load, PF[chosen_index].last, PF[chosen_index].R, PF[chosen_index].M);
}

//least_recently_used(): Simulering av page replacement med LRU

void least_recently_used()
{
   int oldest_last_ref_time = PF[0].last;
   int chosen_index = 0;

   for (int i = 1; i < N; i++) {
      if (PF[i].last < oldest_last_ref_time) {
         oldest_last_ref_time = PF[i].last;
         chosen_index = i;
      }
   }
   printf("Least Recently Used\n Page %d   Loaded:  %d  Last ref:   %d R:  %d  M:  %d", PF[chosen_index].id,
      PF[chosen_index].load, PF[chosen_index].last, PF[chosen_index].R, PF[chosen_index].M);
}

//second_chance(): Simulering av page replacement med Second Chance
//
void second_chance() {
   int min_load_time = PF[0].load;
   int chosen_index = -1;

   while (chosen_index == -1) {
      for (int i = 1; i < N; i++) {
         if (PF[i].load < min_load_time) {
            min_load_time = PF[i].load;
            if (PF[i].R == 0) {
               chosen_index = i;
            }
         }
            else if (PF[i].R == 1) {
               PF[i].R = 0;
               PF[i].load = T;
            }
   }
   }
   printf("Second Chance\n Page:  %d  Loaded:   %d   Last ref:   %d  R:   %d  M:  %d", PF[chosen_index].id,
         PF[chosen_index].load, PF[chosen_index].last, PF[chosen_index].R, PF[chosen_index].M);
}

// main(): Leser filnavn med page frame data, leser inndata fra fil og
// kjører tre ulike page replacement algoritmer
//
int main()
{
   char filename[100];

   // Leser filnavn fra bruker
   printf("File? ");
   scanf("%s", filename);

   // Leser inn prosessdataene
   read_file(filename);

   // Simulerer page replacement
   first_in_first_out();
   least_recently_used();
   second_chance();
}