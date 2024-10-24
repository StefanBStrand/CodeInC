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

// There has been a page fault at system-time (T, in this case 300). Page replacement has to be done.
void first_in_first_out()
{
   // Variable to save smallest load time - min_load_time
   // Loop through struct array  with processes
   int min_load_time = PF[0].load;
   int chosen_index = 0; // keep track of which process-index has the min load time.

   for (int i = 0; i < N; i++) {

      if (PF[i].load < min_load_time) {
         min_load_time = PF[i].load;
         chosen_index = i;
      }
   }
   printf("First-In-First_Out\n Page  %d  Loaded:  %d  Last ref: %d  R: %d  M: %d", PF[chosen_index].id,
      PF[chosen_index].load, PF[chosen_index].last, PF[chosen_index].R, PF[chosen_index].M);
   // if PF[i].load < min_load_time
   // min_load_time = PF[i].load
   // Print statements shows which process is chosen for page replacement.
}

//least_recently_used(): Simulering av page replacement med LRU
//
void least_recently_used()
{
  // Skal programmeres ferdig i oppgave 2
}

//second_chance(): Simulering av page replacement med Second Chance
//
void second_chance()
{
   // Skal programmeres ferdig i oppgave 3
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