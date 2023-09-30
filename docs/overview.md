## Project overview
For the moment we will configure the database manually and export the data into a spreadsheet.
Later, I plan on adding a Flutter app with realtime updates, charts and more.

``` mermaid
flowchart LR;
    A[(Supabase)];
    B(Logger 01) -- readings --> A;
    C(Logger 02) -- readings --> A;
    D(Logger ...) -- readings --> A;
    A -- CSV export --> E[[Excel]];
    F((You)) -- manual settings --> A;
```
