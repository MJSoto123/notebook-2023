// enumera todas las submasks en O(3^n)
for (int m=0; m<(1<<n); ++m)
    for (int s=m; s; s=(s-1)&m)
 ... s and m ... /// procesar submask