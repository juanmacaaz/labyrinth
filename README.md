# labyrinth

https://mega.nz/file/MX4HgSzQ#4tWy1HaJpzSwsWQfjXnsTru5xZhE6iDQ6PJQbaTkBh4  

# Importante

En los ficheros .h  

- do nothing if: A makes no references at all to B
- do nothing if: The only reference to B is in a friend declaration
- forward declare B if: A contains a B pointer or reference: B* myb;
- forward declare B if: one or more functions has a B object/pointer/referenceas a parementer, or as a return type: B MyFunction(B myb);
- #include "b.h" if: B is a parent class of A
- #include "b.h" if: A contains a B object: B myb;

En los ficheros .cpp  

Hacer include de lo que se necesite
