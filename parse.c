#include <stdio.h>
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

int Fsize=50;
int inputs=6;
int proposition = 0;
int invalid = 0;
int negation = 0;
int binary = 0;
int brackets = 0;
int isFormula = 0;

char x[100];
char y[100];
int indx = 0;
int indy = 0;


int i;
int j;


/*put all your functions here.  You will need
1.
int parse(char *g) which returns 1 if a proposition, 2 if neg, 3 if binary, ow 0
Of course you will almost certainly need other functions.

Your program should read 6 formulas in a file called "input.txt" and output in the way indicated below to a file called "output.txt".
*/

int prop(char *g){
  if(*g == 'p' || *g == 'q' || *g == 'r'){
    if (strlen(g)==1)
      return 1;
    else
      return 0;
  }
  else
    return 0;
}
int bfunction(char *g){
  if (*g == 'v' || *g == '^' || *g == '>')
    return 1;
  else
    return 0;
}

int checkformula(char *g){
  if (prop(g)){
    x[indx] = *g;
  }

  else if(*g == '-' && bfunction(g+1)){
    return 0;
  }
  else if(*g == '-' && !bfunction(g+1)){
    g++;
  }
  if (*g == '('){
    brackets += 1;
    x[indx] = *g;
    indx++; g++;
    while (brackets != 0){
      if (*g == '('){
        brackets += 1;
      }
      if (*g == ')'){
        brackets -= 1;
      }
      x[indx] = *g;
      indx++; g++;

    }
    for (int i = 0; i < indx; i++){
      printf("%c", x[i]);
    }
    printf("\n");

    if (!bfunction(g)){
      return 0;
    }
    else{
      g++;
      if(*g == '-' && bfunction(g+1)){
        return 0;
      }
      else if (*g == '-' && !bfunction(g+1)){
        g++;
        while (*g != '\0'){

          y[indy] = *g;
          g++; indy++;
        }
        y[indy-1] = '\0';
        for (int j = 0; j < indy; j++){
          printf("%c", y[j]);
        }
        printf("\n");
      }

    }

  }



}


int parse(char *g){

  if (*g == '-'){ //negation
    printf("negation detected\n");
    negation = 1;
    g++;
  }

  if (prop(g) && strlen(g) == 1){ //proposition
    printf("proposition detected\n");
    if (negation){
      negation = 0;
      return 2;
    }
    else if (strlen(g) == 1 && prop(g))
      return 1;
  }

  if (*g == '('){
    g++;

    isFormula = checkformula(g);

    printf("in a bracket\n");

    if (isFormula && negation){
        negation = 0;
        return 2;
    }
    else if(isFormula){
      return 3;
    }


  else{
    negation = 0;
    return 0;
  }


  }
}

int main()
{ /*input 6 strings from "input.txt" */
  char *names[inputs];/*to store each of the input strings*/

  for (i=0;i<inputs;i++) names[i]=malloc(Fsize);/*create enough space*/



  FILE *fp, *fpout, *fopen();

  if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file input.txt\n");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file\n");exit(1);}/*ouputs to be sent to "output.txt"*/

  fscanf(fp,"%s %s %s %s %s %s",names[0],names[1], names[2], names[3],names[4],names[5]);/*read input strings from "input.txt"*/

  /*lets check your parser*/
  for(i=0;i<inputs;i++)
    {j=parse(names[i]);
      switch(j)
	{
	case(0):fprintf(fpout,"%s is not a formula\n", names[i]);break;
	case(1):fprintf(fpout,"%s is a proposition\n",names[i]);break;
	case(2):fprintf(fpout,"%s is a negation\n",names[i]);break;
	case(3):fprintf(fpout,"%s is a binary formula\n",names[i]);break;
	default:fprintf(fpout,"%s is not a formula\n",names[i]);break;
	}
    }


  fclose(fp);
  fclose(fpout);

  return(0);
}
