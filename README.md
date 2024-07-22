load kardan file intorie

```c
struct Line
{
    Line *perv;
    char *ptr;
    Line *next;
}
```

vaghti cursor roye har line mire
ptr ro az `Line` migiram va tabdil mikonam be struct zir:

```c
struct Chars
{
    Chars *perv;
    char chr;
    Chars *next;
}
```

- darvaghe ye  vector string tabdil be ye chain struct mishe ke rahat mishe be aghab va jello va vasatesh date insert kard

dar akhar ke line change bokhore data az Chars dobare toye ptr hamon line replace mishe

ye chars be soorat static vojod dare ke hamishe avalin `Char` ro roye stack mide
intori rahat mishe line change dad
va toye har line data morede nazar ro rikht
ham to C rahat tare
