#include <stdio.h>
#include "src/huff.c"
typedef unsigned char byte;

int is_bit_i_set(byte c, int i)
{
    byte mask = 1 << i;
    return mask & c;
}

void GetFrequency(FILE * file, unsigned  int * frequencias){
    byte atual;
    while (fread(&atual, 1, 1, file) >= 1)
    {
        //printf("%d %c %u\n", atual, atual, atual);
        frequencias[atual]++;

        //frequencias[(byte)c]++;
    }

}

int Compress(){
    FILE  * file = fopen("C:\\Users\\Valdir Jr\\Desktop\\a.txt","rb");
   // File * saida =
    int unsigned frequencias[256]={0};
    GetFrequency(file, frequencias);
   // MakeTree(frequencias);
    int i;
  /*  for (i=0; i< 256; i++)
    {
        byte atual = i;
        if (frequencias[i]!=0){

            printf("[Freq: %d Caractere: %c ]", frequencias[i],atual);
            int j;
            for (j=7; j>=0;j--)
            {
                printf("%d",is_bit_i_set(atual,j)==0?0:1);
            }
            printf("\n");

        }

    }
*/
    Huff * arvore = MakeTree(frequencias);


   // s
   /* if (file) {
        while ((c = getc(file)) != EOF)
            printf("%c %d\n", (unsigned  char) c, c );
        fclose(file);
    }*/
    fclose(file);
    return 0;

}

int main()
{
    Compress();
    return 0;
}