# SupaSense
![Supabase](https://img.shields.io/badge/Supabase-181818?style=for-the-badge&logo=supabase&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![Espressif](https://img.shields.io/badge/espressif-E7352C?style=for-the-badge&logo=espressif&logoColor=white)

A DIY temperature and humidity monitor connected to Supabase.

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

## Docs
[Go to the docs -->](https://jakesmd.github.io/SupaSense/#/)
