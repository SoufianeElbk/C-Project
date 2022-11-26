#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int n,p,c,i,fact_n=1,fact_p=1,fact=1;
printf("Entrer n: ");
scanf("%d",&n);
do {
printf("Entrer p(inférieure ou égale à n): ");
scanf("%d",&p);}
while(p>n);
for(i=1;i<=n;i++)
fact_n=fact_n*i;
for(i=1;i<=p;i++)
fact_p=fact_p*i;
for(i=1;i<=n-p;i++)
fact=fact*i;
c = fact_n/(fact_p*fact);
printf("La combinaison de %d à partir de %d est %d",p,n,c);
}